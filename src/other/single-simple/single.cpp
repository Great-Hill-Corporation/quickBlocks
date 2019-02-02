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
#include "etherlib.h"

//----------------------------------------------------------------
int main(int argc, const char *argv[]) {
    etherlib_init("binary", quickQuitHandler);
    forEveryFileInFolder(blockCachePath("traces/"), visitFile, NULL);
    forEveryBlockOnDisc(visitBlock, NULL, 0, getLatestBlockFromCache());
    return 1;
}

//----------------------------------------------------------------
bool visitFile(const string_q& path, void *data) {

    if (endsWith(path, '/')) {
        forEveryFileInFolder(path + "*", visitFile, data);
    } else {
        cout << path << "\n";
    }
    return true;
}

//----------------------------------------------------------------
bool visitBlock(CBlock& block, void *data) {

    cout << block << "\n";
    for (uint32_t tr = 0 ; tr < block.transactions.size() ; tr++) {
        cout << block.transactions[tr] << "\n";
    }
    return true;
}
