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
#include "accountname.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CAccountName, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextAccountnameChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextAccountnameChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CAccountName::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
    if (!m_showing)
        return;

    string_q fmt = (fmtIn.empty() ? expContext().fmtMap["accountname_fmt"] : fmtIn);
    if (fmt.empty()) {
        ctx << toJson();
        return;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextAccountnameChunk, this);
}

//---------------------------------------------------------------------------
string_q nextAccountnameChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const CAccountName *>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CAccountName::setValueByName(const string_q& fieldNameIn, const string_q& fieldValueIn) {
    string_q fieldName = fieldNameIn;
    string_q fieldValue = fieldValueIn;

    // EXISTING_CODE
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "address" ) { address = fieldValue; return true; }
            break;
        case 'c':
            if ( fieldName % "color" ) { color = fieldValue; return true; }
            break;
        case 'd':
            if ( fieldName % "description" ) { description = fieldValue; return true; }
            break;
        case 'f':
            if ( fieldName % "firstAppearance" ) { firstAppearance = str_2_Uint(fieldValue); return true; }
            break;
        case 'g':
            if ( fieldName % "group" ) { group = fieldValue; return true; }
            break;
        case 'i':
            if ( fieldName % "is_contract" ) { is_contract = str_2_Bool(fieldValue); return true; }
            if ( fieldName % "is_custom" ) { is_custom = str_2_Bool(fieldValue); return true; }
            if ( fieldName % "is_shared" ) { is_shared = str_2_Bool(fieldValue); return true; }
            break;
        case 'l':
            if ( fieldName % "logo" ) { logo = fieldValue; return true; }
            if ( fieldName % "lastAppearance" ) { lastAppearance = str_2_Uint(fieldValue); return true; }
            if ( fieldName % "lastExport" ) { lastExport = str_2_Uint(fieldValue); return true; }
            break;
        case 'n':
            if ( fieldName % "name" ) { name = fieldValue; return true; }
            if ( fieldName % "nRecords" ) { nRecords = str_2_Uint(fieldValue); return true; }
            break;
        case 'p':
            if ( fieldName % "path" ) { path = fieldValue; return true; }
            break;
        case 's':
            if ( fieldName % "symbol" ) { symbol = fieldValue; return true; }
            if ( fieldName % "source" ) { source = fieldValue; return true; }
            if ( fieldName % "sizeInBytes" ) { sizeInBytes = str_2_Uint(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CAccountName::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CAccountName::Serialize(CArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CBaseNode::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> group;
    archive >> name;
    archive >> address;
    archive >> symbol;
    archive >> description;
    archive >> source;
    archive >> logo;
//    archive >> path;
//    archive >> color;
//    archive >> is_contract;
//    archive >> is_custom;
//    archive >> is_shared;
//    archive >> firstAppearance;
//    archive >> lastAppearance;
//    archive >> lastExport;
//    archive >> nRecords;
//    archive >> sizeInBytes;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CAccountName::SerializeC(CArchive& archive) const {

    // Writing always write the latest version of the data
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << group;
    archive << name;
    archive << address;
    archive << symbol;
    archive << description;
    archive << source;
    archive << logo;
//    archive << path;
//    archive << color;
//    archive << is_contract;
//    archive << is_custom;
//    archive << is_shared;
//    archive << firstAppearance;
//    archive << lastAppearance;
//    archive << lastExport;
//    archive << nRecords;
//    archive << sizeInBytes;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CAccountNameArray& array) {
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
CArchive& operator<<(CArchive& archive, const CAccountNameArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CAccountName::registerClass(void) {
    // only do this once
    if (HAS_FIELD(CAccountName, "schema")) return;

    size_t fieldNum = 1000;
    ADD_FIELD(CAccountName, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CAccountName, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CAccountName, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CAccountName, "cname", T_TEXT,  ++fieldNum);
    ADD_FIELD(CAccountName, "group", T_TEXT, ++fieldNum);
    ADD_FIELD(CAccountName, "name", T_TEXT, ++fieldNum);
    ADD_FIELD(CAccountName, "address", T_TEXT, ++fieldNum);
    ADD_FIELD(CAccountName, "symbol", T_TEXT, ++fieldNum);
    ADD_FIELD(CAccountName, "description", T_TEXT, ++fieldNum);
    ADD_FIELD(CAccountName, "source", T_TEXT, ++fieldNum);
    ADD_FIELD(CAccountName, "logo", T_TEXT, ++fieldNum);
    ADD_FIELD(CAccountName, "path", T_TEXT, ++fieldNum);
    HIDE_FIELD(CAccountName, "path");
    ADD_FIELD(CAccountName, "color", T_TEXT, ++fieldNum);
    HIDE_FIELD(CAccountName, "color");
    ADD_FIELD(CAccountName, "is_contract", T_BOOL, ++fieldNum);
    HIDE_FIELD(CAccountName, "is_contract");
    ADD_FIELD(CAccountName, "is_custom", T_BOOL, ++fieldNum);
    HIDE_FIELD(CAccountName, "is_custom");
    ADD_FIELD(CAccountName, "is_shared", T_BOOL, ++fieldNum);
    HIDE_FIELD(CAccountName, "is_shared");
    ADD_FIELD(CAccountName, "firstAppearance", T_NUMBER, ++fieldNum);
    HIDE_FIELD(CAccountName, "firstAppearance");
    ADD_FIELD(CAccountName, "lastAppearance", T_NUMBER, ++fieldNum);
    HIDE_FIELD(CAccountName, "lastAppearance");
    ADD_FIELD(CAccountName, "lastExport", T_NUMBER, ++fieldNum);
    HIDE_FIELD(CAccountName, "lastExport");
    ADD_FIELD(CAccountName, "nRecords", T_NUMBER, ++fieldNum);
    HIDE_FIELD(CAccountName, "nRecords");
    ADD_FIELD(CAccountName, "sizeInBytes", T_NUMBER, ++fieldNum);
    HIDE_FIELD(CAccountName, "sizeInBytes");

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CAccountName, "schema");
    HIDE_FIELD(CAccountName, "deleted");
    HIDE_FIELD(CAccountName, "showing");
    HIDE_FIELD(CAccountName, "cname");

    builtIns.push_back(_biCAccountName);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextAccountnameChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CAccountName *acc = reinterpret_cast<const CAccountName *>(dataPtr);
    if (acc) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, acc);
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
bool CAccountName::readBackLevel(CArchive& archive) {

    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CAccountName::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextAccountnameChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "address" ) return address;
            break;
        case 'c':
            if ( fieldName % "color" ) return color;
            break;
        case 'd':
            if ( fieldName % "description" ) return description;
            break;
        case 'f':
            if ( fieldName % "firstAppearance" ) return uint_2_Str(firstAppearance);
            break;
        case 'g':
            if ( fieldName % "group" ) return group;
            break;
        case 'i':
            if ( fieldName % "is_contract" ) return bool_2_Str(is_contract);
            if ( fieldName % "is_custom" ) return bool_2_Str(is_custom);
            if ( fieldName % "is_shared" ) return bool_2_Str(is_shared);
            break;
        case 'l':
            if ( fieldName % "logo" ) return logo;
            if ( fieldName % "lastAppearance" ) return uint_2_Str(lastAppearance);
            if ( fieldName % "lastExport" ) return uint_2_Str(lastExport);
            break;
        case 'n':
            if ( fieldName % "name" ) return name;
            if ( fieldName % "nRecords" ) return uint_2_Str(nRecords);
            break;
        case 'p':
            if ( fieldName % "path" ) return path;
            break;
        case 's':
            if ( fieldName % "symbol" ) return symbol;
            if ( fieldName % "source" ) return source;
            if ( fieldName % "sizeInBytes" ) return uint_2_Str(sizeInBytes);
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CBaseNode::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CAccountName& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
CAccountName::CAccountName(const string_q& strIn) {
    string str = substitute(substitute(trim(strIn, '\t'), "\n", ""), "\r", "");

    CStringArray parts;
    explode(parts, str, '\t');
    if (parts.size() > 0) { group = parts[0]; }
    if (parts.size() > 1) { address = toLower(parts[1]); }
    if (parts.size() > 2) { name = parts[2]; }
    if (parts.size() > 3) { description = parts[3]; }
    if (parts.size() > 4) { symbol = parts[4]; }
    if (parts.size() > 5) { source = parts[5]; }
    if (parts.size() > 6) { logo = parts[6]; }
    if (parts.size() > 7) { is_contract = str_2_Bool(parts[7]); }
    if (parts.size() > 8) { is_custom = str_2_Bool(parts[8]); }
    if (parts.size() > 9) { is_shared = str_2_Bool(parts[9]); }
}
// EXISTING_CODE
}  // namespace qblocks

