/*
 * Copyright 2011-2013 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ARX_PLATFORM_ENVIRONMENT_H
#define ARX_PLATFORM_ENVIRONMENT_H

#include <string>

#include "platform/Platform.h"

namespace fs { class path; }

namespace platform {

/*!
 * \brief Initialize envirenment functions
 *
 * On Windows, this sets the %FOLDERID_SavedGames% environment variable to the
 * standard "Saved Games" directory.
 *
 * \param argv0 a path to use for \ref getExecutablePath if no OS-specific function is
 *              available to determine the executable path. Will be ignored if it doesn't
 *              contain any slashes.
 */
void initializeEnvironment(const char * argv0);

/*!
 * \brief Expand a string containing environment variables
 *
 * Expansion is done as it would be in the system's shell.
 *
 * \param in the string to expand.
 */
std::string expandEnvironmentVariables(const std::string & in);

/*!
 * \brief Get a Windows registry entry
 *
 * This does nothing on non-Windows systems.
 *
 * \param name path of the registry entry to read. This is looked up under HKCU first, and
 *             if it doesn't exist there, under HKLM.
 * \param result string to receive the value of the registry key.
 *
 * \return \c true of the requested registry key exists, \c false otherwise.
 */
bool getSystemConfiguration(const std::string & name, std::string & result);

/*!
 * \brief Get the path to the current running executable
 * 
 * \return the executable path if possible or an empty string otherwise
 */
fs::path getExecutablePath();

/*!
 * \brief Get the full path to a helper executable
 *
 * Tries to find a helper executable in the same directory as the current program, in the
 * parent directory, or in the libexec directory in the prefix where arx is installed.
 * If found, returns a full path to the executable.
 * Otherwise, returns a relative path containing only the executable name.
 *
 * \return a path or name suitable for CreateProcess(), exec*p() or system() calls.
 */
fs::path getHelperExecutable(const std::string & name);

#if ARX_PLATFORM != ARX_PLATFORM_WIN32
static const char * const env_list_seperators = ":";
#else
static const char * const env_list_seperators = ";";
#endif

/*!
 * \brief Check if a file descriptor has been closed or redirected to /dev/null
 *
 * \param fd the file descriptor to test - 0 for stdin, 1 for stdout and 2 for stderr.
 */
bool isFileDescriptorDisabled(int fd);

//! Check if standard input is open and doesn't point to /dev/null
inline bool hasStdIn() { return !isFileDescriptorDisabled(0); }

//! Check if standard output is open and doesn't point to /dev/null
inline bool hasStdOut() { return !isFileDescriptorDisabled(1); }

//! Check if standard error is open and doesn't point to /dev/null
inline bool hasStdErr() { return !isFileDescriptorDisabled(2); }

} // namespace platform

#endif // ARX_PLATFORM_ENVIRONMENT_H
