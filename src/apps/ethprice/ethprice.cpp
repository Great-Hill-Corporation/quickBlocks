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
#include "etherlib.h"
#include "options.h"
#include "sftime.h"

//-----------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {

    etherlib_init();

    // Parse command line, allowing for command files
    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    while (!options.commandList.empty()) {
        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;

        string_q message;

        CPriceQuoteArray quotes;
        if (loadPriceData(options.source, quotes, options.freshen, message) && quotes.size()) {

            string_q def = (verbose ? "" : "{ \"date\": \"[{DATE}]\", \"price\": \"[{CLOSE}]\" }");
            string_q fmtStr = getGlobalConfig()->getDisplayStr(!verbose, def, "");
            bool isJson = ((startsWith(fmtStr, "{") && endsWith(fmtStr, "}")) || fmtStr.empty());
            if (options.at) {
                cout << quotes[indexFromTimeStamp(quotes, options.at)].Format(fmtStr);

            } else {
                if (verbose > 1)
                    UNHIDE_FIELD(CPriceQuote, "schema");
                if (isJson)
                    cout << "[\n";
                size_t step = (options.freq / 5);
                bool done = false;
                for (size_t i = 0 ; i < quotes.size() && !done ; i = i + step) {
                    timestamp_t ts = str_2_Ts(quotes[i].Format("[{TIMESTAMP}]"));
                    if (i > 0) {
                        if (isJson)
                            cout << ",";
                        cout << "\n";
                    }
//                    if (i != indexFromTimeStamp(quotes, ts)) {
//                        cerr << cRed << "mismatch between 'i' ("
//                        << i << ") and 'index' ("
//                        << indexFromTimeStamp(quotes, ts) << "). Quitting.\n" << cOff;
//                        return 0;
//                    }
                    cout << quotes[i].Format(fmtStr);
                    if (isTestMode() && ts_2_Date(ts) >= SFTime(2017, 8, 15, 0, 0, 0))
                        done = true;
                }
                if (isJson)
                    cout << "\n]";
                cout << "\n";
            }

        } else {
            return usage(message);

        }
    }
    return 0;
}
