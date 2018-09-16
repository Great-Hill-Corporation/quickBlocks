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
#include <string>
#include "ethslurp.h"
#include "options.h"

extern void findInternalTxIndex(CTransaction& trans);
//--------------------------------------------------------------------------------
int main(int argc, const char * argv[]) {

    etherlib_init();

    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    CAccount theAccount; //CSlurperApp slurper;
    while (!options.commandList.empty()) {

        string_q command = nextTokenClear(options.commandList, '\n');
        cerr << "Processing: " << command << "\n";
        if (!options.parseArguments(command))
            return 0;

        string_q message;
        if (!Slurp(theAccount, options, message)) {

            if (startsWith(message, "No transactions")) {
                cerr << cRed << "\t" << message << cOff << "\n";
                return 0;
            } else {
                return usage(message);
            }
        }

        if (!options.silent) {
            for (size_t i = 0 ; i < theAccount.transactions.size() ; i++) {
                CTransaction *trans = &theAccount.transactions[i];
                trans->m_showing = isInRange(trans->blockNumber, options.blocks.start, options.blocks.stop);
            }
            theAccount.displayString = options.displayString;
            theAccount.Format(cout, options.getFormatString("file", false));
        }
    }

    return 0;
}

//--------------------------------------------------------------------------------
inline void screenMsg(const string_q& msg) {
    if (isTestMode())
        return;
    cerr << "\t" << padRight(msg, 85) << "\r";
    cerr.flush();
}

//--------------------------------------------------------------------------------
bool Slurp(CAccount& theAccount, COptions& options, string_q& message) {

    theAccount.transactions.clear();
    theAccount = CAccount();
    theAccount.addr = options.addrs[0];
    cerr << "\t" << "Slurping " << theAccount.addr << "\n";

    string_q cacheFilename = blockCachePath("slurps/" + theAccount.addr + (options.type == "int" ? ".int" : "") + ".bin");
    CArchive inArchive(READING_ARCHIVE);
    if (fileExists(cacheFilename)) {
        if (!inArchive.Lock(cacheFilename, binaryReadOnly, LOCK_NOWAIT)) {
            message = "Could not open file: '" + cacheFilename + "'\n";
            return options.fromFile;
        }
        theAccount.Serialize(inArchive);
        inArchive.Close();
    }

    // Keep reading until we get less than a full page
    bool done = false;
    while (!done) {
        string_q url = string_q("https://api.etherscan.io/api?module=account&sort=asc") +
                "&action="  + (options.type == "int" ? "txlistinternal" : "txlist") +
                "&address=" + theAccount.addr +
                "&page="    + uint_2_Str(theAccount.latestPage) +
                "&offset="  + uint_2_Str(5000) +
                "&apikey="  + options.api.getKey();

        string_q responseStr = urlToString(url);
        CESResult response;
        response.parseJson3(responseStr);
        if (response.message != "OK")
            return usage("Error retrieving results: " + response.message + ". Quitting...") || options.fromFile;

        uint64_t nRecords = countOf(response.result, '}');
        screenMsg("Downloaded " + uint_2_Str(nRecords) + " records from EtherScan.");

        // pre allocate the array (probably wrong input here--reserve takes max needed size, not addition size needed)
        theAccount.transactions.reserve(theAccount.transactions.size() + nRecords);

        uint64_t nAdded = 0;
        CTransaction trans;
        while (trans.parseJson3(response.result)) {
            if (theAccount.isNewTrans(trans)) {
                if (options.type == "int")
                    findInternalTxIndex(trans);
                theAccount.transactions.push_back(trans);
                screenMsg("Adding records from block " + uint_2_Str(trans.blockNumber) + "...");
                trans = CTransaction();  // reset
                nAdded++;
            } else {
                screenMsg("Scanning " + uint_2_Str(trans.blockNumber) + "." + uint_2_Str(trans.transactionIndex));
            }
        }

        // We're done if we got a page of less than 5,000 records, otherwise we will process the next page
        done = (nRecords < 5000);
        if (!done)
            theAccount.latestPage++;

        if (nAdded) {
            screenMsg("Appending " + uint_2_Str(nAdded) + " new records, total " + uint_2_Str(theAccount.transactions.size()));
            CArchive outArchive(WRITING_ARCHIVE);
            if (outArchive.Lock(cacheFilename, binaryWriteCreate, LOCK_CREATE)) {
                lockSection(true);
                theAccount.Serialize(outArchive);
                outArchive.Close();
                lockSection(false);

            } else {
                message = "\tCould not open file: '" + cacheFilename + "'                 \n";
                return false;
            }
        }
        if (shouldQuit())
            return options.fromFile;
    }
    return (options.fromFile || theAccount.transactions.size() > 0);
}

//---------------------------------------------------------------------------
void findInternalTxIndex(CTransaction& trans) {
    CTransaction thing;
    getTransaction(thing, trans.hash);
    trans.transactionIndex = thing.transactionIndex;
    trans.isInternal = true;
}
