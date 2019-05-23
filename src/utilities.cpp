/**
 * @file utilities.cpp
 *
 * This file offers utility functions in the `utils` namespace for common used
 * file system operations.
 */

#include "utilities.h"
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Checks if a file exists on the file system.
 *
 * @param filepath: the path to the file as string
 * @return true if file exists, otherwise false
 */
bool utils::existsFile(const std::string& filepath) noexcept
{
    struct stat64 sb;

    if (stat64(filepath.c_str(), &sb) == 0 && S_ISREG(sb.st_mode))
    {
        return true;
    }
    return false;
}

/**
 * Checks if a directory exists on the file system.
 *
 * @param dirpath: the path to the directory as string
 * @return true if directory exists, otherwise false
 */
bool utils::existsDirectory(const std::string& dirpath) noexcept
{
    struct stat64 sb;

    if (stat64(dirpath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        return true;
    }
    return false;
}


/**
 * Checks if a string ends with another string.
 *
 * @param s: the string to check
 * @param end: the ending to be checked for
 * @return true if ending is the same, false otherwise
 */
bool utils::endsWith(const string &s, const string &end) noexcept
{
    if (s.length() < end.length())
    {
        return false;
    }

    return 0 == s.compare(s.length() - end.length(), end.length(), end);
}


/**
 * Get all available Lua config files in a directory.
 *
 * @param config_dir: the directory to check for Lua files
 * @return a vector containing all filenames is returned, on error an empty vector is returned
 */
vector<string> utils::getConfigFilenames(const string &config_dir) noexcept
{
    DIR *dir;
    struct dirent *ent;
    vector<string> filenames;

    if (!existsDirectory(config_dir))
    {
        cerr << "config file directory does not exist: " << config_dir << endl;
    }
    else if ((dir = opendir(config_dir.c_str())) != nullptr)
    {
        while ((ent  = readdir(dir)) != nullptr)
        {
            string s(ent->d_name);
            if (utils::endsWith(s, ".lua"))
                filenames.push_back(s);
        }
    }
    else
    {
        cerr << "cannot open config dir: " << config_dir << endl;
    }

    return filenames;
}
