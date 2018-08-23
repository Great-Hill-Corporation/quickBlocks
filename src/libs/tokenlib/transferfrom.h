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
#include "transaction_ex.h"

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class QTransferFrom : public CTransaction_Ex {
public:
    address_t _from;
    address_t _to;
    biguint_t _value;

public:
    QTransferFrom(void);
    QTransferFrom(const QTransferFrom& tr);
    virtual ~QTransferFrom(void);
    QTransferFrom& operator=(const QTransferFrom& tr);

    DECLARE_NODE(QTransferFrom);

    // EXISTING_CODE
    // EXISTING_CODE
    bool operator==(const QTransferFrom& item) const;
    bool operator!=(const QTransferFrom& item) const { return !operator==(item); }
    friend bool operator<(const QTransferFrom& v1, const QTransferFrom& v2);
    friend ostream& operator<<(ostream& os, const QTransferFrom& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const QTransferFrom& tr);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline QTransferFrom::QTransferFrom(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline QTransferFrom::QTransferFrom(const QTransferFrom& tr) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(tr);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline QTransferFrom::~QTransferFrom(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void QTransferFrom::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void QTransferFrom::initialize(void) {
    CTransaction_Ex::initialize();

    _from = "";
    _to = "";
    _value = 0;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void QTransferFrom::duplicate(const QTransferFrom& tr) {
    clear();
    CTransaction_Ex::duplicate(tr);

    _from = tr._from;
    _to = tr._to;
    _value = tr._value;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline QTransferFrom& QTransferFrom::operator=(const QTransferFrom& tr) {
    duplicate(tr);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool QTransferFrom::operator==(const QTransferFrom& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const QTransferFrom& v1, const QTransferFrom& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<QTransferFrom> QTransferFromArray;
extern CArchive& operator>>(CArchive& archive, QTransferFromArray& array);
extern CArchive& operator<<(CArchive& archive, const QTransferFromArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

