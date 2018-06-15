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
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "pricequote.h"
#include "etherlib.h"
#include "pricesource.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CPriceQuote, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextPricequoteChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextPricequoteChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CPriceQuote::Format(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
    if (!m_showing)
        return;

    if (fmtIn.empty()) {
        ctx << toJson();
        return;
    }

    string_q fmt = fmtIn;
    if (handleCustomFormat(ctx, fmt, dataPtr))
        return;

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextPricequoteChunk, this);
}

//---------------------------------------------------------------------------
string_q nextPricequoteChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return ((const CPriceQuote *)dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CPriceQuote::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    if ( fieldName % "date" || fieldName % "timestamp" ) {
        timestamp = toLong(fieldValue);
        date = dateFromTimeStamp((timestamp_t)timestamp);
        return true;
    }
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'c':
            if ( fieldName % "close" ) { close = str2Double(fieldValue); return true; }
            break;
        case 't':
            if ( fieldName % "timestamp" ) { timestamp = toTimestamp(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CPriceQuote::finishParse() {
    // EXISTING_CODE
    date = dateFromTimeStamp((timestamp_t)timestamp);
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CPriceQuote::Serialize(SFArchive& archive) {

    if (archive.isWriting())
        return ((const CPriceQuote*)this)->SerializeC(archive);

    // If we're reading a back level, read the whole thing and we're done.
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> timestamp;
    archive >> close;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CPriceQuote::SerializeC(SFArchive& archive) const {

    // Writing always write the latest version of the data
    ((CPriceQuote*)this)->m_schema = getVersionNum();
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << timestamp;
    archive << close;

    return true;
}

//---------------------------------------------------------------------------
void CPriceQuote::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    size_t fieldNum = 1000;
    ADD_FIELD(CPriceQuote, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CPriceQuote, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CPriceQuote, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CPriceQuote, "timestamp", T_TIMESTAMP, ++fieldNum);
    ADD_FIELD(CPriceQuote, "close", T_DOUBLE, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CPriceQuote, "schema");
    HIDE_FIELD(CPriceQuote, "deleted");
    HIDE_FIELD(CPriceQuote, "showing");

    // EXISTING_CODE
    ADD_FIELD(CPriceQuote, "date", T_DATE, ++fieldNum);
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextPricequoteChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CPriceQuote *pri = (const CPriceQuote *)dataPtr;
    if (pri) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            case 'd':
                if ( fieldIn % "date" ) return pri->date.Format(FMT_JSON);
                break;
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, pri);
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CPriceQuote::handleCustomFormat(CExportContext& ctx, const string_q& fmtIn, void *dataPtr) const {
    // EXISTING_CODE
    // EXISTING_CODE
    return false;
}

//---------------------------------------------------------------------------
bool CPriceQuote::readBackLevel(SFArchive& archive) {

    CBaseNode::readBackLevel(archive);
    bool done = false;
    // EXISTING_CODE
    if (m_schema < 2000) {
        //
        // we used to store a lot more data than we do now, so
        // we have to read this older format old format was:
        // timestamp, open, high, low, close, quoteVolume, volume,
        // weightedAvg but now we read only timstamp and close
        double junk;
        archive >> timestamp;
        archive >> junk;
        archive >> junk;
        archive >> junk;
        archive >> close;
        archive >> junk;
        archive >> junk;
        archive >> junk;
        finishParse();
        done = true;

    }
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
string_q CPriceQuote::getValueByName(const string_q& fieldName) const {

    // Give customized code a chance to override first
    string_q ret = nextPricequoteChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'c':
            if ( fieldName % "close" ) return double2Str(close);
            break;
        case 't':
            if ( fieldName % "timestamp" ) return fromTimestamp(timestamp);
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CBaseNode::getValueByName(fieldName);
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CPriceQuote& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    os << item.Format() << "\n";
    return os;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
//-----------------------------------------------------------------------------------
uint64_t indexFromTimeStamp(const CPriceQuoteArray& quotes, timestamp_t ts) {
    timestamp_t first = (timestamp_t)quotes[0].timestamp;
    if (ts < first)
        return 0;
    timestamp_t since = ts - first;
    return min(quotes.size()-1, size_t(since / (5*60)));
}

//-----------------------------------------------------------------------
string_q asDollars(timestamp_t ts, SFUintBN weiIn) {
    if (weiIn == 0)
        return "";
    static CPriceQuoteArray quotes;
    if (!quotes.size()) {
        string_q message;
        CPriceSource source;
        if (!loadPriceData(source, quotes, false, message, 1)) {
            cerr << "Cannot load price data. Quitting.\n";
            exit(0);
        }
    }
    uint64_t index = indexFromTimeStamp(quotes, ts);
    const CPriceQuote *q = &quotes[index]; // taking a non-const reference
    double price = q->close * 100.0;
    uint64_t pInt = (uint64_t)price;
    weiIn *= pInt;
    weiIn /= 100;
    return wei2Ether(to_string(weiIn).c_str());
}

//-----------------------------------------------------------------------
string_q insertCommas(const string_q& dIn) {
    string_q d = dIn;
    reverse(d);
    string_q ret;
    while (!d.empty()) {
        string_q three = d.substr(0,3);
        d = d.substr(3);
        reverse(three);
        ret = (d.empty()?"":",") + three + ret;
    }
    return ret;
}

//-----------------------------------------------------------------------
string_q dispDollars(timestamp_t ts, SFUintBN weiIn) {
    string_q sBal = asDollars(ts, weiIn);
    string_q d = nextTokenClear(sBal,'.');
    d = insertCommas(d);
    sBal = (sBal.empty() ? "0.00" : d + "." + sBal.substr(0,2));
    return sBal;
}
// EXISTING_CODE
}  // namespace qblocks

