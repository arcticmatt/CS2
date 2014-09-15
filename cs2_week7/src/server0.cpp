/**
@file
@author Ben Yuan
@date 2013
@copyright 2-clause BSD; see License section

@brief
A simple echo server to validate the network wrapper.

@section License

Copyright (c) 2012-2013 California Institute of Technology.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the California Institute of Technology.

*/

#include "server0.h"

using namespace CS2Net;

int main(int argc, char ** argv)
{

    REQUIRE(argc == 2, "usage: %s port", argv[0]);

    CS2Net::Socket listener;
    CS2Net::Socket * incoming_conn = NULL;

    // bind to some arbitrarily chosen port
    // with a backlog of 3 connections allowed
    int err = listener.Bind(atoi(argv[1]), 3);
    REQUIRE(err == 0, "Failed to bind!");

    std::vector<CS2Net::PollFD> poll_vec(1);
    poll_vec[0].sock = &listener;
    poll_vec[0].SetRead(true);

    while (true)
    {
        int poll_err = CS2Net::Poll(&poll_vec, 10);
        REQUIRE(poll_err >= 0, "error on poll");
        // is there a hangup or error?
        if (poll_vec[0].HasHangup() || poll_vec[0].HasError())
        {
            // o noes there's a hangup and/or error
            printf("Error occured while polling\n");
        }
        // did we get anything to read?
        if (poll_vec[0].CanRead())
        {
            incoming_conn = listener.Accept();
            REQUIRE(incoming_conn != NULL, "Failed to accept!");
            std::string *incoming = incoming_conn->Recv(1024, false);
            if (incoming == NULL)
            {
                // Error receiving from the incomming connection
                ERROR("recv error: %s", strerror(errno));
            }
            else
            {
                // Receiving suceeded.
                printf("The message is: %s\n", incoming->c_str());
                int ret2 = incoming_conn->Send(incoming);
                if(ret2 < 0)
                {
                    // Sending message failed.
                    if(ret2 == -1)
                    {
                        ERROR("send error: %s", strerror(errno));
                    }
                    else
                    {
                        ERROR("programmer is doing it wrong");
                    }
                }
            }
            delete incoming_conn;
        }
    }
    return 0;
}


