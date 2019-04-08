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

//-------------------------------------------------------------------
class COptions : public COptionsBase {
public:
    bool isAll;
    bool isRun;
    bool isEdit;
    bool isRemove;
    bool isList;
    bool silent;
    string_q namesp;
    bool writeHeader;
    bool writeSource;

    string_q classNames;
    string_q filter;
    CToml classFile;

    COptions(void);
    ~COptions(void);

    bool parseArguments(string_q& command);
    void Init(void);
};

//-------------------------------------------------------------------
extern bool listClasses(const string_q& path, void *data);

//------------------------------------------------------------------------------------------------------------
extern const char* STR_COMMENT_LINE;
extern const char* STR_CLASS_FILE;
extern const char* STR_CASE_CODE_ARRAY;
extern const char* STR_CASE_SET_CODE_ARRAY;
extern const char* STR_CASE_CODE_STRINGARRAY;
extern const char* STR_OPERATOR_H;
extern const char* STR_OPERATOR_C;
extern const char* STR_SUBCLASS;
extern const char* PTR_SET_CASE;
extern const char* PTR_GET_CASE;
extern const char* STR_GETVALUE1;
extern const char* STR_GETVALUE2;
extern const char* STR_GETOBJ_CODE;
extern const char* STR_GETOBJ_CODE_FIELD;
extern const char* STR_GETSTR_CODE;
extern const char* STR_GETSTR_CODE_FIELD;
extern const char* STR_GETOBJ_HEAD;
extern const char* STR_GETSTR_HEAD;
extern const char* STR_UPGRADE_CODE;
extern const char* STR_SORT_COMMENT_1;
extern const char* STR_SORT_COMMENT_2;
extern const char* STR_EQUAL_COMMENT_1;
extern const char* STR_EQUAL_COMMENT_2;
extern const char* STR_PRTREADFMT;
extern const char* STR_READFMT;
extern const char* STR_PTRWRITEFMT;
extern const char* STR_WRITEFMT;
extern const char* STR_UNKOWNTYPE;
