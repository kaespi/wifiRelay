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

#include "wifi.hpp"

#include "output.hpp"

using namespace relayhost;

Wifi::Wifi()
{
}

Wifi::~Wifi()
{
}

bool Wifi::init(const std::string &ssid, const std::string &passphrase, const unsigned chn,
                const bool hide, const unsigned numConnections)
{
    // stop DHCP service
    wifi_softap_dhcps_stop();

    // configure WiFi to access point mode
    WiFi.persistent(false);
    if (!WiFi.mode(WIFI_AP))
    {
        Output::Error("Failed setting AP WiFi mode");
        return false;
    }

    // set IP address and subnet mask for access point (i.e. this device)
    if (!WiFi.softAPConfig(IPAddress(192,168,0,1), IPAddress(192,168,0,1), IPAddress(255, 255, 255, 0)))
    {
        Output::Error("Failed configuring the IP address");
        return false;
    }

    // initialize DHCP configuration
    struct dhcps_lease dhcpConfig;
    dhcpConfig.enable = true;
    dhcpConfig.start_ip = IPAddress(192,168,0,2);
    dhcpConfig.end_ip   = IPAddress(192,168,0,100);
    // this call here usually fails, I have no idea why. Therefore not checking
    // its return value
    wifi_softap_set_dhcps_lease(&dhcpConfig);

    if (!wifi_softap_dhcps_start())
    {
        Output::Error("Failed starting DHCP service");
        return false;
    }

    // start the access point
    if (!WiFi.softAP(ssid.c_str(), passphrase.c_str(), chn, hide, 5/*numConnections*/))
    {
        Output::Error("Failed starting the AP");
        return false;
    }

    Output::Debug("AP IP address: %s", WiFi.softAPIP().toString().c_str());
    
    return true;
}
