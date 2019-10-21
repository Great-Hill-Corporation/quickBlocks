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
#include "options.h"

//---------------------------------------------------------------------------------------------------
static const COption params[] = {
// BEG_CODE_OPTIONS
    COption("mode", "m", "enum[cmd*|api|both]", OPT_FLAG, "determine which set of tests to run"),
    COption("filter", "f", "enum[fast*|medi|slow|all]", OPT_FLAG, "determine how long it takes to run tests"),
    COption("clean", "c", "", OPT_SWITCH, "clean working folder before running tests"),
    COption("no_quit", "n", "", OPT_SWITCH, "do not quit testing on first error"),
    COption("report", "r", "", OPT_SWITCH, "display performance report to screen"),
    COption("", "", "", OPT_DESCRIPTION, "Retrieve a transaction's logs from the local cache or a running node."),
// END_CODE_OPTIONS
};
static const size_t nParams = sizeof(params) / sizeof(COption);

//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {

    if (!standardOptions(command))
        return false;

// BEG_CODE_LOCAL_INIT
    string_q mode = "";
// END_CODE_LOCAL_INIT
    string_q path;

    Init();
    explode(arguments, command, ' ');
    for (auto arg : arguments) {
        if (false) {
            // do nothing -- make auto code generation easier
// BEG_CODE_AUTO
        } else if (startsWith(arg, "-m:") || startsWith(arg, "--mode:")) {
            if (!confirmEnum("mode", mode, arg))
                return false;

        } else if (startsWith(arg, "-f:") || startsWith(arg, "--filter:")) {
            if (!confirmEnum("filter", filter, arg))
                return false;

        } else if (arg == "-c" || arg == "--clean") {
            clean = true;

        } else if (arg == "-n" || arg == "--no_quit") {
            no_quit = true;

        } else if (arg == "-r" || arg == "--report") {
            report = true;

        } else if (startsWith(arg, '-')) {  // do not collapse

            if (!builtInCmd(arg)) {
                return usage("Invalid option: " + arg);
            }

// END_CODE_AUTO
        } else {
            arg = trim(arg, '/');
            if (arg == "libs" || arg == "libs/") {
                static bool been_here = false;
                if (been_here)
                    break;
                been_here = true;
                tests.push_back("libs/utillib");
                tests.push_back("libs/etherlib");
                tests.push_back("libs/acctlib");

            } else if (arg == "dev_tools" || arg == "dev_tools/") {
                static bool been_here = false;
                if (been_here)
                    break;
                been_here = true;
                tests.push_back("dev_tools/makeClass");

            } else if (arg == "tools" || arg == "tools/") {
                static bool been_here = false;
                if (been_here)
                    break;
                been_here = true;
                tests.push_back("tools/ethQuote");
                tests.push_back("tools/ethslurp");
                tests.push_back("tools/getAccounts");
                tests.push_back("tools/getBlock");
                tests.push_back("tools/getBloom");
                tests.push_back("tools/getLogs");
                tests.push_back("tools/getReceipt");
                tests.push_back("tools/getState");
                tests.push_back("tools/getTokenInfo");
                tests.push_back("tools/getTrace");
                tests.push_back("tools/getTrans");
                tests.push_back("tools/grabABI");
                tests.push_back("tools/whenBlock");
                tests.push_back("tools/whereBlock");

            } else if (arg == "apps" || arg == "apps/") {
                static bool been_here = false;
                if (been_here)
                    break;
                been_here = true;
                tests.push_back("apps/acctExport");
                tests.push_back("apps/acctScrape");
                tests.push_back("apps/blockScrape");
                tests.push_back("apps/cacheMan");
                tests.push_back("apps/cacheStatus");
                tests.push_back("apps/chifra");

            } else {
                tests.push_back(arg);
            }
        }
    }

    modes = (mode == "both" ? BOTH : (mode == "api" ? API : CMD));

    if (filter.empty())
        filter = "fast";
    else if (filter == "all")
        filter = "";

    if (tests.empty()) {
        tests.push_back("libs/utillib");
        tests.push_back("libs/etherlib");
        tests.push_back("libs/acctlib");
        tests.push_back("dev_tools/makeClass");
        tests.push_back("tools/ethQuote");
        tests.push_back("tools/ethslurp");
        tests.push_back("tools/getAccounts");
        tests.push_back("tools/getBlock");
        tests.push_back("tools/getBloom");
        tests.push_back("tools/getLogs");
        tests.push_back("tools/getReceipt");
        tests.push_back("tools/getState");
        tests.push_back("tools/getTokenInfo");
        tests.push_back("tools/getTrace");
        tests.push_back("tools/getTrans");
        tests.push_back("tools/grabABI");
        tests.push_back("tools/whenBlock");
        tests.push_back("tools/whereBlock");
        tests.push_back("apps/acctExport");
        tests.push_back("apps/acctScrape");
        tests.push_back("apps/blockScrape");
        tests.push_back("apps/cacheMan");
        tests.push_back("apps/cacheStatus");
        tests.push_back("apps/chifra");
    }

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    registerOptions(nParams, params);
    optionOn(0);

// BEG_CODE_INIT
    filter = "";
    clean = false;
    no_quit = false;
    report = false;
// END_CODE_INIT

    minArgs = 0;
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void) {
    Init();
}

//---------------------------------------------------------------------------------------------------
COptions::~COptions(void) {
}

//---------------------------------------------------------------------------------------------------
bool COptions::cleanTest(const string_q& path, const string_q& testName) {
    if (!clean)
        return true;
    ostringstream os;
    os << "find ../../../working/" << path << "/" << testName << "/ -depth 1 -name \"get*.txt\" -exec rm '{}' ';' ; ";
    os << "find ../../../working/" << path << "/" << testName << "/ -depth 1 -name \"eth*.txt\" -exec rm '{}' ';' ; ";
    os << "find ../../../working/" << path << "/" << testName << "/ -depth 1 -name \"grab*.txt\" -exec rm '{}' ';' ; ";
    os << "find ../../../working/" << path << "/" << testName << "/ -depth 1 -name \"*Block*.txt\" -exec rm '{}' ';' ; ";
    system(os.str().c_str());
    return true;
}