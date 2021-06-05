#pragma once
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
#include "acctlib.h"

// BEG_ERROR_DEFINES
// END_ERROR_DEFINES

//-----------------------------------------------------------------------------
enum account_t {
    CUSTOM = (1 << 2),
    NAMED = (1 << 3),
    PREFUND = (1 << 4),
    OTHER = (1 << 5),
    ALL = (CUSTOM | NAMED | OTHER)
};

//-----------------------------------------------------------------------------
class COptions : public CAbiOptions {
  public:
    // BEG_CODE_DECLARE
    bool match_case;
    bool entities;
    bool tags;
    // END_CODE_DECLARE

    blknum_t latestBlock;

    CMonitor standards;
    CAccountNameMap items;
    CStringArray searches;
    string_q searchFields;
    uint64_t types;

    COptions(void);
    ~COptions(void);

    bool parseArguments(string_q& command) override;
    void Init(void) override;

    void applyFilter(void);
    bool addIfUnique(const CAccountName& item);

    void exportEntities(const CStringArray& terms);
    bool processEditCommand(CStringArray& terms, bool to_custom);
    bool handle_clean(void);

    bool isTokenContract(const CAccountName& account);
    void finishClean(CAccountName& name);
    bool cleanNames(const string_q& sourceIn, const string_q& destIn);
};
