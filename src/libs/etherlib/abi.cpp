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
#include "abi.h"
#include "node.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CAbi, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextAbiChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextAbiChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CAbi::Format(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
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
        ctx << getNextChunk(fmt, nextAbiChunk, this);
}

//---------------------------------------------------------------------------
string_q nextAbiChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return ((const CAbi *)dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CAbi::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "abiByName" ) {
                char *p = (char *)fieldValue.c_str();
                while (p && *p) {
                    CFunction item;
                    uint32_t nFields = 0;
                    p = item.parseJson(p, nFields);
                    if (nFields)
                        abiByName[abiByName.getCount()] = item;
                }
                return true;
            }
            if ( fieldName % "abiByEncoding" ) {
                char *p = (char *)fieldValue.c_str();
                while (p && *p) {
                    CFunction item;
                    uint32_t nFields = 0;
                    p = item.parseJson(p, nFields);
                    if (nFields)
                        abiByEncoding[abiByEncoding.getCount()] = item;
                }
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CAbi::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CAbi::Serialize(SFArchive& archive) {

    if (archive.isWriting())
        return ((const CAbi*)this)->SerializeC(archive);

    // If we're reading a back level, read the whole thing and we're done.
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> abiByName;
    archive >> abiByEncoding;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CAbi::SerializeC(SFArchive& archive) const {

    // Writing always write the latest version of the data
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << abiByName;
    archive << abiByEncoding;

    return true;
}

//---------------------------------------------------------------------------
void CAbi::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    uint32_t fieldNum = 1000;
    ADD_FIELD(CAbi, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CAbi, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CAbi, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CAbi, "abiByName", T_OBJECT|TS_ARRAY, ++fieldNum);
    ADD_FIELD(CAbi, "abiByEncoding", T_OBJECT|TS_ARRAY, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CAbi, "schema");
    HIDE_FIELD(CAbi, "deleted");
    HIDE_FIELD(CAbi, "showing");

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextAbiChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CAbi *abi = (const CAbi *)dataPtr;
    if (abi) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, abi);
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CAbi::handleCustomFormat(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
    // EXISTING_CODE
    // EXISTING_CODE
    return false;
}

//---------------------------------------------------------------------------
bool CAbi::readBackLevel(SFArchive& archive) {

    CBaseNode::readBackLevel(archive);
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CAbi::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextAbiChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'a':
            if ( fieldName % "abiByName" || fieldName % "abiByNameCnt" ) {
                uint32_t cnt = abiByName.getCount();
                if (endsWith(fieldName, "Cnt"))
                    return asStringU(cnt);
                if (!cnt) return "";
                string_q retS;
                for (uint32_t i = 0 ; i < cnt ; i++) {
                    retS += abiByName[i].Format();
                    retS += ((i < cnt - 1) ? ",\n" : "\n");
                }
                return retS;
            }
            if ( fieldName % "abiByEncoding" || fieldName % "abiByEncodingCnt" ) {
                uint32_t cnt = abiByEncoding.getCount();
                if (endsWith(fieldName, "Cnt"))
                    return asStringU(cnt);
                if (!cnt) return "";
                string_q retS;
                for (uint32_t i = 0 ; i < cnt ; i++) {
                    retS += abiByEncoding[i].Format();
                    retS += ((i < cnt - 1) ? ",\n" : "\n");
                }
                return retS;
            }
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CBaseNode::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CAbi& item) {
    // EXISTING_CODE
    if (sizeof(item) != 0) { // do this to always go through here, but avoid a warning
        for (uint32_t i = 0 ; i < item.abiByName.getCount() ; i++ ) {
            os << item.abiByName[i].Format() << "\n";
        }
        for (uint32_t i = 0 ; i < item.abiByEncoding.getCount() ; i++ ) {
            os << item.abiByEncoding[i].Format() << "\n";
        }
        { return os; }
    }
    // EXISTING_CODE

    os << item.Format() << "\n";
    return os;
}

//---------------------------------------------------------------------------
const CBaseNode *CAbi::getObjectAt(const string_q& fieldName, uint32_t index) const {
    if ( fieldName % "abiByName" && index < abiByName.getCount() )
        return &abiByName[index];
    if ( fieldName % "abiByEncoding" && index < abiByEncoding.getCount() )
        return &abiByEncoding[index];
    return NULL;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
//---------------------------------------------------------------------------
int sortFuncTableByName(const void *ob1, const void *ob2) {
    CFunction *f1 = (CFunction*)ob1;
    CFunction *f2 = (CFunction*)ob2;
    return f2->name.compare(f1->name);
}

//---------------------------------------------------------------------------
int findByName(const void *rr1, const void *rr2) {
    CFunction *f1 = (CFunction*)rr1;
    CFunction *f2 = (CFunction*)rr2;
    return f2->name.compare(f1->name);
}

//---------------------------------------------------------------------------
int cleanCompare(const string_q& s1, const string_q& s2) {
    string_q ss1 = (startsWith(s1, "0x") ? s1.substr(2,8) : s1.substr(0,8));
    string_q ss2 = (startsWith(s2, "0x") ? s2.substr(2,8) : s2.substr(0,8));
    return ss2.compare(ss1);
}

//---------------------------------------------------------------------------
int sortFuncTableByEncoding(const void *ob1, const void *ob2) {
    CFunction *f1 = (CFunction*)ob1;
    CFunction *f2 = (CFunction*)ob2;
    return cleanCompare(f1->encoding, f2->encoding);
}

//---------------------------------------------------------------------------
int findByEncoding(const void *rr1, const void *rr2) {
    CFunction *f1 = (CFunction*)rr1;
    CFunction *f2 = (CFunction*)rr2;
    return cleanCompare(f1->encoding, f2->encoding);
}

//---------------------------------------------------------------------------
CFunction *CAbi::findFunctionByName(const string_q& name) {
    CFunction search;
    search.name = name;
    return abiByName.Find(&search, findByName);
}

//---------------------------------------------------------------------------
CFunction *CAbi::findFunctionByEncoding(const string_q& enc) {
    CFunction search;
    search.encoding = enc;
    return abiByEncoding.Find(&search, findByEncoding);
}

//---------------------------------------------------------------------------
void CAbi::clearABI(void) {
    abiByName.Clear();
    abiByEncoding.Clear();
}

//---------------------------------------------------------------------------
string_q abis[1000][2];
uint32_t nAbis = 0;

//---------------------------------------------------------------------------
void clearAbis(void) {
    nAbis = 0;
}

//---------------------------------------------------------------------------
string_q findEncoding(const string_q& addr, CFunction& func) {
    if (!nAbis) {
        string_q contents = asciiFileToString(blockCachePath("abis/" + addr + ".abi"));
        while (!contents.empty()) {
            abis[nAbis][1] = nextTokenClear(contents, '\n');
            abis[nAbis][0] = nextTokenClear(abis[nAbis][1], '|');
            nAbis++;
        }
    }

    for (uint64_t i = 0 ; i < nAbis ; i++)
        if (abis[i][0] == func.name)
            return abis[i][1];
    return EMPTY;
}

//---------------------------------------------------------------------------
static bool getEncoding(const string_q& abiFilename, const string_q& addr, CFunction& func) {
    if (func.type != "function")
        return false;
    func.name     = nextTokenClear(func.name, '(');
    func.encoding = findEncoding(addr, func);
    return !func.encoding.empty();
}

//---------------------------------------------------------------------------
bool CAbi::loadABIFromFile(const string_q& fileName) {

    string_q contents = asciiFileToString(fileName);
    ASSERT(!contents.empty());
    char *p = cleanUpJson((char *)contents.c_str());
    while (p && *p) {
        CFunction func;
        uint32_t nFields = 0;
        p = func.parseJson(p, nFields);
        if (nFields) {
            abiByName[abiByName.getCount()] = func;
            abiByEncoding[abiByEncoding.getCount()] = func;
        }
    }
    abiByName.Sort(sortFuncTableByName);
    abiByEncoding.Sort(sortFuncTableByEncoding);
    return abiByName.getCount();
}

//---------------------------------------------------------------------------
bool CAbi::loadABIFromCSV(const string_q& fileName) {
    CFunction::registerClass();
    CParameter::registerClass();
    HIDE_FIELD(CParameter, "indexed");
    HIDE_FIELD(CParameter, "isPointer");
    HIDE_FIELD(CParameter, "isArray");
    HIDE_FIELD(CParameter, "isObject");
    string_q contents = asciiFileToString(fileName);
    ASSERT(!contents.empty());
    while (!contents.empty()) {
        string_q json = nextTokenClear(contents,'\n');
        string_q encoding = nextTokenClear(json,'\t');
        CFunction func;
        uint32_t nFields = 0;
        char *p = cleanUpJson((char *)json.c_str());
        func.parseJson(p, nFields);
        if (nFields) {
            abiByEncoding[abiByEncoding.getCount()] = func;
            cout << func.encoding << ": " << func.name << ": " << func.inputs.getCount() << "\n";
        }
    }
    abiByEncoding.Sort(sortFuncTableByEncoding);
    return abiByEncoding.getCount();
}

//---------------------------------------------------------------------------
bool CAbi::loadABI(const string_q& addr) {
    // Already loaded?
    if (abiByName.getCount() && abiByEncoding.getCount())
        return true;

    string_q abiFilename = blockCachePath("abis/" + addr + ".json");
    if (!fileExists(abiFilename))
        return false;

    cerr << "\tLoading abi file: " << abiFilename << "...\n";
    if (loadABIFromFile(abiFilename)) {

        string_q abis1;

        // Get the encodings
        for (uint32_t i=0;i<abiByName.getCount();i++) {
            getEncoding(abiFilename, addr, abiByName[i]);
            abis1 += abiByName[i].Format("[{NAME}]|[{ENCODING}]\n");
        }

        // We need to do both since they are copies
        for (uint32_t i=0;i<abiByEncoding.getCount();i++) {
            getEncoding(abiFilename, addr, abiByEncoding[i]);
        }

        if (!fileExists(blockCachePath("abis/" + addr + ".abi")) && !abis1.empty())
            stringToAsciiFile(blockCachePath("abis/" + addr + ".abi"), abis1);

        if (verbose) {
            for (uint32_t i = 0 ; i < abiByName.getCount() ; i++) {
                CFunction *f = &abiByName[i];
                if (f->type == "function")
                    cerr << f->Format("[\"{NAME}|][{ENCODING}\"]").Substitute("\n", " ") << "\n";
            }
        }
    }
    return abiByName.getCount();
}

//---------------------------------------------------------------------------
bool visitABIs(const string_q& path, void *dataPtr) {

    if (endsWith(path, ".json")) {
        string_q *str = (string_q*)dataPtr;
        *str += (path+"\n");
    }
    return true;
}

//---------------------------------------------------------------------------
void rebuildFourByteDB(void) {

    string_q fileList;
    string_q abiPath = blockCachePath("abis/");
    cout << abiPath << "\n";
    forEveryFileInFolder(abiPath+"*", visitABIs, &fileList);

    CFunctionArray funcArray;
    while (!fileList.empty()) {
        string_q fileName = nextTokenClear(fileList, '\n');
        CAbi abi;
        abi.loadABIFromFile(fileName);
        for (uint32_t f = 0 ; f < abi.abiByEncoding.getCount() ; f++) {
            funcArray[funcArray.getCount()] = abi.abiByEncoding[f];
            cout << abi.abiByEncoding[f].encoding << " : " << abi.abiByEncoding[f].name << " : " << abi.abiByEncoding[f].signature << "\n";
        }
    }
    funcArray.Sort(sortFuncTableByEncoding);
    SFArchive funcCache(WRITING_ARCHIVE);
    if (funcCache.Lock(abiPath+"abis.bin", binaryWriteCreate, LOCK_CREATE)) {
        funcCache << funcArray;
        funcCache.Release();
    }
}

//---------------------------------------------------------------------------
static CFunctionArray *getABIArray(void) {

    static CFunctionArray *theArrayPtr = NULL;
    if (!theArrayPtr) {
        static CFunctionArray theArray;
        string_q abiPath = blockCachePath("abis/abis.bin");
        SFArchive funcCache(READING_ARCHIVE);
        if (funcCache.Lock(abiPath, binaryReadOnly, LOCK_WAIT)) {
            funcCache >> theArray;
            funcCache.Release();
        }
        theArrayPtr = &theArray;
    }
    return theArrayPtr;
}

//---------------------------------------------------------------------------
int cleanCompareI(const string_q& s1, const string_q& s2) {
    string_q ss1 = toLower(startsWith(s1, "0x") ? s1.substr(2,8) : s1.substr(0,8));
    string_q ss2 = toLower(startsWith(s2, "0x") ? s2.substr(2,8) : s2.substr(0,8));
    return ss2.compare(ss1);
}

//---------------------------------------------------------------------------
int findByEncodingI(const void *rr1, const void *rr2) {
    CFunction *f1 = (CFunction*)rr1;
    CFunction *f2 = (CFunction*)rr2;
    return cleanCompareI(f1->encoding, f2->encoding);
}

//---------------------------------------------------------------------------
CFunction *findFunctionByEncoding(const string_q& encoding) {
    CFunctionArray *array = getABIArray();
    if (array) {
        CFunction search;
        search.encoding = encoding;
        return array->Find(&search, findByEncodingI);
    }
    return NULL;
}
// EXISTING_CODE
}  // namespace qblocks

