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
 * Parts of this file were generated with makeClass --run. Edit only those parts of
 *  the code inside of 'EXISTING_CODE' tags.
 */
#include "etherlib.h"
#include "appearance.h"

namespace qblocks {
//----------------------------------------------------------------
struct CIndexHeader {
    uint32_t magic;
    uint8_t hash[32];
    uint32_t nAddrs;
    uint32_t nRows;
};

//----------------------------------------------------------------
struct CIndexedAddress {
    uint8_t bytes[20];
    uint32_t offset;
    uint32_t cnt;
};

//----------------------------------------------------------------
struct CIndexedAppearance {
    uint32_t blk;
    uint32_t txid;
    CIndexedAppearance(void) {
        blk = txid = 0;
    }
    CIndexedAppearance(uint32_t b, uint32_t t) : blk(b), txid(t) {
    }
    CIndexedAppearance(const string_q& b, const string_q& t)
        : blk((uint32_t)str_2_Uint(b)), txid((uint32_t)str_2_Uint(t)) {
    }
    CIndexedAppearance(string_q& line) {  // NOLINT
        replaceAll(line, ".", "\t");
        if (!contains(line, "\t"))
            return;
        blk = (uint32_t)str_2_Uint(nextTokenClear(line, '\t'));
        txid = (uint32_t)str_2_Uint(nextTokenClear(line, '\t'));
    }
};
typedef vector<CIndexedAppearance> CIndexedAppearanceArray;
inline bool operator<(const CIndexedAppearance& v1, const CIndexedAppearance& v2) {
    return ((v1.blk != v2.blk) ? v1.blk < v2.blk : v1.txid < v2.txid);
}
inline bool sortIndexedAppearanceReverse(const CIndexedAppearance& v1, const CIndexedAppearance& v2) {
    return !((v1.blk != v2.blk) ? v1.blk < v2.blk : v1.txid < v2.txid);
}

//---------------------------------------------------------------------------
class CIndexArchive : public CArchive {
  public:
    CIndexHeader* header;
    uint64_t nAddrs;
    CIndexedAddress* addresses;
    uint64_t nApps;
    CIndexedAppearance* appearances;

    explicit CIndexArchive(bool mode);
    ~CIndexArchive(void);
    bool ReadIndexFromBinary(const string_q& fn);

  private:
    char* rawData;
    CIndexArchive(void) : CArchive(READING_ARCHIVE) {
    }
};
}  // namespace qblocks
