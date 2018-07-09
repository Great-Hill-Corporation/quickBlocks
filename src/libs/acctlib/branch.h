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
#include <map>
#include "etherlib.h"
#include "treenode.h"

namespace qblocks {

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CBranch : public CTreeNode {
public:
    string_q branchValue;

public:
    CBranch(void);
    CBranch(const CBranch& br);
    virtual ~CBranch(void);
    CBranch& operator=(const CBranch& br);

    DECLARE_NODE(CBranch);

    // EXISTING_CODE
    CTreeNode *nodes[16];
    explicit CBranch(const string_q& _value);
    CBranch(char _i1, CTreeNode* _n1, const string_q& _value = "");
    CBranch(char _i1, CTreeNode* _n1, char _i2, CTreeNode* _n2);
    string_q at(const string_q& _key) const override;
    CTreeNode* insert(const string_q& _key, const string_q& _value) override;
    CTreeNode* remove(const string_q& _key) override;
    bool visitItems(ACCTVISITOR func, void *data) const override;

private:
    char activeBranch() const;
    CTreeNode *rejig();
    // EXISTING_CODE
    bool operator==(const CBranch& item) const;
    bool operator!=(const CBranch& item) const { return !operator==(item); }
    friend bool operator<(const CBranch& v1, const CBranch& v2);
    friend ostream& operator<<(ostream& os, const CBranch& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CBranch& br);
    bool readBackLevel(SFArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CBranch::CBranch(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CBranch::CBranch(const CBranch& br) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(br);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CBranch::~CBranch(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBranch::clear(void) {
    // EXISTING_CODE
    for (int i = 0 ; i < 16 ; i++)
        if (nodes[i])
            delete nodes[i];
    memset(nodes, 0, sizeof(CTreeNode*) * 16);
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBranch::initialize(void) {
    CTreeNode::initialize();

    branchValue = "";

    // EXISTING_CODE
    memset(nodes, 0, sizeof(CTreeNode*) * 16);
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBranch::duplicate(const CBranch& br) {
    clear();
    CTreeNode::duplicate(br);

    branchValue = br.branchValue;

    // EXISTING_CODE
    for (int i = 0 ; i < 16 ; i++)
        if (br.nodes[i])
            *nodes[i] = *br.nodes[i];
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CBranch& CBranch::operator=(const CBranch& br) {
    duplicate(br);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CBranch::operator==(const CBranch& item) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CBranch& v1, const CBranch& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CBranch> CBranchArray;
extern SFArchive& operator>>(SFArchive& archive, CBranchArray& array);
extern SFArchive& operator<<(SFArchive& archive, const CBranchArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
extern string_q nextTreenodeChunk(const string_q& fieldIn, const void *data);
// EXISTING_CODE
}  // namespace qblocks

