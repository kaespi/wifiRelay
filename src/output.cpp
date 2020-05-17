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

#include "output.hpp"

#include <sstream>
#include <HardwareSerial.h>

using namespace relayhost;

const unsigned MAX_BUF_LEN = 255;

bool Output::outputSerial;
Verbosity Output::verbLevel;

void Output::init(bool serial, Verbosity verb)
{
    // initialize serial connection if configured to use it
    if (serial)
    {
        Serial.flush();
        Serial.begin(115200);
        Serial.println();
        Serial.println();

        outputSerial = true;
    }

    verbLevel = verb;
}

void Output::Error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buf[MAX_BUF_LEN];
    buf[0] = 'E';
    buf[1] = ':';
    buf[2] = ' ';
    vsnprintf(buf+3, MAX_BUF_LEN-3, fmt, args);
    Serial.println(buf);
}

void Output::Debug(const char *fmt, ...)
{
    if (verbLevel > Verbosity::VERB_NONE)
    {
        va_list args;
        va_start(args, fmt);
        char buf[MAX_BUF_LEN];
        buf[0] = 'D';
        buf[1] = ':';
        buf[2] = ' ';
        vsnprintf(buf+3, MAX_BUF_LEN-3, fmt, args);
        Serial.println(buf);
    }
    
}
