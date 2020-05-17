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

#include <ESP8266WiFi.h>

namespace relayhost
{
    //! Class taking care of the WiFi stuff in the relay
    class Wifi
    {
    public:
        //! Constructor
        Wifi();

        //! Destructor
        ~Wifi();

        //! Initialize the host
        bool init(const std::string &ssid, const std::string &passphrase, const unsigned chn = 1,
                  const bool hide = false, const unsigned numConnections = 2);
    
    };
}
