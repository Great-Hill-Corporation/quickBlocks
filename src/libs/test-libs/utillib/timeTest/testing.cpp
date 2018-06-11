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
#include <string>
#include <algorithm>
#include "utillib.h"

//------------------------------------------------------------------------
class CThisTest : public testing::Test {
public:
                 CThisTest(void) : Test() {}
    virtual void SetUp    (void) {}
    virtual void TearDown (void) {}
};

//------------------------------------------------------------------------
TEST_F(CThisTest, TestTime) {
    SFTime time1(2016,10,1,12,0,0);
    SFTime time2(2018,6,2,12,0,0);

    cerr << "Running " << testName << "\n";
    cerr << "\ttime1:  " << time1 << "\n";
    cerr << "\ttime2:  " << time2 << "\n";

    ASSERT_FALSE("time1 > time2",  (time1 > time2));
    ASSERT_TRUE ("time1 !< time2", (time1 < time2));
    ASSERT_TRUE ("time1.month == 10", (time1.GetMonth() == 10));
    ASSERT_TRUE ("time2.day == 2", (time2.GetDay() == 2));

    return true;
}}

#include "options.h"
//------------------------------------------------------------------------
int main(int argc, const char *argv[]) {

    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    while (!options.commandList.empty()) {
        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;

        switch (options.testNum) {
            case 0: LOAD_TEST(TestTime); break;
        }
    }

    return RUN_ALL_TESTS();
}
