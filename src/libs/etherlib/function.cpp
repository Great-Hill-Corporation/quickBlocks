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
#include "function.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CFunction, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextFunctionChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextFunctionChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CFunction::Format(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
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
        ctx << getNextChunk(fmt, nextFunctionChunk, this);
}

//---------------------------------------------------------------------------
string_q nextFunctionChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return ((const CFunction *)dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CFunction::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    if ( fieldName % "signature" ) {
        signature = getSignature(SIG_CANONICAL);
        return true;
    } else if (fieldName % "name") {
        name = fieldValue.Substitute("_","");
        return true;
    }
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "anonymous" ) { anonymous = str2Bool(fieldValue); return true; }
            break;
        case 'c':
            if ( fieldName % "constant" ) { constant = str2Bool(fieldValue); return true; }
            break;
        case 'e':
            if ( fieldName % "encoding" ) { encoding = fieldValue; return true; }
            break;
        case 'i':
            if ( fieldName % "inputs" ) {
                char *p = (char *)fieldValue.c_str();
                while (p && *p) {
                    CParameter item;
                    uint32_t nFields = 0;
                    p = item.parseJson(p, nFields);
                    if (nFields)
                        inputs[inputs.getCount()] = item;
                }
                return true;
            }
            break;
        case 'n':
            if ( fieldName % "name" ) { name = fieldValue; return true; }
            break;
        case 'o':
            if ( fieldName % "outputs" ) {
                char *p = (char *)fieldValue.c_str();
                while (p && *p) {
                    CParameter item;
                    uint32_t nFields = 0;
                    p = item.parseJson(p, nFields);
                    if (nFields)
                        outputs[outputs.getCount()] = item;
                }
                return true;
            }
            break;
        case 'p':
            if ( fieldName % "payable" ) { payable = str2Bool(fieldValue); return true; }
            break;
        case 's':
            if ( fieldName % "signature" ) { signature = fieldValue; return true; }
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
void CFunction::finishParse() {
    // EXISTING_CODE
    for (uint32_t i = 0 ; i < inputs.getCount() ; i++)
        hasAddrs |= (inputs[i].type == "address");
    signature = getSignature(SIG_CANONICAL);
    encoding  = encodeItem();
    // The input parameters need to have a name. If not, we provide one
    int cnt = 0;
    for (uint32_t i = 0 ; i < inputs.getCount() ; i++) {
        if (inputs[i].name.empty())
            inputs[i].name = "param_" + asString(cnt++);
    }
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CFunction::Serialize(SFArchive& archive) {

    if (archive.isWriting())
        return ((const CFunction*)this)->SerializeC(archive);

    // If we're reading a back level, read the whole thing and we're done.
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> name;
    archive >> type;
    archive >> anonymous;
    archive >> constant;
    archive >> payable;
    archive >> signature;
    archive >> encoding;
    archive >> inputs;
    archive >> outputs;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CFunction::SerializeC(SFArchive& archive) const {

    // Writing always write the latest version of the data
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << name;
    archive << type;
    archive << anonymous;
    archive << constant;
    archive << payable;
    archive << signature;
    archive << encoding;
    archive << inputs;
    archive << outputs;

    return true;
}

//---------------------------------------------------------------------------
void CFunction::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    uint32_t fieldNum = 1000;
    ADD_FIELD(CFunction, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CFunction, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CFunction, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CFunction, "name", T_TEXT, ++fieldNum);
    ADD_FIELD(CFunction, "type", T_TEXT, ++fieldNum);
    ADD_FIELD(CFunction, "anonymous", T_BOOL, ++fieldNum);
    ADD_FIELD(CFunction, "constant", T_BOOL, ++fieldNum);
    ADD_FIELD(CFunction, "payable", T_BOOL, ++fieldNum);
    ADD_FIELD(CFunction, "signature", T_TEXT, ++fieldNum);
    ADD_FIELD(CFunction, "encoding", T_TEXT, ++fieldNum);
    ADD_FIELD(CFunction, "inputs", T_OBJECT|TS_ARRAY, ++fieldNum);
    ADD_FIELD(CFunction, "outputs", T_OBJECT|TS_ARRAY, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CFunction, "schema");
    HIDE_FIELD(CFunction, "deleted");
    HIDE_FIELD(CFunction, "showing");

    // EXISTING_CODE
    HIDE_FIELD(CFunction, "indexed");
    HIDE_FIELD(CFunction, "anonymous");
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextFunctionChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CFunction *fun = (const CFunction *)dataPtr;
    if (fun) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            case 'h':
                if ( fieldIn % "hex" ) {
                    string_q ret = fun->name + "(";
                    for (uint32_t i = 0 ; i < fun->inputs.getCount() ; i++) {
                        ret += fun->inputs[i].type;
                        if (i < fun->inputs.getCount())
                            ret += ",";
                    }
                    ret += ")";
                    replace(ret, ",)", ")");
                    return (ret + "\t" + string2Hex(ret));

                } else if ( fieldIn % "hasAddrs" ) {
                    return asString(fun->hasAddrs);

                }
                break;
            case 'i':
                if ( fieldIn % "isBuiltin" ) {
                    return asString(fun->isBuiltin);
                }
                break;
            case 'o':
                if ( fieldIn % "origName" ) {
                    return fun->origName;
                }
                break;
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, fun);
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CFunction::handleCustomFormat(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
    // EXISTING_CODE
    // EXISTING_CODE
    return false;
}

//---------------------------------------------------------------------------
bool CFunction::readBackLevel(SFArchive& archive) {

    CBaseNode::readBackLevel(archive);
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CFunction::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextFunctionChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "anonymous" ) return asString(anonymous);
            break;
        case 'c':
            if ( fieldName % "constant" ) return asString(constant);
            break;
        case 'e':
            if ( fieldName % "encoding" ) return encoding;
            break;
        case 'i':
            if ( fieldName % "inputs" || fieldName % "inputsCnt" ) {
                uint32_t cnt = inputs.getCount();
                if (endsWith(fieldName, "Cnt"))
                    return asStringU(cnt);
                if (!cnt) return "";
                string_q retS;
                for (uint32_t i = 0 ; i < cnt ; i++) {
                    retS += inputs[i].Format();
                    retS += ((i < cnt - 1) ? ",\n" : "\n");
                }
                return retS;
            }
            break;
        case 'n':
            if ( fieldName % "name" ) return name;
            break;
        case 'o':
            if ( fieldName % "outputs" || fieldName % "outputsCnt" ) {
                uint32_t cnt = outputs.getCount();
                if (endsWith(fieldName, "Cnt"))
                    return asStringU(cnt);
                if (!cnt) return "";
                string_q retS;
                for (uint32_t i = 0 ; i < cnt ; i++) {
                    retS += outputs[i].Format();
                    retS += ((i < cnt - 1) ? ",\n" : "\n");
                }
                return retS;
            }
            break;
        case 'p':
            if ( fieldName % "payable" ) return asString(payable);
            break;
        case 's':
            if ( fieldName % "signature" ) return signature;
            break;
        case 't':
            if ( fieldName % "type" ) return type;
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CBaseNode::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CFunction& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    os << item.Format() << "\n";
    return os;
}

//---------------------------------------------------------------------------
const CBaseNode *CFunction::getObjectAt(const string_q& fieldName, uint32_t index) const {
    if ( fieldName % "inputs" && index < inputs.getCount() )
        return &inputs[index];
    if ( fieldName % "outputs" && index < outputs.getCount() )
        return &outputs[index];
    return NULL;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
//---------------------------------------------------------------------------
string_q CFunction::getSignature(uint64_t parts) const {
    uint32_t cnt = inputs.getCount();

    string_q nm = (origName.empty() ? name : origName);
    CStringExportContext ctx;
    ctx << (parts & SIG_FTYPE  ? "\t"+type+" " : "");
    ctx << (parts & SIG_FNAME  ? nm            : "");
    ctx << (parts & SIG_FSPACE ? string_q(' ', 35-type.length()-nm.length()) : "");
    ctx << (parts & SIG_FTYPE || parts & SIG_FNAME  ? "("    : "");
    for (uint32_t j = 0 ; j < cnt ; j++) {
        ctx << (parts & SIG_ITYPE    ? inputs[j].type : "");
        ctx << (parts & SIG_IINDEXED ? (inputs[j].indexed ? " indexed" : "") : "");
        ctx << (parts & SIG_INAME    ? " "+inputs[j].name : "");
        ctx << (parts & SIG_ITYPE    ? (j < cnt-1 ? "," : "") : "");
    }
    ctx << (parts & SIG_FTYPE || parts & SIG_FNAME  ? ")" : "");
    if (parts == SIG_ENCODE)
        ctx << (parts & SIG_ENCODE ? (parts & SIG_FNAME ? " " + encoding : encoding + " ") : "");
    else
        ctx << (parts & SIG_ENCODE ? " [" + encoding + "]" : "");
    if (verbose && parts != SIG_CANONICAL) {
        ctx << (anonymous ? " anonymous" : "");
        ctx << (constant  ? " constant" : "");
        ctx << (payable   ? " payable" : "");
    }

    replaceAll(ctx.str, " )", ")");
    return trim(ctx.str);
}

//-----------------------------------------------------------------------
string_q CFunction::encodeItem(void) const {
    string_q hex = string2Hex(signature);
    string_q ret;
extern bool getSha3(const string_q& hexIn, string_q& shaOut);
    getSha3(hex, ret);
    ret = (type == "event" ? ret : ret.substr(0,10));
    return ret;
}
// EXISTING_CODE
}  // namespace qblocks

