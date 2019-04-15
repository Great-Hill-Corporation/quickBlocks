/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "options.h"
#include "question.h"

//------------------------------------------------------------------------------------------------
bool COptions::handle_ls(void) {

    // ls mode does not require a running node
    nodeNotRequired();

    ostringstream os;
    os << endl << cGreen << "Monitor path: " << cWhite << monitorsPath << endl;

    CStringArray files;
    listFilesInFolder(files, monitorsPath + "*.*", false);

    CAccountNameArray accounts;
    for (auto file : files) {
        if (endsWith(file, ".acct.bin")) {
            replace(file, monitorsPath, "");
            CAccountName item;
            item.addr = nextTokenClear(file, '.');
            getNamedAccount(item, item.addr);
            item.name = substitute(substitute(item.name, "(", ""), ")", "");
            accounts.push_back(item);
        }
    }
    if (accounts.size() == 0) {
        CAccountName item;
        item.addr = "none";
        accounts.push_back(item);
    }
    sort(accounts.begin(), accounts.end());

    if (stats || contains(tool_flags, "-l")) {
        for (auto acct : accounts) {
            os << "Address: " << cTeal << acct.addr << cOff << endl;
            os << "\tName:       " << cYellow << (acct.name.empty() ? "" : acct.name) << cOff << endl;
            os << "\tFilename:   " << cYellow << substitute(getMonitorPath(acct.addr), getCachePath(""), "./") << cOff << endl;
            os << "\tFile size:  " << cYellow << (((double)fileSize(getMonitorPath(acct.addr)))/1024./1024.) << " MB" << cOff << endl;
            os << "\tLast block: " << cYellow << asciiFileToString(getMonitorLast(acct.addr)) << cOff;
            os << "\tnRecords:   " << cYellow << fileSize(getMonitorPath(acct.addr)) / sizeof(CAppearance_base) << cOff << endl;
        }

    } else {
#ifdef TIOCGSIZE
        struct ttysize ts;
        ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
        size_t ncols = ts.ts_cols;
#elif defined(TIOCGWINSZ)
        struct winsize ts;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
        size_t ncols = ts.ws_col;
#endif /* TIOCGSIZE */
        ncols = max(ncols, (size_t)1);

        size_t mx = 0;
        for (auto acct : accounts)
            mx = max(mx, acct.addr.length() + 20 + 3);
        mx = max(mx, (size_t)50);

        uint64_t cnt = 0;
        os << "  " << cGreen << "Current monitors:" << cOff << endl;
        for (auto acct : accounts) {
            os << "    " << cTeal << acct.addr;
            string_q nm = acct.name.empty() ? "" : " (" + acct.name.substr(0,20) + ")";
            os << padRight(nm, 23);
            if (ncols == 1 || !(++cnt % (ncols / mx)))
                os << endl;
        }
        os << cOff << endl;
    }

    if (isTestMode())
        cout << substitute(os.str(), getCachePath(""), "$BLOCK_CACHE/");
    else
        cout << os.str();

    return true;
}
