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

//---------------------------------------------------------------
extern bool lookupDate(CBlock& block, const SFTime& date);
extern void unloadCache(void);

//---------------------------------------------------------------
int main(int argc, const char *argv[]) {

    etherlib_init();

    // Parse command line, allowing for command files
    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    while (!options.commandList.empty()) {
        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;

        for (size_t i = 0 ; i < options.requests.size() ; i++) {

            string_q value = options.requests[i];
            string_q mode = nextTokenClear(value, ':');

            string_q special;
            if (mode == "special") {
                mode = "block";
                special = nextTokenClear(value, '|');
                if (str_2_Uint(value) > getLatestBlockFromClient()) {
                    cout << "The block number you requested (";
                    cout << cTeal << special << ": " << value << cOff;
                    cout << ") is after the latest block (";
                    cout << cTeal << (isTestMode() ? "TESTING" : toStringU(getLatestBlockFromClient())) << cOff;
                    cout << "). Quitting...\n";
                    return 0;
                }
            }

            CBlock block;
            if (mode == "block") {
                queryBlock(block, value, false, false);

            } else if (mode == "date") {
                if (!fileExists(miniBlockCache)) {
                    cout << "Looking up blocks by date is not supported without a miniBlock ";
                    cout << "database, which is an advanced feature.\n";

                } else {
                    SFTime date = dateFromTimeStamp((timestamp_t)str_2_Uint(value));
                    bool found = lookupDate(block, date);
                    if (!found) {
                        unloadCache();
                        return 0;
                    }
                }
            }

            // special case for the zero block
            if (block.blockNumber == 0)
                block.timestamp = 1438269960;

            string_q def = (options.alone ?
                                    "[{BLOCKNUMBER}\\t][{DATE}]\\n" :
                                    "block #[{BLOCKNUMBER}][ : {TIMESTAMP}][ : {DATE}]\\n");
            string_q fmt = getGlobalConfig()->getDisplayStr(options.alone, def);
            if (verbose && !special.empty()) {
                string_q sp = "(" + special + ")";
                replace(fmt, "{BLOCKNUMBER}", "{BLOCKNUMBER} " + sp);
            }
            cout << block.Format(fmt);
        }
    }

    unloadCache();
    return 0;
}

//---------------------------------------------------------------
static CMiniBlock *blocks = NULL;
static uint64_t nBlocks = 0;
static uint64_t below = ULONG_MAX;
static uint64_t above = 0;
#define tD(a) dateFromTimeStamp(a)

//---------------------------------------------------------------
int findFunc(const void *v1, const void *v2) {
    const CMiniBlock *m1 = (const CMiniBlock *)v1;
    const CMiniBlock *m2 = (const CMiniBlock *)v2;
    below = (m1->timestamp > m2->timestamp ? m2->blockNumber : below);
    above = (m1->timestamp < m2->timestamp ? m2->blockNumber : above);
    return static_cast<int>(m1->timestamp - m2->timestamp);
}

//---------------------------------------------------------------
class CBlockFinder {
public:
    timestamp_t ts;
    uint64_t found;
    explicit CBlockFinder(timestamp_t t) : ts(t), found(0) { }
};

//---------------------------------------------------------------
bool lookCloser(CBlock& block, void *data) {

    CBlockFinder *bf = reinterpret_cast<CBlockFinder*>(data);
    if (block.timestamp <= bf->ts) {
        bf->found = block.blockNumber;
        return true;
    }
    return false;
}

//---------------------------------------------------------------
bool lookupDate(CBlock& block, const SFTime& date) {
    if (!blocks) {
        nBlocks = fileSize(miniBlockCache) / sizeof(CMiniBlock);
        blocks = new CMiniBlock[nBlocks];
        if (!blocks)
            return usage("Could not allocate memory for the blocks (size needed: " + toStringU(nBlocks) + ").\n");
        bzero(blocks, sizeof(CMiniBlock)*(nBlocks));
        if (verbose)
            cerr << "Allocated room for " << nBlocks << " miniBlocks.\n";

        // Next, we try to open the mini-block database (caller will cleanup)
        FILE *fpBlocks = fopen(miniBlockCache.c_str(), binaryReadOnly);
        if (!fpBlocks)
            return usage("Could not open the mini-block database: " + miniBlockCache + ".\n");

        // Read the entire mini-block database into memory in one chunk
        size_t nRead = fread(blocks, sizeof(CMiniBlock), nBlocks, fpBlocks);
        if (nRead != nBlocks)
            return usage("Error encountered reading mini-blocks database.\n Quitting...");
        if (verbose)
            cerr << "Read " << nRead << " miniBlocks into memory.\n";
    }

    CMiniBlock mini;
    mini.timestamp = toTimestamp(date);
    CMiniBlock *found = reinterpret_cast<CMiniBlock*>(bsearch(&mini, blocks, nBlocks, sizeof(CMiniBlock), findFunc));
    if (found) {
        queryBlock(block, toStringU(found->blockNumber), false, false);
        return true;
    }

    //  cout << mini.timestamp << " is somewhere between " << below << " and " << above << "\n";
    CBlockFinder finder(mini.timestamp);
    forEveryBlockOnDisc(lookCloser, &finder, below, above-below);
    queryBlock(block, toStringU(finder.found), false, false);
    return true;
}

//---------------------------------------------------------------
void unloadCache(void) {
    if (blocks) {
        delete [] blocks;
        blocks = NULL;
    }
}
