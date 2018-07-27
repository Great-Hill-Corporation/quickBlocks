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
#include <algorithm>
#include <vector>
#include "database.h"
#include "biglib.h"

namespace qblocks {

    extern string_q cTeal, cOff;
    //-------------------------------------------------------------------------
    class CToml : public CSharedResource {
    private:
        void clear(void);

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

            CTomlKey(void);
            CTomlKey(const string_q& n, const string_q& v, bool c) : keyName(n), value(v), comment(c) { }
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

    public:
        vector<CTomlGroup> groups;

        explicit CToml(const string_q& fileName);
        ~CToml(void);

        string_q getType(void) const override { return "CToml"; }

        string_q getConfigStr   (const string_q& group, const string_q& key, const string_q& def) const;
        uint64_t getConfigInt   (const string_q& group, const string_q& key, uint64_t def) const;
        biguint_t getConfigBigInt(const string_q& group, const string_q& key, biguint_t def) const;
        bool     getConfigBool  (const string_q& group, const string_q& key, bool def) const;
        string_q getDisplayStr  (bool terse, const string_q& def, const string_q& color = cTeal) const;

        void setConfigStr  (const string_q& group, const string_q& key, const string_q& value);
        void setConfigInt  (const string_q& group, const string_q& key, uint64_t value);
        void setConfigBool (const string_q& group, const string_q& key, bool value);

        bool writeFile(void);
        bool readFile(const string_q& filename);
        void mergeFile(CToml *tomlIn);

        friend ostream& operator<<(ostream& os, const CToml& tomlIn);
    };

    //-------------------------------------------------------------------------
    extern ostream& operator<<(ostream& os, const CToml& t);

}  // namespace qblocks
