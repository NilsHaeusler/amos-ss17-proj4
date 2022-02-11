/**
 * @file utilities.h
 *
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

namespace utils {
  bool existsFile(const std::string& filepath) noexcept;
  bool existsDirectory(const std::string& dirpath) noexcept;
  bool endsWith(const std::string &s, const std::string &end) noexcept;
  std::vector<std::string> getConfigFilenames(const std::string &config_dir) noexcept;
}

#endif /* UTILITIES_H */
