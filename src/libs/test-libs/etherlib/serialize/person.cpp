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
#include <algorithm>
#include "person.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CPerson, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextPersonChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextPersonChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CPerson::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
    if (!m_showing)
        return;

    if (fmtIn.empty()) {
        ctx << toJson();
        return;
    }

    string_q fmt = fmtIn;
    // EXISTING_CODE
    // EXISTING_CODE

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextPersonChunk, this);
}

//---------------------------------------------------------------------------
string_q nextPersonChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return ((const CPerson *)dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CPerson::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "age" ) { age = toUnsigned(fieldValue); return true; }
            break;
        case 'n':
            if ( fieldName % "name" ) { name = fieldValue; return true; }
            if ( fieldName % "next" ) {
                clear();
                next = new CPerson;
                if (next) {
                    char *p = cleanUpJson((char *)fieldValue.c_str());  // NOLINT
                    size_t nFields = 0;
                    next->parseJson(p, nFields);
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
void CPerson::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CPerson::Serialize(SFArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CBaseNode::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> name;
    archive >> age;
    next = NULL;
    bool has_next = false;
    archive >> has_next;
    if (has_next) {
        string_q className;
        archive >> className;
        next = (CPerson *)createObjectOfType(className);  // NOLINT
        if (!next)
            return false;
        next->Serialize(archive);
    }
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CPerson::SerializeC(SFArchive& archive) const {

    // Writing always write the latest version of the data
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << name;
    archive << age;
    archive << (next != NULL);
    if (next) {
        archive << next->getRuntimeClass()->getClassNamePtr();
        next->SerializeC(archive);
    }

    return true;
}

//---------------------------------------------------------------------------
SFArchive& operator>>(SFArchive& archive, CPersonArray& array) {
    uint64_t count;
    archive >> count;
    array.resize(count);
    for (size_t i = 0 ; i < count ; i++) {
        ASSERT(i < array.capacity());
        array.at(i).Serialize(archive);
    }
    return archive;
}

//---------------------------------------------------------------------------
SFArchive& operator<<(SFArchive& archive, const CPersonArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CPerson::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    size_t fieldNum = 1000;
    ADD_FIELD(CPerson, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CPerson, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CPerson, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CPerson, "name", T_TEXT, ++fieldNum);
    ADD_FIELD(CPerson, "age", T_NUMBER, ++fieldNum);
    ADD_FIELD(CPerson, "next", T_POINTER, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CPerson, "schema");
    HIDE_FIELD(CPerson, "deleted");
    HIDE_FIELD(CPerson, "showing");

    builtIns.push_back(_biCPerson);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextPersonChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CPerson *per = (const CPerson *)dataPtr;  // NOLINT
    if (per) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, per);
                // EXISTING_CODE
                // EXISTING_CODE
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CPerson::readBackLevel(SFArchive& archive) {

    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CPerson::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextPersonChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "age" ) return asStringU(age);
            break;
        case 'n':
            if ( fieldName % "name" ) return name;
            if ( fieldName % "next" ) {
                if (next)
                    return next->Format();
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
ostream& operator<<(ostream& os, const CPerson& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

