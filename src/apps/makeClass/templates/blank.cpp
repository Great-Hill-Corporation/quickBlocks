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
#include "[{LONG}].h"
[OTHER_INCS]
[{NAMESPACE1}]
//---------------------------------------------------------------------------
IMPLEMENT_NODE([{CLASS_NAME}], [{BASE_CLASS}]);

//---------------------------------------------------------------------------
[{SCOPE}] string_q next[{PROPER}]Chunk(const string_q& fieldIn, const void *dataPtr);
static string_q next[{PROPER}]Chunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void [{CLASS_NAME}]::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
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
        ctx << getNextChunk(fmt, next[{PROPER}]Chunk, this);
}

//---------------------------------------------------------------------------
string_q next[{PROPER}]Chunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return ((const [{CLASS_NAME}] *)dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool [{CLASS_NAME}]::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

[{PARENT_SET}]
    switch (tolower(fieldName[0])) {
[FIELD_SETCASE]    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void [{CLASS_NAME}]::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool [{CLASS_NAME}]::Serialize(SFArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // If we're reading a back level, read the whole thing and we're done.
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
[ARCHIVE_READ]	finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool [{CLASS_NAME}]::SerializeC(SFArchive& archive) const {

    // Writing always write the latest version of the data
[{PARENT_SER2}]
    // EXISTING_CODE
    // EXISTING_CODE
[ARCHIVE_WRITE]
    return true;
}

//---------------------------------------------------------------------------
SFArchive& operator>>(SFArchive& archive, [{CLASS_NAME}]Array& array) {
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
SFArchive& operator<<(SFArchive& archive, const [{CLASS_NAME}]Array& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void [{CLASS_NAME}]::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    [{PARENT_REG}]size_t fieldNum = 1000;
    ADD_FIELD([{CLASS_NAME}], "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD([{CLASS_NAME}], "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD([{CLASS_NAME}], "showing", T_BOOL,  ++fieldNum);
[REGISTER_FIELDS]

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD([{CLASS_NAME}], "schema");
    HIDE_FIELD([{CLASS_NAME}], "deleted");
    HIDE_FIELD([{CLASS_NAME}], "showing");

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q next[{PROPER}]Chunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const [{CLASS_NAME}] *[{SHORT3}] = (const [{CLASS_NAME}] *)dataPtr;  // NOLINT
    if ([{SHORT3}]) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, [{SHORT3}]);
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
bool [{CLASS_NAME}]::readBackLevel(SFArchive& archive) {

    [{BASE_CLASS}]::[{PAR_READ_HEAD}](archive);
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

[{OPERATORS}]
//---------------------------------------------------------------------------
string_q [{CLASS_NAME}]::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = next[{PROPER}]Chunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    [{FIELD_CASE}]

    // EXISTING_CODE
    // EXISTING_CODE

[{SUBCLASSFLDS}]    // Finally, give the parent class a chance
    return [{BASE_CLASS}]::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const [{CLASS_NAME}]& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

[{GET_OBJ}][{GET_STR}]//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
[{NAMESPACE2}]
