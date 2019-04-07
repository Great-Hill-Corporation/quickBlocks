/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "options.h"
#include "question.h"

//------------------------------------------------------------------------------------------------
bool COptions::handle_freshen(void) {

    // freshen mode technically does not require a running node since it only reads the index
    nodeNotRequired();

    if (addrs.empty())
        return usage("This function requires an address. Quitting...");

    if (!freshen_internal(monitorsPath, addrs, tool_flags, freshen_flags))
        return false;

    return true;
}

//------------------------------------------------------------------------------------------------
bool freshen_internal(const string_q& path, const address_t& addr, const string_q& tool_flags, const string_q& freshen_flags) {

    // freshen mode technically does not require a running node since it only reads the index
    nodeNotRequired();

    ostringstream os;
    os << "cd " << path << " ; ";
    os << "acctScrape " << tool_flags << " " << freshen_flags << " " << addr << " ; ";

    if (isTestMode())
        cout << substitute(os.str(), getCachePath(""), "$BLOCK_CACHE/") << endl;
    else {
        if (system(os.str().c_str())) { }  // Don't remove. Silences compiler warnings
        usleep(500000); // this sleep is here so that chifra remains responsive to Cntl+C. Do not remove
    }

    return true;
}

//------------------------------------------------------------------------------------------------
bool freshen_internal(const string_q& path, const CAddressArray& addrs, const string_q& tool_flags, const string_q& freshen_flags) {

    // freshen mode technically does not require a running node since it only reads the index
    nodeNotRequired();

    ostringstream os;
    os << "cd " << path << " ; ";
    os << "acctScrape " << tool_flags << " " << freshen_flags << " ";
    for (auto addr : addrs)
        os << addr << " ";
    os << " ; ";

    if (isTestMode())
        cout << substitute(os.str(), getCachePath(""), "$BLOCK_CACHE/") << endl;
    else {
        if (system(os.str().c_str())) { }  // Don't remove. Silences compiler warnings
        usleep(500000); // this sleep is here so that chifra remains responsive to Cntl+C. Do not remove
    }

    return true;
}
