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
#include <algorithm>
#include "setapprovalforall.h"
#include "etherlib.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(QSetApprovalForAll, CTransaction_Ex);

//---------------------------------------------------------------------------
static string_q nextSetapprovalforallChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextSetapprovalforallChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void QSetApprovalForAll::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
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
        ctx << getNextChunk(fmt, nextSetapprovalforallChunk, this);
}

//---------------------------------------------------------------------------
string_q nextSetapprovalforallChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const QSetApprovalForAll *>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool QSetApprovalForAll::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    if (CTransaction_Ex::setValueByName(fieldName, fieldValue))
        return true;

    switch (tolower(fieldName[0])) {
        case '_':
            if ( fieldName % "_operator" ) { _operator = str_2_Addr(fieldValue); return true; }
            if ( fieldName % "_approved" ) { _approved = str_2_Bool(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void QSetApprovalForAll::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool QSetApprovalForAll::Serialize(CArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CTransaction_Ex::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> _operator;
    archive >> _approved;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool QSetApprovalForAll::SerializeC(CArchive& archive) const {

    // Writing always write the latest version of the data
    CTransaction_Ex::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << _operator;
    archive << _approved;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, QSetApprovalForAllArray& array) {
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
CArchive& operator<<(CArchive& archive, const QSetApprovalForAllArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void QSetApprovalForAll::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    CTransaction_Ex::registerClass();

    size_t fieldNum = 1000;
    ADD_FIELD(QSetApprovalForAll, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(QSetApprovalForAll, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(QSetApprovalForAll, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(QSetApprovalForAll, "cname", T_TEXT,  ++fieldNum);
    ADD_FIELD(QSetApprovalForAll, "_operator", T_ADDRESS, ++fieldNum);
    ADD_FIELD(QSetApprovalForAll, "_approved", T_BOOL, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(QSetApprovalForAll, "schema");
    HIDE_FIELD(QSetApprovalForAll, "deleted");
    HIDE_FIELD(QSetApprovalForAll, "showing");
    HIDE_FIELD(QSetApprovalForAll, "cname");

    builtIns.push_back(_biQSetApprovalForAll);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextSetapprovalforallChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const QSetApprovalForAll *set = reinterpret_cast<const QSetApprovalForAll *>(dataPtr);
    if (set) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, set);
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
bool QSetApprovalForAll::readBackLevel(CArchive& archive) {

    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q QSetApprovalForAll::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextSetapprovalforallChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case '_':
            if ( fieldName % "_operator" ) return addr_2_Str(_operator);
            if ( fieldName % "_approved" ) return int_2_Str(_approved);
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CTransaction_Ex::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const QSetApprovalForAll& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

