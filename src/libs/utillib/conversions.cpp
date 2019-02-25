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
#include "biglib.h"
#include "conversions.h"

// TODO(tjayrush): inline these conversions

namespace qblocks {

    extern uint64_t hex_2_Uint64(const string_q& str);
    extern int64_t  hex_2_Int64(const string_q& str) { return (int64_t)hex_2_Uint64(str); }
    extern biguint_t exp_2_BigUint (const string_q &str);

    //--------------------------------------------------------------------------------
    string_q chr_2_HexStr(const string_q& str) {
        if (startsWith(str, "0x"))
            return str;
        ostringstream os;
        os << "0x";
        for (auto elem : str)
            os << hex << (unsigned int)elem;
        return os.str();
    }

    //--------------------------------------------------------------------------------
    string_q bnu_2_Hex(const biguint_t& i) {
        return string(BigUnsignedInABase(i, 16));
    }

    //--------------------------------------------------------------------------------
    string_q uint_2_Hex(uint64_t num) {
        biguint_t bn = num;
        return toLower("0x" + bnu_2_Hex(bn));
    }

    //--------------------------------------------------------------------------------
    string_q wei_2_Ether(const string_q& _value) {
        // Make sure the wei number is at least 18 characters long. Once it is,
        // reverse it, put a decimal at the 18th position, reverse it back,
        // trim leading '0's except the tens digit.
        string_q ret = _value;
        if (ret.length() < 18)
            ret = substitute(padLeft(_value, 18), " ", "0");
        reverse(ret);
        ret = extract(ret, 0, 18) + "." + extract(ret, 18);
        reverse(ret);
        ret = trimLeading(ret, '0');
        if (startsWith(ret, '.'))
            ret = "0" + ret;
        if (contains(ret, "0-")) {
            ret = "-" + substitute(ret, "0-", "0");
        }
        ret = substitute(ret, "-.", "-0.");
        return ret;
    }

    //-----------------------------------------------------------------------
    string_q wei_2_Ether(biguint_t in) {
        string_q ret = wei_2_Ether(bnu_2_Str(in));
        if (contains(ret, "."))
            ret = trimTrailing(ret, '0');
        return trimTrailing(ret, '.');
    }

    //--------------------------------------------------------------------------------
    class bloom_tHex : public BigNumStore<unsigned char> {
    public:
        explicit bloom_tHex(const biguint_t& numIn);
        string_q str;
    };

    //--------------------------------------------------------------------------------
    string_q bloom_2_Bytes(const bloom_t& bl) {
        if (bl == 0)
            return "0x0";
        bloom_tHex b2(bl);
        return ("0x" + padLeft(toLower(b2.str), 512, '0'));
    }

    //--------------------------------------------------------------------------------
    string_q bloom_2_Bits(const bloom_t& bl) {
        if (bl == 0)
            return "0x0";
        string_q ret = substitute(bloom_2_Bytes(bl), "0x", "");
        replaceAll(ret, "0", "0000");  // no bits

        replaceAll(ret, "1", "0001");  // one bit
        replaceAll(ret, "2", "0010");
        replaceAll(ret, "4", "0100");
        replaceAll(ret, "8", "1000");

        replaceAll(ret, "3", "0011");  // two bits
        replaceAll(ret, "5", "0101");
        replaceAll(ret, "6", "0110");
        replaceAll(ret, "9", "1001");
        replaceAll(ret, "a", "1010");
        replaceAll(ret, "c", "1100");

        replaceAll(ret, "7", "0111");  // three bits
        replaceAll(ret, "b", "1011");
        replaceAll(ret, "d", "1101");
        replaceAll(ret, "e", "1110");

        replaceAll(ret, "f", "1111");  // four bits
        return ret;
    }

    //-------------------------------------------------------------------------------------
    string_q bloom_2_Bar(const bloom_t& bl) {
        string_q ret = substitute(bloom_2_Bytes(bl), "0x", "");
        replaceAll(ret, "0", "");   // no bits

        replaceAll(ret, "1", ".");  // one bit
        replaceAll(ret, "2", ".");
        replaceAll(ret, "4", ".");
        replaceAll(ret, "8", ".");

        replaceAll(ret, "3", "-");  // two bits
        replaceAll(ret, "5", "-");
        replaceAll(ret, "6", "-");
        replaceAll(ret, "9", "-");
        replaceAll(ret, "a", "-");
        replaceAll(ret, "c", "-");

        replaceAll(ret, "7", "+");  // three bits
        replaceAll(ret, "b", "+");
        replaceAll(ret, "d", "+");
        replaceAll(ret, "e", "+");

        replaceAll(ret, "f", "o");  // four bits
        return ret;
    }

    //--------------------------------------------------------------------------------
    bool str_2_Bool(const string_q& str) {
        return static_cast<bool>(str % "true" || str_2_Int(str) != 0);
    }

    //--------------------------------------------------------------------------------
    int64_t str_2_Int(const string_q& str) {
        return (int64_t)(isHexStr(str) ? hex_2_Int64(str) : strtol(str.c_str(), NULL, 10));
    }

    //--------------------------------------------------------------------------------
    uint64_t str_2_Uint(const string_q& str) {
        return (uint64_t)(isHexStr(str) ? hex_2_Uint64(str) : strtoul(str.c_str(), NULL, 10));
    }

    //--------------------------------------------------------------------------------
    string_q str_2_Hex(const string_q& str) {
        if (str == "null")
            return str;
        if (str.empty())
            return "0x0";
        biguint_t bn = str_2_Wei(str);
        return toLower("0x" + bnu_2_Hex(bn));
    }

    //--------------------------------------------------------------------------------
    gas_t str_2_Gas(const string_q& str) {
        return str_2_Uint(str);
    }

    //--------------------------------------------------------------------------------
    double str_2_Double(const string_q& str) {
        return static_cast<double>(strtold(str.c_str(), NULL));
    }

    //--------------------------------------------------------------------------------
    inline bigint_t str_2_BigInt_nonhex(const string_q& s) {
        biguint_t val;
        if (s[0] == '-') {
            string_q ss = s.substr(1,s.length());
            val = str_2_BigUint(ss);
            return bigint_t(val, -1);
        } else if (s[0] == '+') {
            string_q ss = s.substr(1,s.length());
            val = str_2_BigUint(ss);
            return bigint_t(val, 1);
        }
        return str_2_BigUint(s);
    }

    //--------------------------------------------------------------------------------
    inline string_q getMax(size_t bits) {
        typedef map<size_t, string_q> sizeMap;
        static sizeMap map;
        if (map.size() == 0) {
            map[256] = "115792089237316195423570985008687907853269984665640564039457584007913129639935";
            map[248] = "452312848583266388373324160190187140051835877600158453279131187530910662655";
            map[240] = "1766847064778384329583297500742918515827483896875618958121606201292619775";
            map[232] = "6901746346790563787434755862277025452451108972170386555162524223799295";
            map[224] = "26959946667150639794667015087019630673637144422540572481103610249215";
            map[216] = "105312291668557186697918027683670432318895095400549111254310977535";
            map[208] = "411376139330301510538742295639337626245683966408394965837152255";
            map[200] = "1606938044258990275541962092341162602522202993782792835301375";
            map[192] = "6277101735386680763835789423207666416102355444464034512895";
            map[184] = "24519928653854221733733552434404946937899825954937634815";
            map[176] = "95780971304118053647396689196894323976171195136475135";
            map[168] = "374144419156711147060143317175368453031918731001855";
            map[160] = "1461501637330902918203684832716283019655932542975";
            map[152] = "5708990770823839524233143877797980545530986495";
            map[144] = "22300745198530623141535718272648361505980415";
            map[136] = "87112285931760246646623899502532662132735";
            map[128] = "340282366920938463463374607431768211455";
            map[120] = "1329227995784915872903807060280344575";
            map[112] = "5192296858534827628530496329220095";
            map[104] = "20282409603651670423947251286015";
            map[ 96] = "79228162514264337593543950335";
            map[ 88] = "309485009821345068724781055";
            map[ 80] = "1208925819614629174706175";
            map[ 72] = "4722366482869645213695";
            map[ 64] = "18446744073709551615";
            map[ 56] = "72057594037927935";
            map[ 48] = "281474976710655";
            map[ 40] = "1099511627775";
            map[ 32] = "4294967295";
            map[ 24] = "16777215";
            map[ 16] = "65535";
            map[  8] = "255";
        }
        return map[bits];
    }

    //--------------------------------------------------------------------------------
    bigint_t str_2_BigInt(const string_q& s, size_t bits) {
        if (s.empty() || s == "0x")
            return 0;

        if (!isHexStr(s))
            return str_2_BigInt_nonhex(s);

        biguint_t uValIn = str_2_BigUint(s);

        string_q ss = substitute(s, "0x", "");
        ss = trimLeading(ss, '0');
        size_t len = ss.length();

extern uint64_t verbose;
if (verbose > 1) {
    cout << "bits:         " << bits << endl;
    cout << "len:          " << len << endl;
    cout << "l*4:          " << len * 4 << endl;
    cout << "b/4:          " << (bits / 4) << endl;
}

        if (bits != 257 && len < bits / 4)
            ss = padLeft(ss, bits / 4, '0');
        else
            bits = min((size_t)256, len * 4);

if (verbose > 1)
    cout << "s:            " << s << endl;

        string_q maxStr = getMax(bits);
        if (maxStr.empty())
            return uValIn;
        bigint_t maxInt = bigint_t(str_2_BigUint(maxStr), 1);

if (verbose > 1) {
    cout << "maxStr:       " << maxStr << endl;
    cout << "maxInt:       " << maxInt << endl;
}

        bigint_t sVal = bigint_t(uValIn, 1);
if (verbose > 1) {
    cout << "sVal:         " << sVal << endl;
    cout << "(maxInt / 2): " << (maxInt / 2) << endl;
}

        if (sVal > (maxInt / 2)) // If it's bigger than half, we have to wrap
            sVal = sVal - maxInt - 1; // wrap if larger than half of max int256

if (verbose > 1) {
    cout << "sVal2:        " << sVal << endl;
}

        return sVal;
    }

    //--------------------------------------------------------------------------------
    biguint_t str_2_BigUint(const string_q& str, size_t bits) {
        if (str.empty() || str == "0x")
            return 0;

        string_q ss = substitute(str, "0x", "");
        ss = trimLeading(ss, '0');

        biguint_t ret;
        if (isHexStr(str)) {
            size_t lenInBits = ss.length() * 4;
            if (lenInBits > bits && bits != 257) {
                reverse(ss);
                ss = ss.substr(0,bits/4);
                reverse(ss);
            }
            ret = str_2_Wei("0x" + ss);
        } else {
            ret = biguint_t(BigUnsignedInABase(ss, 10));
        }

        if (bits == 257)
            return ret;

        string_q maxStr = getMax(bits);
        if (maxStr.empty())
            return ret;
        biguint_t maxInt = biguint_t(BigUnsignedInABase(maxStr, 10));

extern uint64_t verbose;
if (verbose > 1) {
    cout << "bits:         " << bits << endl;
    cout << "maxStr:       " << maxStr << endl;
    cout << "maxInt:       " << maxInt << endl;
    cout << "ret:          " << ret << endl;
}

        if (ret > maxInt) // If it's bigger than the max size, we have to wrap
            ret = (ret % maxInt);

        return ret;
    }

    //--------------------------------------------------------------------------------
    address_t str_2_Addr(const string_q& str) {
        if (isZeroAddr(str))
            return "0x0";

        string_q ret = substitute(str, "0x", "");
        if (ret.length() == 64) {
            string_q leading(64-40, '0');
            if (startsWith(ret, leading))
                replace(ret, leading, "");
        }

        return "0x" + toLower(padLeft(ret, 20 * 2, '0'));
    }

    //--------------------------------------------------------------------------------
    hash_t str_2_Hash(const string_q& str) {
        if (isZeroHash(str))
            return "0x0";
        string_q ret = substitute(str, "0x", "");
        return toLower("0x" + padLeft(ret, 32 * 2, '0'));
    }

    //--------------------------------------------------------------------------------
    biguint_t str_2_Wei(const string_q& str) {
        if (contains(str, "0x"))
            return biguint_t(BigUnsignedInABase(extract(str, 2).c_str(), 16));
        if (contains(str, "e"))
            return exp_2_BigUint(str.c_str());
        return str_2_BigUint(str);
    }

    //--------------------------------------------------------------------------------
    bloom_t str_2_Bloom(const string_q& str) {
        return str_2_Wei(str);
    }

    //--------------------------------------------------------------------------------
    topic_t str_2_Topic(const string_q& str) {
        return str_2_Wei(str);
    }

    //--------------------------------------------------------------------------------
    string_q bool_2_Str(bool num) {
        if (!num)
            return "false";
        return "true";
    }

    //--------------------------------------------------------------------------------
    string_q bool_2_Str_t(bool num) {
        if (!num)
            return "";
        return "true";
    }

    //--------------------------------------------------------------------------------
    string_q int_2_Str(int64_t i) {
        ostringstream os;
        os << i;
        return os.str();
    }

    //--------------------------------------------------------------------------------
    string_q uint_2_Str(uint64_t i) {
        ostringstream os;
        os << i;
        return os.str();
    }

    //--------------------------------------------------------------------------------
    string_q gas_2_Str(const gas_t& gas) {
        return uint_2_Str(gas);
    }

    //--------------------------------------------------------------------------------
    string_q double_2_Str(double f, size_t nDecimals) {

        // if no nDecimals specified, default to 10 with trailing zero truncation
        bool truncate = false;
        if(nDecimals == NOPOS) {
            nDecimals = 10;
            truncate = true;
        }

        stringstream stream;
        stream << fixed << setprecision((int)nDecimals) << f;
        string_q str = stream.str();
        if(truncate) {
            str.erase(str.find_last_not_of('0') + 1, string_q::npos);
            // if all decimals gone, truncate period
            str.erase(str.find_last_not_of('.') + 1, string_q::npos);
        }
        return str;
    }

    //--------------------------------------------------------------------------------
    string_q bni_2_Str(const bigint_t& num) {
        return (num.isNegative() ? string("-") : "") + bnu_2_Str(num.getMagnitude());
    }

    //--------------------------------------------------------------------------------
    string_q bnu_2_Str(const biguint_t& num) {
        return string(BigUnsignedInABase(num, 10));
    }

    //--------------------------------------------------------------------------------
    string_q addr_2_Str(const address_t& addr) {
        return (addr.empty() ? "0x0" : addr);
    }

    //--------------------------------------------------------------------------------
    string_q hash_2_Str(const hash_t& hash) {
        return (hash.empty() ? "0x0" : hash);
    }

    //--------------------------------------------------------------------------------
    string_q wei_2_Str(const wei_t& wei) {
        return bnu_2_Str(wei);
    }

    //--------------------------------------------------------------------------------
    string_q bloom_2_Str(const bloom_t& bloom) {
        return bnu_2_Str(bloom);
    }

    //--------------------------------------------------------------------------------
    string_q topic_2_Str(const topic_t& topic) {
        return ("0x" + padLeft(toLower(bnu_2_Hex(topic)), 64, '0'));
    }

    //--------------------------------------------------------------------------------
    bool isZeroHash(const hash_t& hash) {
        if (!isNumeral(hash) && !isHexStr(hash))
            return false;
        return (str_2_Wei(hash) == 0);
    }

    //--------------------------------------------------------------------------------
    bool isZeroAddr(const address_t& addr) {
        return isZeroHash(addr);
    }

    //--------------------------------------------------------------------------------
    bool isNumeral(const string_q& test) {
        for (size_t i = 0 ; i < test.length() ; i++)
            if (!isdigit(test[i]))
                return false;
        return true;
    }

    //--------------------------------------------------------------------------------
    bool isHexStr(const string_q& str) {
        if (!startsWith(str, "0x") || str.size() < 2)
            return false;
        for (auto ch : extract(str,2))
            if (!isxdigit(ch))
                return false;
        return true;
    }

    //--------------------------------------------------------------------------------
    bool isAddress(const address_t& addrIn) {
        return (addrIn.length() == 42 && isHexStr(addrIn));
    }

    //--------------------------------------------------------------------------------
    bool isHash(const hash_t& hashIn) {
        return (hashIn.length() == 66 && isHexStr(hashIn));
    }

    //--------------------------------------------------------------------------------
    bool isUnsigned(const string_q& in) {
        // Empty string is not valid...
        if (in.empty())
            return false;
        // ...first character must be 0-9 (no negatives)...
        if (!isdigit(in[0]))
            return false;
        // ...or first two must be '0x' and the third must be non negative hex digit
        if (startsWith(in, "0x") && in.length() > 2)
            return isxdigit(in.at(2));
        return true;
    }

    //--------------------------------------------------------------------------------
    timestamp_t str_2_Ts(const string_q& str) {
        return str_2_Int(str);
    }

    //----------------------------------------------------------------------------------------------------
    timestamp_t date_2_Ts(const time_q& timeIn) {
        time_q  jan1970(1970, 1, 1, 0, 0, 0);
        if (timeIn < jan1970)
            return 0;

        int64_t j70 = jan1970.GetTotalSeconds();
        int64_t t   = timeIn.GetTotalSeconds();
        return (t - j70);
    }

    //--------------------------------------------------------------------------------
    string_q ts_2_Str(timestamp_t ts) {
        return int_2_Str(ts);
    }

    //----------------------------------------------------------------------------------------------------
    time_q ts_2_Date(timestamp_t tsIn) {
        time_t utc = tsIn;
        tm unused;
        struct tm *ret = gmtime_r(&utc, &unused);

        char retStr[40];
        strftime(retStr, sizeof(retStr), "%Y-%m-%d %H:%M:%S UTC", ret);

        string_q str = retStr;
        uint32_t y = (uint32_t)str_2_Uint(nextTokenClear(str, '-'));
        uint32_t m = (uint32_t)str_2_Uint(nextTokenClear(str, '-'));
        uint32_t d = (uint32_t)str_2_Uint(nextTokenClear(str, ' '));
        uint32_t h = (uint32_t)str_2_Uint(nextTokenClear(str, ':'));
        uint32_t mn = (uint32_t)str_2_Uint(nextTokenClear(str, ':'));
        uint32_t s = (uint32_t)str_2_Uint(nextTokenClear(str, ' '));
        return time_q(y, m, d, h, mn, s);
    }

    //
    // NOT IN HEADER
    //
    //--------------------------------------------------------------------------------
    uint64_t hex_2_Uint64(const string_q& str) {

        string_q hex = toLower(startsWith(str, "0x") ? extract(str, 2) : str);
        reverse(hex);

        const char *s = hex.c_str();
        uint64_t ret = 0, mult = 1;
        while (*s) {
            int val = *s - '0';
            if (*s >= 'a' && *s <= 'f')
                val = *s - 'a' + 10;
            ret += (mult * (uint64_t)val);
            s++;
            mult *= 16;
        }

        return ret;
    }

    //--------------------------------------------------------------------------------
    biguint_t exp_2_BigUint(const string_q &s) {
        string_q exponent = s.c_str();
        string_q decimals = nextTokenClear(exponent, 'e');
        string_q num = nextTokenClear(decimals, '.');
        uint64_t nD = decimals.length();
        uint64_t e = str_2_Uint(exponent);
        biguint_t ee = 1;
        uint64_t power = e - nD;
        for (uint64_t i = 0 ; i < power ; i++)
            ee *= 10;
        num += decimals;
        return str_2_BigUint(num) * ee;
    }

    //--------------------------------------------------------------------------------
    bloom_tHex::bloom_tHex(const biguint_t& numIn) {

        len = 1024;
        allocate(1024);

        biguint_t x2(numIn);
        unsigned int nDigits = 0;
        while (x2.len != 0) {
            biguint_t lastDigit(x2);
            lastDigit.divide(16, x2);
            blk[nDigits] = (unsigned char)lastDigit.to_uint();
            nDigits++;
        }
        len = nDigits;

        char s[1024+1];
        memset(s, '\0', sizeof(s));
        for (unsigned int p = 0 ; p < len ; p++) {
            unsigned short c = blk[len-1-p];  // NOLINT
            s[p] = ((c < 10) ? char('0' + c) : char('A' + c - 10));  // NOLINT
        }
        str = s;
    }

    //----------------------------------------------------------------------------
    typedef unsigned char uchar_t;
    inline uchar_t hex_2_Ascii(const char * const str) {
        uchar_t c;
        c =  (uchar_t)((str[0] >= 'A' ? ((str[0] & 0xDF) - 'A') + 10 : (str[0] - '0')));
        c *= 16;
        c = (uchar_t)(c + (str[1] >= 'A' ? ((str[1]&0xDF)-'A')+10 : (str[1]-'0')));
        return c;
    }

    //----------------------------------------------------------------------------
    string_q hex_2_Str(const string_q& inHex, size_t nBytes) {
        string_q in = (startsWith(inHex, "0x") ? extract(inHex, 2) : inHex);
        in = in.substr(0, nBytes * 2);
        // TODO(tjayrush): what is this substitute for? Some weird test case? Try to remove it
        in = substitute(in, "2019", "27");

        string_q ret;
        while (!in.empty()) {
            string_q nibble = extract(in, 0, 2);
            in = extract(in, 2);
            char ch = (char)hex_2_Ascii((char*)nibble.c_str());  // NOLINT
            ret += (char)ch;
        }
        return ret;
    }

    //----------------------------------------------------------------------------
    string_q hex_2_Str_old(const string_q& inHex) {
        string_q ret, in = (startsWith(inHex, "0x") ? extract(inHex, 2) : inHex);
        while (!in.empty()) {
            string_q nibble = extract(in, 0, 2);
            in = extract(in, 2);
            char ch = (char)hex_2_Ascii((char*)nibble.c_str());  // NOLINT
            if (!isprint(ch))
                return "";
            ret += (char)ch;
        }
        return ret;
    }

}  // namespace qblocks
