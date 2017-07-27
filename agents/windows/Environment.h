// +------------------------------------------------------------------+
// |             ____ _               _        __  __ _  __           |
// |            / ___| |__   ___  ___| | __   |  \/  | |/ /           |
// |           | |   | '_ \ / _ \/ __| |/ /   | |\/| | ' /            |
// |           | |___| | | |  __/ (__|   <    | |  | | . \            |
// |            \____|_| |_|\___|\___|_|\_\___|_|  |_|_|\_\           |
// |                                                                  |
// | Copyright Mathias Kettner 2017             mk@mathias-kettner.de |
// +------------------------------------------------------------------+
//
// This file is part of Check_MK.
// The official homepage is at http://mathias-kettner.de/check_mk.
//
// check_mk is free software;  you can redistribute it and/or modify it
// under the  terms of the  GNU General Public License  as published by
// the Free Software Foundation in version 2.  check_mk is  distributed
// in the hope that it will be useful, but WITHOUT ANY WARRANTY;  with-
// out even the implied warranty of  MERCHANTABILITY  or  FITNESS FOR A
// PARTICULAR PURPOSE. See the  GNU General Public License for more de-
// ails.  You should have  received  a copy of the  GNU  General Public
// License along with GNU Make; see the file  COPYING.  If  not,  write
// to the Free Software Foundation, Inc., 51 Franklin St,  Fifth Floor,
// Boston, MA 02110-1301 USA.

#ifndef Environment_h
#define Environment_h

#include <string>

class LoggerAdaptor;
class WinApiAdaptor;

class Environment {
public:
    Environment(bool use_cwd, const LoggerAdaptor &logger,
                const WinApiAdaptor &winapi);
    ~Environment();

    // TODO: this is an evil hack, but currently there is at least one global
    // function that requires access to the env that isn't easily refactored
    static Environment *instance();

    std::string hostname() const { return _hostname; }

    std::string currentDirectory() const { return _current_directory; }
    std::string agentDirectory() const { return _agent_directory; }

    std::string pluginsDirectory() const { return _plugins_directory; }
    std::string configDirectory() const { return _config_directory; }
    std::string localDirectory() const { return _local_directory; }
    std::string spoolDirectory() const { return _spool_directory; }
    std::string stateDirectory() const { return _state_directory; }
    std::string tempDirectory() const { return _temp_directory; }
    std::string logDirectory() const { return _log_directory; }
    std::string binDirectory() const { return _bin_directory; }

    std::string logwatchStatefile() const { return _logwatch_statefile; }
    std::string eventlogStatefile() const { return _eventlog_statefile; }

public:
    bool isWinNt() const;

    // return windows version as a combined value, with major version in the
    // upper 8 bits
    // and minor in the lower bits, i.e. 0x0501 for windows xp (32-bit)
    uint16_t winVersion() const;

private:
    std::string determineHostname() const;
    std::string determineCurrentDirectory() const;
    std::string determineAgentDirectory(bool use_cwd) const;
    std::string assignDirectory(const char *name) const;

private:
    static Environment *s_Instance;

    const LoggerAdaptor &_logger;
    const WinApiAdaptor &_winapi;

    const std::string _hostname;

    const std::string _current_directory;
    const std::string _agent_directory;
    const std::string _plugins_directory;
    const std::string _config_directory;
    const std::string _local_directory;
    const std::string _spool_directory;
    const std::string _state_directory;
    const std::string _temp_directory;
    const std::string _log_directory;
    const std::string _bin_directory;

    const std::string _logwatch_statefile;
    const std::string _eventlog_statefile;
};

#endif  // Environment_h
