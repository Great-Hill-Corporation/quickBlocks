/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/
#include <ncurses.h>
#include <signal.h>
#include "etherlib.h"
#include "parselib.h"
#include "processing.h"
#include "debug.h"

// EXISTING_CODE
// EXISTING_CODE

//-----------------------------------------------------------------------
int main(int argc, const char *argv[]) {

    parselib_init(myQuitHandler);
    if (argc < 2)
        verbose = true;
    cerr << "Starting monitor...\r";
    cerr.flush();

    blknum_t clientHeight;
    uint64_t cacheHeight;
    getLatestBlocks(cacheHeight, clientHeight);

    // Parse command line, allowing for command files
    COptions visitor;
    if (!visitor.prepareArguments(argc, argv)) {
        etherlib_cleanup();
        return 0;
    }

    // while (!visitor.commandList.empty())
    {
        string_q command = nextTokenClear(visitor.commandList, '\n');
        if (!visitor.parseArguments(command)) {
            etherlib_cleanup();
            return 0;
        }

        uint64_t blockNum = visitor.blockStats.minWatchBlock-1;
        if (visitor.kBlock > blockNum)
            blockNum = visitor.kBlock;

        // Figure out which block to start on. Use earliest block from the watches. Note that
        // 'displayFromCache' may modify this to lastest visited block
        cout << "\r\n";
        if (visitor.kBlock) {
            // we're not starting at the beginning
            for (uint32_t i = 0 ; i < visitor.watches.size() ; i++) {
                visitor.watches.at(i).qbis.endBal = getNodeBal(visitor.watches.at(i).balanceHistory, visitor.watches.at(i).address, blockNum);
            }
        }

        if (visitor.debugger_on) {
            remove("./cache/debug");
            initscr();
            raw();
            keypad(stdscr, true);
            noecho();
            refresh();
            atexit(myOnExitHandler);
            signal(SIGWINCH, do_resize);
            cout << "Starting balances:\r\n";
            cout.flush();
        }

        if (visitor.json_on) {
            // show certain fields and hide others
            UNHIDE_FIELD(CTransaction, "cname");
            UNHIDE_FIELD(CTransaction, "articulated");
            UNHIDE_FIELD(CTransaction, "traces");
            UNHIDE_FIELD(CTransaction, "isError");
            HIDE_FIELD  (CTransaction, "gasUsed");

            UNHIDE_FIELD(CLogEntry,    "cname");
            UNHIDE_FIELD(CLogEntry,    "articulated");

            UNHIDE_FIELD(CReceipt,     "events");
            HIDE_FIELD  (CReceipt,     "logs");

            HIDE_FIELD  (CTrace,       "blockHash");
            HIDE_FIELD  (CTrace,       "blockNumber");
            HIDE_FIELD  (CTrace,       "transactionHash");
            HIDE_FIELD  (CTrace,       "transactionPosition");
        }

        if (!visitor.debugger_on && !verbose)
            verbose = 1;
        visitor.displayFromCache(blockNum);

        time_q now = Now();
        cerr << argv[0] << ": " << now.Format(FMT_JSON) << ": "
        << "{ "
        << cYellow << visitor.transStats.nDisplayed    << cOff << " displayed from cache; "
        << cYellow << visitor.transStats.nAccountedFor << cOff << " accounted for"
        << " }                        \r\n";

        if (visitor.debugger_on) {
            // If we were debugging and we did nothing, let the user know
            if ((visitor.transStats.nDisplayed + visitor.transStats.nAccountedFor) == 0) {
                cerr << "Nothing to do. Hit enter to quit...";
                cerr.flush();
                getchar();
            }
        }
    }

    if (visitor.debugger_on) {
        cout << "Press any key to quit.";
        cout.flush();
        getchar();
    }

    etherlib_cleanup();
    return 0;
}

//-----------------------------------------------------------------------
void myQuitHandler(int s) {
    quickQuitHandler(-1);
    remove("./cache/debug");
    if (!isendwin()) {
        endwin();
    }
    exit(1);
}

//-----------------------------------------------------------------------
void do_resize(int dummy) {
    // ignore
}

// EXISTING_CODE
// EXISTING_CODE
