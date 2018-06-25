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

class COptions : public COptionsBase {
public:
    uint64_t parts;
    bool noconst;
    bool open;
    bool asJson;
    bool raw;
    bool asData;
    bool decNames;
    SFAddressArray addrs;
    string_q primaryAddr;
    string_q classDir;
    string_q prefix;
    string_q theABI;
    bool silent;

    COptions(void);
    ~COptions(void);

    string_q postProcess(const string_q& which, const string_q& str) const override;
    bool parseArguments(string_q& command) override;
    void Init(void) override;

    bool isToken(void) const { return prefix % "tokenlib"; }
    bool isWallet(void) const { return prefix % "walletlib"; }
    bool isBuiltin(void) const { return isToken() || isWallet(); }
};

extern string_q getPrefix(const string_q& in);
