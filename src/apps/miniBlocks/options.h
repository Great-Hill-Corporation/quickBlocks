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
#include "etherlib.h"
#include "reporter.h"

//-----------------------------------------------------------------------------
class COptions : public COptionsBase {
public:
    string_q mode;
    bool deep;
    uint32_t skip;
    blknum_t startBlock;
    blknum_t maxBlocks;

    COptions(void);
    ~COptions(void);

    bool parseArguments(string_q& command);
    void Init(void);
};

//-----------------------------------------------------------------------------
extern void checkMiniBlocks    (const COptions& opts, CVisitor& reporter);
extern bool checkMiniBlock     (CMiniBlock& block, const CMiniTrans *trans, void *data);
extern bool visitNonEmptyBlock (CBlock& node, void *data);
extern bool visitEmptyBlock    (CBlock& node, void *data);
