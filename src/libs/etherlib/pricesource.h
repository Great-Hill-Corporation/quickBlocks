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
#include "pricequote.h"

namespace qblocks {

    typedef bool (*PRICEPARSEFUNC)(CPriceQuote& quote, string_q& str);
    extern bool parsePoloniex(CPriceQuote& quote, string_q& str);
    extern const char* STR_PRICE_URL;

    class CPriceSource {
    public:
        string_q url;
        string_q pair;
        PRICEPARSEFUNC func;
        CPriceSource(const string_q& u = STR_PRICE_URL,
                     const string_q& p = "USDT_ETH",
                     PRICEPARSEFUNC f = parsePoloniex)
            : url(u), pair(p), func(f) {}
        string_q getDatabasePath(void) const;
    };

    extern bool loadPriceData(const CPriceSource& source, CPriceQuoteArray& quotes,
                    bool freshen, string_q& message, uint64_t step = 1);

}  // namespace qblocks
