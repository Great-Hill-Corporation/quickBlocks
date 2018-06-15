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
#include "runtimeclass.h"

namespace qblocks {

    //-------------------------------------------------------------------------
    CRuntimeClass::~CRuntimeClass(void) {
        ClearFieldList();
        ASSERT(!m_FieldList);
    }

    //-------------------------------------------------------------------------
    char *CRuntimeClass::getClassNamePtr(void) const {
        return m_ClassName;
    }

    //-------------------------------------------------------------------------
    bool CRuntimeClass::IsDerivedFrom(const CRuntimeClass* pBaseClass) const {
        const CRuntimeClass* pClassThis = this;
        while (pClassThis != NULL) {
            if (pClassThis == pBaseClass)
                return true;
            pClassThis = pClassThis->m_BaseClass;
        }
        return false;
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::ClearFieldList(void) {
        if (m_FieldList) {
            LISTPOS p = m_FieldList->GetHeadPosition();
            while (p) {
                CFieldData *field = m_FieldList->GetNext(p);
                delete field;
            }
            m_FieldList->RemoveAll();
            delete m_FieldList;
            m_FieldList = NULL;
        }
    }

    //-------------------------------------------------------------------------
    string_q CRuntimeClass::listOfFields(char sep) const {
        string_q ret;
        if (m_FieldList) {
            LISTPOS p = m_FieldList->GetHeadPosition();
            while (p) {
                CFieldData *field = m_FieldList->GetNext(p);
                ret += field->m_fieldName + sep;
            }
        }
        return ret;
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::hideAllFields(void) {
        if (m_FieldList) {
            LISTPOS p = m_FieldList->GetHeadPosition();
            while (p) {
                CFieldData *field = m_FieldList->GetNext(p);
                field->setHidden(true);
            }
        }
        return;
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::showAllFields(void) {
        if (m_FieldList) {
            LISTPOS p = m_FieldList->GetHeadPosition();
            while (p) {
                CFieldData *field = m_FieldList->GetNext(p);
                field->setHidden(false);
            }
        }
        return;
    }

    //-------------------------------------------------------------------------
    int sortFieldsByName(const void *v1, const void *v2) {
        CFieldData *f1 = (CFieldData *)v1;
        CFieldData *f2 = (CFieldData *)v2;
        return f1->m_fieldName.compare(f2->m_fieldName);
    }
    //-------------------------------------------------------------------------
    void CRuntimeClass::sortFieldList(void) {
        if (m_FieldList) {

            // Sort it into a temporary list...
            CFieldList tmpList;
            LISTPOS p = m_FieldList->GetHeadPosition();
            while (p) {
                CFieldData *field = m_FieldList->GetNext(p);
                tmpList.AddSorted(field, sortFieldsByName);
            }

            // ...clear it out...
            *m_FieldList = CFieldList();

            // ...sort it into the original list
            p = tmpList.GetHeadPosition();
            while (p) {
                CFieldData *field = tmpList.GetNext(p);
                m_FieldList->AddTail(field);
            }
        }
        return;
    }

    //-------------------------------------------------------------------------
    void CRuntimeClass::AddField(const string_q& fieldName, size_t dataType, size_t fieldID) {
        if (!m_FieldList)
            m_FieldList = new CFieldList;
        ASSERT(m_FieldList);

        CFieldData *field = new CFieldData;
        if (field) {
            field->m_fieldName = fieldName;
            field->m_fieldType = dataType;
            field->m_fieldID = fieldID;
            m_FieldList->AddTail(field);
        }
    }

    //-------------------------------------------------------------------------
    CBuiltIn::CBuiltIn(CRuntimeClass *pClass, const string_q& className, size_t size,
                       PFNV createFunc, CRuntimeClass *pBase) {
        m_pClass = pClass;
        string_q copy = className;
        if (!copy.empty())
            pClass->m_ClassName = strdup(copy.c_str());

        pClass->m_ObjectSize = size;
        pClass->m_BaseClass  = pBase;
        pClass->m_FieldList  = NULL;
        pClass->m_CreateFunc = createFunc;
    }
}  // namespace qblocks
