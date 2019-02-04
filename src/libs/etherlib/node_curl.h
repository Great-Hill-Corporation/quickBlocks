#pragma once
/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2018 Great Hill Corporation (http://greathill.com)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include "etherlib.h"

namespace qblocks {

    //-------------------------------------------------------------------------
    class CCurlContext {
    public:
        string_q          headerStr;
        string_q          baseURL;
        bool              nodeRequired;
        CURLCALLBACKFUNC  callBackFunc;
        CURLCALLBACKFUNC  curlNoteFunc;
        bool              earlyAbort;
        string_q          postData;
        string_q          result;
        string_q          provider;
        bool              is_error;
        size_t            theID;
        CURL              *curlHandle;
        struct curl_slist *headerPtr;

        CCurlContext(void);

        CURL    *getCurl    (void);
        void     releaseCurl(void);
        void     setPostData(const string_q& method, const string_q& params);
        string_q getCurlID  (void);
        void     clear      (void);
        CURLCALLBACKFUNC setCurlCallback(CURLCALLBACKFUNC func);
    };

    extern CCurlContext *getCurlContext  (void);

    extern void          nodeNotRequired (void);
    extern bool          isNodeRunning   (void);
    extern bool          nodeHasBalances (void);
    extern bool          nodeHasTraces   (void);
    extern string_q      setDataSource   (const string_q& newSrc);

    extern string_q      callRPC         (const string_q& method, const string_q& params, bool raw);
    extern bool          getObjectViaRPC (CBaseNode &node, const string_q& method, const string_q& params);

    extern size_t        writeCallback   (char *ptr, size_t size, size_t nmemb, void *userdata);
    extern size_t        errorCallback   (char *ptr, size_t size, size_t nmemb, void *userdata);
}  // namespace qblocks
