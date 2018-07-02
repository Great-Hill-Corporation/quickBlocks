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
#include "options.h"
#include "reporter.h"

//-----------------------------------------------------------------------------
int main(int argc, const char *argv[]) {

    etherlib_init();
    CTreeRoot::registerClass();
    CTreeNode::registerClass();
    CInfix::registerClass();
    CBranch::registerClass();
    CLeaf::registerClass();

    // Parse command line, allowing for command files
    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    if (options.commandList.empty())
        options.commandList = "null";
    while (!options.commandList.empty()) {
        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;

        if (options.all) {
            options.startBlock = 0;
            options.nBlocks = getLatestBlockFromClient();
        }

        CFilename fn("accts.bin");
        cout << getCWD() << " : " << fn.getFullPath() << "\n";
        bool exists = fileExists(fn.getFullPath());
        string_q msg = string_q(exists ? "Reading" : "Accumulating") + " accounts between blocks " +
                            asStringU(options.startBlock) + " and " +
                            asStringU(options.startBlock+options.nBlocks) + " (nBlocks: " +
                            asStringU(options.nBlocks) + ")";

        CReporter reporter;
        reporter.tree = new CTreeRoot;
        if (reporter.tree) {
            reporter.startTimer(msg);
            if (exists) {
                SFArchive archive(READING_ARCHIVE);
                if (archive.Lock(fn.getFullPath(), binaryReadOnly, LOCK_WAIT)) {
                    reporter.tree->Serialize(archive);
                    archive >> reporter.nBlocksVisited;
                    archive >> reporter.nTransVisited;
                    archive.Close();
                    if (isTestMode())
                        ::remove(fn.getFullPath().c_str());
                }
            } else {
                forEveryBlockOnDisc(buildTree, &reporter, options.startBlock, options.nBlocks);
                SFArchive archive(WRITING_ARCHIVE);
                if (archive.Lock(fn.getFullPath(), binaryWriteCreate, LOCK_WAIT)) {
                    reporter.tree->Serialize(archive);
                    archive << reporter.nBlocksVisited;
                    archive << reporter.nTransVisited;
                    archive.Close();
                }
            }
            reporter.stopTimer();

            //-----------------------------------------------
            reporter.startTimer("Displaying accounts...");
            forEveryAccount(reporter.tree, printTree, &reporter);
            reporter.stopTimer();
        }
        reporter.finalReport();
    }

    return 0;
}

//-----------------------------------------------------------------------
bool buildTree(CBlock& block, void *data) {

    CReporter *r = reinterpret_cast<CReporter*>(data);

    r->nBlocksVisited++;
    for (size_t i = 0 ; i < block.transactions.size() ; i++) {
        CTransaction *tr = (CTransaction*)&block.transactions[i];  // NOLINT
        if (string_q(tr->to).empty())
            tr->to = "0x0";
        r->nTransVisited++;
        r->tree->insert(tr->from, asStringU(block.blockNumber));
        r->tree->insert(tr->to, asStringU(block.blockNumber));
    }
    cerr << dateFromTimeStamp(block.timestamp) << " -- " << r->nBlocksVisited << ": " << r->nTransVisited << "\r";
    cerr.flush();
    return true;
}

//-----------------------------------------------------------------------------
bool printTree(const CTreeNode *node, void *data) {
    CReporter *r = reinterpret_cast<CReporter*>(data);

    r->nAccts++;

    // This simply accumulates the longest common prefixes
    if (r->getNext) {
        r->maxMatch2 = r->strs;
        r->getNext = false;
    }

    if (r->isMax()) {
        r->maxDepth  = countOf(r->strs, '-');
        r->getNext = true;
        r->maxMatch1 = r->strs;
    }
    if (r->type == T_LEAF) {
        if (r->counter < MAX_CNTS)
            r->counters[r->counter]++;
        if (r->counter > 5)
            r->gtFive++;
        if (r->counter > r->maxCnt) {
            r->maxCnt = r->counter;
            r->maxStr = r->strs;
        }
    }
    r->counter = 0;

    // print the report
    r->interumReport();

    return true;
}

//-----------------------------------------------------------------------------
void CReporter::interumReport(void) {
    string_q types[] = {
        cWhite   +     "T_TRTOP " + cOff,
        cRed     +     "T_TRLEAF" + cOff,
        bYellow  + "\n""T_BRANCH" + cOff,
        cGreen   + "\n""T_INFIX " + cOff,
    };

    cout << types[type] << " " << substitute(substitute(substitute(strs, "+", ""), "-", ""), "|0", "") << "\n";
}

