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
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "etherlib.h"

namespace qblocks {

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CEthState : public CBaseNode {
public:
    blknum_t blockNumber;
    biguint_t balance;
    uint64_t nonce;
    string_q code;
    string_q storage;
    address_t address;

public:
    CEthState(void);
    CEthState(const CEthState& et);
    virtual ~CEthState(void);
    CEthState& operator=(const CEthState& et);

    DECLARE_NODE(CEthState);

    // EXISTING_CODE
    // EXISTING_CODE
    bool operator==(const CEthState& item) const;
    bool operator!=(const CEthState& item) const { return !operator==(item); }
    friend bool operator<(const CEthState& v1, const CEthState& v2);
    friend ostream& operator<<(ostream& os, const CEthState& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CEthState& et);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CEthState::CEthState(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CEthState::CEthState(const CEthState& et) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(et);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CEthState::~CEthState(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CEthState::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CEthState::initialize(void) {
    CBaseNode::initialize();

    blockNumber = 0;
    balance = 0;
    nonce = 0;
    code = "";
    storage = "";
    address = "";

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CEthState::duplicate(const CEthState& et) {
    clear();
    CBaseNode::duplicate(et);

    blockNumber = et.blockNumber;
    balance = et.balance;
    nonce = et.nonce;
    code = et.code;
    storage = et.storage;
    address = et.address;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CEthState& CEthState::operator=(const CEthState& et) {
    duplicate(et);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CEthState::operator==(const CEthState& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // Default equality operator as defined in class definition
    return blockNumber == item.blockNumber;
}

//-------------------------------------------------------------------------
inline bool operator<(const CEthState& v1, const CEthState& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // Default sort as defined in class definition
    return v1.blockNumber < v2.blockNumber;
}

//---------------------------------------------------------------------------
typedef vector<CEthState> CEthStateArray;
extern CArchive& operator>>(CArchive& archive, CEthStateArray& array);
extern CArchive& operator<<(CArchive& archive, const CEthStateArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
typedef map<address_t,CEthState> CEthStateMap;
// EXISTING_CODE
}  // namespace qblocks

