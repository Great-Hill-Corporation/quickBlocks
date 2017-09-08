#pragma once
/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "ethtypes.h"
#include "abilib.h"
#include "transaction.h"

namespace qblocks {

//--------------------------------------------------------------------------
class CBlock;
typedef SFArrayBase<CBlock>         CBlockArray;
typedef SFList<CBlock*>             CBlockList;
typedef SFUniqueList<CBlock*>       CBlockListU;

// EXISTING_CODE
// TODO(tjayrush): The fields here are the least stuff QuickBlocks needs, I should create a MegaBlock that contains all
// EXISTING_CODE

//--------------------------------------------------------------------------
class CBlock : public CBaseNode {
public:
    SFUint32 gasLimit;
    SFUint32 gasUsed;
    SFHash hash;
    SFBloom logsBloom;
    SFUint32 blockNumber;
    SFHash parentHash;
    timestamp_t timestamp;
    CTransactionArray transactions;

public:
    CBlock(void);
    CBlock(const CBlock& bl);
    ~CBlock(void);
    CBlock& operator=(const CBlock& bl);

    DECLARE_NODE(CBlock);

    // EXISTING_CODE
#if 0
    SFAddress author;
    SFString difficulty;
    SFString extraData;
    SFString logsBloom;
    SFAddress miner;
    SFHash mixHash;
    SFString nonce;
    SFString receiptRoot;
    SFString receiptsRoot;
    SFStringArray sealFields;
    SFString sha3Uncles;
    SFString size;
    SFString stateRoot;
    SFString totalDifficulty;
    SFString transactionsRoot;
    SFStringArray uncles;
#endif
    // EXISTING_CODE

protected:
    void Clear(void);
    void Init(void);
    void Copy(const CBlock& bl);
    bool readBackLevel(SFArchive& archive);

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CBlock::CBlock(void) {
    Init();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CBlock::CBlock(const CBlock& bl) {
    // EXISTING_CODE
    // EXISTING_CODE
    Copy(bl);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CBlock::~CBlock(void) {
    Clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBlock::Clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBlock::Init(void) {
    CBaseNode::Init();

    gasLimit = 0;
    gasUsed = 0;
    hash = "";
    logsBloom = 0;
    blockNumber = 0;
    parentHash = "";
    timestamp = 0;
    transactions.Clear();

    // EXISTING_CODE
#if 0
    author = "";
    difficulty = "";
    extraData = "";
    miner = "";
    mixHash = "";
    nonce = "";
    receiptRoot = "";
    receiptsRoot = "";
    sealFields.Clear();
    sha3Uncles = "";
    size = "";
    stateRoot = "";
    totalDifficulty = "";
    transactionsRoot = "";
    uncles.Clear();
#endif
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBlock::Copy(const CBlock& bl) {
    Clear();
    CBaseNode::Copy(bl);

    gasLimit = bl.gasLimit;
    gasUsed = bl.gasUsed;
    hash = bl.hash;
    logsBloom = bl.logsBloom;
    blockNumber = bl.blockNumber;
    parentHash = bl.parentHash;
    timestamp = bl.timestamp;
    transactions = bl.transactions;

    // EXISTING_CODE
#if 0
    author = bl.author;
    difficulty = bl.difficulty;
    extraData = bl.extraData;
    miner = bl.miner;
    mixHash = bl.mixHash;
    nonce = bl.nonce;
    receiptRoot = bl.receiptRoot;
    receiptsRoot = bl.receiptsRoot;
    sealFields = bl.sealFields;
    sha3Uncles = bl.sha3Uncles;
    size = bl.size;
    stateRoot = bl.stateRoot;
    totalDifficulty = bl.totalDifficulty;
    transactionsRoot = bl.transactionsRoot;
    uncles = bl.uncles;
#endif
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CBlock& CBlock::operator=(const CBlock& bl) {
    Copy(bl);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

#define NEW_CODE
#ifdef NEW_CODE
#else
//---------------------------------------------------------------------------
inline SFString CBlock::getValueByName(const SFString& fieldName) const {
    // EXISTING_CODE
    // EXISTING_CODE
    return Format("[{"+toUpper(fieldName)+"}]");
}
#endif

//---------------------------------------------------------------------------
IMPLEMENT_ARCHIVE_ARRAY(CBlockArray);
IMPLEMENT_ARCHIVE_ARRAY_C(CBlockArray);
IMPLEMENT_ARCHIVE_LIST(CBlockList);

//---------------------------------------------------------------------------
extern SFArchive& operator<<(SFArchive& archive, const CBlock& blo);
extern SFArchive& operator>>(SFArchive& archive, CBlock& blo);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
}  // namespace qblocks

