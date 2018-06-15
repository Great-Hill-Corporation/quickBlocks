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
#include "traceaction.h"
#include "trace.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CTraceAction, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextTraceactionChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextTraceactionChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CTraceAction::Format(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
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
        ctx << getNextChunk(fmt, nextTraceactionChunk, this);
}

//---------------------------------------------------------------------------
string_q nextTraceactionChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return ((const CTraceAction *)dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CTraceAction::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "address" ) { address = toAddress(fieldValue); return true; }
            break;
        case 'b':
            if ( fieldName % "balance" ) { balance = toWei(fieldValue); return true; }
            break;
        case 'c':
            if ( fieldName % "callType" ) { callType = fieldValue; return true; }
            break;
        case 'f':
            if ( fieldName % "from" ) { from = toAddress(fieldValue); return true; }
            break;
        case 'g':
            if ( fieldName % "gas" ) { gas = toGas(fieldValue); return true; }
            break;
        case 'i':
            if ( fieldName % "init" ) { init = fieldValue; return true; }
            if ( fieldName % "input" ) { input = fieldValue; return true; }
            break;
        case 'r':
            if ( fieldName % "refundAddress" ) { refundAddress = toAddress(fieldValue); return true; }
            break;
        case 't':
            if ( fieldName % "to" ) { to = toAddress(fieldValue); return true; }
            break;
        case 'v':
            if ( fieldName % "value" ) { value = toWei(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CTraceAction::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CTraceAction::Serialize(SFArchive& archive) {

    if (archive.isWriting())
        return ((const CTraceAction*)this)->SerializeC(archive);

    // If we're reading a back level, read the whole thing and we're done.
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> address;
    archive >> balance;
    archive >> callType;
    archive >> from;
    archive >> gas;
    archive >> init;
    archive >> input;
    archive >> refundAddress;
    archive >> to;
    archive >> value;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CTraceAction::SerializeC(SFArchive& archive) const {

    // Writing always write the latest version of the data
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << address;
    archive << balance;
    archive << callType;
    archive << from;
    archive << gas;
    archive << init;
    archive << input;
    archive << refundAddress;
    archive << to;
    archive << value;

    return true;
}

//---------------------------------------------------------------------------
void CTraceAction::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    size_t fieldNum = 1000;
    ADD_FIELD(CTraceAction, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CTraceAction, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CTraceAction, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CTraceAction, "address", T_ADDRESS, ++fieldNum);
    ADD_FIELD(CTraceAction, "balance", T_WEI, ++fieldNum);
    ADD_FIELD(CTraceAction, "callType", T_TEXT, ++fieldNum);
    ADD_FIELD(CTraceAction, "from", T_ADDRESS, ++fieldNum);
    ADD_FIELD(CTraceAction, "gas", T_GAS, ++fieldNum);
    ADD_FIELD(CTraceAction, "init", T_TEXT, ++fieldNum);
    ADD_FIELD(CTraceAction, "input", T_TEXT, ++fieldNum);
    ADD_FIELD(CTraceAction, "refundAddress", T_ADDRESS, ++fieldNum);
    ADD_FIELD(CTraceAction, "to", T_ADDRESS, ++fieldNum);
    ADD_FIELD(CTraceAction, "value", T_WEI, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CTraceAction, "schema");
    HIDE_FIELD(CTraceAction, "deleted");
    HIDE_FIELD(CTraceAction, "showing");

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextTraceactionChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CTraceAction *tra = (const CTraceAction *)dataPtr;
    if (tra) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, tra);
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CTraceAction::handleCustomFormat(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
    // EXISTING_CODE
    // EXISTING_CODE
    return false;
}

//---------------------------------------------------------------------------
bool CTraceAction::readBackLevel(SFArchive& archive) {

    CBaseNode::readBackLevel(archive);
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
SFArchive& operator<<(SFArchive& archive, const CTraceAction& tra) {
    tra.SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
SFArchive& operator>>(SFArchive& archive, CTraceAction& tra) {
    tra.Serialize(archive);
    return archive;
}

//---------------------------------------------------------------------------
string_q CTraceAction::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextTraceactionChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "address" ) return fromAddress(address);
            break;
        case 'b':
            if ( fieldName % "balance" ) return fromWei(balance);
            break;
        case 'c':
            if ( fieldName % "callType" ) return callType;
            break;
        case 'f':
            if ( fieldName % "from" ) return fromAddress(from);
            break;
        case 'g':
            if ( fieldName % "gas" ) return fromGas(gas);
            break;
        case 'i':
            if ( fieldName % "init" ) return init;
            if ( fieldName % "input" ) return input;
            break;
        case 'r':
            if ( fieldName % "refundAddress" ) return fromAddress(refundAddress);
            break;
        case 't':
            if ( fieldName % "to" ) return fromAddress(to);
            break;
        case 'v':
            if ( fieldName % "value" ) return fromWei(value);
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CBaseNode::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CTraceAction& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    os << item.Format() << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
}  // namespace qblocks

