//whenDeployed
//isContract
//    if (when) {
//        if (!nodeHasBalances())
//            return usage("--whenDep option requires a full archive node. Quitting...");
//        for (auto item : items) {
//            if (!isContractAt(item))
//                return usage("Address " + item + " is not a smart contract, you may not use 
//--whenDep. Quitting...");
//        }
//    }




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
    COption("~address_list", "one or more addresses (0x...) from which to retrieve balances"),
    COption("~!block_list",  "an optional list of one or more blocks at which to report balances, defaults to 'latest'"),
    COption("-nozero",       "suppress the display of zero balance accounts"),
    COption("-changes",      "only report a balance when it changes from one block to the next"),
    COption("-mode:<val>",   "control which state to export. One of [none|all|balance|nonce|code|storage]"),
    COption("@fmt:<fmt>",    "export format (one of [none|json|txt|csv|api])"),
    COption("",              "Retrieve the balance (in wei) for one or more addresses at the given block(s).\n"),
};
static const size_t nParams = sizeof(params) / sizeof(COption);

extern const char *STR_DISPLAY;
//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {

    if (!standardOptions(command))
        return false;

    string_q format = STR_DISPLAY;
    Init();
    explode(arguments, command, ' ');
    for (auto arg : arguments) {
        if (arg == "-n" || arg == "--nozero") {
            exclude_zero = true;

        } else if (arg == "-c" || arg == "--changes") {
            changes = true;

        } else if (startsWith(arg, "-m:") || startsWith(arg, "--mode:")) {
            arg = substitute(substitute(arg, "-m:", ""), "--mode:", "");
            if (arg == "none") mode = ST_NONE;
            if (arg == "balance") mode = ethstate_t(mode|ST_BALANCE);
            if (arg == "nonce") mode = ethstate_t(mode|ST_NONCE);
            if (arg == "code") mode = ethstate_t(mode|ST_CODE);
            if (arg == "storage") mode = ethstate_t(mode|ST_STORAGE);
            if (arg == "all") mode = ethstate_t(mode|ST_ALL);

        } else if (arg == "-o" || arg == "--code") {
            mode = ethstate_t(mode|ST_CODE);

        } else if (arg == "-s" || arg == "--storage") {
            mode = ethstate_t(mode|ST_STORAGE);

        } else if (arg == "-a" || arg == "--all") {
            mode = ethstate_t(ST_BALANCE|ST_NONCE|ST_CODE|ST_STORAGE);

        } else if (startsWith(arg, '-')) {  // do not collapse
            if (!builtInCmd(arg)) {
                return usage("Invalid option: " + arg);
            }

        } else if (isHash(arg)) {
            string_q ret = blocks.parseBlockList(arg, newestBlock);
            if (endsWith(ret, "\n")) {
                cerr << "\n  " << ret << "\n";
                return false;
            } else if (!ret.empty()) {
                return usage(ret);
            }

        } else if (startsWith(arg, "0x")) {

            if (!isAddress(arg))
                return usage(arg + " does not appear to be a valid Ethereum address. Quitting...");
            address_t l = toLower(arg);
            CEthState record;
            record.address = l;
            items[l] = record;

        } else {

            string_q ret = blocks.parseBlockList(arg, newestBlock);
            if (endsWith(ret, "\n")) {
                cerr << "\n  " << ret << "\n";
                return false;
            } else if (!ret.empty()) {
                return usage(ret);
            }
        }
    }

    if (!blocks.hasBlocks())
        blocks.numList.push_back(newestBlock);  // use 'latest'

    if (!items.size())
        return usage("You must provide at least one Ethereum address.");

    string_q add;
    if (mode & ST_BALANCE) { add += "\t[{BALANCE}]";  UNHIDE_FIELD(CEthState, "balance"); }
    if (mode & ST_NONCE)   { add += "\t[{NONCE}]";    UNHIDE_FIELD(CEthState, "nonce");   }
    if (mode & ST_CODE)    { add += "\t[{CODE}]";     UNHIDE_FIELD(CEthState, "code");    }
    if (mode & ST_STORAGE) { add += "\t[{STORGAGE}]"; UNHIDE_FIELD(CEthState, "storage"); }
    format += add;

    switch (exportFmt) {
        case NONE1: break;
        case API1:
        case JSON1: format = ""; break;
        case TXT1:
        case CSV1:
            format = getGlobalConfig()->getConfigStr("display", "format", format.empty() ? STR_DISPLAY : format);
            manageFields("CAccountName:" + cleanFmt(format, exportFmt));
            break;
    }

    if ( expContext().asEther   ) format = substitute(format, "{BALANCE}", "{ETHER}");
    if ( expContext().asDollars ) format = substitute(format, "{BALANCE}", "{DOLLARS}");
    expContext().fmtMap["format"] = expContext().fmtMap["header"] = cleanFmt(format, exportFmt);

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    registerOptions(nParams, params);

    exclude_zero = false;
    changes = false;
    prevBal = 0;
    mode = ST_BALANCE;

    items.clear();
    blocks.Init();
    CHistoryOptions::Init();
    newestBlock = oldestBlock = getLastBlock_client();
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void) : CHistoryOptions(), item(NULL) {
    sorts[0] = GETRUNTIME_CLASS(CBlock);
    sorts[1] = GETRUNTIME_CLASS(CTransaction);
    sorts[2] = GETRUNTIME_CLASS(CReceipt);
    Init();
}

//--------------------------------------------------------------------------------
COptions::~COptions(void) {
}

//--------------------------------------------------------------------------------
string_q COptions::postProcess(const string_q& which, const string_q& str) const {
    if (which == "options") {
        return substitute(substitute(str, "address_list block_list", "<address> [address...] [block...]"), "-l|", "-l fn|");

    } else if (which == "notes" && (verbose || COptions::isReadme)) {
        string_q ret;
        ret += "[{addresses}] must start with '0x' and be forty two characters long.\n";
        ret += "[{block_list}] may be a space-separated list of values, a start-end range, a [{special}], or any combination.\n";
        ret += "This tool retrieves information from the local node or rpcProvider if configured (see documentation).\n";
        ret += "If the queried node does not store historical state, the results are undefined.\n";
        ret += "[{special}] blocks are detailed under " + cTeal + "[{whenBlock --list}]" + cOff + ".\n";
        ret += "[{balance}] is the default mode. To select a single mode use [{none}] first, followed by that mode.\n";
        ret += "You may specify multiple modes on a single line.\n";
        return ret;
    }
    return str;
}

//--------------------------------------------------------------------------------
const char *STR_DISPLAY = "[{ADDRESS}]\t[{BLOCKNUMBER}]";
