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
#include "options.h"

//------------------------------------------------------------
SFString diffStr(const SFString& str1, const SFString& str2) {
    SFString diff = str1;
    SFString junk = str2;
    while (!junk.empty()) {
        SFString line = nextTokenClear(junk,'\n');
        replace(diff, line,"\n");
    }
    SFString ret = trim(diff.Substitute("\n\n","\n"), '\n');
    if (!ret.empty())
        ret += "\n";
    return ret;
}

//------------------------------------------------------------
SFString removeField(const SFString& strIn, const SFString& field) {

    SFString search = "\"" + field + "\":";
    if (!contains(strIn, search))
        return strIn;

    SFString ret;
    SFString str = strIn;
    //while (contains(str, search))
    {
        size_t start = str.find(search);
        SFString before = str.substr(0,start);
        SFString rest   = str.substr(start);

        size_t end = rest.find(",")+1; // first comma
        if (startsWith(rest, search+"[")) // unless it's an array, then end of array
            end = rest.find("]")+1;
        SFString during = rest.substr(0,end);
        SFString after  = rest.substr(end);

        before = trim(before, '\n');
        during = trim(during, '\n');
        after  = trim(after,  '\n');
        ret += (before + after);
        str = after;
    }

    return ret;
}

//------------------------------------------------------------
const SFString removes[] = {
    // fields in RPC but not in QuickBlocks
    "author", "condition", "creates", "extraData", "mixHash", "networkId", "chainId",
    "nonce", "nonce", // NOT A DUP--IT NEEDS TO BE HERE BECAUSE THERE ARE TWO DIFFERENT NONCES
    "publicKey", "r", "raw", "receiptsRoot", "s", "sealFields", "sha3Uncles", "size", "standardV", "stateRoot",
    "totalDifficulty", "transactionsRoot", "uncles", "v", "logsBloom",
    // fields in QuickBlocks but not in RPC
    "contractAddress", "cumulativeGasUsed", "receipt", "address", "data", "logIndex", "topics", "price", "finalized", "isError",

    // WARNING: status must be last because we only use it after byzan
    "status", 
    // WARNING: status must be last because we only use it after byzan
};
uint32_t nRemoved = sizeof(removes) / sizeof(SFString);

//------------------------------------------------------------
SFString hiddenFields(void) {
    SFString ret = "Hidden fields:\n";
    for (uint32_t i = 0 ; i < nRemoved ; i++) {
        ret += removes[i];
        if (i < nRemoved-1)
            ret += ", ";
    }
    return ret + "\n\n";
}

//------------------------------------------------------------
SFString cleanAll(const SFString& str, bool remove, bool isByzan) {

    if (!remove)
        nRemoved = 0;
    else if (isByzan)
        nRemoved--; // don't remove status if were post-byzantium

    SFString orig = str;
    replaceAny(orig, "\t\r {}","");
    replaceAll(orig, ",",",\n"); // put everything on its own line
    for (uint32_t i = 0 ; i < nRemoved ; i++) {
        SFString search = "\"" + removes[i] + "\":";
        while (contains(orig, search)) {
            orig = removeField(orig, removes[i]);
        }
    }
    orig = orig.Substitute("}]","");
    replaceAll(orig, ",", "");
    replaceAll(orig, "[", "");
    replaceAll(orig, "]", "");
    replaceAll(orig, "\"to\":null","\"to\":\"0x0\"");
    orig = trimWhitespace(orig);
    orig = orig.Substitute("\"result\":","").Substitute("\"transactions\":","").Substitute("\"logs\":","");
    orig = orig.Substitute("\"jsonrpc\":","");
    orig = orig.Substitute("0x" + SFString('0',512), "0x0"); // minimize bloom filters
    replaceAll(orig, "\n\n", "\n");
    // get rid of id
    SFString ret;
    while (!orig.empty()) {
        SFString line = nextTokenClear(orig, '\n');
        if (!startsWith(line, "\"id\":"))
            ret += (line + "\n");
    }
    return trim(ret.Substitute("\"\"","\"\n\"").Substitute("\n\n","\n"), '\n');
}

//------------------------------------------------------------
SFString sorted(const SFString& inIn) {
    SFStringArray inList, outList;
    SFString in = inIn;
    while (!in.empty()) {
        inList[inList.getCount()] = nextTokenClear(in,'\n');
    }
    inList.Sort(sortByStringValue);
    for (uint32_t i = 0 ; i < inList.getCount()-1 ; i++) {
        if (inList[i] != inList[i+1] && contains(inList[i], ":"))
            outList[outList.getCount()] = inList[i];
    }
    // add the last one of it's not already there
    if (inList[inList.getCount()-1] != outList[outList.getCount()-1])
        outList[outList.getCount()] = inList[inList.getCount()-1];

    SFString ret;
    for (uint32_t i = 0 ; i < outList.getCount() ; i++)
        ret += (outList[i] + "\n");
    return ret;
}

//------------------------------------------------------------
SFString normalizeBlock(const SFString& inIn, bool remove, bool isByzan) {
    return sorted(cleanAll(inIn, remove, isByzan));
}
