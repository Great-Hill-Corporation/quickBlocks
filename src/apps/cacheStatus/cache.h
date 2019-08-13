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
class CCache : public CBaseNode {
public:
    string_q type;
    string_q path;
    uint64_t nFiles;
    uint64_t nFolders;
    uint64_t sizeInBytes;
    bool valid_counts;

public:
    CCache(void);
    CCache(const CCache& ca);
    virtual ~CCache(void);
    CCache& operator=(const CCache& ca);

    DECLARE_NODE(CCache);

    // EXISTING_CODE
    void noteFile(const string_q& p) { nFiles++; sizeInBytes += fileSize(p); }
    void noteFolder(const string_q& p) { nFolders++; }
    void reset(void) { initialize(); }
    // EXISTING_CODE
    bool operator==(const CCache& item) const;
    bool operator!=(const CCache& item) const { return !operator==(item); }
    friend bool operator<(const CCache& v1, const CCache& v2);
    friend ostream& operator<<(ostream& os, const CCache& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CCache& ca);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CCache::CCache(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CCache::CCache(const CCache& ca) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(ca);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CCache::~CCache(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CCache::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CCache::initialize(void) {
    CBaseNode::initialize();

    type = "";
    path = "";
    nFiles = 0;
    nFolders = 0;
    sizeInBytes = 0;
    valid_counts = false;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CCache::duplicate(const CCache& ca) {
    clear();
    CBaseNode::duplicate(ca);

    type = ca.type;
    path = ca.path;
    nFiles = ca.nFiles;
    nFolders = ca.nFolders;
    sizeInBytes = ca.sizeInBytes;
    valid_counts = ca.valid_counts;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CCache& CCache::operator=(const CCache& ca) {
    duplicate(ca);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CCache::operator==(const CCache& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CCache& v1, const CCache& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CCache> CCacheArray;
extern CArchive& operator>>(CArchive& archive, CCacheArray& array);
extern CArchive& operator<<(CArchive& archive, const CCacheArray& array);

//---------------------------------------------------------------------------
extern CArchive& operator<<(CArchive& archive, const CCache& cac);
extern CArchive& operator>>(CArchive& archive, CCache& cac);

//---------------------------------------------------------------------------
// EXISTING_CODE
typedef vector<CCache*> CCachePtrArray;
// EXISTING_CODE
}  // namespace qblocks

