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
#include "options.h"

extern const char* STR_NAME_DATA;
//-----------------------------------------------------------------------
int main(int argc, const char *argv[]) {

    getCurlContext()->provider = "None";  // This will run without a node
    etherlib_init();

    COptions options;
    options.setProgramName(basename((char*)argv[0]));

    // Handle help on this tool's command line for this tool only if there are not enough args or if
    // --help is the first item in the command list. Otherwise, we need to pass it to subcommand
    bool isHelp = (argc == 1);
    CStringArray h = { "--help", "-h" };
    for (auto i : h) {
        if (argc >= 2 && i == argv[1]) {
            if (!isHelp)
                isHelp = true;
        }
    }
    if (isHelp) {
        optionOn(OPT_HELP);
        if (isTestMode())
            colorsOff();
        return usage();
    }

    // Act normally
    if (!options.prepareArguments(argc, argv))
        return 0;

    while (!options.commandList.empty()) {
        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;
        string_q cmd = options.toolName.first + " " + options.args + " --qblocks";
        if (isTestMode())
            cout << "calling: " << cmd << "\n";
        if (system(cmd.c_str())) { }  // Don't remove. Silences compiler warnings
        cout << "\n";
    }
    return 0;
}
