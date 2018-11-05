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
#include "buyrecipient.h"
#include "etherlib.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CBuyRecipient, CTransaction);

//---------------------------------------------------------------------------
static string_q nextBuyrecipientChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextBuyrecipientChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CBuyRecipient::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
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
        ctx << getNextChunk(fmt, nextBuyrecipientChunk, this);
}

//---------------------------------------------------------------------------
string_q nextBuyrecipientChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const CBuyRecipient *>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CBuyRecipient::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    if (CTransaction::setValueByName(fieldName, fieldValue))
        return true;

    switch (tolower(fieldName[0])) {
        case 'r':
            if ( fieldName % "recipient" ) { recipient = str_2_Addr(fieldValue); return true; }
            if ( fieldName % "r" ) { r = toLower(fieldValue); return true; }
            break;
        case 's':
            if ( fieldName % "s" ) { s = toLower(fieldValue); return true; }
            break;
        case 'v':
            if ( fieldName % "v" ) { v = (uint32_t)str_2_Uint(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CBuyRecipient::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CBuyRecipient::Serialize(CArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CTransaction::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> recipient;
    archive >> v;
    archive >> r;
    archive >> s;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CBuyRecipient::SerializeC(CArchive& archive) const {

    // Writing always write the latest version of the data
    CTransaction::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << recipient;
    archive << v;
    archive << r;
    archive << s;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CBuyRecipientArray& array) {
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
CArchive& operator<<(CArchive& archive, const CBuyRecipientArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CBuyRecipient::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    CTransaction::registerClass();

    size_t fieldNum = 1000;
    ADD_FIELD(CBuyRecipient, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CBuyRecipient, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CBuyRecipient, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CBuyRecipient, "cname", T_TEXT,  ++fieldNum);
    ADD_FIELD(CBuyRecipient, "recipient", T_ADDRESS, ++fieldNum);
    ADD_FIELD(CBuyRecipient, "v", T_NUMBER, ++fieldNum);
    ADD_FIELD(CBuyRecipient, "r", T_TEXT, ++fieldNum);
    ADD_FIELD(CBuyRecipient, "s", T_TEXT, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CBuyRecipient, "schema");
    HIDE_FIELD(CBuyRecipient, "deleted");
    HIDE_FIELD(CBuyRecipient, "showing");
    HIDE_FIELD(CBuyRecipient, "cname");

    builtIns.push_back(_biCBuyRecipient);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextBuyrecipientChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CBuyRecipient *buy = reinterpret_cast<const CBuyRecipient *>(dataPtr);
    if (buy) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, buy);
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
bool CBuyRecipient::readBackLevel(CArchive& archive) {

    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CBuyRecipient::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextBuyrecipientChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'r':
            if ( fieldName % "recipient" ) return addr_2_Str(recipient);
            if ( fieldName % "r" ) return r;
            break;
        case 's':
            if ( fieldName % "s" ) return s;
            break;
        case 'v':
            if ( fieldName % "v" ) return uint_2_Str(v);
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CTransaction::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CBuyRecipient& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

