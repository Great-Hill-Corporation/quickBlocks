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
class CChangeController : public CTransaction {
public:
    address_t _newController;

public:
    CChangeController(void);
    CChangeController(const CChangeController& ch);
    virtual ~CChangeController(void);
    CChangeController& operator=(const CChangeController& ch);

    DECLARE_NODE(CChangeController);

    // EXISTING_CODE
    // EXISTING_CODE
    bool operator==(const CChangeController& item) const;
    bool operator!=(const CChangeController& item) const { return !operator==(item); }
    friend bool operator<(const CChangeController& v1, const CChangeController& v2);
    friend ostream& operator<<(ostream& os, const CChangeController& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CChangeController& ch);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CChangeController::CChangeController(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CChangeController::CChangeController(const CChangeController& ch) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(ch);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CChangeController::~CChangeController(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CChangeController::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CChangeController::initialize(void) {
    CTransaction::initialize();

    _newController = "";

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CChangeController::duplicate(const CChangeController& ch) {
    clear();
    CTransaction::duplicate(ch);

    _newController = ch._newController;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CChangeController& CChangeController::operator=(const CChangeController& ch) {
    duplicate(ch);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CChangeController::operator==(const CChangeController& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CChangeController& v1, const CChangeController& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CChangeController> CChangeControllerArray;
extern CArchive& operator>>(CArchive& archive, CChangeControllerArray& array);
extern CArchive& operator<<(CArchive& archive, const CChangeControllerArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

