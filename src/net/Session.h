/***
 *
 * Copyright (C) 2018 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#ifndef SESSION_H
#define SESSION_H

#include <string>
#include "Socket.h"

class Session
{
public:
    Session(){}
    bool Connect(const std::string& ip, uint16_t port);
    void Close();
    void Update();

    void SendUInt(uint32_t value) const;
    void SendUShort(uint16_t value) const;
    void SendByte(char byte) const;
    void SendString(const std::string& value) const;
    void Send(const char* data, size_t size) const;

    inline bool IsRunning() const
    {
        return m_Socket.IsConnected();
    }

private:   
    Socket m_Socket;
    std::string m_IP;
    uint16_t m_Port;

};

#endif // SESSION_H