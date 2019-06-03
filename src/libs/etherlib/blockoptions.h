#pragma once
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
#include "utillib.h"

//-----------------------------------------------------------------------------
class CBlockOptions : public COptionsBase {
public:
    COptionsBlockList blocks;
    CBlockOptions(void);
    string_q getBlockNumList(void);
    void Init(void);
};

//-----------------------------------------------------------------------------
class CHistoryOptions : public CBlockOptions {
public:
    blknum_t newestBlock;
    blknum_t oldestBlock;
    CHistoryOptions(void) { Init(); }
    ~CHistoryOptions(void) { }
    void Init(void) override { CBlockOptions::Init(); newestBlock = oldestBlock = NOPOS; }
    bool hasHistory(void) const;
};

//-----------------------------------------------------------------------------
extern string_q getDispBal(blknum_t blockNum, biguint_t bal);
extern bool wrangleTxId(string_q& argIn, string_q& errorMsg);
extern bool getDirectionalTxId(blknum_t bn, txnum_t txid, const string_q& dir, string_q& argOut, string_q& errorMsg);
