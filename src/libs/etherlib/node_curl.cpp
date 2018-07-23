/*-------------------------------------------------------------------------------------------
 * QuickBlocks - Decentralized, useful, and detailed data from Ethereum blockchains
 * Copyright (c) 2018 Great Hill Corporation (http://quickblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include "node.h"
#include "node_curl.h"

namespace qblocks {

    //-------------------------------------------------------------------------
    extern size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    extern size_t traceCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    extern size_t nullCallback(char *ptr, size_t size, size_t nmemb, void *userdata);

    //-------------------------------------------------------------------------
    CCurlContext::CCurlContext(void) {
        headers      = "Content-Type: application/json\n";
        baseURL      = "http://localhost:8545";
        callBackFunc = writeCallback;
        curlNoteFunc = NULL;
        theID        = 1;
        Clear();
    }

    //-------------------------------------------------------------------------
    string_q CCurlContext::getCurlID(void) {
        return uint_2_Str(isTestMode() ? 1 : theID++);
    }

    //-------------------------------------------------------------------------
// #define DEBUG_RPC
    void CCurlContext::setPostData(const string_q& method, const string_q& params) {
        Clear();
        postData += "{";
        postData +=  quote("jsonrpc") + ":"  + quote("2.0")  + ",";
        postData +=  quote("method")  + ":"  + quote(method) + ",";
        postData +=  quote("params")  + ":"  + params + ",";
        postData +=  quote("id")      + ":"  + quote(getCurlID());
        postData += "}";
#ifdef DEBUG_RPC
        cerr << postData << "\n";
        cerr.flush();
#endif
        curl_easy_setopt(getCurl(), CURLOPT_POSTFIELDS,    postData.c_str());
        curl_easy_setopt(getCurl(), CURLOPT_POSTFIELDSIZE, postData.length());
        curl_easy_setopt(getCurl(), CURLOPT_WRITEDATA,     this);
        curl_easy_setopt(getCurl(), CURLOPT_WRITEFUNCTION, callBackFunc);
    }

    //-------------------------------------------------------------------------
    void CCurlContext::Clear(void) {
        earlyAbort   = false;
        is_error     = false;
        postData     = "";
        result       = "";
//      source       = "binary";
    }

    //-------------------------------------------------------------------------
    static CCurlContext theCurlContext;

    //-------------------------------------------------------------------------
    CCurlContext *getCurlContext(void) {
        return &theCurlContext;
    }

    //--------------------------------------------------------------------------
    CURLCALLBACKFUNC CCurlContext::setCurlCallback(CURLCALLBACKFUNC func) {
        CURLCALLBACKFUNC prev = getCurlContext()->callBackFunc;
        getCurlContext()->callBackFunc = func;
        return prev;
    }

    //-------------------------------------------------------------------------
    CURL *getCurl(bool cleanup) {
        static CURL *curl = NULL;
        static struct curl_slist *headers = NULL;
        if (!curl && !cleanup) {
            curl = curl_easy_init();
            if (!curl) {
                fprintf(stderr, "Curl failed to initialize. Quitting...\n");
                exit(0);
            }

            string_q head = getCurlContext()->headers;
            while (!head.empty()) {
                string_q next = nextTokenClear(head, '\n');
                headers = curl_slist_append(headers, (char*)next.c_str());  // NOLINT
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            if (getCurlContext()->provider == "remote") {
                curl_easy_setopt(curl, CURLOPT_URL, "https://pmainnet.infura.io/");

            } else if (getCurlContext()->provider == "ropsten") {
                curl_easy_setopt(curl, CURLOPT_URL, "https://testnet.infura.io/");

            } else {
                curl_easy_setopt(curl, CURLOPT_URL, getCurlContext()->baseURL.c_str());
            }

        } else if (cleanup) {

            if (headers)
                curl_slist_free_all(headers);
            if (curl)
                curl_easy_cleanup(curl);
            headers = NULL;
            curl = NULL;
            return NULL;
        }

        return curl;
    }

    //-------------------------------------------------------------------------
    bool isNodeRunning(void) {
        CURLCALLBACKFUNC prev = getCurlContext()->setCurlCallback(nullCallback);
        getCurlContext()->setPostData("web3_clientVersion", "[]");
        CURLcode res = curl_easy_perform(getCurl());
        getCurlContext()->setCurlCallback(prev);
        return (res == CURLE_OK);
    }

    //-------------------------------------------------------------------------
    string_q callRPC(const string_q& method, const string_q& params, bool raw) {

        // getCurlContext()->callBackFunc = writeCallback;
        getCurlContext()->setPostData(method, params);

        CURLcode res = curl_easy_perform(getCurl());
        if (res != CURLE_OK && !getCurlContext()->earlyAbort) {
            string_q currentSource = getCurlContext()->provider;
            string_q fallBack = getEnvStr("FALLBACK");
            if (!fallBack.empty() && currentSource != fallBack) {
                if (fallBack != "infura") {
                    cerr << cYellow;
                    cerr << "\n";
                    cerr << "\tWarning: " << cOff << "Only the 'infura' fallback is supported.\n";
                    cerr << "\tIt is impossible for QuickBlocks to proceed. Quitting...\n";
                    cerr << "\n";
                    exit(0);
                }

                if (fallBack == "infura" && startsWith(method, "trace_")) {
                    cerr << cYellow;
                    cerr << "\n";
                    cerr << "\tWarning: " << cOff << "A trace request was made to the fallback\n";
                    cerr << "\tnode. " << fallBack << " does not support tracing. It ";
                    cerr << "is impossible\n\tfor QuickBlocks to proceed. Quitting...\n";
                    cerr << "\n";
                    exit(0);
                }
                getCurlContext()->theID--;
                getCurlContext()->provider = "remote";
                // reset curl
                getCurl(true); getCurl();
                // since we failed, we leave the new provider, otherwise we would have to save
                // the results and reset it here.
                return callRPC(method, params, raw);
            }
            cerr << cYellow;
            cerr << "\n";
            cerr << "\tWarning: " << cOff << "The request to the Ethereum node ";
            cerr << "resulted in\n\tfollowing error message: ";
            cerr << bTeal << curl_easy_strerror(res) << cOff << ".\n";
            cerr << "\tIt is impossible for QuickBlocks to proceed. Quitting...\n";
            cerr << "\n";
            exit(0);
        }

        if (getCurlContext()->result.empty()) {
            cerr << cYellow;
            cerr << "\n";
            cerr << "\tWarning:" << cOff << "The Ethereum node  resulted in an empty\n";
            cerr << "\tresponse. It is impossible forQuickBlocks to proceed. Quitting...\n";
            cerr << "\n";
            exit(0);
        } else if (contains(getCurlContext()->result, "error")) {
            if (verbose > 1) {
                cerr << getCurlContext()->result;
                cerr << getCurlContext()->postData << "\n";
            }
        }

#ifdef DEBUG_RPC
        //    cout << "\n" << string_q(80, '-') << "\n";
        //    cout << thePost << "\n";
        cout << string_q(60, '=') << "\n";
        cout << "received: " << getCurlContext()->result << "\n";
        cout.flush();
#endif

        if (raw)
            return getCurlContext()->result;
        CRPCResult generic;
        char *p = cleanUpJson((char*)getCurlContext()->result.c_str());  // NOLINT
        generic.parseJson(p);
        return generic.result;
    }

    //-------------------------------------------------------------------------
    bool getObjectViaRPC(CBaseNode &node, const string_q& method, const string_q& params) {
        string_q ret = callRPC(method, params, false);
        node.parseJson((char *)ret.c_str());  // NOLINT
        return true;
    }

    //-------------------------------------------------------------------------
    size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
        string_q part;
        part.reserve(size*nmemb+1);
        char *s = (char*)part.c_str();  // NOLINT
        strncpy(s, ptr, size * nmemb);
        s[size*nmemb]='\0';
        ASSERT(userdata);
        CCurlContext *data = (CCurlContext*)userdata;  // NOLINT
        data->result += s;

        if (data && data->curlNoteFunc)
            if (!(*data->curlNoteFunc)(ptr, size, nmemb, userdata))  // returns zero if it wants us to stop
                return 0;

        // Note: we used to skip over any trace that contained a long string
        // of characters with '5b5b5b5b5b5b5b5b5b5b5b5b' which started around
        // block 38004005 and ran for about 5000 blocks. We no longer do that
        // here, but it requires correcting blooms and cached blocks since
        // they would be skipped.
        // TODO(tjayrush): has issue #124 on QuickBlocks private been fixed?
#if 0
        if (strstr(s, "5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b") != NULL) {
            // This is the hack trace (there are many), so skip it
            cerr << "Curl response contains '5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b'. Aborting.\n";
            cerr.flush();
            getCurlContext()->earlyAbort = true;
            return 0;
        }
#endif

//        if (shouldQuit()) {
//            getCurlContext()->earlyAbort = true;
//            return 0;
//        }

        return size * nmemb;
    }

    //-------------------------------------------------------------------------
    size_t traceCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
        // Curl does not close the string, so we have to
        ptr[size*nmemb-1] = '\0';
        CCurlContext *data = (CCurlContext*)userdata;  // NOLINT
        data->result = "ok";
        if (strstr(ptr, "erro") != NULL) {
            data->result = "error";
            getCurlContext()->is_error = true;
            getCurlContext()->earlyAbort = true;
            return 0;
        }

//        if (shouldQuit()) {
//            getCurlContext()->earlyAbort = true;
//            return 0;
//        }

        return size * nmemb;
    }

    //-------------------------------------------------------------------------
    size_t nullCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
        return size * nmemb;
    }
}  // namespace qblocks
