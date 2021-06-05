/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
/*
 * Parts of this file were generated with makeClass --options. Edit only those parts of
 * the code outside of the BEG_CODE/END_CODE sections
 */
#include "options.h"

//---------------------------------------------------------------------------------------------------
static const COption params[] = {
    // BEG_CODE_OPTIONS
    // clang-format off
    COption("blocks", "", "list<blknum>", OPT_REQUIRED | OPT_POSITIONAL, "a space-separated list of one or more blocks to retrieve"),  // NOLINT
    COption("hashes", "e", "", OPT_SWITCH, "display only transaction hashes, default is to display full transaction detail"),  // NOLINT
    COption("uncles", "U", "", OPT_SWITCH, "display uncle blocks (if any) instead of the requested block"),
    COption("trace", "t", "", OPT_SWITCH, "export the traces from the block as opposed to the block data"),
    COption("apps", "a", "", OPT_SWITCH, "display all address appearances in the block"),
    COption("uniq", "u", "", OPT_SWITCH, "display only uniq address appearances per block"),
    COption("uniq_tx", "n", "", OPT_SWITCH, "display only uniq address appearances per transaction"),
    COption("count", "c", "", OPT_SWITCH, "display counts of appearances (for --apps, --uniq, or --uniq_tx) or transactions"),  // NOLINT
    COption("cache", "o", "", OPT_SWITCH, "force a write of the block to the cache"),
    COption("", "", "", OPT_DESCRIPTION, "Retrieve one or more blocks from the chain or local cache."),
    // clang-format on
    // END_CODE_OPTIONS
};
static const size_t nParams = sizeof(params) / sizeof(COption);

extern const char* STR_FORMAT_COUNT_JSON;
extern const char* STR_FORMAT_COUNT_TXT;
extern const char* STR_FORMAT_COUNT_TXT_VERBOSE;
extern const char* STR_FORMAT_FILTER_JSON;
extern const char* STR_FORMAT_FILTER_TXT;
//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {
    if (!standardOptions(command))
        return false;

    // BEG_CODE_LOCAL_INIT
    bool apps = false;
    bool uniq = false;
    bool uniq_tx = false;
    // END_CODE_LOCAL_INIT

    Init();
    blknum_t latest = getBlockProgress(BP_CLIENT).client;
    explode(arguments, command, ' ');
    for (auto arg : arguments) {
        string_q orig = arg;

        // do not collapse
        if (false) {
            // do nothing -- make auto code generation easier
            // BEG_CODE_AUTO
        } else if (arg == "-e" || arg == "--hashes") {
            hashes = true;

        } else if (arg == "-U" || arg == "--uncles") {
            uncles = true;

        } else if (arg == "-t" || arg == "--trace") {
            trace = true;

        } else if (arg == "-a" || arg == "--apps") {
            apps = true;

        } else if (arg == "-u" || arg == "--uniq") {
            uniq = true;

        } else if (arg == "-n" || arg == "--uniq_tx") {
            uniq_tx = true;

        } else if (arg == "-c" || arg == "--count") {
            count = true;

        } else if (arg == "-o" || arg == "--cache") {
            cache = true;

        } else if (startsWith(arg, '-')) {  // do not collapse

            if (!builtInCmd(arg)) {
                return invalid_option(arg);
            }

        } else {
            if (!parseBlockList2(this, blocks, arg, latest))
                return false;

            // END_CODE_AUTO
        }
    }

    // BEG_DEBUG_DISPLAY
    LOG_TEST_LIST("blocks", blocks, blocks.empty());
    LOG_TEST_BOOL("hashes", hashes);
    LOG_TEST_BOOL("uncles", uncles);
    LOG_TEST_BOOL("trace", trace);
    LOG_TEST_BOOL("apps", apps);
    LOG_TEST_BOOL("uniq", uniq);
    LOG_TEST_BOOL("uniq_tx", uniq_tx);
    LOG_TEST_BOOL("count", count);
    LOG_TEST_BOOL("cache", cache);
    // END_DEBUG_DISPLAY

    if (Mocked("blocks"))
        return false;

    if (cache)
        etherlib_init(defaultQuitHandler);

    filterType = (uniq_tx ? "uniq_tx" : (uniq ? "uniq" : (apps ? "apps" : "")));

    if (cache && uncles)
        return usage("The --cache option is not available for uncle blocks.");

    if (cache && !filterType.empty())
        return usage("The --cache option is not available when using one of the address options.");

    if (trace && !isTracingNode())
        return usage("A tracing node is required for the --trace options to work properly.");

    if (trace && !filterType.empty())
        return usage("The --trace option is not available when using one of the address options.");

    if (trace && hashes)
        return usage("The --hashes and --trace options are exclusive.");

    if (blocks.empty())
        return usage("You must specify at least one block.");

    secsFinal =
        (timestamp_t)getGlobalConfig("getBlocks")->getConfigInt("settings", "secs_when_final", (uint64_t)secsFinal);

    if (expContext().asParity) {
        manageFields("CTransaction:cumulativeGasUsed,gasUsed,timestamp", FLD_HIDE);
        RENAME_FIELD(CBlock, "blockNumber", "number");
        GETRUNTIME_CLASS(CBlock)->sortFieldList();
    }

    if (hashes) {
        manageFields("CTransaction:all", FLD_HIDE);
        manageFields("CBlock:all", FLD_HIDE);
        manageFields("CBlock:hash,blockNumber,parentHash,timestamp,tx_hashes", FLD_SHOW);
    }

    if (expContext().exportFmt == NONE1)
        expContext().exportFmt = (isApiMode() ? API1 : (filterType.empty() ? JSON1 : TXT1));

    // Display formatting
    if (count) {
        string_q ff = verbose ? STR_FORMAT_COUNT_TXT_VERBOSE : STR_FORMAT_COUNT_TXT;
        if (verbose <= 2)
            ff = substitute(ff, "\t[{TRACE_COUNT}]", "");
        if (filterType.empty()) {
            replace(ff, "\"[{FILTER_TYPE}]\": [{ADDR_COUNT}]", "");
            replace(ff, "\t[{ADDR_COUNT}]", "");
        }
        configureDisplay("", "CBlock", ff);

    } else if (!filterType.empty()) {
        configureDisplay("", "CBlock", STR_FORMAT_FILTER_TXT);
        if (blocks.hasZeroBlock) {
            optionOn(OPT_PREFUND);
            loadNames();
        }

    } else if (trace) {
        configureDisplay("getBlocks", "CTrace", STR_DISPLAY_TRACE);

    } else {
        configureDisplay("getBlocks", "CBlock", STR_DISPLAY_BLOCK);
    }

    if (expContext().exportFmt == API1 || expContext().exportFmt == JSON1) {
        if (count) {
            string_q ff = STR_FORMAT_COUNT_JSON;
            if (filterType.empty()) {
                replace(ff, ",\n \"[{FILTER_TYPE}]\": [{ADDR_COUNT}]", "");
                replace(ff, "\t[{ADDR_COUNT}]", "");
            }
            expContext().fmtMap["format"] = expContext().fmtMap["header"] = cleanFmt(ff);

        } else if (!filterType.empty()) {
            expContext().fmtMap["format"] = expContext().fmtMap["header"] = cleanFmt(STR_FORMAT_FILTER_JSON);
        }
    }
    if (noHeader)
        expContext().fmtMap["header"] = "";

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    registerOptions(nParams, params);
    optionOn(OPT_RAW);

    // BEG_CODE_INIT
    hashes = false;
    uncles = false;
    trace = false;
    count = false;
    cache = false;
    // END_CODE_INIT

    filterType = "";
    secsFinal = (60 * 5);
    addrCounter = 0;
    blocks.Init();
    CBlockOptions::Init();
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void) {
    Init();
    expContext().exportFmt = NONE1;

    // BEG_CODE_NOTES
    // clang-format off
    notes.push_back("`blocks` is a space-separated list of values, a start-end range, a `special`, or any combination.");  // NOLINT
    notes.push_back("`blocks` may be specified as either numbers or hashes.");
    notes.push_back("`special` blocks are detailed under `chifra when --list`.");
    // clang-format on
    // END_CODE_NOTES

    // BEG_ERROR_STRINGS
    // END_ERROR_STRINGS
}

//--------------------------------------------------------------------------------
COptions::~COptions(void) {
}

//--------------------------------------------------------------------------------
bool COptions::isMulti(void) const {
    return isApiMode() || ((blocks.stop - blocks.start) > 1 || blocks.hashList.size() > 1 || blocks.numList.size() > 1);
}

//--------------------------------------------------------------------------------
void interumReport(ostream& os, blknum_t i) {
    os << (!(i % 150) ? "." : (!(i % 1000)) ? "+" : "");  // dots '.' at every 150, '+' at every 1000
    os.flush();
}

//--------------------------------------------------------------------------------
const char* STR_FORMAT_COUNT_JSON =
    "{\n"
    " \"blockNumber\": [{BLOCKNUMBER}],\n"
    " \"transactionsCnt\": [{TRANSACTIONSCNT}],\n"
    " \"[{FILTER_TYPE}]\": [{ADDR_COUNT}]"
    "}\n";

//--------------------------------------------------------------------------------
const char* STR_FORMAT_COUNT_TXT = "[{BLOCKNUMBER}]\t[{TRANSACTIONSCNT}]\t[{ADDR_COUNT}]";
const char* STR_FORMAT_COUNT_TXT_VERBOSE =
    "[{BLOCKNUMBER}]\t[{UNCLE_COUNT}]\t[{TRANSACTIONSCNT}]\t[{TRACE_COUNT}]\t[{ADDR_COUNT}]";

//--------------------------------------------------------------------------------
const char* STR_FORMAT_FILTER_JSON =
    "{\n"
    " \"bn\": \"[{BN}]\",\n"
    " \"tx\": \"[{TX}]\",\n"
    " \"tc\": \"[{TC}]\",\n"
    " \"addr\": \"[{ADDR}]\",\n"
    " \"reason\": \"[{REASON}]\"\n"
    "}\n";

//--------------------------------------------------------------------------------
const char* STR_FORMAT_FILTER_TXT = "[{BN}]\t[{TX}]\t[{TC}]\t[{ADDR}]\t[{REASON}]";
