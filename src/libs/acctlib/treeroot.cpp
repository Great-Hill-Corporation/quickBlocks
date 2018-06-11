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
#include "treeroot.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CTreeRoot, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextTreerootChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextTreerootChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CTreeRoot::Format(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
    if (!m_showing)
        return;

    if (fmtIn.empty()) {
        ctx << toJson();
        return;
    }

    string_q fmt = fmtIn;
    if (handleCustomFormat(ctx, fmt, dataPtr))
        return;

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextTreerootChunk, this);
}

//---------------------------------------------------------------------------
string_q nextTreerootChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return ((const CTreeRoot *)dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CTreeRoot::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'r':
            if ( fieldName % "root" ) {
                Clear();
                root = new CTreeNode;
                if (root) {
                    char *p = cleanUpJson((char *)fieldValue.c_str());
                    uint32_t nFields = 0;
                    root->parseJson(p, nFields);
                    return true;
                }
                return false;
            }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CTreeRoot::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CTreeRoot::Serialize(SFArchive& archive) {

    if (archive.isWriting())
        return ((const CTreeRoot*)this)->SerializeC(archive);

    // If we're reading a back level, read the whole thing and we're done.
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    root = NULL;
    bool has_root = false;
    archive >> has_root;
    if (has_root) {
        string_q className;
        archive >> className;
        root = createTreeNode(className);
        if (!root)
            return false;
        root->Serialize(archive);
    }
    // EXISTING_CODE
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CTreeRoot::SerializeC(SFArchive& archive) const {

    // Writing always write the latest version of the data
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    archive << (root != NULL);
    if (root) {
        string_q className = root->getRuntimeClass()->getClassNamePtr();
        archive << className;
        root->SerializeC(archive);
    }
    // EXISTING_CODE

    return true;
}

//---------------------------------------------------------------------------
void CTreeRoot::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    uint32_t fieldNum = 1000;
    ADD_FIELD(CTreeRoot, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CTreeRoot, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CTreeRoot, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CTreeRoot, "root", T_POINTER, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CTreeRoot, "schema");
    HIDE_FIELD(CTreeRoot, "deleted");
    HIDE_FIELD(CTreeRoot, "showing");

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextTreerootChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CTreeRoot *tre = (const CTreeRoot *)dataPtr;
    if (tre) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, tre);
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CTreeRoot::handleCustomFormat(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
    // EXISTING_CODE
    // EXISTING_CODE
    return false;
}

//---------------------------------------------------------------------------
bool CTreeRoot::readBackLevel(SFArchive& archive) {

    CBaseNode::readBackLevel(archive);
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CTreeRoot::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextTreerootChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'r':
            if ( fieldName % "root" ) {
                if (root)
                    return root->Format();
                return "";
            }
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CBaseNode::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CTreeRoot& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    os << item.Format() << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
    //-----------------------------------------------------------------------------
    string_q CTreeRoot::at(const string_q& _key) const {
        if (!root)
            return "";
        return root->at(_key);
    }

    //-----------------------------------------------------------------------------
    void CTreeRoot::remove(const string_q& _key) {
        if (root)
            root = root->remove(_key);
    }

    //-----------------------------------------------------------------------------
    void CTreeRoot::insert(const string_q& _key, const string_q& _value) {
        if (_value.empty())
            remove(_key);
        if (verbose == 2) { cerr << "treeroot inserting " << _key << " at " << _value << "\n"; }
        root =
            root ?
                root->insert(_key, _value) :
                new CLeaf(_key, _value);
    }

    //-----------------------------------------------------------------------------
    bool CTreeRoot::visitItems(ACCTVISITOR func, void *data) const {
        ASSERT(func);
        CVisitData *vd = reinterpret_cast<CVisitData*>(data);
        vd->level = 0;
        if (root) {
            bool ret = root->visitItems(func, data);
            return ret;
        }
        return true;
    }

    //------------------------------------------------------------------
    bool forEveryAccount(CTreeRoot *trie, ACCTVISITOR func, void *data) {
        ASSERT(trie);
        return trie->visitItems(func, data);
    }
// EXISTING_CODE
}  // namespace qblocks

