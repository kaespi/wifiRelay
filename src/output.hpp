// wifiRelay - 230VAC relay controlled through WiFi
// Copyright (C) 2020 Kaspar Giger

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <string>
#include <cstdarg>

namespace relayhost
{
    enum class Verbosity
    {
        VERB_NONE = 0,      //!< Verbosity level 0 (no debug output)
        VERB_1    = 1,      //!< Verbosity level 1 (important debug output)
        VERB_2    = 2       //!< Verbosity level 2 (more debug output)
    };

    //! Class taking care of the debug outputs
    class Output
    {
    public:
        //! Initialize the output
        static void init(bool serial = true, Verbosity verb = Verbosity::VERB_NONE);

        //! Emits a debug message
        static void Debug(const char *fmt, ...);

        //! Emits an error message
        static void Error(const char *fmt, ...);

    
    private:
        //! If true use the serial connection for debugging
        static bool outputSerial;

        //! Current verbosity level
        static Verbosity verbLevel;
    };
}
