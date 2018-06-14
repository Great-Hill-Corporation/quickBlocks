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
#include "abilib.h"

namespace qblocks {

//--------------------------------------------------------------------------
class CLogEntry;
typedef SFArrayBase<CLogEntry>         CLogEntryArray;
typedef SFList<CLogEntry*>             CLogEntryList;
typedef SFUniqueList<CLogEntry*>       CLogEntryListU;

// EXISTING_CODE
class CReceipt;
#define SFTopicArray SFBigUintArray
// EXISTING_CODE

//--------------------------------------------------------------------------
class CLogEntry : public CBaseNode {
public:
    SFAddress address;
    string_q data;
    uint64_t logIndex;
    SFTopicArray topics;

public:
    CLogEntry(void);
    CLogEntry(const CLogEntry& lo);
    virtual ~CLogEntry(void);
    CLogEntry& operator=(const CLogEntry& lo);

    DECLARE_NODE(CLogEntry);

    const string_q getStringAt(const string_q& name, uint32_t i) const override;

    // EXISTING_CODE
    const CReceipt *pReceipt;
#if 0
    SFHash blockHash;
    uint32_t blockNumber;
    SFHash transactionHash;
    uint32_t transactionIndex;
#endif
    bool operator==(const CLogEntry& le) const;
    bool operator!=(const CLogEntry& le) const { return !operator==(le); };
    // EXISTING_CODE
    friend ostream& operator<<(ostream& os, const CLogEntry& item);

protected:
    void Clear(void);
    void Init(void);
    void Copy(const CLogEntry& lo);
    bool readBackLevel(SFArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CLogEntry::CLogEntry(void) {
    Init();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CLogEntry::CLogEntry(const CLogEntry& lo) {
    // EXISTING_CODE
    // EXISTING_CODE
    Copy(lo);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CLogEntry::~CLogEntry(void) {
    Clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CLogEntry::Clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CLogEntry::Init(void) {
    CBaseNode::Init();

    address = "";
    data = "";
    logIndex = 0;
    topics.clear();

    // EXISTING_CODE
#if 0
    blockHash = "";
    blockNumber = 0;
    transactionHash = "";
    transactionIndex = 0;
#endif
    pReceipt = NULL;
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CLogEntry::Copy(const CLogEntry& lo) {
    Clear();
    CBaseNode::Copy(lo);

    address = lo.address;
    data = lo.data;
    logIndex = lo.logIndex;
    topics = lo.topics;

    // EXISTING_CODE
#if 0
    blockHash = lo.blockHash;
    blockNumber = lo.blockNumber;
    transactionHash = lo.transactionHash;
    transactionIndex = lo.transactionIndex;
#endif
    // no deep copy because it's const
    pReceipt = lo.pReceipt;
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CLogEntry& CLogEntry::operator=(const CLogEntry& lo) {
    Copy(lo);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//---------------------------------------------------------------------------
IMPLEMENT_ARCHIVE_ARRAY(CLogEntryArray);
IMPLEMENT_ARCHIVE_ARRAY_C(CLogEntryArray);
IMPLEMENT_ARCHIVE_LIST(CLogEntryList);

//---------------------------------------------------------------------------
extern SFArchive& operator<<(SFArchive& archive, const CLogEntry& log);
extern SFArchive& operator>>(SFArchive& archive, CLogEntry& log);

//---------------------------------------------------------------------------
// EXISTING_CODE
extern string_q nextReceiptChunk(const string_q& fieldIn, const void *data);
extern string_q nextLogentryChunk(const string_q& fieldIn, const void *data);
// EXISTING_CODE
}  // namespace qblocks

