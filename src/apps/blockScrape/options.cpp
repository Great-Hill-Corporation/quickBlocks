/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 * All Rights Reserved
 *------------------------------------------------------------------------*/
/*
 * Parts of this file were generated with makeClass --options. Edit only those parts of
 * the code outside of the BEG_CODE/END_CODE sections
 */
#define LOGGING_LEVEL_TEST
#include "options.h"

//---------------------------------------------------------------------------------------------------
static const COption params[] = {
    // BEG_CODE_OPTIONS
    // clang-format off
    COption("mode", "", "enum[run|quit|pause|restart]", OPT_REQUIRED | OPT_POSITIONAL, "control the block scraper"),
    COption("n_blocks", "n", "<uint64>", OPT_FLAG, "maximum number of blocks to process (defaults to 5000)"),
    COption("n_block_procs", "b", "<uint64>", OPT_HIDDEN | OPT_FLAG, "number of block channels for blaze"),
    COption("n_addr_procs", "a", "<uint64>", OPT_HIDDEN | OPT_FLAG, "number of address channels for blaze"),
    COption("pin", "p", "", OPT_SWITCH, "pin new chunks (and blooms) to IPFS (requires Pinata key and running IPFS node)"),  // NOLINT
    COption("sleep", "s", "<double>", OPT_FLAG, "the number of seconds to sleep between passes (default 14)"),
    COption("once", "o", "", OPT_HIDDEN | OPT_SWITCH, "run the a single block scrape, do not behave as long running process"),  // NOLINT
    COption("", "", "", OPT_DESCRIPTION, "Scan the chain and update the TrueBlocks index of appearances."),
    // clang-format on
    // END_CODE_OPTIONS
};
static const size_t nParams = sizeof(params) / sizeof(COption);

//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {
    ENTER("parseArguments");

    if (!standardOptions(command))
        return false;

    // BEG_CODE_LOCAL_INIT
    // END_CODE_LOCAL_INIT

    CBlock block;
    getBlock_light(block, getBlockProgress(BP_CLIENT).client);
    latestBlockTs = block.timestamp;
    latestBlockNum = block.blockNumber;

    Init();
    explode(arguments, command, ' ');
    for (auto arg : arguments) {
        if (false) {
            // do nothing -- make auto code generation easier
            // BEG_CODE_AUTO
        } else if (startsWith(arg, "-n:") || startsWith(arg, "--n_blocks:")) {
            if (!confirmUint("n_blocks", n_blocks, arg))
                return false;
        } else if (arg == "-n" || arg == "--n_blocks") {
            return flag_required("n_blocks");

        } else if (startsWith(arg, "-b:") || startsWith(arg, "--n_block_procs:")) {
            if (!confirmUint("n_block_procs", n_block_procs, arg))
                return false;
        } else if (arg == "-b" || arg == "--n_block_procs") {
            return flag_required("n_block_procs");

        } else if (startsWith(arg, "-a:") || startsWith(arg, "--n_addr_procs:")) {
            if (!confirmUint("n_addr_procs", n_addr_procs, arg))
                return false;
        } else if (arg == "-a" || arg == "--n_addr_procs") {
            return flag_required("n_addr_procs");

        } else if (arg == "-p" || arg == "--pin") {
            pin = true;

        } else if (startsWith(arg, "-s:") || startsWith(arg, "--sleep:")) {
            if (!confirmDouble("sleep", sleep, arg))
                return false;
        } else if (arg == "-s" || arg == "--sleep") {
            return flag_required("sleep");

        } else if (arg == "-o" || arg == "--once") {
            once = true;

        } else if (startsWith(arg, '-')) {  // do not collapse

            if (!builtInCmd(arg)) {
                return invalid_option(arg);
            }

        } else {
            if (!mode.empty())
                return usage("Please specify only one mode.");
            if (!confirmEnum("mode", mode, arg))
                return false;

            // END_CODE_AUTO
        }
    }

    // BEG_DEBUG_DISPLAY
    LOG_TEST("mode", mode, (mode == ""));
    LOG_TEST("n_blocks", n_blocks, (n_blocks == (isDockerMode() ? 100 : 2000)));
    LOG_TEST("n_block_procs", n_block_procs, (n_block_procs == (isDockerMode() ? 5 : 10)));
    LOG_TEST("n_addr_procs", n_addr_procs, (n_addr_procs == (isDockerMode() ? 10 : 20)));
    LOG_TEST_BOOL("pin", pin);
    LOG_TEST("sleep", sleep, (sleep == 14));
    LOG_TEST_BOOL("once", once);
    // END_DEBUG_DISPLAY

    if (Mocked(""))
        return false;

    if (mode.empty())
        mode = "run";

    // no less than one half second of sleep between runs
    if (sleep < .5)
        sleep = .5;

    if (pin && !getApiKey(lic)) {
        if (!isTestMode()) {
            ostringstream os;
            os << "The --pin option requires you to have a Pinata key.";
            return usage(os.str());
        }
    }

    // We shouldn't run if we're already running...
    if (mode == "run" && amIRunning("blockScrape")) {
        LOG_WARN("The blockScrape app is already running.");
        return false;
    }

    // Nor should we run if the index is being actively scanned...
    if (isRunning("acctExport")) {
        LOG_WARN("Refusing to run while acctExport is running.");
        return false;
    }

    // In test mode, all we do is try to control and report on the state (but we never scrape)
    // Control the state of the app (the state is stored in a temporary file). This only returns
    // false if we moved from stopped state to running state. All other state changes end here.
    bool result = changeState();
    if (isTestMode()) {
        string_q current;
        getCurrentState(current);
        ostringstream os;
        os << "{" << endl;
        os << "  \"message\": \"Testing only\"," << endl;
        os << "  \"mode\": \"" << mode << "\"," << endl;
        os << "  \"n_blocks\": " << n_blocks << "," << endl;
        os << "  \"n_block_procs\": " << n_block_procs << "," << endl;
        os << "  \"n_addr_procs\": " << n_addr_procs << "," << endl;
        os << "  \"pin\": " << pin << "," << endl;
        os << "  \"current\": " << current << "," << endl;
        os << "}" << endl;
        cout << os.str();
        if (!contains(command, "run") && !contains(command, "quit") && !contains(command, "restart") &&
            !contains(command, "pause"))
            cleanupAndQuit();
        getCurrentState(current);
        LOG_INFO("file contents: ", asciiFileToString(getCachePath("tmp/scraper-state.txt")));
        return false;
    }

    // In non-testing mode, we first try to change the state of the scraper (if stopped, start...if
    // started, pause, etc.). We store the state in a temporary file (terrible idea, but it works).
    // `changeState` returns false only if we moved from not running --> running. In this case, we
    // want to enter the scraping state. All other states changes end here and the invocation quits.
    if (result)
        return false;

    // Debugging data...
    LOG_DIR8(indexFolder);
    LOG_DIR8(indexFolder_finalized);
    LOG_DIR8(indexFolder_blooms);
    LOG_DIR8(indexFolder_staging);
    LOG_DIR8(indexFolder_unripe);
    LOG_DIR8(indexFolder_ripe);

    // We need this below...
    const CToml* config = getGlobalConfig("blockScrape");

    // A tracing node is required. Otherwise, the index will be 'short' (i.e. it will
    // be missing appearances). This is okay, if the user tells us it's okay. For
    // example, if the user only wants an index of event emitters or something
    bool needsTracing = config->getConfigBool("requires", "tracing", true);
    if (needsTracing && !isTracingNode()) {
        string_q errMsg = "Tracing is required for this program to work properly.";
        if (isDockerMode())
            errMsg += " If you're running docker, enable remote RPC endpoints.";
        cleanupAndQuit();
        return usage(errMsg);
    }

    // Parity traces are much better (and easier to use) than Geth's. But, in some
    // cases, the user may not care and tells us she doesn't need parity
    bool needsParity = config->getConfigBool("requires", "parity", true);
    if (needsParity && !isParity()) {
        cleanupAndQuit();
        return usage(
            "This tool requires Parity. Add [requires]\\nparity=false to $CONFIG/blockScrape.toml to turn "
            "this "
            "restriction off.");
    }

    // Balances are needed to make reconcilations. The user may not need that, so we allow it
    bool needsBalances = config->getConfigBool("requires", "balances", false);
    if (needsBalances && !nodeHasBalances(true)) {
        cleanupAndQuit();
        return usage("This tool requires an --archive node with historical balances.");
    }

    // This may be the first time we've ever run. In that case, we need to build the zero block index file...
    string chunkId = padNum9(0) + "-" + padNum9(0);
    string_q bloomPath = getIndexPath("blooms/" + chunkId + ".bloom");
    if (!fileExists(bloomPath)) {
        ASSERT(expContext().prefundMap.size() == 8893);  // This is a known value
        LOG_INFO("Index for block zero was not found. Building it from ", uint_2_Str(expContext().prefundMap.size()),
                 " prefunds.");

        CStringArray appearances;
        for (auto prefund : expContext().prefundMap) {
            // The prefund transactions have 'zero' block numbers and an index into thier location
            // in the list of presale addresses which is sorted by address. We need to do this in order to
            // distinquish each transaction when it is exported.
            ostringstream os;
            os << prefund.first << "\t" << padNum9(0) << "\t" << padNum5((uint32_t)appearances.size()) << endl;
            appearances.push_back(os.str());
        }

        // Write the chunk and the bloom to the binary cache
        string_q chunkPath = getIndexPath("finalized/" + chunkId + ".bin");
        writeIndexAsBinary(chunkPath, appearances, (pin ? visitToPin : nullptr), &pinList);
        LOG_INFO("Done...");
    }

    // The previous run may have quit early, leaving the folders in a mild state of
    // disrepair. We clean that up here.
    ::remove((indexFolder_staging + "000000000-temp.txt").c_str());
    cleanFolder(indexFolder_unripe);

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    registerOptions(nParams, params);
    optionOn(OPT_PREFUND);
    optionOff(OPT_FMT);
    // Since we need prefunds, let's load the names library here
    CAccountName unused;
    getNamedAccount(unused, "0x0");

    // BEG_CODE_INIT
    // clang-format off
    n_blocks = getGlobalConfig("blockScrape")->getConfigInt("settings", "n_blocks", (isDockerMode() ? 100 : 2000));
    n_block_procs = getGlobalConfig("blockScrape")->getConfigInt("settings", "n_block_procs", (isDockerMode() ? 5 : 10));
    n_addr_procs = getGlobalConfig("blockScrape")->getConfigInt("settings", "n_addr_procs", (isDockerMode() ? 10 : 20));
    // clang-format on
    pin = false;
    sleep = 14;
    once = false;
    // END_CODE_INIT
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void) {
    Init();

    // BEG_CODE_NOTES
    // clang-format off
    // clang-format on
    // END_CODE_NOTES

    // BEG_ERROR_STRINGS
    // END_ERROR_STRINGS

    // Establish the folders that hold the data...
    establishMonitorFolders();
    establishFolder(indexFolder);
    establishFolder(indexFolder_finalized);
    establishFolder(indexFolder_blooms);
    establishFolder(indexFolder_staging);
    establishFolder(indexFolder_unripe);
    establishFolder(indexFolder_ripe);
    establishFolder(getCachePath("tmp/"));
}

//--------------------------------------------------------------------------------
COptions::~COptions(void) {
}

//--------------------------------------------------------------------------------
ScrapeState COptions::getCurrentState(string_q& current) {
    if (controlFile.empty())
        controlFile = getCachePath("tmp/scraper-state.txt");
    current = asciiFileToString(controlFile);
    if (current == "running") {
        state = STATE_RUNNING;
    } else if (current == "paused") {
        state = STATE_PAUSED;
    } else {
        state = STATE_STOPPED;
        current = "stopped";
    }
    LOG8("Current state ", current, ".");
    return state;
}

//--------------------------------------------------------------------------------
bool COptions::changeState(void) {
    if (isTestMode())
        verbose = 10;
    state = getCurrentState(stateStr);
    switch (state) {
        case STATE_STOPPED:
            if (mode == "run" || mode.empty()) {
                manageRemoveList(controlFile);
                stringToAsciiFile(controlFile, "running");
                state = STATE_RUNNING;
                cout << "{ \"status\": \"running\" }" << endl;
                LOG_TEST_STR("changing state: stopped --> running");
                return false;
            } else {
                if (!(stateStr == "stopped" && mode == "quit"))
                    LOG_ERR("blockScrape is ", stateStr, ". Cannot ", mode, ".");
            }
            break;
        case STATE_RUNNING:
            if (mode == "pause") {
                stringToAsciiFile(controlFile, "paused");
                state = STATE_PAUSED;
                stateStr = "paused";
                LOG_TEST_STR("changing state: running --> paused");
            } else if (mode == "quit") {
                ::remove(controlFile.c_str());
                state = STATE_STOPPED;
                stateStr = "stopped";
                LOG_TEST_STR("changing state: running --> stopped");
            } else if (mode == "run") {
                LOG_ERR("blockScrape is already ", stateStr, ". Cannot ", mode, ".");
                LOG_ERR("If this is in error, remove the file ", (isTestMode() ? "--controlFile--" : controlFile));
                // state = STATE_RUNNING; // redunant, but okay
            } else if (mode == "restart") {
                LOG_ERR("blockScrape is ", stateStr, ". Cannot ", mode, ".");
                // state = STATE_RUNNING; // redunant, but okay
            }
            break;
        case STATE_PAUSED:
            if (mode == "restart" || mode == "run") {
                stringToAsciiFile(controlFile, "running");
                state = STATE_RUNNING;
                stateStr = "running";
                LOG_TEST_STR("changing state: paused --> running");
            } else if (mode == "quit") {
                ::remove(controlFile.c_str());
                state = STATE_STOPPED;
                stateStr = "stopped";
                LOG_TEST_STR("changing state: paused --> stopped");
            } else {
                LOG_ERR("blockScrape is ", stateStr, ". Cannot ", mode, ".");
                // state = STATE_PAUSED; // redunant, but okay
            }
            break;
        default:
            ASSERT("Never happens.");
            break;
    }
    cout << "{ \"status\": \"" << stateStr << "\" }" << endl;
    return true;
}
