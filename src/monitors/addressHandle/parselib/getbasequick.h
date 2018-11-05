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
#include "transaction.h"

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CGetBaseQuick : public CTransaction {
public:
    string_q _base;

public:
    CGetBaseQuick(void);
    CGetBaseQuick(const CGetBaseQuick& ge);
    virtual ~CGetBaseQuick(void);
    CGetBaseQuick& operator=(const CGetBaseQuick& ge);

    DECLARE_NODE(CGetBaseQuick);

    // EXISTING_CODE
    // EXISTING_CODE
    bool operator==(const CGetBaseQuick& item) const;
    bool operator!=(const CGetBaseQuick& item) const { return !operator==(item); }
    friend bool operator<(const CGetBaseQuick& v1, const CGetBaseQuick& v2);
    friend ostream& operator<<(ostream& os, const CGetBaseQuick& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CGetBaseQuick& ge);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CGetBaseQuick::CGetBaseQuick(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CGetBaseQuick::CGetBaseQuick(const CGetBaseQuick& ge) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(ge);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CGetBaseQuick::~CGetBaseQuick(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CGetBaseQuick::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CGetBaseQuick::initialize(void) {
    CTransaction::initialize();

    _base = "";

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CGetBaseQuick::duplicate(const CGetBaseQuick& ge) {
    clear();
    CTransaction::duplicate(ge);

    _base = ge._base;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CGetBaseQuick& CGetBaseQuick::operator=(const CGetBaseQuick& ge) {
    duplicate(ge);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CGetBaseQuick::operator==(const CGetBaseQuick& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CGetBaseQuick& v1, const CGetBaseQuick& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CGetBaseQuick> CGetBaseQuickArray;
extern CArchive& operator>>(CArchive& archive, CGetBaseQuickArray& array);
extern CArchive& operator<<(CArchive& archive, const CGetBaseQuickArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

