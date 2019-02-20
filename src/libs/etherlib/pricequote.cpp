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
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include <algorithm>
#include "pricesource.h"
#include "pricequote.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CPriceQuote, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextPricequoteChunk(const string_q& fieldIn, const void *dataPtr);
static string_q nextPricequoteChunk_custom(const string_q& fieldIn, const void *dataPtr);

//---------------------------------------------------------------------------
void CPriceQuote::Format(ostream& ctx, const string_q& fmtIn, void *dataPtr) const {
    if (!m_showing)
        return;

    string_q fmt = (fmtIn.empty() ? expContext().fmtMap["pricequote_fmt"] : fmtIn);
    if (fmt.empty()) {
        ctx << toJson();
        return;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextPricequoteChunk, this);
}

//---------------------------------------------------------------------------
string_q nextPricequoteChunk(const string_q& fieldIn, const void *dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const CPriceQuote *>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool CPriceQuote::setValueByName(const string_q& fieldName, const string_q& fieldValue) {
    // EXISTING_CODE
    if ( fieldName % "date" || fieldName % "timestamp" ) {
        timestamp = str_2_Int(fieldValue);
        date = ts_2_Date((timestamp_t)timestamp);
        return true;
    }
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'c':
            if ( fieldName % "close" ) { close = str_2_Double(fieldValue); return true; }
            break;
        case 't':
            if ( fieldName % "timestamp" ) { timestamp = str_2_Ts(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CPriceQuote::finishParse() {
    // EXISTING_CODE
    date = ts_2_Date((timestamp_t)timestamp);
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CPriceQuote::Serialize(CArchive& archive) {

    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CBaseNode::Serialize(archive);
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
bool CPriceQuote::SerializeC(CArchive& archive) const {

    // Writing always write the latest version of the data
    ((CPriceQuote*)this)->m_schema = getVersionNum();  // NOLINT
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << timestamp;
    archive << close;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CPriceQuoteArray& array) {
    uint64_t count;
    archive >> count;
    array.resize(count);
    for (size_t i = 0 ; i < count ; i++) {
        ASSERT(i < array.capacity());
        array.at(i).Serialize(archive);
    }
    return archive;
}

//---------------------------------------------------------------------------
CArchive& operator<<(CArchive& archive, const CPriceQuoteArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0 ; i < array.size() ; i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CPriceQuote::registerClass(void) {
    // only do this once
    if (HAS_FIELD(CPriceQuote, "schema")) return;

    size_t fieldNum = 1000;
    ADD_FIELD(CPriceQuote, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(CPriceQuote, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(CPriceQuote, "showing", T_BOOL,  ++fieldNum);
    ADD_FIELD(CPriceQuote, "cname", T_TEXT,  ++fieldNum);
    ADD_FIELD(CPriceQuote, "timestamp", T_TIMESTAMP, ++fieldNum);
    ADD_FIELD(CPriceQuote, "close", T_DOUBLE, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CPriceQuote, "schema");
    HIDE_FIELD(CPriceQuote, "deleted");
    HIDE_FIELD(CPriceQuote, "showing");
    HIDE_FIELD(CPriceQuote, "cname");

    builtIns.push_back(_biCPriceQuote);

    // EXISTING_CODE
    ADD_FIELD(CPriceQuote, "date", T_DATE, ++fieldNum);
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextPricequoteChunk_custom(const string_q& fieldIn, const void *dataPtr) {
    const CPriceQuote *pri = reinterpret_cast<const CPriceQuote *>(dataPtr);
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
                // EXISTING_CODE
                // EXISTING_CODE
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CPriceQuote::readBackLevel(CArchive& archive) {

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
            if ( fieldName % "close" ) return double_2_Str(close, 5);
            break;
        case 't':
            if ( fieldName % "timestamp" ) return ts_2_Str(timestamp);
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

    item.Format(os, "", nullptr);
    os << "\n";
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
static string_q getWeiQuote(const CPriceQuoteArray& quotes, timestamp_t ts, biguint_t weiIn) {
    uint64_t index = indexFromTimeStamp(quotes, ts);
    double price = quotes[index].close * 100.0;
    weiIn *= ((uint64_t)price);
    weiIn /= 100;
    return wei_2_Ether(bnu_2_Str(weiIn));
}

//-----------------------------------------------------------------------
string_q wei_2_Dollars(timestamp_t ts, biguint_t weiIn) {
    if (weiIn == 0)
        return "";

    //TODO(tjayrush): global data
    static CPriceQuoteArray quotes;
    if (quotes.size()) // leave early if we can
        return getWeiQuote(quotes, ts, weiIn);

    { // give ourselves a frame to make the mutex
        mutex aMutex;
        lock_guard<mutex> lock(aMutex);
        if (quotes.size()) // leave early if we can (another thread may have filled the array while we were waiting
            return getWeiQuote(quotes, ts, weiIn);

        string_q message;
        CPriceSource source;
        if (!loadPriceData(source, quotes, false, message, 1)) {
            cerr << "Cannot load price data. Quitting.\n";
            quickQuitHandler(EXIT_FAILURE);
        }
    }
    return getWeiQuote(quotes, ts, weiIn);
}

//-----------------------------------------------------------------------
string_q insertCommas(const string_q& dIn) {
    string_q d = dIn;
    reverse(d);
    string_q ret;
    while (!d.empty()) {
        string_q three = extract(d, 0, 3);
        d = extract(d, 3);
        reverse(three);
        ret = (d.empty()?"":",") + three + ret;
    }
    return ret;
}

//-----------------------------------------------------------------------
string_q displayDollars(timestamp_t ts, biguint_t weiIn) {
    string_q ret = wei_2_Dollars(ts, weiIn);
    string_q d = nextTokenClear(ret, '.');
    d = insertCommas(d);
    return (ret.empty() ? "0.00" : d + "." + extract(ret, 0, 2));
}
// EXISTING_CODE
}  // namespace qblocks

