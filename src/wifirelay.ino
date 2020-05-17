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
#include "webserver.hpp"
#include "relay.hpp"
#include "output.hpp"

static relayhost::Wifi hostWifi;
static relayhost::Webserver hostServer;
static relayhost::Relay hostRelay;

//! port to listen for the HTTP requests
const unsigned port = 7788;
//! pin to which the relay is connected
const unsigned pin = 2;

//! Continuous running loop
void loop()
{
    hostServer.handleRequests();
    hostRelay.update();
}

//! Initialization
void setup()
{
    // for debugging purposes, initialize a serial connection
    relayhost::Output::init(true, relayhost::Verbosity::VERB_2);
    delay(1000);

    // ************** RELAY INITIALIZATION *********************
    relayhost::Output::Debug("Setting up relay");
    hostRelay.init(pin);

    // ************** WIFI NETWORK INITIALIZATION **************
    relayhost::Output::Debug("Setting up WiFi relay host");
    hostWifi.init("<ssid>", "<passphrase>");

    // ************** WEBSERVER INITIALIZATION *****************
    relayhost::Output::Debug("Setting up Webserver");
    hostServer.init(port, &hostRelay);
}
