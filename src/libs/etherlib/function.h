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
#include "utillib.h"
#include "parameter.h"

namespace qblocks {

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CFunction : public CBaseNode {
public:
    string_q name;
    string_q type;
    bool anonymous;
    bool constant;
    bool payable;
    string_q signature;
    string_q encoding;
    CParameterArray inputs;
    CParameterArray outputs;

public:
    CFunction(void);
    CFunction(const CFunction& fu);
    virtual ~CFunction(void);
    CFunction& operator=(const CFunction& fu);

    DECLARE_NODE(CFunction);

    const CBaseNode *getObjectAt(const string_q& fieldName, size_t index) const override;

    // EXISTING_CODE
    bool hasAddrs;
    string_q getSignature(uint64_t parts) const;
    string_q encodeItem(void) const;
    bool isBuiltin;
    string_q origName;
    // EXISTING_CODE
    friend bool operator<(const CFunction& f1, const CFunction& f2);
    friend ostream& operator<<(ostream& os, const CFunction& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CFunction& fu);
    bool readBackLevel(SFArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CFunction::CFunction(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CFunction::CFunction(const CFunction& fu) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(fu);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CFunction::~CFunction(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CFunction::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CFunction::initialize(void) {
    CBaseNode::initialize();

    name = "";
    type = "";
    anonymous = 0;
    constant = 0;
    payable = 0;
    signature = "";
    encoding = "";
    inputs.clear();
    outputs.clear();

    // EXISTING_CODE
    hasAddrs = false;
    isBuiltin = false;
    origName = "";
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CFunction::duplicate(const CFunction& fu) {
    clear();
    CBaseNode::duplicate(fu);

    name = fu.name;
    type = fu.type;
    anonymous = fu.anonymous;
    constant = fu.constant;
    payable = fu.payable;
    signature = fu.signature;
    encoding = fu.encoding;
    inputs = fu.inputs;
    outputs = fu.outputs;

    // EXISTING_CODE
    hasAddrs = fu.hasAddrs;
    isBuiltin = fu.isBuiltin;
    origName = fu.origName;
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CFunction& CFunction::operator=(const CFunction& fu) {
    duplicate(fu);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//--------------------------------------------------------------------------
inline bool operator<(const CFunction& v1, const CFunction& v2) {
    return v1.encoding < v2.encoding;
};

//---------------------------------------------------------------------------
typedef vector<CFunction> CFunctionArray;
extern SFArchive& operator>>(SFArchive& archive, CFunctionArray& array);
extern SFArchive& operator<<(SFArchive& archive, const CFunctionArray& array);

//---------------------------------------------------------------------------
// EXISTING_CODE
inline bool sortByFuncName(const CFunction& f1, const CFunction& f2) {
    return f2.name < f1.name;
}
// EXISTING_CODE
}  // namespace qblocks

