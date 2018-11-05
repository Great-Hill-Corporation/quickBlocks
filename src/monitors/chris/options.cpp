/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/
#include "main.h"

//---------------------------------------------------------------------------------------------------
static COption params[] = {
    COption("-parse",        "display parsed input data"),
    COption("-lo(g)s",       "display smart contract lo(g)s or events"),
    COption("-trace",        "display smart contract internal traces"),
    COption("-accounting",   "display credits and debits per account and reconcile at each block"),
#ifdef DEBUGGER_ON
    COption("-no_check",     "do not do balance check at each block"),
    COption("-debug",        "enter debug mode (pause after each transaction)"),
#endif
    COption("-single",       "if debugging is enable, single step through transactions"),
    COption("-export",       "export the transactions to export file"),
    COption("-json",         "ignore export format and export as json"),
    COption("-bals",         "if a balance does not reconcile, export a message to a file"),
    COption("-list",         "display list of monitored accounts"),
    COption("-kBlock:<num>", "start processing at block :k"),
    COption("-offset:<num>", "offset to kBlock"),
    COption("",              "Index transactions for a given Ethereum address (or series of addresses).\r\n"),
};
static size_t nParams = sizeof(params) / sizeof(COption);

extern const char* defTransFmt;
extern const char* defTraceFmt;
extern string_q cleanFmt(const string_q& str);
//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {

    if (!standardOptions(command))
        return false;

    Init();
    while (!command.empty()) {
        string_q arg = nextTokenClear(command, ' ');
        if (contains(arg, "-k:") || contains(arg, "--kBlock:")) {

            arg = substitute(substitute(arg, "-k:", ""), "--kBlock:", "");
            if (!isNumeral(arg)) {
                cerr << substitute(usageStr("You must specify a block number (" + arg + ")"), "\n", "\r\n");
                return false;
            }
            kBlock = str_2_Uint(arg);

        } else if (contains(arg, "-o:") || contains(arg, "--offset:")) {

            arg = substitute(substitute(arg, "-o:", ""), "--offset:", "");
            if (!isNumeral(arg)) {
                cerr << substitute(usageStr("You must specify a number for offset (" + arg + ")"), "\n", "\r\n");
                return false;
            }
            offset = str_2_Uint(arg);

        } else if (arg == "--single" || arg == "--single_step") {
            single_on = true;

        } else if (arg == "-n" || arg == "--no_check") {
            no_check = true;

        } else if (arg == "-a" || arg == "--accounting") {
            accounting_on = true;

        } else if (arg == "-g" || arg == "--logs") {
            logs_on = true;

        } else if (arg == "-t" || arg == "--trace") {
            trace_on = true;

        } else if (arg == "-p" || arg == "--parse") {
            parse_on = true;

        } else if (arg == "-b" || arg == "--bals") {
            report_bals = true;

        } else if (arg == "-d" || arg == "--debug") {
            debugger_on = true;

        } else if (arg == "-e" || arg == "--export") {
            export_on = true;

        } else if (arg == "-j" || arg == "--json") {
            colorsOff();
            json_on = true;

        } else if (arg == "-l" || arg == "--list") {
            colorsOff();
            CToml toml("./config.toml");
            COptions visitor;
            if (!visitor.loadWatches(toml))
                return false;

            if (visitor.watches.size() > 2)
                cout << "[";

            for (uint32_t i=0;i<visitor.watches.size()-1;i++) {
                cout << " { ";
                cout << "\"address\": \""  << visitor.watches[i].color << visitor.watches[i].address    << cOff << "\", ";
                cout << "\"firstBlock\": " << bRed                     << visitor.watches[i].firstBlock << cOff << ", ";
                cout << "\"name\": \""     << visitor.watches[i].color << visitor.watches[i].name       << cOff << "\"";
                cout << " }" << ( i < visitor.watches.size()-2 ? ",\r\n " : " \r\n");
            }

            if (visitor.watches.size() > 2)
                cout << "]";

            exit(0);

        } else if (startsWith(arg, '-')) {  // do not collapse
            if (!builtInCmd(arg)) {
                return usage("Invalid option: " + arg);
            }
        }
    }

    kBlock = max((blknum_t)0, kBlock-offset);

    if (debugger_on && !accounting_on)
        return usage("If you want to use the debugger, you must use the --accounting option as well.");

    if (!fileExists("./config.toml"))
        return usage("The config.toml file was not found. Are you in the right folder? Quitting...\n");

    CToml toml("./config.toml");
    if (!loadWatches(toml))
        return false;

    accounting_on  =          toml.getConfigBool("display", "accounting",  false) || accounting_on;
    logs_on        =          toml.getConfigBool("display", "logs",        false) || logs_on;
    trace_on       =          toml.getConfigBool("display", "trace",       false) || trace_on;
    parse_on       =          toml.getConfigBool("display", "parse",       false) || parse_on;
    debugger_on    =          toml.getConfigBool("display", "debug",       false) || debugger_on;
    single_on      =          toml.getConfigBool("display", "single",      false) || single_on;
    no_check       =          toml.getConfigBool("display", "no_check",    false) || no_check;
    autocorrect_on =          toml.getConfigBool("display", "autocorrect", false) || autocorrect_on;
    json_on        =          toml.getConfigBool("formats", "as_json",     false) || json_on;

    // If we're not told to use Json, then we use format strings. No format string == export as json
    if (!json_on) {
        transFmt   = cleanFmt(toml.getConfigStr ("formats", "trans_fmt",   defTransFmt));
        traceFmt   = cleanFmt(toml.getConfigStr ("formats", "trace_fmt",   defTraceFmt));
    } else {
        debugger_on = accounting_on = trace_on = logs_on = false;
    }

    replaceAll(transFmt, "{ISERROR}", cRed + "ERROR:{b:ISERROR}");
    replaceAll(traceFmt, "{ISERROR}", cRed + "ERROR:{b:ISERROR}");

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    paramsPtr = params;
    nParamsRef = nParams;

    no_check = false;
    single_on = false;
    accounting_on = false;
    logs_on = false;
    trace_on = false;
    debugger_on = false;
    export_on = false;
    parse_on = false;
    autocorrect_on = false;
    report_bals = false;
    json_on = false;
    kBlock = 0;
    offset = 0;
    minArgs = 0;
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void) : transStats(), blockStats(),
#ifdef DEBUGGER_ON
    tBuffer(),
#endif
    transFmt(""), traceFmt(""), esc_hit(false) {
    Init();
    barLen(80);
}

//--------------------------------------------------------------------------------
COptions::~COptions(void) {
}

//-----------------------------------------------------------------------
string_q cleanFmt(const string_q& str) {
    return (substitute(substitute(substitute(substitute(substitute((str), "\\n\\\n", "\\n"), "\n", ""), "\\n", "\n"), "\\t", "\t"), "\\r", "\r"));
}

//-----------------------------------------------------------------------
//const char* defTransFmt = "{ \"date\": \"[{DATE}]\", \"from\": \"[{FROM}]\", \"to\": \"[{TO}]\", \"value\": \"[{VALUE}]\" }";
const char* defTransFmt = "+=+ \"date\": \"[{DATE}]\", \"from\": \"[{FROM}]\", \"to\": \"[{TO}]\", \"value\": \"[{VALUE}]\" =+=";
const char* defTraceFmt = "{ \"[{DATESH}]\", \"[{TIME}]\", \"[{FROM}]\", \"[{TO}]\", \"[{VALUE}]\" }";
