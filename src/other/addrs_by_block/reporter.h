#pragma once
/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/

#include "acctlib1.h"
//-----------------------------------------------------------------------------
extern uint64_t startBlock;
extern uint64_t nBlocks;

//----------------------------------------------------------------------------
inline unsigned char hex2Ascii(const char *str) {
    unsigned char c;
    c =  (unsigned char)((str[0] >= 'A' ? ((str[0]&0xDF)-'A')+10 : (str[0]-'0')));
    c *= 16;
    c = (unsigned char)(c + (str[1] >= 'A' ? ((str[1]&0xDF)-'A')+10 : (str[1]-'0')));
    return c;
}

//-----------------------------------------------------------------------------
class CReporter : public CVisitData {
public:
    CArchive *archives[256];
    blknum_t nBlocksVisited;
    txnum_t nTransVisited;
    blknum_t nAccts;
    blknum_t maxDepth;
    string_q maxMatch1;
    string_q maxMatch2;
    bool getNext;
    double startLoad;
    double endLoad;
    double startPrint;
    double endPrint;
    uint64_t stopping;
    CTreeRoot *tree;

    CReporter(void)
        : nBlocksVisited(0), nTransVisited(0),
          nAccts(0), maxDepth(0), getNext(false),
          startLoad(0), endLoad(0), startPrint(0), endPrint(0), stopping(30), tree(NULL)
    {
        for (int i=0;i<256;i++)
            archives[i] = NULL;
    }

    ~CReporter(void) { if (tree) delete tree; }

    void startTimer(const string_q& msg) {
        cerr << msg << "\n"; cerr.flush();
        if (startLoad == 0.0) startLoad = qbNow();
        else                  startPrint = qbNow();
    }

    void stopTimer(void) {
        if (endLoad == 0.0) endLoad = qbNow();
        else                endPrint = qbNow();
    }

    void finalReport(void) {
        cout << "nAccts:    " << cGreen << nAccts         << cOff << "\n";
        cout << "maxDepth:  " << cGreen << maxDepth       << cOff << "\n";
        cout << "maxMatch1: " << cGreen << maxMatch1      << cOff << "\n";
        cout << "maxMatch2: " << cGreen << maxMatch2      << cOff << "\n";
//        cout << "nBlocks:   " << cGreen << nBlocksVisited << cOff << "\n";
//        cout << "nTrans:    " << cGreen << nTransVisited  << cOff << "\n";
        cout.flush();
    }

    void interumReport(void);
    bool isMax(void) {
        if (contains(strs0, "-0+-0+-0+-0+-0+-0+-0+-0+-0+-0+-0+000000000000000000000"))
            return false;
        return (countOf(strs0, '-') > maxDepth);
    }
};

//-----------------------------------------------------------------------------
extern bool printTree(const CTreeNode *node, void *data);
extern bool buildTree(CBlock& block, void *data);
