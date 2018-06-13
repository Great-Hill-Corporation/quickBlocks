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
#include "options_base.h"
#include "conversions.h"

namespace qblocks {

    //--------------------------------------------------------------------------------
    blknum_t COptionsBlockList::parseBlockOption(string_q& msg, blknum_t lastBlock) const {

        blknum_t ret = NOPOS;

        string_q arg = msg;
        msg = "";

        // if it's a number, return it
        if (isNumeral(arg) || isHexStr(arg)) {
            ret = toUnsigned(arg);

        } else {
            // if it's not a number, it better be a special value, and we better be able to find it
            CNameValue spec;
            if (pOptions && pOptions->findSpecial(spec, arg)) {
                if (spec.getName() == "latest") {
                    ret = lastBlock;
                } else {
                    ret = toUnsigned(spec.getValue());
                }
            } else {
                msg = "The given value '" + arg + "' is not a numeral or a special named block. Quitting...\n";
                return NOPOS;
            }
        }

        if (ret > lastBlock) {
            string_q lateStr = (isTestMode() ? "--" : asStringU(lastBlock));
            msg = "Block " + arg + " is later than the last valid block " + lateStr + ". Quitting...\n";
            return NOPOS;
        }

        return ret;
    }

    //--------------------------------------------------------------------------------
    string_q COptionsBlockList::parseBlockList(const string_q& argIn, blknum_t lastBlock) {
        string_q arg = argIn;
        if (contains(arg, "-")) {

            // If we already have a range, bail
            if (start != stop)
                return "Specify only a single block range at a time.";

            string_q stp = arg;
            string_q strt = nextTokenClear(stp, '-');
            if (strt == "latest")
                return "Cannot start range with 'latest'";

            string_q msg = strt;
            start = parseBlockOption(msg, lastBlock);
            if (!msg.empty())
                return msg;
            msg = stp;
            stop = parseBlockOption(msg, lastBlock);
            if (!msg.empty())
                return msg;

            if (stop <= start)
                return "'stop' must be strictly larger than 'start'";

        } else {

            if (isHash(arg)) {
                hashList.push_back(arg);

            } else {
                string_q msg = arg;
                blknum_t num = parseBlockOption(msg, lastBlock);
                if (!msg.empty())
                    return msg;
                numList.push_back(num);
            }
        }

        latest = lastBlock;
        return "";
    }

    //--------------------------------------------------------------------------------
    void COptionsBlockList::Init(void) {
        numList.Clear();
        hashList.clear();
        start = stop = 0;
        hashFind = NULL;
    }

    //--------------------------------------------------------------------------------
    COptionsBlockList::COptionsBlockList(void) {
        Init();
    }

    //--------------------------------------------------------------------------------
    bool COptionsBlockList::forEveryBlockNumber(UINT64VISITFUNC func, void *data) const {
        if (!func)
            return false;

        for (uint64_t i = start ; i < stop ; i++) {
            if (!(*func)(i, data))
                return false;
        }
        for (uint32_t i = 0 ; i < numList.getCount() ; i++) {
            uint64_t n = numList[i];
            if (!(*func)(n, data))
                return false;
        }
        if (hashFind) {
            for (uint32_t i = 0 ; i < hashList.size() ; i++) {
                uint64_t n = (*hashFind)(hashList[i], data);
                if (!(*func)(n, data))
                    return false;
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------
    bool COptionsBlockList::isInRange(blknum_t bn) const {
        if (start <= bn && bn < stop)
            return true;
        for (uint32_t i = 0 ; i < numList.getCount() ; i++)
            if (bn == numList[i])
                return true;
        return false;
    }

}  // namespace qblocks
