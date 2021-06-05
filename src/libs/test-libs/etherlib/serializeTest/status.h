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
#include "cache.h"

namespace qblocks {

// EXISTING_CODE
typedef vector<CCache*> CCachePtrArray;
// EXISTING_CODE

//--------------------------------------------------------------------------
class CStatus : public CBaseNode {
  public:
    string_q client_version;
    string_q trueblocks_version;
    string_q rpc_provider;
    string_q balance_provider;
    string_q host;
    bool is_scraping;
    CCachePtrArray caches;

  public:
    CStatus(void);
    CStatus(const CStatus& st);
    virtual ~CStatus(void);
    CStatus& operator=(const CStatus& st);

    DECLARE_NODE(CStatus);

    const CBaseNode* getObjectAt(const string_q& fieldName, size_t index) const override;

    // EXISTING_CODE
    // EXISTING_CODE
    bool operator==(const CStatus& it) const;
    bool operator!=(const CStatus& it) const {
        return !operator==(it);
    }
    friend bool operator<(const CStatus& v1, const CStatus& v2);
    friend ostream& operator<<(ostream& os, const CStatus& it);

  protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CStatus& st);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CStatus::CStatus(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CStatus::CStatus(const CStatus& st) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(st);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CStatus::~CStatus(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CStatus::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CStatus::initialize(void) {
    CBaseNode::initialize();

    client_version = "";
    trueblocks_version = "";
    rpc_provider = "";
    balance_provider = "";
    host = "";
    is_scraping = false;
    caches.clear();

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CStatus::duplicate(const CStatus& st) {
    clear();
    CBaseNode::duplicate(st);

    client_version = st.client_version;
    trueblocks_version = st.trueblocks_version;
    rpc_provider = st.rpc_provider;
    balance_provider = st.balance_provider;
    host = st.host;
    is_scraping = st.is_scraping;
    caches = st.caches;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CStatus& CStatus::operator=(const CStatus& st) {
    duplicate(st);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CStatus::operator==(const CStatus& it) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CStatus& v1, const CStatus& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CStatus> CStatusArray;
extern CArchive& operator>>(CArchive& archive, CStatusArray& array);
extern CArchive& operator<<(CArchive& archive, const CStatusArray& array);

//---------------------------------------------------------------------------
extern const char* STR_DISPLAY_STATUS;

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
}  // namespace qblocks
