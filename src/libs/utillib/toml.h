#pragma once
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
//#define NEW_TOML

#include <algorithm>
#include <vector>
#include "database.h"
#include "biglib.h"
//#include "toml_new.h"

namespace qblocks {

#if 0
    typedef bool (*TOMLGROUPFUNC)(const void *group);
    class CNewToml {
        string_q m_filename;
    public:
        CNewToml(const string_q& path);
        bool writeFile(void);
        bool readFile(const string_q& filename);
        void mergeFile(CNewToml *tomlIn);
        string_q  getConfigStr   (const string_q& group, const string_q& key, const string_q& def) const;
        string_q  getConfigJson  (const string_q& group, const string_q& key, const string_q& def) const;
        uint64_t  getConfigInt   (const string_q& group, const string_q& key, uint64_t def) const;
        biguint_t getConfigBigInt(const string_q& group, const string_q& key, biguint_t def) const;
        bool      getConfigBool  (const string_q& group, const string_q& key, bool def) const;
        string_q  getDisplayStr  (bool terse, const string_q& def, const string_q& color = "") const;
        uint64_t getVersion(void) const;
        void setConfigArray(const string_q& group, const string_q& key, const string_q& value);
        void setConfigStr(const string_q& group, const string_q& key, const string_q& value);
        void setFilename(const string_q& fn);
        bool forEveryGroup(TOMLGROUPFUNC func) const;
        bool isBackLevel(void) const;
        string_q getFilename(void) const { return m_filename; }
    public:
        tableptr_t toml;
        void clear(void) { }
    };

    inline ostream& operator<<(ostream& stream, const CNewToml& a) {
        stream << *a.toml;
        return stream;
    }
#endif

//#ifdef NEW_TOML
//#define CToml CNewToml
//#else
    extern string_q cTeal, cOff;
    //-------------------------------------------------------------------------
    class CToml : public CSharedResource {
    private:
        // no default construction or copies
        CToml(void) {}
        CToml(const CToml& toml);
        CToml& operator= (const CToml& toml);

        //-------------------------------------------------------------------------
        // support class for toml file
        class CTomlKey {
        public:
            string_q keyName;
            string_q value;
            bool     comment;
            bool     deleted;

            CTomlKey(void);
            CTomlKey(const string_q& n, const string_q& v, bool c) : keyName(n), value(v), comment(c), deleted(false) { }
            CTomlKey(const CTomlKey& key);
            CTomlKey& operator=(const CTomlKey& key);
        };

        //-------------------------------------------------------------------------
        // support class for toml file
        class CTomlGroup {
        public:
            string_q         groupName;
            bool             isArray;
            bool             isComment;
            vector<CTomlKey> keys;

            CTomlGroup(void);
            CTomlGroup(const string_q& n, bool a, bool c) : groupName(n), isArray(a), isComment(c) { }
            CTomlGroup(const CTomlGroup& group);

            ~CTomlGroup(void);

            CTomlGroup& operator=(const CTomlGroup& group);
            void addKey(const string_q& keyName, const string_q& val, bool commented);

        private:
            void clear(void);
            void copy(const CTomlGroup& group);

        };

    protected:
        void addGroup(const string_q& group, bool commented, bool array);
        void addKey  (const string_q& group, const string_q& key, const string_q& val, bool commented);

        CTomlGroup *findGroup(const string_q& group) const;
        CTomlKey   *findKey  (const string_q& group, const string_q& key) const;
        void        deleteKey(const string_q& group, const string_q& key);

    public:
        vector<CTomlGroup> groups;

        explicit CToml(const string_q& fileName);
        ~CToml(void);

        void clear(void);

        string_q getType(void) const override { return "CToml"; }

        string_q  getConfigStr   (const string_q& group, const string_q& key, const string_q& def) const;
        string_q  getConfigJson  (const string_q& group, const string_q& key, const string_q& def) const;
        uint64_t  getConfigInt   (const string_q& group, const string_q& key, uint64_t def) const;
        biguint_t getConfigBigInt(const string_q& group, const string_q& key, biguint_t def) const;
        bool      getConfigBool  (const string_q& group, const string_q& key, bool def) const;
        string_q  getDisplayStr  (bool terse, const string_q& def, const string_q& color = cTeal) const;
        uint64_t  getVersion     (void) const;

        void setConfigArray(const string_q& group, const string_q& key, const string_q& value);
        void setConfigStr  (const string_q& group, const string_q& key, const string_q& value);
        void setConfigInt  (const string_q& group, const string_q& key, uint64_t value);
        void setConfigBool (const string_q& group, const string_q& key, bool value);

        bool writeFile(void);
        bool readFile(const string_q& filename);
        void mergeFile(CToml *tomlIn);

        bool isBackLevel(void) const;
//        bool forEveryGroup(TOMLGROUPFUNC func) const;
//
        friend ostream& operator<<(ostream& os, const CToml& tomlIn);
    };

    //-------------------------------------------------------------------------
    extern ostream& operator<<(ostream& os, const CToml& t);
//    extern ostream& operator<<(ostream& os, const CToml::CTomlGroup& g);
//    extern ostream& operator<<(ostream& os, const CToml::CTomlKey& k);
//#endif

}  // namespace qblocks
