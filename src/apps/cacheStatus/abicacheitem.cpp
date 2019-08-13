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
#include "abicacheitem.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CAbiCacheItem, CAccountName);

//---------------------------------------------------------------------------
static string_q nextAbicacheitemChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextAbicacheitemChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CAbiCacheItem::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
    if (!m_showing)
        return;

    string_q fmt = (fmtIn.empty() ? expContext().fmtMap["abicacheitem_fmt"] : fmtIn);
    if (fmt.empty()) {
        ctx << toJson();
        return;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextAbicacheitemChunk, this);
}

//---------------------------------------------------------------------------
string_q nextAbicacheitemChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const CAbiCacheItem *>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CAbiCacheItem::setValueByName(const string_q& fieldNameIn, const string_q& fieldValueIn) {
    string_q fieldName = fieldNameIn;
    string_q fieldValue = fieldValueIn;

    // EXISTING_CODE
    // EXISTING_CODE

    if (CAccountName::setValueByName(fieldName, fieldValue))
        return true;

    switch (tolower(fieldName[0])) {
        case 'n':
            if ( fieldName % "nFunctions" ) { nFunctions = str_2_Uint(fieldValue); return true; }
            if ( fieldName % "nEvents" ) { nEvents = str_2_Uint(fieldValue); return true; }
            if ( fieldName % "nOther" ) { nOther = str_2_Uint(fieldValue); return true; }
            break;
        case 't':
            if ( fieldName % "type" ) { type = fieldValue; return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CAbiCacheItem::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CAbiCacheItem::Serialize(CArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CAccountName::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> type;
    archive >> nFunctions;
    archive >> nEvents;
    archive >> nOther;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CAbiCacheItem::SerializeC(CArchive& archive) const {

    // Writing always write the latest version of the data
    CAccountName::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << type;
    archive << nFunctions;
    archive << nEvents;
    archive << nOther;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CAbiCacheItemArray& array) {
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
CArchive& operator<<(CArchive& archive, const CAbiCacheItemArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CAbiCacheItem::registerClass(void) {
    // only do this once
    if (HAS_FIELD(CAbiCacheItem, "schema")) return;

    CAccountName::registerClass();

    size_t fieldNum = 1000;
    ADD_FIELD(CAbiCacheItem, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CAbiCacheItem, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CAbiCacheItem, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CAbiCacheItem, "cname", T_TEXT,  ++fieldNum);
    ADD_FIELD(CAbiCacheItem, "type", T_TEXT, ++fieldNum);
    ADD_FIELD(CAbiCacheItem, "nFunctions", T_NUMBER, ++fieldNum);
    ADD_FIELD(CAbiCacheItem, "nEvents", T_NUMBER, ++fieldNum);
    ADD_FIELD(CAbiCacheItem, "nOther", T_NUMBER, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CAbiCacheItem, "schema");
    HIDE_FIELD(CAbiCacheItem, "deleted");
    HIDE_FIELD(CAbiCacheItem, "showing");
    HIDE_FIELD(CAbiCacheItem, "cname");

    builtIns.push_back(_biCAbiCacheItem);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextAbicacheitemChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CAbiCacheItem *abi = reinterpret_cast<const CAbiCacheItem *>(dataPtr);
    if (abi) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, abi);
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
bool CAbiCacheItem::readBackLevel(CArchive& archive) {

    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
CArchive& operator<<(CArchive& archive, const CAbiCacheItem& abi) {
    abi.SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CAbiCacheItem& abi) {
    abi.Serialize(archive);
    return archive;
}

//---------------------------------------------------------------------------
string_q CAbiCacheItem::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextAbicacheitemChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'n':
            if ( fieldName % "nFunctions" ) return uint_2_Str(nFunctions);
            if ( fieldName % "nEvents" ) return uint_2_Str(nEvents);
            if ( fieldName % "nOther" ) return uint_2_Str(nOther);
            break;
        case 't':
            if ( fieldName % "type" ) return type;
            break;
    }

    // EXISTING_CODE
    if ( fieldName % "firstAppearance" || fieldName % "latestAppearance" || fieldName % "nRecords" )
        return "";
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CAccountName::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CAbiCacheItem& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
}  // namespace qblocks

