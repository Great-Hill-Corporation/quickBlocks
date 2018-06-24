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
#include <algorithm>
#include "basetypes.h"
#include "runtimeclass.h"

namespace qblocks {

    //-------------------------------------------------------------------------
    CRuntimeClass::CRuntimeClass(void) {
    }

    //-------------------------------------------------------------------------
    CRuntimeClass::~CRuntimeClass(void) {
    }

    //-------------------------------------------------------------------------
    char *CRuntimeClass::getClassNamePtr(void) const {
        return m_ClassName;
    }

    //-------------------------------------------------------------------------
    bool CRuntimeClass::isDerivedFrom(const CRuntimeClass* pBaseClass) const {
        const CRuntimeClass* pClassThis = this;
        while (pClassThis != NULL) {
            if (pClassThis == pBaseClass)
                return true;
            pClassThis = pClassThis->m_BaseClass;
        }
        return false;
    }

    //-------------------------------------------------------------------------
    CBaseNode *CRuntimeClass::createObject(void) {
        if (m_CreateFunc)
            return (*m_CreateFunc)();
        return NULL;
    }

    //-------------------------------------------------------------------------
    CFieldData *CRuntimeClass::findField(const string_q& fieldName) {
        for (size_t i = 0 ; i < fieldList.size() ; i++) {
            if (fieldList[i].getName() == fieldName)
                return &fieldList[i];
        }
        return NULL;
    }

    //-------------------------------------------------------------------------
    bool CRuntimeClass::isFieldHidden(const string_q& fieldName) {
        const CFieldData *f = findField(fieldName);
        if (f)
            return f->isHidden();
        return false;
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::addField(const string_q& fieldName, size_t dataType, size_t fieldID) {
        CFieldData field(fieldName, fieldID, dataType);
        fieldList.push_back(field);
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::sortFieldList(void) {
        sort(fieldList.begin(), fieldList.end());
        return;
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::hideAllFields(void) {
        for (size_t i = 0 ; i < fieldList.size(); i++) {
            fieldList.at(i).setHidden(true);
        }
        return;
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::showAllFields(void) {
        for (size_t i = 0 ; i < fieldList.size(); i++) {
            fieldList.at(i).setHidden(false);
        }
        return;
    }

    //-------------------------------------------------------------------------
    bool CRuntimeClass::forEveryField(FIELDVISITFUNC func, void *data) {
        if (!func)
            return true;

        for (auto field : fieldList) {
            if (!(*func)(field, data))
                return false;
        }

        return true;
    }

    //-------------------------------------------------------------------------
    CBuiltIn::CBuiltIn(CRuntimeClass *pClass, const string_q& className, size_t size, \
                            PFNV createFunc, CRuntimeClass *pBase) {
        m_pClass = pClass;
        string_q copy = className;
        if (!copy.empty())
            pClass->m_ClassName = strdup(copy.c_str());
        pClass->m_ObjectSize = size;
        pClass->m_BaseClass  = pBase;
        pClass->m_CreateFunc = createFunc;
    }
}  // namespace qblocks
