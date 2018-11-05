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
#include "newclonetokenevent.h"
#include "etherlib.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CNewCloneTokenEvent, CLogEntry);

//---------------------------------------------------------------------------
static string_q nextNewclonetokeneventChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextNewclonetokeneventChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CNewCloneTokenEvent::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
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
        ctx << getNextChunk(fmt, nextNewclonetokeneventChunk, this);
}

//---------------------------------------------------------------------------
string_q nextNewclonetokeneventChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const CNewCloneTokenEvent *>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CNewCloneTokenEvent::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    if (CLogEntry::setValueByName(fieldName, fieldValue))
        return true;

    switch (tolower(fieldName[0])) {
        case '_':
            if ( fieldName % "_cloneToken" ) { _cloneToken = str_2_Addr(fieldValue); return true; }
            if ( fieldName % "_snapshotBlock" ) { _snapshotBlock = str_2_Wei(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CNewCloneTokenEvent::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CNewCloneTokenEvent::Serialize(CArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CLogEntry::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> _cloneToken;
    archive >> _snapshotBlock;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CNewCloneTokenEvent::SerializeC(CArchive& archive) const {

    // Writing always write the latest version of the data
    CLogEntry::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << _cloneToken;
    archive << _snapshotBlock;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CNewCloneTokenEventArray& array) {
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
CArchive& operator<<(CArchive& archive, const CNewCloneTokenEventArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CNewCloneTokenEvent::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    CLogEntry::registerClass();

    size_t fieldNum = 1000;
    ADD_FIELD(CNewCloneTokenEvent, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CNewCloneTokenEvent, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CNewCloneTokenEvent, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CNewCloneTokenEvent, "cname", T_TEXT,  ++fieldNum);
    ADD_FIELD(CNewCloneTokenEvent, "_cloneToken", T_ADDRESS, ++fieldNum);
    ADD_FIELD(CNewCloneTokenEvent, "_snapshotBlock", T_NUMBER, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CNewCloneTokenEvent, "schema");
    HIDE_FIELD(CNewCloneTokenEvent, "deleted");
    HIDE_FIELD(CNewCloneTokenEvent, "showing");
    HIDE_FIELD(CNewCloneTokenEvent, "cname");

    builtIns.push_back(_biCNewCloneTokenEvent);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextNewclonetokeneventChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CNewCloneTokenEvent *newp = reinterpret_cast<const CNewCloneTokenEvent *>(dataPtr);
    if (newp) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, newp);
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
bool CNewCloneTokenEvent::readBackLevel(CArchive& archive) {

    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CNewCloneTokenEvent::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextNewclonetokeneventChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case '_':
            if ( fieldName % "_cloneToken" ) return addr_2_Str(_cloneToken);
            if ( fieldName % "_snapshotBlock" ) return bnu_2_Str(_snapshotBlock);
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CLogEntry::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CNewCloneTokenEvent& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

