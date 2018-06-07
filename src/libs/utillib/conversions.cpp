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
#include "biglib.h"
#include "conversions.h"

namespace qblocks {

    //------------------------------------------------------------------
    class SFBloomHex : public SFBigNumStore<unsigned char> {
    public:
        SFBloomHex(const SFUintBN& numIn);
        SFString str;
    };

#define OLD_CODE 1
    //------------------------------------------------------------------
    SFBloomHex::SFBloomHex(const SFUintBN& numIn) {

        len = 1024;
        allocate(1024);

        SFUintBN x2(numIn);
        unsigned int nDigits = 0;
        while (x2.len != 0)
        {
            SFUintBN lastDigit(x2);
            lastDigit.divide(16, x2);
            blk[nDigits] = (unsigned char)lastDigit.to_ushort();
            nDigits++;
        }
        len = nDigits;

#ifdef OLD_CODE
        char s[1024+1];
		memset(s,'\0',sizeof(s));
        for (unsigned int p=0;p<len;p++) {
            unsigned short c = blk[len-1-p];
            s[p] = ((c < 10) ? char('0'+c) : char('A'+c-10));
        }
        str = s;
#else
        str.reserve(1025);
        char *pStr = (char*)(const char*)str.c_str();
        memset(pStr,'\0',1025);
        for (unsigned int p = 0 ; p < len ; p++) {
            unsigned short c = blk[len-1-p];
            pStr[p] = ((c < 10) ? char('0'+c) : char('a'+c-10));
        }
#endif
    }

    //------------------------------------------------------------------
    SFString bloom2Bytes(const SFBloom& bl) {
        if (bl == 0)
            return "0x0";
        SFBloomHex b2(bl);
#ifdef OLD_CODE
        return ("0x" + padLeft(toLower(b2.str),512,'0'));
#else
        return ("0x" + padLeft(b2.str,512,'0'));
#endif
    }

    //-------------------------------------------------------------------------
    SFString bloom2Bits(const SFBloom& b) {
        SFString ret = bloom2Bytes(b).Substitute("0x", "");
        ret.ReplaceAll("0","0000");
        ret.ReplaceAll("1","0001");
        ret.ReplaceAll("2","0010");
        ret.ReplaceAll("3","0011");
        ret.ReplaceAll("4","0100");
        ret.ReplaceAll("5","0101");
        ret.ReplaceAll("6","0110");
        ret.ReplaceAll("7","0111");
        ret.ReplaceAll("8","1000");
        ret.ReplaceAll("9","1001");
        ret.ReplaceAll("a","1010");
        ret.ReplaceAll("b","1011");
        ret.ReplaceAll("c","1100");
        ret.ReplaceAll("d","1101");
        ret.ReplaceAll("e","1110");
        ret.ReplaceAll("f","1111");
        return ret;
    }

    /*
        Javascipt: Returns a checksummed address
        @param {String} address
        @return {String}
        exports.toChecksumAddress = function (address) {
            address = exports.stripHexPrefix(address).toLowerCase()
            const hash = exports.sha3(address).toString('hex')
            let ret = '0x'
            for (let i = 0; i < address.length; i++) {
                if (parseInt(hash[i], 16) >= 8) {
                    ret += address[i].toUpperCase()
                } else {
                    ret += address[i]
                }
            }
            return ret
        }
    */
}  // namespace qblocks
