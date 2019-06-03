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
#include "basetypes.h"

#include "toml.h"
#include "conversions.h"
#include "version.h"
#include "sfstring.h"

namespace qblocks {

//#ifndef NEW_TOML
    //-------------------------------------------------------------------------
    CToml::CToml(const string_q& fileName) : CSharedResource() {
        setFilename(fileName);
        if (!fileName.empty())
            readFile(fileName);
    }

    //-------------------------------------------------------------------------
    CToml::~CToml(void) {
        clear();
    }

    //-------------------------------------------------------------------------
    void CToml::clear(void) {
        groups.clear();
    }

    //-------------------------------------------------------------------------
    void CToml::addGroup(const string_q& group, bool commented, bool array) {
        if (findGroup(group))
            return;
        CTomlGroup newGroup(group, array, commented);
        groups.push_back(newGroup);
    }

    //-------------------------------------------------------------------------
    CToml::CTomlGroup *CToml::findGroup(const string_q& group) const {
//        string_q search = (group.empty() ? "root-level" : group);
        for (size_t i = 0 ; i < groups.size() ; i++) {
            if (groups[i].groupName == group) {
                return &((CToml*)this)->groups[i];  // NOLINT
                }
            }
        return NULL;
    }

    //-------------------------------------------------------------------------
    void CToml::addKey(const string_q& group, const string_q& key, const string_q& val, bool commented) {
        CTomlGroup *grp = findGroup(group);
        if (grp)
            grp->addKey(key, val, commented);
        return;
    }

    //-------------------------------------------------------------------------
    CToml::CTomlKey *CToml::findKey(const string_q& group, const string_q& keyIn) const {
        CTomlGroup *grp = findGroup(group);
        if (grp) {
            for (size_t i = 0 ; i < grp->keys.size() ; i++)
                if (grp->keys[i].keyName == keyIn)
                    return &grp->keys[i];
        }
        return NULL;
    }

    //-------------------------------------------------------------------------
    uint64_t CToml::getConfigInt(const string_q& group, const string_q& key, uint64_t def) const {
        string_q ret = getConfigStr(group, key, uint_2_Str(def));
        return str_2_Uint(ret);
    }

    //-------------------------------------------------------------------------
    bool CToml::getConfigBool(const string_q& group, const string_q& key, bool def) const {
        string_q ret = getConfigStr(group, key, int_2_Str(def?1:0));
        replaceAny(ret, ";\t\n\r ", "");
        return ((ret == "true" || ret == "1") ? true : false);
    }

    //---------------------------------------------------------------------------------------
extern string_q stripFullLineComments(const string_q& inStr);
extern string_q collapseArrays(const string_q& inStr);
    bool CToml::readFile(const string_q& filename) {
        string_q curGroup;
        clear();

        string_q contents;
        asciiFileToString(filename, contents);
        replaceAll(contents, "\\\n ", "\\\n");  // if ends with '\' + '\n' + space, make it just '\' + '\n'
        replaceAll(contents, "\\\n", "");       // if ends with '\' + '\n', its a continuation, so fold in
        replaceAll(contents, "\\\r\n", "");     // same for \r\n
        contents = collapseArrays(stripFullLineComments(contents));
        while (!contents.empty()) {
            string_q value = trimWhitespace(nextTokenClear(contents, '\n'));
            bool comment = startsWith(value, '#');
            if (comment)
                value = extract(value, 1);
            if (!value.empty()) {
                bool isArray = contains(value, "[[");
                if (startsWith(value, '[')) {  // it's a group
                    value = trim(trimWhitespace(substitute(substitute(value, "[", ""), "]", "")),'\"');
                    addGroup(value, comment, isArray);
                    curGroup = value;

                } else {
                    if (curGroup.empty()) {
                        string_q group = "root-level";
                        addGroup(group, false, false);
                        curGroup = group;
                    }
                    string_q key = nextTokenClear(value, '=');  // value may be empty, but not whitespace
                    addKey(curGroup, trimWhitespace(key), trimWhitespace(value), comment);
                }
            }
        }
//        sort(groups.begin(), groups.end());
//        for (auto& group : groups)
//            sort(group.keys.begin(), group.keys.end());
//
        return true;
    }

    //---------------------------------------------------------------------------------------
    bool is_str(const string_q& str) {
        if (str.empty())
            return true;
        if (startsWith(str, '['))
            return false;
        if (isAddress(str))
            return true;
        if (isdigit(str[0]))
            return false;
        if (str == "true" || str == "false")
            return false;
        return true;
    }

    string_q escape_quotes(const string_q& str) {
        string_q res;
        for (auto it = str.begin(); it != str.end(); ++it) {
            if (*it == '"' )
                res += "\\";
            res += *it;
        }
        return res;
    }

    //---------------------------------------------------------------------------------------
    bool CToml::writeFile(void) {
        if (!Lock(m_filename, modeWriteCreate, LOCK_CREATE)) {
            LockFailure();
            return false;
        }

        if (isBackLevel()) {
            // remove some old crap
            deleteKey("version", "version");
            deleteKey("", "version");
        }
        setConfigStr("version", "current", getVersionStr(false,false));

        bool first = true;
        for (auto group : groups) {
            ostringstream os;
            os << (first?"":"\n") << (group.isComment?"#":"");
            os << (group.isArray?"[[":"[") << group.groupName << (group.isArray?"]]":"]") << "\n";
            for (auto key : group.keys) {
                if (!key.deleted) {
                    os << (key.comment ? "#" : "");
                    os << key.keyName << " = ";
                    if (group.groupName == "version" || is_str(key.value))
                        os << "\"";
                    os << escape_quotes(key.value);
                    if (group.groupName == "version" || is_str(key.value))
                        os << "\"";
                    os << (key.deleted ? " (deleted)" : "");
                    os << endl;
                }
            }
            WriteLine(os.str().c_str());
            first = false;
        }
        Release();
        return true;
    }

    //---------------------------------------------------------------------------------------
    bool CToml::isBackLevel(void) const {
        if (getVersion() < getVersionNum(0,6,0))
            return true;
        // This is where we would handle future upgrades
        return false;
    }

    //---------------------------------------------------------------------------------------
    void CToml::mergeFile(CToml *tomlIn) {
        for (auto group : tomlIn->groups) {
            for (auto key : group.keys) {
                setConfigStr(group.groupName, key.keyName, "\"" + key.value + "\"");
                if (key.deleted)
                    deleteKey(group.groupName, key.keyName);
            }
        }
    }

    //---------------------------------------------------------------------------------------
    biguint_t CToml::getConfigBigInt(const string_q& group, const string_q& key, biguint_t def) const {
        string_q ret = getConfigStr(group, key, bnu_2_Str(def));
        string_q check = ret;
        replaceAny(check, "0123456789abcdefABCDEF", "");
        if (!check.empty()) {
            cerr << "Big int config item " << group << "::" << key << " is not an integer...returning zero.";
            return 0;
        }
        return str_2_BigUint(ret);
    }

    //---------------------------------------------------------------------------------------
    string_q CToml::getConfigStr(const string_q& group, const string_q& key, const string_q& def) const {
        string_q env = getEnvStr(toUpper(group + "_" + key));
        if (!env.empty())
            return env;
        CTomlKey *found = findKey(group, key);
        if (found && !found->comment)
            return found->value;
        return def;
    }

    //---------------------------------------------------------------------------------------
    string_q CToml::getConfigJson(const string_q& group, const string_q& key, const string_q& def) const {
        return getConfigStr(group, key, def);
    }

    //-------------------------------------------------------------------------
    uint64_t CToml::getVersion(void) const {
        // handle older ways of stroring version. Note: after 0.6.0, always stored as [version]current
        string_q value = getConfigStr("version", "current", getConfigStr("", "version", "0.0.0"));
        uint16_t v1 = (uint16_t)str_2_Uint(nextTokenClear(value, '.'));
        uint16_t v2 = (uint16_t)str_2_Uint(nextTokenClear(value, '.'));
        uint16_t v3 = (uint16_t)str_2_Uint(nextTokenClear(value, '.'));
        return getVersionNum(v1, v2, v3);
    }

    //-------------------------------------------------------------------------
    string_q CToml::getDisplayStr(bool terse, const string_q& def, const string_q& color) const {
//        string_q color = (colorIn.empty() ? cTeal : colorIn);
        string_q fmt = getConfigStr("display", (terse ? "terse" : "format"), "<not_set>");
        if (fmt == "<not_set>")
            fmt = def;
        if (!color.empty()) {
            replaceAll(fmt, "{", color+"{");
            replaceAll(fmt, "}", "}"+cOff);
        }

        string_q ret = substitute(fmt, "\\n\\\n", "\\n");
        ret = substitute(ret, "\n", "");
        ret = substitute(ret, "\\n", "\n");
        ret = substitute(ret, "\\t", "\t");
        ret = substitute(ret, "\\r", "\r");
        return ret;
    }

    //-------------------------------------------------------------------------
    void CToml::setConfigInt(const string_q& group, const string_q& key, uint64_t value) {
        setConfigStr(group, key, int_2_Str((int64_t)value));
    }

    //-------------------------------------------------------------------------
    void CToml::setConfigBool(const string_q& group, const string_q& key, bool value) {
        setConfigStr(group, key, int_2_Str(value));
    }

    //-------------------------------------------------------------------------
    void CToml::setConfigArray(const string_q& group, const string_q& key, const string& value) {
        setConfigStr(group, key, value);
        CToml::CTomlGroup *grp = findGroup(group);
        if (grp)
            grp->isArray = true;
    }

    //-------------------------------------------------------------------------
    void CToml::setConfigStr(const string_q& group, const string_q& keyIn, const string_q& value) {
        bool comment = startsWith(keyIn, '#');
        string_q key = (comment ? extract(keyIn, 1) : keyIn);

        CTomlGroup *grp = findGroup(group);
        if (!grp) {
            addGroup(group, false, false);
            addKey(group, key, value, comment);

        } else {
            CTomlKey *found = findKey(group, key);
            if (found) {
                found->comment = comment;
                found->value = value;
            } else {
                addKey(group, key, value, comment);
            }
        }
    }

    //-------------------------------------------------------------------------
    ostream& operator<<(ostream& os, const CToml& tomlIn) {
        for (auto group : tomlIn.groups) {
            bool isEmpty = group.groupName == "empty-group";
            if (!isEmpty) {
                os << (group.isComment ? "#" : "");
                os << (group.isArray ? "[[" : "[");
                os << group.groupName;
                os << (group.isArray ? "]]" : "]");
                os << endl;
            }
            for (auto key : group.keys) {
                os << (isEmpty ? "" : "\t");
                os << (key.comment || group.isComment ? "#" : "");
                os << key.keyName << " = " << key.value;
                os << (key.deleted ? " (deleted)" : "");
                os << endl;
            }
        }
        return os;
    }

#if 0
    //-------------------------------------------------------------------------
    ostream& operator<<(ostream& os, const CToml& tomlIn) {
        for (auto group : tomlIn.groups)
            os << group;
        return os;
    }
#endif

    //-------------------------------------------------------------------------
    CToml::CTomlKey::CTomlKey() : comment(false) {
    }

    //-------------------------------------------------------------------------
    CToml::CTomlKey::CTomlKey(const CTomlKey& key)
        : keyName(key.keyName), value(key.value), comment(key.comment), deleted(key.deleted) { }

    //-------------------------------------------------------------------------
    CToml::CTomlKey& CToml::CTomlKey::operator=(const CTomlKey& key) {
        keyName = key.keyName;
        value = key.value;
        comment = key.comment;
        deleted = key.deleted;
        return *this;
    }

    //-------------------------------------------------------------------------
    CToml::CTomlGroup::CTomlGroup(void) {
        clear();
    }

    //-------------------------------------------------------------------------
    CToml::CTomlGroup::CTomlGroup(const CTomlGroup& group) {
        copy(group);
    }

    //-------------------------------------------------------------------------
    CToml::CTomlGroup::~CTomlGroup(void) {
        clear();
    }

    //-------------------------------------------------------------------------
    CToml::CTomlGroup& CToml::CTomlGroup::operator=(const CTomlGroup& group) {
        copy(group);
        return *this;
    }

    //-------------------------------------------------------------------------
    void CToml::CTomlGroup::clear(void) {
        groupName = "";
        isComment = false;
        isArray = false;
        keys.clear();
    }

    //-------------------------------------------------------------------------
    void CToml::CTomlGroup::copy(const CTomlGroup& group) {
        clear();

        groupName = group.groupName;
        isComment = group.isComment;
        isArray   = group.isArray;
        keys.clear();
        for (auto key : group.keys)
            keys.push_back(key);
    }

    //---------------------------------------------------------------------------------------
    void CToml::CTomlGroup::addKey(const string_q& keyName, const string_q& val, bool commented) {
        string_q str = substitute(val, "\"\"\"", "");
        if (endsWith(str, '\"'))
            replaceReverse(str, "\"", "");
        if (startsWith(str, '\"'))
            replace(str, "\"", "");
        str = substitute(str, "\\\"", "\"");  // unescape
        str = substitute(str, "\\#",  "#");  // unescape
        CTomlKey key(keyName, str, commented);
        key.deleted = contains(val, "(deleted)");
        keys.push_back(key);
        return;
    }

    //---------------------------------------------------------------------------------------
    void CToml::deleteKey(const string_q& group, const string_q& key) {
        CToml::CTomlKey *kPtr = findKey(group, key);
        if (kPtr)
            kPtr->deleted = true;
    }

    //---------------------------------------------------------------------------------------
    string_q stripFullLineComments(const string_q& inStr) {
        string_q str = inStr;
        string_q ret;
        while (!str.empty()) {
            string_q line = trimWhitespace(nextTokenClear(str, '\n'));
            if (line.length() && line[0] != '#') {
                ret += (line + "\n");
            }
        }
        return ret;
    }

    //---------------------------------------------------------------------------------------
    string_q collapseArrays(const string_q& inStr) {
        if (!contains(inStr, "[[") && !contains(inStr, "]]"))
            return inStr;

        string_q ret;
#if 0
        enum { OUT, IN };
        size_t state = OUT;
        string_q str = substitute(substitute(inStr,"[[","+ARRAY+"),"]]\n","-ARRAY-\n`");
        for (auto& ch : str) {
            switch (state) {
                case OUT:
                    if (ch == '`')
                        state = IN;
                    break;
                case IN:
                    if (ch == ']')
                        state = OUT;
                    else if (ch == '\n')
                        ch = ' ';
                    break;
                default:
                    break;
            }
            ret += ch;
        }
        replaceAll(ret,"+ARRAY+", "[");
        replaceAll(ret,"-ARRAY-", "]");
        replaceAll(ret,"`", "");
        cout << ret << endl;
        return ret;
#endif
        string_q str = substitute(inStr, "  ", " ");
        replace(str, "[[", "`");
        string_q front = nextTokenClear(str, '`');
        str = "[[" + str;
        str = substitute(str, "[[", "<array>");
        str = substitute(str, "]]", "</array>\n<name>");
        str = substitute(str, "[", "</name>\n<value>");
        str = substitute(str, "]", "</value>\n<name>");
        replaceReverse(str, "<name>", "");
        replaceAll(str, "<name>\n", "<name>");
        replaceAll(str, " = </name>", "</name>");
        while (contains(str, "</array>")) {
            string_q array = snagFieldClear(str, "array");
            string_q vals;
            while (contains(str, "</value>")) {
                string_q name = substitute(substitute(snagFieldClear(str, "name"), "=", ""), "\n", "");
                string_q value = substitute(substitute(snagFieldClear(str, "value"), "\n", ""), "=", ":");
                vals += name + " = [ " + value + " ]\n";
            }
            string_q line = "[[" + array + "]]\n" + vals;
            ret += line;
        }
        return front + ret;
    }

//#endif
#if 0
    CNewToml::CNewToml(const string_q& path) {
        setFilename(path);
        if (!path.empty())
            readFile(path);
    }

    bool CNewToml::writeFile(void) {
        return true;
    }

    bool CNewToml::readFile(const string_q& filename) {
        toml = parse_file(filename);
        return true;
    }

    void CNewToml::mergeFile(CNewToml *tomlIn) {
    }

    string_q CNewToml::getConfigStr(const string_q& group, const string_q& key, const string_q& def) const {
        string_q env = getEnvStr(toUpper(group + "_" + key));
        if (!env.empty())
            return env;
        auto val = (group.empty() ? toml->get_as<string>(key) : toml->get_qualified_as<string>(group+"."+key));
        if (val)
            return *val;
        return def;
    }

    class toml_test_writer {
    public:
        toml_test_writer(std::ostream& s) : stream_(s) { }
        void visit(const tomlvalue_t<string_q>& v) {
            stream_ << "{\"type\":\"string\",\"value\":\"" << CTomlWriter::escape_string(v.get()) << "\"}";
        }
        void visit(const tomlvalue_t<int64_t>& v) {
            stream_ << "{\"type\":\"integer\",\"value\":\"" << v.get() << "\"}";
        }
        void visit(const tomlvalue_t<double>& v) {
            stream_ << "{\"type\":\"float\",\"value\":\"" << v.get() << "\"}";
        }
        void visit(const tomlvalue_t<loc_date_t>& v) {
            stream_ << "{\"type\":\"local_date\",\"value\":\"" << v.get() << "\"}";
        }
        void visit(const tomlvalue_t<loc_time_t>& v) {
            stream_ << "{\"type\":\"local_time\",\"value\":\"" << v.get() << "\"}";
        }
        void visit(const tomlvalue_t<loc_datetime_t>& v) {
            stream_ << "{\"type\":\"local_datetime\",\"value\":\"" << v.get() << "\"}";
        }
        void visit(const tomlvalue_t<off_datetime_t>& v) {
            stream_ << "{\"type\":\"datetime\",\"value\":\"" << v.get() << "\"}";
        }
        void visit(const tomlvalue_t<bool>& v) {
            stream_ << "{\"type\":\"bool\",\"value\":\"" << v << "\"}";
        }
        void visit(const tomlarray_t& arr) {
            stream_ << "{\"type\":\"array\",\"value\":[";
            auto it = arr.get().begin();
            while (it != arr.get().end()) {
                (*it)->accept(*this);
                if (++it != arr.get().end())
                    stream_ << ", ";
            }
            stream_ << "]}";
        }
        void visit(const tomltablearray_t& tarr) {
            stream_ << "[";
            auto arr = tarr.get();
            auto ait = arr.begin();
            while (ait != arr.end()) {
                (*ait)->accept(*this);
                if (++ait != arr.end())
                    stream_ << ", ";
            }
            stream_ << "]";
        }
        void visit(const tomltable_t& t) {
            stream_ << "{";
            auto it = t.begin();
            while (it != t.end()) {
                stream_ << '"' << CTomlWriter::escape_string(it->first)
                << "\":";
                it->second->accept(*this);
                if (++it != t.end())
                    stream_ << ", ";
            }
            stream_ << "}";
        }
    private:
        std::ostream& stream_;
    };

    string_q CNewToml::getConfigJson(const string_q& group, const string_q& key, const string_q& def) const {
        string_q env = getEnvStr(toUpper(group + "_" + key));
        if (!env.empty())
            return env;
        ostringstream os;
        toml_test_writer writer{os};
        toml->accept(writer);
        os << endl;
        return os.str();
    }

    uint64_t CNewToml::getConfigInt(const string_q& group, const string_q& key, uint64_t def) const {
        string_q env = getEnvStr(toUpper(group + "_" + key));
        if (!env.empty())
            return str_2_Uint(env);
        string_q search = (group.empty() ? key : group + "." + key);
        auto val = toml->get_as<uint64_t>(search);
        if (val)
            return *val;
        return def;
    }

    bool CNewToml::getConfigBool(const string_q& group, const string_q& key, bool def) const {
        string_q env = getEnvStr(toUpper(group + "_" + key));
        if (!env.empty())
            return str_2_Bool(env);
        string_q search = (group.empty() ? key : group + "." + key);
        auto val = toml->get_as<bool>(search);
        if (val)
            return *val;
        return def;
    }

    //-------------------------------------------------------------------------
    string_q CNewToml::getDisplayStr(bool terse, const string_q& def, const string_q& colorIn) const {
        string_q color = (colorIn.empty() ? cTeal : colorIn);
        string_q fmt = getConfigStr("display", (terse ? "terse" : "format"), "<not_set>");
        if (fmt == "<not_set>")
            fmt = def;
        if (!color.empty()) {
            replaceAll(fmt, "{", color+"{");
            replaceAll(fmt, "}", "}"+cOff);
        }

        string_q ret = substitute(fmt, "\\n\\\n", "\\n");
        ret = substitute(ret, "\n", "");
        ret = substitute(ret, "\\n", "\n");
        ret = substitute(ret, "\\t", "\t");
        ret = substitute(ret, "\\r", "\r");
        return ret;
    }

    //-------------------------------------------------------------------------
    uint64_t CNewToml::getVersion(void) const {
        // handle older ways of stroring version. Note: after 0.6.0, always stored as [version]current
        string_q value = getConfigStr("version", "current", getConfigStr("", "version", "0.0.0"));
        uint16_t v1 = (uint16_t)str_2_Uint(nextTokenClear(value, '.'));
        uint16_t v2 = (uint16_t)str_2_Uint(nextTokenClear(value, '.'));
        uint16_t v3 = (uint16_t)str_2_Uint(nextTokenClear(value, '.'));
        return getVersionNum(v1, v2, v3);
    }

    //-------------------------------------------------------------------------
    void CNewToml::setConfigArray(const string_q& group, const string_q& key, const string_q& value) {
    }

    void CNewToml::setConfigStr(const string_q& group, const string_q& key, const string_q& value) {
    }

    void CNewToml::setFilename(const string_q& fn) {
        m_filename = fn;
    }
#endif
}  // namespace qblocks
