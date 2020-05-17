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

#include "webserver.hpp"

#include "output.hpp"

using namespace relayhost;

ESP8266WebServer Webserver::server;
Relay *Webserver::relay = nullptr;

Webserver::Webserver()
{
}

Webserver::~Webserver()
{
}

bool Webserver::init(const unsigned port, Relay * const r)
{
    server.on("/", HTTP_POST, handlePostRqst);
    server.begin(port);

    relay = r;
}

void Webserver::handleRequests()
{
    server.handleClient();
}

void Webserver::handlePostRqst()
{
    if (relay != nullptr)
    {
        if (server.hasArg("trigger") && server.arg("trigger").toInt())
        {
            Output::Debug("POST Switch on once");
            relay->triggerOnce();
        }
        if (server.hasArg("toggle") && server.arg("toggle").toInt())
        {
            Output::Debug("POST Toggle");
            relay->toggleOnOff();
        }
    }
}
