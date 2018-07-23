#pragma once
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
#include "etherlib.h"
#include "node_curl.h"

namespace qblocks {

    //-------------------------------------------------------------------------
    // setup and tear down of the library
    extern void     etherlib_init           (const string_q& primarySource = "binary",
                                                QUITHANDLER qh = defaultQuitHandler);
    inline void     etherlib_init           (QUITHANDLER qh) { etherlib_init("binary", qh); }
    extern void     etherlib_cleanup        (void);

    //-------------------------------------------------------------------------
    // fastest methods to access data
    extern bool     getBlock                (CBlock& block,       blknum_t blockNum);
    extern bool     getTransaction          (CTransaction& trans, blknum_t blockNum, txnum_t txID);
    extern bool     getReceipt              (CReceipt& receipt,   const SFHash& txHash);
    extern bool     getLogEntry             (CLogEntry& log,      const SFHash& txHash);
    extern void     getTraces               (CTraceArray& traces, const SFHash& txHash);
    extern size_t   getTraceCount           (const SFHash& hashIn);

    //-------------------------------------------------------------------------
    // other methods to access data
    extern bool     getBlock                (CBlock& block,       const SFHash& blockHash);
    extern bool     getTransaction          (CTransaction& trans, const SFHash& txHash);
    extern bool     getTransaction          (CTransaction& trans, const SFHash& blockHash, txnum_t txID);

    //-------------------------------------------------------------------------
    extern bool     queryBlock              (CBlock& block,       const string_q& num, bool needTrace, bool byHash,
                                                                    size_t& nTraces);
    extern bool     queryBlock              (CBlock& block,       const string_q& num, bool needTrace, bool byHash);

    //-------------------------------------------------------------------------
    // lower level access to the node's responses
    extern bool     queryRawBlock           (string_q& results,   const string_q& blockNum,
                                                    bool needTrace, bool hashesOnly);
    extern bool     queryRawTransaction     (string_q& results,   const SFHash& txHash);
    extern bool     queryRawReceipt         (string_q& results,   const SFHash& txHash);
    extern bool     queryRawLog             (string_q& results,   const SFHash& hashIn);
    extern bool     queryRawTrace           (string_q& results,   const SFHash& hashIn);
    extern bool     queryRawLogs            (string_q& results,   const address_t& addr,
                                                    uint64_t fromBlock, uint64_t toBlock);

    //-----------------------------------------------------------------------
    extern SFHash   getRawBlock             (blknum_t bn);
    extern SFHash   getRawBlockHash         (blknum_t bn);
    extern SFHash   getRawTransactionHash   (blknum_t bn, txnum_t tx);

    //-----------------------------------------------------------------------
    extern void     writeToJson             (const CBaseNode& node, const string_q& fileName);
    extern bool     readFromJson            (      CBaseNode& node, const string_q& fileName);

    //-----------------------------------------------------------------------
    extern bool     writeBlockToBinary      (const CBlock& block, const string_q& fileName);
    extern bool     readBlockFromBinary     (      CBlock& block, const string_q& fileName);

    //-------------------------------------------------------------------------
    extern string_q getVersionFromClient    (void);
    inline bool     isGeth                  (void) { return contains(toLower(getVersionFromClient()), "geth"); }  // NOLINT
    inline bool     isParity                (void) { return contains(toLower(getVersionFromClient()), "parity"); }  // NOLINT
    extern bool     getAccounts             (CAddressArray& addrs);
    extern uint64_t getLatestBlockFromClient(void);
    extern uint64_t getLatestBlockFromCache (void);
    extern bool     getLatestBlocks         (uint64_t& cache, uint64_t& client);

    //-------------------------------------------------------------------------
    extern bool     getCode                 (const address_t& addr, string_q& theCode);
    inline string_q getCode                 (const address_t& addr) { string_q ret; getCode(addr, ret); return ret; }  // NOLINT
    inline bool     isContract              (const address_t& addr) { return !substitute(getCode(addr), "0x", "").empty(); }  // NOLINT
    extern SFUintBN getBalance              (const address_t& addr, blknum_t blockNum, bool isDemo);
    extern bool     getSha3                 (const string_q& hexIn, string_q& shaOut);
    inline string_q getSha3                 (const string_q& hexIn) { string_q ret; getSha3(hexIn,ret); return ret; }  // NOLINT

    //-------------------------------------------------------------------------
    extern string_q getJsonFilename         (uint64_t num);
    extern string_q getBinaryFilename       (uint64_t num);
    extern string_q getBinaryPath           (uint64_t num);

    //-------------------------------------------------------------------------
    // function pointer types for forEvery functions
    typedef bool (*BLOCKVISITFUNC)          (CBlock& block, void *data);
    typedef bool (*TRANSVISITFUNC)          (CTransaction& trans, void *data);
    typedef bool (*LOGVISITFUNC)            (CLogEntry& log, void *data);
    typedef bool (*TRACEVISITFUNC)          (CTrace& trace, void *data);

    //-------------------------------------------------------------------------
    // forEvery functions
    extern bool forEveryBlock                (BLOCKVISITFUNC func, void *data, const string_q& block_list);  // NOLINT
    extern bool forEveryBlock                (BLOCKVISITFUNC func, void *data, uint64_t start, uint64_t count, uint64_t skip=1);  // NOLINT
    extern bool forEveryBlockOnDisc          (BLOCKVISITFUNC func, void *data, uint64_t start, uint64_t count, uint64_t skip=1);  // NOLINT
    extern bool forEveryNonEmptyBlockOnDisc  (BLOCKVISITFUNC func, void *data, uint64_t start, uint64_t count, uint64_t skip=1);  // NOLINT
    extern bool forEveryEmptyBlockOnDisc     (BLOCKVISITFUNC func, void *data, uint64_t start, uint64_t count, uint64_t skip=1);  // NOLINT

    //-------------------------------------------------------------------------
    // forEvery functions
    extern bool forEveryBloomFile            (FILEVISITOR    func, void *data, uint64_t start, uint64_t count, uint64_t skip = 1);  // NOLINT
    //-------------------------------------------------------------------------
    // forEvery functions
    extern bool forEveryTransactionInList    (TRANSVISITFUNC func, void *data, const string_q& trans_list);
    extern bool forEveryTransactionInBlock   (TRANSVISITFUNC func, void *data, const CBlock& block);

    //-------------------------------------------------------------------------
    // forEvery functions
    extern bool forEveryTraceInTransaction   (TRACEVISITFUNC func, void *data, const CTransaction& trans);
    extern bool forEveryTraceInBlock         (TRACEVISITFUNC func, void *data, const CBlock& block);
    extern bool forEveryLogInTransaction     (LOGVISITFUNC func,   void *data, const CTransaction& trans);
    extern bool forEveryLogInBlock           (LOGVISITFUNC func,   void *data, const CBlock& block);

    //-------------------------------------------------------------------------
    extern string_q blockCachePath(const string_q& _part);

    #define fullBlockIndex (blockCachePath("fullBlocks.bin"))
    #define accountIndex   (blockCachePath("accountTree.bin"))
    #define miniBlockCache (blockCachePath("miniBlocks.bin"))
    #define miniTransCache (blockCachePath("miniTrans.bin"))
    #define blockFolder    (blockCachePath("blocks/"))
    #define bloomFolder    (blockCachePath("blooms/"))
    extern SFUintBN weiPerEther;

}  // namespace qblocks

//-------------------------------------------------------------------------
extern bool visitBlockNumber(blknum_t bn,         void *data);
extern bool visitBlock      (CBlock& block,       void *data);
extern bool visitTransaction(CTransaction& trans, void *data);
extern bool visitLog        (CLogEntry& log,      void *data);
extern bool visitTrace      (CTrace& trace,       void *data);

