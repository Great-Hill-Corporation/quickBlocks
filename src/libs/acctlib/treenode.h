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
#include "etherlib.h"

namespace qblocks {

//--------------------------------------------------------------------------
class CTreeNode;
typedef SFArrayBase<CTreeNode>         CTreeNodeArray;

// EXISTING_CODE
using ACCTVISITOR = bool (*)(const CTreeNode *v, void *data);
// EXISTING_CODE

//--------------------------------------------------------------------------
class CTreeNode : public CBaseNode {
public:
    uint64_t index;
    string_q prefixS;

public:
    CTreeNode(void);
    CTreeNode(const CTreeNode& tr);
    virtual ~CTreeNode(void);
    CTreeNode& operator=(const CTreeNode& tr);

    DECLARE_NODE(CTreeNode);

    // EXISTING_CODE
    virtual string_q at(const string_q& _key) const { return ""; }
    virtual CTreeNode* insert(const string_q& _key, const string_q& _value) { return NULL; }
    virtual CTreeNode* remove(const string_q& _key) { return NULL; }
    virtual bool visitItems(ACCTVISITOR func, void *data) const { return true; }
    CTreeNode* newBranch(const string_q& _k1, const string_q& _v1, const string_q& _k2, const string_q& _v2);
    // EXISTING_CODE
    friend ostream& operator<<(ostream& os, const CTreeNode& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CTreeNode& tr);
    bool readBackLevel(SFArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CTreeNode::CTreeNode(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CTreeNode::CTreeNode(const CTreeNode& tr) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(tr);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CTreeNode::~CTreeNode(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CTreeNode::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CTreeNode::initialize(void) {
    CBaseNode::initialize();

    index = 0;
    prefixS = "";

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CTreeNode::duplicate(const CTreeNode& tr) {
    clear();
    CBaseNode::duplicate(tr);

    index = tr.index;
    prefixS = tr.prefixS;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CTreeNode& CTreeNode::operator=(const CTreeNode& tr) {
    duplicate(tr);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//---------------------------------------------------------------------------
extern SFArchive& operator>>(SFArchive& archive, CTreeNodeArray& array);
extern SFArchive& operator<<(SFArchive& archive, const CTreeNodeArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
//---------------------------------------------------------------------------
inline unsigned commonPrefix(const string_q& _t, const string_q& _u) {
    size_t s = min(_t.length(), _u.length());
    for (size_t i = 0 ; ; ++i)
        if (i == s || (_t[i] != _u[i]))
            return (unsigned)i;
    return (unsigned)s;
}
// EXISTING_CODE
}  // namespace qblocks

