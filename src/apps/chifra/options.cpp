/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "options.h"
#include "question.h"

//---------------------------------------------------------------------------------------------------
static const COption params[] = {
    COption("~command", "one of [ seed | scrape | daemon | list | export | stats | ls | rm | names | config ]"),
    COption("",         "Create a TrueBlocks monitor configuration.\n"),
};
static const size_t nParams = sizeof(params) / sizeof(COption);

extern bool visitIndexFiles(const string_q& path, void *data);
//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {

    if (!standardOptions(command))
        return false;

    Init();
    explode(arguments, command, ' ');
    for (auto arg : arguments) {

        if (mode.empty() && startsWith(arg, '-')) {

            if (!builtInCmd(arg)) {
                return usage("Invalid option: " + arg);
            }

        } else {

            if (contains(params[0].description, " " + arg + " ")) {
                if (!mode.empty())
                    return usage("Please specify " + params[0].description + ". Quitting...");
                mode = arg;
                if (mode == "stats") {
                    mode = "ls";
                    stats = true;
                }

            } else if (isAddress(arg)) {
                addrs.push_back(toLower(arg));

            } else {
                if (arg == "--useBlooms")
                    freshen_flags = (arg + " ");
                else
                    tool_flags += (arg + " ");

            }
        }
    }

    if (mode.empty())
        return usage("Please specify " + params[0].description + ". Quitting...");
    establishFolder(getMonitorPath("", FM_PRODUCTION));
    establishFolder(getMonitorPath("", FM_STAGING));

//    if (verbose) {
//        tool_flags += " --verbose";
//        freshen_flags += " --verbose";
//    }

    tool_flags = trim(tool_flags, ' ');
    freshen_flags = trim(freshen_flags, ' ');

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    registerOptions(nParams, params);

    addrs.clear();
    tool_flags    = "";
    freshen_flags = "";
    mode          = "";
    stats         = false;
    minArgs       = 0;
    api_mode      = !getEnvStr("API_MODE").empty();
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void) : txCache(WRITING_ARCHIVE) {
    Init();
}

//--------------------------------------------------------------------------------
COptions::~COptions(void) {
}
