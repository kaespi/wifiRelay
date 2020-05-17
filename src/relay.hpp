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

namespace relayhost
{
    //! Class taking care of the WiFi stuff in the relay
    class Relay
    {
    public:
        //! Constructor
        Relay();

        //! Destructor
        ~Relay();

        //! Initialization
        void init(const unsigned relayPin, const unsigned msWaitClosed = 50000);

        //! Commands a toggling of the relay state
        void toggleOnOff();

        //! Trigger switching on the relay just once
        void triggerOnce();

        //! Updates the relay state (if needed)
        void update();

    private:
        enum class RelayState
        {
            OFF,        //!< relay switched off
            ON,
        };

        //! number of milliseconds to leave the relay on when it is triggered once
        unsigned long msLeaveRelayOn;

        //! pin where the relay is connected to
        unsigned pin;

        //! state of the relay
        RelayState state;

        //! if true then the next update variables are set
        bool nextUpdateSet;

        //! instance of the ESP8266's web server
        unsigned long msNextUpdate;

        //! state of the relay to be applied next
        RelayState nextUpdateState;

        //! sets the state of the relay to on
        void setOn();

        //! sets the state of the relay to off
        void setOff();
    };
}
