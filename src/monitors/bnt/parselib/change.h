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
class CChange : public CTransaction {
public:
    address_t _fromToken;
    address_t _toToken;
    biguint_t _amount;
    biguint_t _minReturn;

public:
    CChange(void);
    CChange(const CChange& ch);
    virtual ~CChange(void);
    CChange& operator=(const CChange& ch);

    DECLARE_NODE(CChange);

    // EXISTING_CODE
    // EXISTING_CODE
    bool operator==(const CChange& item) const;
    bool operator!=(const CChange& item) const { return !operator==(item); }
    friend bool operator<(const CChange& v1, const CChange& v2);
    friend ostream& operator<<(ostream& os, const CChange& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CChange& ch);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CChange::CChange(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CChange::CChange(const CChange& ch) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(ch);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CChange::~CChange(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CChange::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CChange::initialize(void) {
    CTransaction::initialize();

    _fromToken = "";
    _toToken = "";
    _amount = 0;
    _minReturn = 0;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CChange::duplicate(const CChange& ch) {
    clear();
    CTransaction::duplicate(ch);

    _fromToken = ch._fromToken;
    _toToken = ch._toToken;
    _amount = ch._amount;
    _minReturn = ch._minReturn;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CChange& CChange::operator=(const CChange& ch) {
    duplicate(ch);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CChange::operator==(const CChange& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CChange& v1, const CChange& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CChange> CChangeArray;
extern CArchive& operator>>(CArchive& archive, CChangeArray& array);
extern CArchive& operator<<(CArchive& archive, const CChangeArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

