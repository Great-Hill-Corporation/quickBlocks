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
#include "basetypes.h"
#include "biglib.h"
#include "basenode.h"
#include "sfarchive.h"
#include "exportcontext.h"
#include "conversions.h"
#include "version.h"
#include "testing.h"

namespace qblocks {

    //--------------------------------------------------------------------------------
    CRuntimeClass CBaseNode::classCBaseNode;
    static CBuiltIn _biBaseNode(&CBaseNode::classCBaseNode, "CBaseNode", sizeof(CBaseNode), NULL, NULL);

    //--------------------------------------------------------------------------------
    CBaseNode::CBaseNode(void) {
        initialize();
    }

    //--------------------------------------------------------------------------------
    CBaseNode::~CBaseNode(void) {
    }

    //--------------------------------------------------------------------------------
    void CBaseNode::initialize(void) {
        m_deleted  = false;
        m_schema = getVersionNum();
        m_showing = true;
    }

    //--------------------------------------------------------------------------------
    void CBaseNode::duplicate(const CBaseNode& bn) {
        m_deleted  = bn.m_deleted;
        m_schema = bn.m_schema;
        m_showing = bn.m_showing;
    }

    //--------------------------------------------------------------------------------
    bool CBaseNode::isDeleted(void) const {
        return (m_deleted);
    }

    //--------------------------------------------------------------------------------
    void CBaseNode::setDeleted(bool del) {
        m_deleted = del;
    }

    //--------------------------------------------------------------------------------
    bool CBaseNode::isKindOf(const CRuntimeClass* pClass) const {
        CRuntimeClass* pClassThis = getRuntimeClass();
        return pClassThis->IsDerivedFrom(pClass);
    }

    //--------------------------------------------------------------------------------
    CRuntimeClass* CBaseNode::getRuntimeClass() const {
        return &CBaseNode::classCBaseNode;
    }

    //--------------------------------------------------------------------------------
    string_q CBaseNode::getValueByName(const string_q& fieldName) const {

        switch (tolower(fieldName[0])) {
            case 'd':
                if ( fieldName % "deleted" ) return asStringU(m_deleted);
                break;
            case 's':
                if ( fieldName % "schema" ) return asStringU(m_schema);
                if ( fieldName % "showing" ) return asStringU(m_showing);
                break;
        }

        return "";
    }

    //--------------------------------------------------------------------------------
    char *CBaseNode::parseCSV(char *s, size_t& nFields, const string_q *fields) {
        nFields = 0;

        typedef enum { OUTSIDE = 0, INSIDE } parseState;
        parseState state = OUTSIDE;

        char *fieldVal = NULL;
        while (*s) {
            switch (state) {
                case OUTSIDE:
                    if (*s == '\"') {
                        state = INSIDE;
                        fieldVal = s+1;

                    } else if (*s == '\n') {
                        finishParse();
                        return (s+1);
                    }
                    s++;
                    break;

                case INSIDE:
                    if (*s == '\"') {
                        *s = '\0';
                        if (!this->setValueByName(fields[nFields++], fieldVal)) {
//                          fprintf(stderr, "Bad field name %s. Quitting...", fields[nFields-1].c_str());
//                          return NULL;
                        }
                        fieldVal = NULL;
                        state = OUTSIDE;

                    }
                    s++;
                    break;
            }
        }
        finishParse();
        return NULL;
    }

    //--------------------------------------------------------------------------------
    char *CBaseNode::parseText(char *s, size_t& nFields, const string_q *fields) {
        size_t max = nFields;
        nFields = 0;
        char *fieldVal = s;
        while (s && *s) {
            switch (*s) {
                case '\r':
                    break;
                case '\t':
                    *s = '\0';
                    this->setValueByName(fields[nFields++], fieldVal);
                    fieldVal = s+1;
                    break;
                case '\n':
                    *s = '\0';
                    this->setValueByName(fields[nFields++], fieldVal);
                    finishParse();
                    return s+1;
            }
            s++;
        }
        if (nFields < max)
            this->setValueByName(fields[nFields++], fieldVal);
        finishParse();
        return NULL;
    }

    //--------------------------------------------------------------------------------
    char *CBaseNode::parseJson(char *s) {
        size_t nFields = 0;
        return parseJson(s, nFields);
    }

//#define DEBUG_PARSER
#ifdef DEBUG_PARSER
    string_q tbs;
#endif

    //--------------------------------------------------------------------------------
    char *CBaseNode::parseJson(char *s, size_t& nFields) {
#ifdef DEBUG_PARSER
        string_q ss = s;
        string_q tt('-',25);
        tt += "\n";
        cout << tt << s << "\n" << tt;
        cout << tt << extract(ss, ss.find("{"),   300) << "\n" << tt;
        cout << tt << extract(ss, ss.length()-300,300) << "\n" << tt;
        cout.flush();
        tbs+="\t";
#endif
        typedef enum { OUTSIDE = 0, IN_NAME, IN_VAL } parseState;
        parseState state = OUTSIDE;

        char *fieldName = NULL;
        char *fieldVal = NULL;
        while (s && *s) {
            switch (state) {
                case OUTSIDE:
                    if (*s == '{')
                        state = IN_NAME;
                    s++;
                    break;

                case IN_NAME:
                    if (!fieldName) {
                        fieldName = s;

                    } else if (*s == ':') {
                        state = IN_VAL;
                        *s = '\0';
#ifdef DEBUG_PARSER
//                      printf("fn: %-10.10s fv: %-40.40s ---> %-60.60s\n" , fieldName, fieldVal, (s+1));
#endif
                    }
                    s++;
                    break;

                case IN_VAL:
                    fieldVal = s;
                    if (*s == '[') {  // array skip to end of array
                        fieldVal++;
                        s++;
                        int lev = 1;
                        bool done = false;
                        while (s && *s && !done) {
                            if (*s == '[') {
                                lev++;

                            } else if (lev == 1 && *s == ']') {
                                done = true;
                                if (*s == ']')
                                    lev--;
                                s--;  // remove the closing bracket

                            } else if (*s == ']') {
                                lev--;
                            }
                            s++;
                        }
                    } else {
                        int lev = 1;
                        bool done = false;
                        while (s && *s && !done) {
                            if (*s == '{') {
                                lev++;

                            } else if (lev == 1 && (*s == ',' || *s == '}')) {
                                done = true;
                                if (*s == '}')
                                    lev--;
                                s--;

                            } else if (*s == '}') {
                                lev--;
                            }
                            s++;
                        }
                    }
                    *s = '\0';
#ifdef DEBUG_PARSER
                    printf("%sfn: %-20.20s fv: %-60.60s ---> %-40.40s\n",
                           (const char*)tbs, fieldName, fieldVal, (s+1));
                    fflush(stdout);
#endif
                    nFields += this->setValueByName(fieldName, fieldVal);
                    fieldName = NULL;
                    fieldVal = NULL;
                    state = IN_NAME;
                    s++;
                    if (*s && *s == ',')
                        s++;
                    if (s && *s && (*s == '{' || *s == '}' || *s == ']')) {
                        finishParse();
#ifdef DEBUG_PARSER
                        replace(tbs, "\t", "");
#endif
                        return s;
                    }
                    break;
            }
        }
#ifdef DEBUG_PARSER
        replace(tbs, "\t", "");
#endif
        finishParse();
        return NULL;
    }

    //--------------------------------------------------------------------
    inline bool isWhiteSpace(char c) {
        // TODO: this is unsafe if the JSON contains preservable spaces. Since that is not the case with Ethereum data, it's okay
        return (c == '\0' || c == ' ' || c == '\n' || c == '\r' || c == '\t');
    }

    //--------------------------------------------------------------------------------
    char *cleanUpJson(char *s) {
        if (!s)
            return s;
        char *l = s, *start = s;
        while (*s) {
            if (!isWhiteSpace(*s) && *s != '\"') {  // zap all the white space and quotes
                *l = *s;
                l++;
            }
            s++;
        }
        *l = '\0';
        return start;
    }

    //---------------------------------------------------------------------------
    bool CBaseNode::readBackLevel(SFArchive& archive) {

        // The following code assumes we do not change the format of the header
        archive >> m_deleted;
        archive >> m_schema;
        archive >> m_showing;
        string_q str;
        archive >> str;
        ASSERT(str == string_q(getRuntimeClass()->getClassNamePtr()));

        // Return true if this is a back level version
        return true;
    }

    //---------------------------------------------------------------------------
    bool CBaseNode::Serialize(SFArchive& archive) {
        archive >> m_deleted;
        archive >> m_schema;
        archive >> m_showing;
        string_q str;
        archive >> str;
        ASSERT(str == string_q(getRuntimeClass()->getClassNamePtr()));
        return false;
    }

    //---------------------------------------------------------------------------
    bool CBaseNode::SerializeC(SFArchive& archive) const {

        // Not happy with this, but we must set the schema to the latest before we write data
        // since we always write the latest version to the hard drive.
        ((CBaseNode*)this)->m_schema = getVersionNum();

        archive << m_deleted;
        archive << m_schema;
        archive << m_showing;
        archive << getRuntimeClass()->getClassNamePtr();
        return false;
    }

    //---------------------------------------------------------------------------
    static CExportOptions expC;
    CExportOptions& expContext(void) {
        return expC;
    }

    //---------------------------------------------------------------------------
    void incIndent(void) {
        expC.lev++;
    }

    //---------------------------------------------------------------------------
    void decIndent(void) {
        expC.lev--;
    }

    //---------------------------------------------------------------------------
    string_q indent(void) {
        return string_q(expC.spcs*expC.lev, expC.tab);
    }

    extern string_q decBigNum(const string_q& str);
    //--------------------------------------------------------------------------------
    string_q CBaseNode::toJson1(void) const {
        return substitute(substitute(substitute(toJson(), "\t", " "), "\n", ""), "  ", " ");
    }

    //--------------------------------------------------------------------------------
    string_q CBaseNode::toJson(void) const {
        const CFieldList *fieldList = getRuntimeClass()->GetFieldList();
        if (!fieldList) {
            cerr << "No fieldList in " << getRuntimeClass()->m_ClassName
                << ". Did you register the class? Quitting...\n";
            cerr.flush();
            exit(0);
        }

        // TODO(tjayrush): THIS PER DISPLAY LOOKUP IS SLOW - THIS SHOULD ONLY BE DONE ONCE
        // If a class is not a direct decendent of CBaseNode we want to include the parent nodes' fields
        // in the list as well
        CRuntimeClass *pThis = getRuntimeClass();
        CRuntimeClass *pPar  = pThis->m_BaseClass;
        CRuntimeClass *pBase = GETRUNTIME_CLASS(CBaseNode);
        if (pPar != pBase) {
            CFieldList theList = *fieldList;
            const CFieldList *fieldListA = pPar->GetFieldList();
            if (fieldListA) {
                LISTPOS lPos = fieldListA->SFList<CFieldData *>::GetHeadPosition();
                while (lPos) {
                    CFieldData *fld = fieldListA->GetNext(lPos);
                    if (!fld->isHidden())
                        theList.AddTail(fld);
                }
            }
            return toJson(&theList);
        }
        return toJson(fieldList);
    }

    //--------------------------------------------------------------------------------
    string_q CBaseNode::toJson(const string_q& fieldStrIn) const {

        CRuntimeClass *pClass = getRuntimeClass();
        if (!pClass)
            return "";

        const CFieldList *fieldList = pClass->GetFieldList();
        if (!fieldList) {
            cerr << "No fieldList in " << pClass->m_ClassName << ". Did you register the class?\n";
            return "";
        }

        vector<CFieldData*> fields;
        string_q fieldStr = fieldStrIn;
        while (!fieldStr.empty()) {
            string_q field = nextTokenClear(fieldStr, '|');
            CFieldData *fld = pClass->findField(field);
            if (!fld)
                cerr << "Could not find field " << field << " in class " << pClass->m_ClassName << ".\n";
            else
                fields.push_back(fld);
        }

        CFieldList theList;
        for (auto fld : fields)
            theList.AddTail(fld);

        return toJson(&theList);
    }

    //--------------------------------------------------------------------------------
    string_q CBaseNode::toJsonFldList(const CFieldList *fieldList) const {
        string_q ret;
        bool first = true;
        if (!expContext().noFrst)
            ret += indent();
        expContext().noFrst = false;
        LISTPOS lPos = fieldList->SFList<CFieldData *>::GetHeadPosition();
        while (lPos) {
            incIndent();
            CFieldData *fld = fieldList->GetNext(lPos);
            string_q val = getValueByName(fld->m_fieldName);
            if (!fld->isHidden() && (!val.empty() || fld->isArray())) {
                if (!first) {
                    if (expContext().colored)
                        ret += "#";
                    ret += ",\n";
                } else {
                    ret += "\n";
                }
                first = false;
                ret += indent();
                ret += "\"" + fld->m_fieldName + "\"";
                ret += ": ";
                if (expContext().colored)
                    ret += "%";
                if (fld->isArray()) {
                    incIndent();
                    val = substitute(getValueByName(fld->m_fieldName), "\n{", "\n"+indent()+"{");
                    ret += (val.empty() ? "[]" : "[\n" + indent() + val);
                    decIndent();
                    ret += (val.empty() ? "" : indent() + "]");

                } else if (fld->isObject()) {
                    ret += val;

                } else if (fld->m_fieldType == T_BLOOM) {
                    ret += "\"" + val + "\"";


                } else if (fld->m_fieldType & TS_NUMERAL) {
                    if (expContext().quoteNums) ret += "\"";
                    ret += (expContext().hexNums) ? toHex(val) : decBigNum(val);
                    if (expContext().quoteNums) ret += "\"";

                } else if (val == "null") {
                    ret += val;

                } else {
                    ret += "\"" + val + "\"";
                }
            }
            decIndent();
        }

        return ret;
    }

    //--------------------------------------------------------------------------------
    string_q CBaseNode::toJson(const CFieldList *fieldList) const {
        ASSERT(fieldList);
        string_q ret;
        ret += "{";
        ret += trim(toJsonFldList(fieldList));
        ret += "\n";
        ret += indent();
        ret += "}";
        return ret;
    }

    //--------------------------------------------------------------------------------
    string_q decBigNum(const string_q& str) {
        string_q ret = str;
        size_t len = ret.length();
             if (len > 29) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+29";
        else if (len > 28) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+28";
        else if (len > 27) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+27";
        else if (len > 26) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+26";
        else if (len > 25) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+25";
        else if (len > 24) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+24";
        else if (len > 23) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+23";
        else if (len > 22) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+22";
        else if (len > 21) ret = extract(ret, 0, 1) + "." + trimTrailing(extract(ret, 1), '0') + "e+21";
        replace(ret, ".e+", "e+");
        return ret;
    }

    //--------------------------------------------------------------------------------
    string_q nextBasenodeChunk(const string_q& fieldIn, const CBaseNode *node) {
        if (node) {
            string_q className = node->getRuntimeClass()->getClassNamePtr();
            switch (tolower(fieldIn[0])) {
                case 'd':
                    if ( fieldIn % "deleted" ) return asString(node->isDeleted());
                    break;
                case 'n':
                    if ( fieldIn % "null" ) return "<x>";
                    break;
                case 'p':
                    if ( fieldIn % "parsed" ) {
                        const CFieldList *fieldList = node->getRuntimeClass()->GetFieldList();
                        if (!fieldList) {
                            cerr << "No fieldList in " << node->getRuntimeClass()->m_ClassName
                                << ". Did you register the class? Quitting...\n";
                            cerr.flush();
                            exit(0);
                        }
                        string_q ret;
                        ret += "{";
                        ret += node->toJsonFldList(fieldList);
                        ret += "}";
                        return substitute(ret, "\n", "");;
                    }
                    break;
                case 's':
                    if ( fieldIn % "schema" ) return asStringU(node->m_schema);
                    if ( fieldIn % "showing" ) return asStringU(node->m_showing);
                    break;
                default:
                    break;
            }
        }

        return EMPTY;
    }

    //---------------------------------------------------------------------------------------------
    string_q getNextChunk(string_q& fmtOut, NEXTCHUNKFUNC func, const void *data) {
        string_q chunk = fmtOut;
        if (!contains(fmtOut, "[")) {
            // There are no more tokens.  Return the last chunk and empty out the format
            fmtOut = EMPTY;
            return chunk;
        }

        if (!startsWith(fmtOut, '[')) {
            // We've encountered plain text outside of a token. There is more to process so grab
            // the next chunk and then prepare the remaining chunk by prepending the token.
            // The next time through we will hit the token.
            chunk  = nextTokenClear(fmtOut, '[', false);
            fmtOut = "[" + fmtOut;
            return chunk;
        }

        // We've hit a token, toss the start token, look for a field and toss the last token
        // leaving the remainder of the format in fmtOut.  A field is found if we find a pair
        // of squigglies).  Save text inside the start token and outside the field in pre and post
        ASSERT(startsWith(fmtOut, '['));

        string_q pre, fieldName, post;
        nextTokenClear(fmtOut, '[', false);  // toss the start token
        if (contains(chunk, "{")) {
            // we've encountered a field
            pre       = nextTokenClear(fmtOut, '{', false);
            fieldName = nextTokenClear(fmtOut, '}', false);
            post      = nextTokenClear(fmtOut, ']', false);
        } else {
            // we've encountered a token with no field inside of it.  Just pull off
            // the entire contents into post.  It will be returned just below.
            post = nextTokenClear(fmtOut, ']', false);
        }

        // Either no squigglies were found or an empty pair of squigglies were found.  In either
        // case return surrounding text (text inside the token and outside the squiggles)
        if (fieldName.empty())
            return pre + post;

        // We have a field so lets process it.
        ASSERT(fieldName.length() >= 2);
        bool isPrompt = false;

        // The fieldname may contain b: in which case the field is a bool. Display only 'true' values
        // (in other words, false is same as empty)
        bool isBool = false;
        if (contains(fieldName, "b:")) {
            isBool = true;
            replace(fieldName, "b:", EMPTY);
        }

        // The fieldname may contain p: or w:width: or both.  If it contains either it
        // must contain them at the beginning of the string (before the fieldName).  Anything
        // left after the last ':' is considered the fieldName
        string_q promptName = fieldName;
        if (contains(fieldName, "p:")) {
            isPrompt = true;
            replace(fieldName, "p:", EMPTY);
            promptName = fieldName;
        }

        size_t maxWidth = 0xdeadbeef, lineWidth = 0xdeadbeef;
        bool rightJust = false, lineJust = false;
        if (contains(fieldName, "w:")) {
            ASSERT(extract(fieldName, 0, 2) % "w:");  // must be first modifier in the string
            replace(fieldName, "w:", EMPTY);   // get rid of the 'w:'
            maxWidth = toLongU(fieldName);   // grab the width
            nextTokenClear(fieldName, ':');    // skip to the start of the fieldname
        } else if (contains(fieldName, "r:")) {
            ASSERT(extract(fieldName, 0, 2) % "r:");  // must be first modifier in the string
            replace(fieldName, "r:", EMPTY);   // get rid of the 'w:'
            maxWidth = toLongU(fieldName);   // grab the width
            nextTokenClear(fieldName, ':');    // skip to the start of the fieldname
            rightJust = true;
        } else if (contains(fieldName, "l:")) {
            ASSERT(extract(fieldName, 0, 2) % "l:");  // must be first modifier in the string
            replace(fieldName, "l:", "");   // get rid of the 'w:'
            lineWidth = toLongU(fieldName);   // grab the width
            nextTokenClear(fieldName, ':');    // skip to the start of the fieldname
            lineJust = true;
        }

        //--------------------------------------------------------------------
#define truncPad(str, size)  (size == 0xdeadbeef ? str : padRight(extract(str, 0, size), size))
#define truncPadR(str, size) (size == 0xdeadbeef ? str : padLeft (extract(str, 0, size), size))

        // Get the value of the field.  If the value of the field is empty we return empty for the entire token.
        string_q fieldValue = (func)(fieldName, data);
        if (isBool && fieldValue == "0")
            fieldValue = "";
        if (!isPrompt && fieldValue.empty())
            return EMPTY;
        if (isBool) // we know it's true, so we want to only show the pre and post
            fieldValue = "";
        if (rightJust) {
            fieldValue = truncPadR(fieldValue, maxWidth);  // pad or truncate
        } else {
            fieldValue = truncPad(fieldValue, maxWidth);  // pad or truncate
        }
        if (lineJust) {
extern string_q reformat1(const string_q& in, size_t len);
            fieldValue = reformat1(fieldValue, lineWidth);
        }

        // The field is not hidden, the value of the field is not empty, we are not working
        // on a prompt, so we toss back the token referencing the value of the field.
        if (!isPrompt)
            return pre + fieldValue + post;

        // We are working on a prompt.  Pick up customizations if any
        string_q prompt = promptName;
        if (rightJust) {
            prompt = truncPadR(prompt, maxWidth);  // pad or truncate
        } else {
            prompt = truncPad(prompt, maxWidth);  // pad or truncate
        }
        return pre + prompt + post;
    }

    //--------------------------------------------------------------------------------
    string_q fldNotFound(const string_q& str) {
        return "Field not found: " + str + "\n";
    }

    //--------------------------------------------------------------------------------
    void CBaseNode::doExport(ostream& os) const {

        CFieldList *list = getRuntimeClass()->GetFieldList();
        LISTPOS pos;

        CFieldData *lastVisible = NULL;
        pos = list->GetHeadPosition();
        while (pos) {
            CFieldData *field = list->GetNext(pos);
            if (!field->isHidden())
                lastVisible = field;
        }

        os << "{\n";
        incIndent();
        pos = list->GetHeadPosition();
        while (pos) {
            CFieldData *field = list->GetNext(pos);
            if (!field->isHidden()) {
                string_q name = field->getName();
                os << indent() << "\"" << name << "\": ";
                if (field->isArray()) {
                    uint64_t cnt = toLongU(getValueByName(name+"Cnt"));
                    os << "[";
                    if (cnt) {
                        incIndent();
                        os << "\n";
                        for (size_t i = 0 ; i < cnt ; i++) {
                            os << indent();
                            const CBaseNode *node = getObjectAt(name, i);
                            if (node) {
                                node->doExport(os);
                            } else {
                                os << "\"" << getStringAt(name, i) << "\"";
                            }
                            if (i < cnt-1)
                                os << ",";
                            os << "\n";
                        }
                        decIndent();
                        os << indent();
                    }
                    os << "]";
                } else if (field->isObject()) {
                    const CBaseNode *node = getObjectAt(name, 0);
                    if (node) {
                        node->doExport(os);
                    } else {
                        os << getValueByName(name);
                    }
                } else {
                    string_q val = getValueByName(name);
                    bool isNum = field->m_fieldType & TS_NUMERAL;
                    if (isNum && expContext().hexNums && !startsWith(val, "0x"))
                        val = toHex(val);
                    bool quote = (!isNum || expContext().quoteNums) && val != "null";
                    if (quote)
                        os << "\"";
                    os << val;
                    if (quote)
                        os << "\"";
                }
                if (field != lastVisible)
                    os << ",";
                os << "\n";
            }
        }
        decIndent();
        os << indent();
        os << "}";
    }

    //-----------------------------------------------------------------------
    string_q reformat1(const string_q& in, size_t len) {
        string_q ret = in;
        if (ret.length() > len+10) {
            CStringArray parts;
            while (!ret.empty()) {
                string_q s = extract(ret, 0, len);
                replace(ret, s, "");
                if (s.length() == len) {
                    s += "...";
                    s += "\r\n\t\t\t    ";
                }
                parts.push_back(s);
            }
            ASSERT(ret.empty());
            for (size_t i = 0 ; i < parts.size() ; i++)
                ret += parts[i];
        }
        return ret;
    }
}  // namespace qblocks

uint64_t testing::Test::nFuncs;
testing::PF testing::Test::funcs[];

