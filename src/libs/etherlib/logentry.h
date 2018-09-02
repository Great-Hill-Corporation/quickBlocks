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

namespace qblocks {

// EXISTING_CODE
class CReceipt;
// EXISTING_CODE

//--------------------------------------------------------------------------
class CLogEntry : public CBaseNode {
public:
    address_t address;
    string_q data;
    uint64_t logIndex;
    CTopicArray topics;

public:
    CLogEntry(void);
    CLogEntry(const CLogEntry& lo);
    virtual ~CLogEntry(void);
    CLogEntry& operator=(const CLogEntry& lo);

    DECLARE_NODE(CLogEntry);

    const string_q getStringAt(const string_q& name, size_t i) const override;

    // EXISTING_CODE
    const CReceipt *pReceipt;
    string_q articulatedLog;
    CFunction *func;
    // EXISTING_CODE
    bool operator==(const CLogEntry& item) const;
    bool operator!=(const CLogEntry& item) const { return !operator==(item); }
    friend bool operator<(const CLogEntry& v1, const CLogEntry& v2);
    friend ostream& operator<<(ostream& os, const CLogEntry& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CLogEntry& lo);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CLogEntry::CLogEntry(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CLogEntry::CLogEntry(const CLogEntry& lo) {
    // EXISTING_CODE
    func = NULL;
    // EXISTING_CODE
    duplicate(lo);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CLogEntry::~CLogEntry(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CLogEntry::clear(void) {
    // EXISTING_CODE
    if (func)
        delete func;
    func = NULL;
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CLogEntry::initialize(void) {
    CBaseNode::initialize();

    address = "";
    data = "";
    logIndex = 0;
    topics.clear();

    // EXISTING_CODE
    pReceipt = NULL;
    articulatedLog = "";
    func = NULL;
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CLogEntry::duplicate(const CLogEntry& lo) {
    clear();
    CBaseNode::duplicate(lo);

    address = lo.address;
    data = lo.data;
    logIndex = lo.logIndex;
    topics = lo.topics;

    // EXISTING_CODE
    articulatedLog = lo.articulatedLog;
    // no deep copy because it's const
    pReceipt = lo.pReceipt;
    func = (lo.func ? new CFunction(*lo.func) : NULL);
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CLogEntry& CLogEntry::operator=(const CLogEntry& lo) {
    duplicate(lo);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CLogEntry::operator==(const CLogEntry& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CLogEntry& v1, const CLogEntry& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CLogEntry> CLogEntryArray;
extern CArchive& operator>>(CArchive& archive, CLogEntryArray& array);
extern CArchive& operator<<(CArchive& archive, const CLogEntryArray& array);

//---------------------------------------------------------------------------
extern CArchive& operator<<(CArchive& archive, const CLogEntry& log);
extern CArchive& operator>>(CArchive& archive, CLogEntry& log);

//---------------------------------------------------------------------------
// EXISTING_CODE
extern string_q nextReceiptChunk(const string_q& fieldIn, const void *data);
extern string_q nextLogentryChunk(const string_q& fieldIn, const void *data);
// EXISTING_CODE
}  // namespace qblocks

