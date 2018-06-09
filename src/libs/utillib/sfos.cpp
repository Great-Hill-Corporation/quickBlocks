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
#include <glob.h>
#include <libgen.h>
#include <algorithm>

#include "basetypes.h"

#include "sfos.h"
#include "sftime.h"
#include "string.h"

namespace qblocks {

    #define ANY_FILETYPE -1
    #define remove unlink

    //------------------------------------------------------------------
    static SFString escapePath(const SFString& nameIn) {
        SFString name = nameIn;
        name.ReplaceAll(" ", "\\ ");
        name.ReplaceAll("&", "\\&");
        name.ReplaceAll("(", "\\(");
        name.ReplaceAll(")", "\\)");
        name.ReplaceAll("'", "\\'");
        return name;
    }

    //------------------------------------------------------------------
    static int globErrFunc(const char *epath, int eerrno) {
        //  perror(epath);
        return 0;
    }

    //------------------------------------------------------------------
    int copyFile(const SFString& fromIn, const SFString& toIn) {
        SFString from = escapePath(fromIn);
        SFString to   = escapePath(toIn);

        const SFString copyCmd = "cp -pf";
        SFString command = copyCmd + " " + from + " " + to;
        if (system((const char *)command)) { }  // do not remove. The test just silences compiler warnings
        return static_cast<int>(fileExists(to));
    }

    //------------------------------------------------------------------
    // Returns a list of either files or folders, but not both.
    //------------------------------------------------------------------
    void doGlob(uint32_t& nStrs, SFString *strs, const SFString& maskIn, int wantFiles, bool keepPaths ) {
        ASSERT(!strs || nStrs);

        glob_t globBuf;

        SFString mask = maskIn;

        // should check return code
        glob((const char *)mask, GLOB_MARK, globErrFunc, &globBuf);

        size_t n = globBuf.gl_pathc;
        uint32_t mx = nStrs;
        nStrs = 0;
        char c;

        for (size_t i = 0 ; i < n ; i++) {
            // get path
            char *tmp = globBuf.gl_pathv[i];
            // last char
            c   = tmp[strlen(tmp) - 1];

            // if path ends in '/' then this is directory, filter accordingly

            bool isDir = ('/' == c);
            bool listEm = ((isDir) ? !wantFiles : wantFiles);
            if (wantFiles == ANY_FILETYPE)
                listEm = true;

            if (listEm) {
                if (NULL != strs) {
                    SFString path = globBuf.gl_pathv[i];

                    // filter specified directories and remove trailing '/'
                    if (path.endsWith('/'))
                        path = path.substr(0,path.length() - 1);

                    if (!keepPaths) {
                        // trim path to last directory / file
#ifdef MAC
                        char res[kMaxPathSize];
                        path = basename_r(path.c_str(), res);  // NOLINT
#else
                        path = basename((char *)path.c_str());  // NOLINT
#endif
                        if (path.startsWith('/'))
                            path = path.substr(1);
                        // The path we return is always just the name of the folder or file
                        // without any leading (or even existing) '/'
                        ASSERT(path.length() && path[0] != '/');
                    }

                    if (wantFiles == ANY_FILETYPE) {
                        if (isDir)
                            path = "d-" + path;
                        else
                            path = "f-" + path;
                    }

                    strs[nStrs] = path;
                }

                nStrs++;
                if (NULL != strs && nStrs >= mx) {
                    break;
                }
            }
        }

        globfree(&globBuf);
    }

    //-------------------------------------------------------------------------------------------------------------
    inline bool waitForCreate(const SFString& filename) {
        uint32_t mx = 1000;
        uint32_t cnt = 0;
        while (cnt < mx && !fileExists(filename))
            cnt++;

        return fileExists(filename);
    }

    //------------------------------------------------------------------------------------------
    SFString doCommand(const SFString& cmd) {

        SFTime now = Now();
        SFString tmpPath = "/tmp/";
        SFString filename = tmpPath + makeValidName("qb_" + now.Format("%Y%m%d%H%M%S"));
        SFString theCommand = (cmd + " >" + filename);
        if (system(theCommand.c_str())) { }  // Don't remove. Silences compiler warnings

        // Check twice for existance since the previous command creates the file but may take some time
        waitForCreate(filename);
extern SFString binaryFileToString(const SFString& filename);
        SFString ret = binaryFileToString(filename);
        remove(filename.c_str());
        return trim(ret, '\n');
    }

    //------------------------------------------------------------------
    SFString getCWD(const SFString& filename) {
        char buffer[kMaxPathSize];
        if (::getcwd(buffer, kMaxPathSize)) { }  // do not remove. The test just silences compiler warnings
        SFString folder = buffer;
        if (!folder.endsWith('/'))
            folder += "/";
        return folder + filename;  // may be empty
    }

    //------------------------------------------------------------------
    bool fileExists(const SFString& file) {
        struct stat statBuf;
        return !file.empty() && stat((const char *)file, &statBuf) == 0;
    }

    //------------------------------------------------------------------
    bool folderExists(const SFString& folderName) {
        if (folderName.empty())
            return false;

        SFString folder = folderName;
        if (!folder.endsWith('/'))
            folder += '/';

        uint32_t nFiles = 0;
        listFiles(nFiles, NULL, folder+"*.*");
        // check to see if it is just folders
        if (!nFiles)
            listFolders(nFiles, NULL, folder+"*.*");
        if (!nFiles)
            listFolders(nFiles, NULL, folder+".");

        return (nFiles > 0);
    }

    //------------------------------------------------------------------
    void listFiles(uint32_t& nStrs, SFString *strs, const SFString& mask) {
        uint32_t ret = 0;
        doGlob(ret, strs, mask, true, mask.Contains("/*/")); /* fixes color coding in pico */
        nStrs = ret;
    }

    //------------------------------------------------------------------
    void listFolders(uint32_t& nStrs, SFString *strs, const SFString& mask) {
        uint32_t ret = 0;
        doGlob(ret, strs, mask, false, mask.Contains("/*/")); /* fixes color coding in pico */
        nStrs = ret;
    }

    //------------------------------------------------------------------
    void listFilesOrFolders(uint32_t& nStrs, SFString *strs, const SFString& mask) {
        uint32_t ret = 0;
        doGlob(ret, strs, mask, ANY_FILETYPE, mask.Contains("/*/"));
        nStrs = ret;
    }

    //------------------------------------------------------------------
    uint64_t fileSize(const SFString& filename) {
        if (!fileExists(filename))
            return 0;

        struct stat statBuf;
        stat((const char *)filename, &statBuf);
        return (uint64_t)statBuf.st_size;
    }
} // namespace qblocks

#include "filenames.h"

namespace qblocks {
    //----------------------------------------------------------------------------
    bool establishFolder(const SFString& path, SFString& created) {
        if (fileExists(path) || folderExists(path))
            return true;

        CFilename fullPath(path);
        SFString targetFolder = fullPath.getFullPath();
        size_t find = targetFolder.rfind('/');
        targetFolder = targetFolder.substr(0,find) + "/";
        SFString folder = targetFolder;
        SFString curFolder = "/";
        while (!folder.empty()) {
            curFolder += nextTokenClear(folder, '/') + "/";
            if (!folderExists(curFolder)) {
                mkdir(curFolder.c_str(), (mode_t)0755);
                if (created.empty())
                    created = curFolder;
            }
        }
        return folderExists(targetFolder);
    }
}  // namespace qblocks
