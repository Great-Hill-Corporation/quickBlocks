#pragma once
/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "etherlib.h"
#include "acctlib.h"

//-----------------------------------------------------------------------
class COptions : public COptionsBase {
public:
    CAbi abis;
    CAccountWatchArray monitors;
    CAccountWatchArray named;
    CAppearanceArray_base items;
    bool writeTxs;
    bool writeTraces;
    bool skipDdos;
    size_t maxTraces;
    bool articulate;
    bool doLogs;
    bool doTraces;
    bool doBalances;
    bool doABIs;
    bool freshenOnly;
    map<uint32_t,address_t> prefundMap;
    map<uint32_t,address_t> blkRewardMap;
    map<address_t,bool>     abiMap;
    uint32_t *ts_array;
    size_t ts_cnt;

    COptions(void);
    ~COptions(void);

    bool parseArguments(string_q& command);
    void Init(void);
    string_q postProcess(const string_q& which, const string_q& str) const;

    bool loadOneAddress(CAppearanceArray_base& apps, const address_t& addr);
    bool loadAllAppearances(void);
    bool exportData(void);
    bool exportBalances(void);
    bool loadTsArray(void);
};
