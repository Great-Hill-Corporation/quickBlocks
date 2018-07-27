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
#include <vector>
#include <map>
#include "abilib.h"
#include "logentry.h"

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CNewReceipt : public CBaseNode {
public:
    address_t contractAddress;
    gas_t gasUsed;
    CLogEntryArray logs;
    bloom_t logsBloom;
    bool isError;

public:
    CNewReceipt(void);
    CNewReceipt(const CNewReceipt& ne);
    virtual ~CNewReceipt(void);
    CNewReceipt& operator=(const CNewReceipt& ne);

    DECLARE_NODE(CNewReceipt);

    const CBaseNode *getObjectAt(const string_q& fieldName, size_t index) const override;

    // EXISTING_CODE
    friend class CTransaction;
    // EXISTING_CODE
    bool operator==(const CNewReceipt& item) const;
    bool operator!=(const CNewReceipt& item) const { return !operator==(item); }
    friend bool operator<(const CNewReceipt& v1, const CNewReceipt& v2);
    friend ostream& operator<<(ostream& os, const CNewReceipt& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CNewReceipt& ne);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CNewReceipt::CNewReceipt(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CNewReceipt::CNewReceipt(const CNewReceipt& ne) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(ne);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CNewReceipt::~CNewReceipt(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CNewReceipt::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CNewReceipt::initialize(void) {
    CBaseNode::initialize();

    contractAddress = "";
    gasUsed = 0;
    logs.clear();
    logsBloom = 0;
    isError = 0;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CNewReceipt::duplicate(const CNewReceipt& ne) {
    clear();
    CBaseNode::duplicate(ne);

    contractAddress = ne.contractAddress;
    gasUsed = ne.gasUsed;
    logs = ne.logs;
    logsBloom = ne.logsBloom;
    isError = ne.isError;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CNewReceipt& CNewReceipt::operator=(const CNewReceipt& ne) {
    duplicate(ne);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CNewReceipt::operator==(const CNewReceipt& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CNewReceipt& v1, const CNewReceipt& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CNewReceipt> CNewReceiptArray;
extern CArchive& operator>>(CArchive& archive, CNewReceiptArray& array);
extern CArchive& operator<<(CArchive& archive, const CNewReceiptArray& array);

//---------------------------------------------------------------------------
extern CArchive& operator<<(CArchive& archive, const CNewReceipt& newp);
extern CArchive& operator>>(CArchive& archive, CNewReceipt& newp);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

