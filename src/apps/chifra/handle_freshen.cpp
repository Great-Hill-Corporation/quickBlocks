/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "options.h"
#include "question.h"

//------------------------------------------------------------------------------------------------
bool freshen_internal(freshen_t mode, const CAddressArray& addrs, const string_q& tool_flags, const string_q& freshen_flags) {

    ENTER4("freshen_internal");
    nodeNotRequired();

    ostringstream base;
    base << "acctScrape " << tool_flags << " " << freshen_flags << " [ADDRS] ;";

    // Build groups of five addresses at a time
    size_t cnt = 0;
    string_q groupsOfFive;
    for (auto addr : addrs) {
        groupsOfFive += (addr + " ");
        if (!(++cnt % 5)) { // we don't want to do too many addrs at a time
            groupsOfFive += "|";
            cnt = 0;
        }
    }

    // Process them until we're done
    while (!groupsOfFive.empty()) {
        string_q thisGroup = nextTokenClear(groupsOfFive, '|');
        string_q cmd = substitute(base.str(), "[ADDRS]", thisGroup);
        LOG4("Calling " + cmd);
        if (isTestMode())
            cout << substitute(cmd, getCachePath(""), "$BLOCK_CACHE/") << endl;

        else {
            if (system(cmd.c_str())) { }  // Don't remove. Silences compiler warnings
            if (!groupsOfFive.empty())
                usleep(500000); // this sleep is here so that chifra remains responsive to Cntl+C. Do not remove
        }
    }
    EXIT_NOMSG4(true);
}
