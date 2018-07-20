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

//--------------------------------------------------------------
int main(int argc, const char *argv[]) {

    etherlib_init();

    // Parse command line, allowing for command files
    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    // while (!options.commandList.empty())
    {
        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;

        string_q cachePath = substitute(blockCachePath(""), "/blocks/", "/"+options.mode+"s/");
        if (isTestMode())
            cachePath = "--";
        cout << cYellow << "\nReport on " << options.mode << " locations:" << cOff;
        cout << (verbose ? "" : "\n  (cache folder: " + cachePath + ")") << "\n";

        string_q list = options.getBlockNumList();
        while (!list.empty()) {
            blknum_t bn = str_2_Uint(nextTokenClear(list, '|'));
            CFilename fileName(substitute(getBinaryFilename(bn), "/blocks/", "/"+options.mode+"s/"));
            bool exists = fileExists(fileName.getFullPath());

            string_q path = (verbose ? fileName.getFullPath() :
                                fileName.relativePath(substitute(blockCachePath(""),
                                                        "/blocks/", "/"+options.mode + "s/")));
            string_q vers = getVersionFromClient();
            if (isTestMode() && verbose)
                path = "--";
            if (isTestMode())
                vers = "--";
            string_q fallback = getEnvStr("FALLBACK");
            bool running_node = isNodeRunning();

            cout << "\t" << options.mode << " " << cTeal << padLeft(toStringU(bn), 9) << cOff << " ";
            if (exists)            cout << "found at cache:  " << cTeal << path << cOff << "\n";
            else if (running_node)      cout << "found at node:   " << vers << "\n";
            else if (!fallback.empty()) cout << "found at remote: " << fallback << "\n";
            else                        cout << "was not found\n";
        }
    }
    return 0;
}
