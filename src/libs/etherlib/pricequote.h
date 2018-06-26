#pragma once
/*-------------------------------------------------------------------------------------------
 * QuickBlocks - Decentralized, useful, and detailed data from Ethereum blockchains
 * Copyright (c) 2018 Great Hill Corporation (http://quickblocks.io)
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
#include "abilib.h"

namespace qblocks {

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CPriceQuote : public CBaseNode {
public:
    timestamp_t timestamp;
    double close;

public:
    CPriceQuote(void);
    CPriceQuote(const CPriceQuote& pr);
    virtual ~CPriceQuote(void);
    CPriceQuote& operator=(const CPriceQuote& pr);

    DECLARE_NODE(CPriceQuote);

    // EXISTING_CODE
    SFTime date;
    // EXISTING_CODE
    friend bool operator<(const CPriceQuote& v1, const CPriceQuote& v2);
    friend ostream& operator<<(ostream& os, const CPriceQuote& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CPriceQuote& pr);
    bool readBackLevel(SFArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CPriceQuote::CPriceQuote(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CPriceQuote::CPriceQuote(const CPriceQuote& pr) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(pr);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CPriceQuote::~CPriceQuote(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CPriceQuote::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CPriceQuote::initialize(void) {
    CBaseNode::initialize();

    timestamp = 0;
    close = 0.0;

    // EXISTING_CODE
    date = earliestDate;
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CPriceQuote::duplicate(const CPriceQuote& pr) {
    clear();
    CBaseNode::duplicate(pr);

    timestamp = pr.timestamp;
    close = pr.close;

    // EXISTING_CODE
    date = pr.date;
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CPriceQuote& CPriceQuote::operator=(const CPriceQuote& pr) {
    duplicate(pr);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool operator<(const CPriceQuote& v1, const CPriceQuote& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CPriceQuote> CPriceQuoteArray;
extern SFArchive& operator>>(SFArchive& archive, CPriceQuoteArray& array);
extern SFArchive& operator<<(SFArchive& archive, const CPriceQuoteArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
extern uint64_t indexFromTimeStamp(const CPriceQuoteArray& quotes, timestamp_t ts);
extern string_q asDollars(timestamp_t ts, SFUintBN weiIn);
extern string_q dispDollars(timestamp_t ts, SFUintBN weiIn);
// EXISTING_CODE
}  // namespace qblocks

