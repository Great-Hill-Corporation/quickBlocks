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
#define NOWALLETLIB
#include "etherlib.h"
#include "options.h"

void reportByToken(COptions& options);
void reportByAccount(COptions& options);
extern SFUintBN getTokenInfo(const string_q& value,  const SFAddress& token, const SFAddress& holder, blknum_t blockNum);
//--------------------------------------------------------------
int main(int argc, const char *argv[]) {

    etherlib_init();

    // Parse command line, allowing for command files
    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    while (!options.commandList.empty()) {

        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;

        if (options.asData)
            cout << "block\ttoken\tholder\ttoken balance\n";
        if (options.byAccount)
            reportByAccount(options);
        else
            reportByToken(options);

    }
    return 0;
}

//--------------------------------------------------------------
void reportByToken(COptions& options) {

    SFUintBN totalVal = 0;
    uint64_t nAccts = countOf(options.holders, '|') + 1;
    bool needsTotal = (nAccts > 1 && options.total);

    bool needsNewline = true;
    // For each token contract
    string_q tokens = options.tokens;
    while (!tokens.empty()) {
        SFAddress token = nextTokenClear(tokens, '|');
        if (!options.asData)
            cout << "\n  For token contract: " << bBlue << token << cOff << "\n";

        // For each holder
        string_q holders = options.holders;
        while (!holders.empty()) {
            SFAddress holder = nextTokenClear(holders, '|');

            // For each block
            string_q blocks = options.getBlockNumList();
            while (!blocks.empty()) {
                blknum_t blockNum = toLongU(nextTokenClear(blocks, '|'));
                SFUintBN bal = getTokenInfo("balance", token, holder, blockNum);
                totalVal += bal;
                string_q sBal = to_string(bal).c_str();
                if (expContext().asEther) {
                    sBal = wei2Ether(to_string(bal).c_str());
                } else if (expContext().asDollars) {
                    CBlock blk;
                    getBlock(blk, blockNum);
                    sBal = padLeft("$" + dispDollars(blk.timestamp, bal),14);
                }

                needsNewline = true;
                if (bal > 0 || !options.noZero) {
                    if (options.asData) {
                        cout << blockNum << "\t" << token << "\t" << holder << "\t" << sBal << "\n";
                    } else {
                        cout << "    Balance for account " << cGreen << holder << cOff;
                        cout << " at block " << cTeal << blockNum << cOff;
                        cout << " is " << cYellow << sBal << cOff << "\n";
                    }
                    needsNewline = false;
                } else if (!isTestMode()) {
                    if (options.asData) {
                        cerr << blockNum << "\t" << token << "\t" << holder << "         \r";
                    } else {
                        cerr << "    Balance for account " << cGreen << holder << cOff;
                        cerr << " at block " << cTeal << blockNum << cOff;
                        cerr << " is " << cYellow << sBal << cOff << "           \r";
                    }
                }
                cerr.flush();
                cout.flush();
            }
        }
    }

    if (needsTotal) {
        string_q sBal = to_string(totalVal).c_str();
        if (expContext().asEther) {
            sBal = wei2Ether(to_string(totalVal).c_str());
        } else if (expContext().asDollars) {
            CBlock blk;
            getBlock(blk, getLatestBlockFromClient());
            sBal = padLeft("$" + dispDollars(blk.timestamp, totalVal),14);
        }
        cout << "        Total for " << cGreen << nAccts << cOff;
        cout << " accounts at " << cTeal << "latest" << cOff << " block";
        cout << " is " << cYellow << sBal.Substitute("  "," ") << cOff << "\n";
    }

    if (needsNewline)
        cerr << "                                                                                              \n";
}

//--------------------------------------------------------------
void reportByAccount(COptions& options) {

    SFUintBN totalVal = 0;
    uint64_t nAccts = countOf(options.holders, '|') + 1;
    bool needsTotal = (nAccts > 1 && options.total);

    bool needsNewline = true;
    // For each holder
    string_q holders = options.holders;
    while (!holders.empty()) {
        SFAddress holder = nextTokenClear(holders, '|');
        if (!options.asData)
            cout << "\n  For account: " << bBlue << holder << cOff << "\n";

        // For each token contract
        string_q tokens = options.tokens;
        while (!tokens.empty()) {
            SFAddress token = nextTokenClear(tokens, '|');

            // For each block
            string_q blocks = options.getBlockNumList();
            while (!blocks.empty()) {
                blknum_t blockNum = toLongU(nextTokenClear(blocks, '|'));
                SFUintBN bal = getTokenInfo("balance", token, holder, blockNum);
                totalVal += bal;
                string_q sBal = to_string(bal).c_str();
                if (expContext().asEther) {
                    sBal = wei2Ether(to_string(bal).c_str());
                } else if (expContext().asDollars) {
                    CBlock blk;
                    getBlock(blk, blockNum);
                    sBal = padLeft("$" + dispDollars(blk.timestamp, bal),14);
                }

                needsNewline = true;
                if (bal > 0 || !options.noZero) {
                    if (options.asData) {
                        cout << blockNum << "\t" << token << "\t" << holder << "\t" << sBal << "\n";
                    } else {
                        cout << "    Balance of token contract " << cGreen << token << cOff;
                        cout << " at block " << cTeal << blockNum << cOff;
                        cout << " is " << cYellow << sBal << cOff << "\n";
                    }
                    needsNewline = false;
                } else if (!isTestMode()) {
                    if (options.asData) {
                        cerr << blockNum << "\t" << token << "\t" << holder << "         \r";
                    } else {
                        cerr << "    Balance of token contract " << cGreen << token << cOff;
                        cerr << " at block " << cTeal << blockNum << cOff;
                        cerr << " is " << cYellow << sBal << cOff << "           \r";
                    }
                }
                cerr.flush();
                cout.flush();
            }
        }
    }

    if (needsTotal) {
        string_q sBal = to_string(totalVal).c_str();
        if (expContext().asEther) {
            sBal = wei2Ether(to_string(totalVal).c_str());
        } else if (expContext().asDollars) {
            CBlock blk;
            getBlock(blk, getLatestBlockFromClient());
            sBal = padLeft("$" + dispDollars(blk.timestamp, totalVal),14);
        }
        cout << "        Total for " << cGreen << nAccts << cOff;
        cout << " accounts at " << cTeal << "latest" << cOff << " block";
        cout << " is " << cYellow << sBal.Substitute("  "," ") << cOff << "\n";
    }

    if (needsNewline)
        cerr << "                                                                                              \n";
}

//-------------------------------------------------------------------------
SFUintBN getTokenInfo(const string_q& value, const SFAddress& token, const SFAddress& holder, blknum_t blockNum) {

    ASSERT(isAddress(token));
    ASSERT(isAddress(holder));

    string_q t = "0x" + padLeft(token.substr(2), 40, '0');  // address to send the command to
    string_q h =        padLeft(holder.substr(2), 64, '0'); // encoded data for the transaction

    string_q cmd = "[{\"to\": \"[TOKEN]\", \"data\": \"0x70a08231[HOLDER]\"}, \"[BLOCK]\"]";
    //        string_q cmd = "[{\"to\": \"[TOKEN]\", \"data\": \"0x18160ddd\"}, \"[BLOCK]\"]";
    replace(cmd, "[TOKEN]",  t);
    replace(cmd, "[HOLDER]", h);
    replace(cmd, "[BLOCK]",  toHex(blockNum));

    return toWei(callRPC("eth_call", cmd, false));
}

