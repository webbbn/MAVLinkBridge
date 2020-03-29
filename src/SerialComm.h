/****************************************************************************
 *
 * Copyright (c) 2015, 2016 Gus Grubba. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file SerialComm.h
 *
 * @author Gus Grubba <mavlink@grubba.com>
 */

#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include "CommLink.h"

#include <termios.h>

class Serial_Port;

class SerialComm : public CommLink
{
public:
    SerialComm(bool raw, bool verbose);
    ~SerialComm();
    enum {
        // Status flags
        SERIAL_PORT_CLOSED,
        SERIAL_PORT_OPEN,
        SERIAL_PORT_ERROR
    };
    bool        init(std::string port);
    bool        open();
    void        close();
    void        write(mavlink_message_t& message);
    void        write(std::vector<uint8_t> data);
    //-- From gThread
    void        run();
private:
    int         _openPort       (const char* port);
    int         _writePort      (void *buffer, int len);
    int         _readMessage    (mavlink_message_t& message);
    bool        _setupPort      (int baud);
private:
    int         _fd;
    int         _baudrate;
    int         _status;
    std::string     _uart_name;
    struct termios  _savedtio;
    bool        _verbose;
};

#endif // SERIALCOMM_H
