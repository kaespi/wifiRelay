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

#include "relay.hpp"
#include "output.hpp"

#include <Arduino.h>

using namespace relayhost;

Relay::Relay()
    : nextUpdateSet(false), msNextUpdate(0), state(RelayState::OFF)
{
}

Relay::~Relay()
{
}

void Relay::init(const unsigned relayPin, const unsigned msWaitClosed)
{
    msLeaveRelayOn = msWaitClosed;
    pin = relayPin;

    pinMode(pin, OUTPUT);
    setOff();
}

void Relay::update()
{
    if (nextUpdateSet && millis() > msNextUpdate)
    {
        nextUpdateSet = false;
        if (nextUpdateState==RelayState::ON)
        {
            setOn();
        }
        else
        {
            setOff();
        }
        
    }
}

void Relay::toggleOnOff()
{
    // this button press overrides a pending change...
    nextUpdateSet = false;

    if (state==RelayState::OFF)
    {
        setOn();
    }
    else
    {
        if (state != RelayState::ON)
        {
            Output::Error("Don't know in which state the relay is (%u)", state);
        }
        setOff();
    }
}

void Relay::triggerOnce()
{
    if (nextUpdateSet && state==RelayState::ON && nextUpdateState==RelayState::OFF)
    {
        // a trigger was already commanded, therefore do nothing
    }
    else
    {
        nextUpdateSet = true;
        msNextUpdate = millis() + msLeaveRelayOn;
        nextUpdateState = RelayState::OFF;

        setOn();
    }
}

void Relay::setOn()
{
    Output::Debug("Relay closed");
    state = RelayState::ON;
    digitalWrite(pin, LOW);
}

void Relay::setOff()
{
    Output::Debug("Relay opened");
    state = RelayState::OFF;
    digitalWrite(pin, HIGH);
}
