/**
@file
@author Ben Yuan
@date 2013
@copyright 2-clause BSD; see License section

@brief
A more complex echo client to validate the network wrapper.

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

#include "client1.h"
#include <sys/time.h>

using namespace CS2Net;

int main(int argc, char ** argv)
{

    REQUIRE(argc == 3, "usage: %s hostname port", argv[0]);

    /* TODO: write this code.
    *
    * This should be a client that connects to a remote server,
    * sends a message of your choice no more than once per second,
    * and echoes any messages it receives in the meantime
    * without having to block on recv.
    *
    **/
    long timeDiff = 2;
    timeval t1, t2;
    CS2Net::Socket sock;
    std::string hostname(argv[1]);
    uint16_t port = atoi(argv[2]);
    int ret = sock.Connect(&hostname, port);

    if(ret < 0)
    {
        // Connecting failed
        if(ret == -1) { ERROR("connect error: %s", strerror(errno));
        }
        else if(ret == -3)
        {
            ERROR("connect error: %s", gai_strerror(errno));
        }
        else
        {
            ERROR("programmer is doing it wrong");
        }
    }
    else
    {
        std::vector<CS2Net::PollFD> poll_vec(1);
        poll_vec[0].sock = &sock;
        poll_vec[0].SetRead(true);
        poll_vec[0].SetWrite(true);

        while (true)
        {
            if (timeDiff >= 2)
            {
                std::string to_send("some stuff to send");

                int ret2 = sock.Send(&to_send);
                if(ret2 < 0)
                {
                    // bad stuff happened
                    if(ret2 == -1)
                    {
                        ERROR("send error: %s", strerror(errno));
                    }
                    else
                    {
                        ERROR("programmer is doing it wrong");
                    }
                }
                else
                {
                    // Send succeeded
                    gettimeofday(&t1, NULL);
                    gettimeofday(&t2, NULL);
                    timeDiff = t2.tv_sec - t1.tv_sec;
                }
            }
            else
            {
                gettimeofday(&t2, NULL);
                timeDiff = t2.tv_sec - t1.tv_sec;
            }

            // now do the poll (10 ms timeout)
            int poll_err = CS2Net::Poll(&poll_vec, 10);
            REQUIRE(poll_err >= 0, "error on poll!?");

            // is there a hangup or error?
            if (poll_vec[0].HasHangup() || poll_vec[0].HasError())
            {
                // o noes there's a hangup and/or error
                printf("Error occured while polling\n");
            }
            // did we get anything to read?
            if (poll_vec[0].CanRead())
            {
                // yay the first socket is readable
                std::string *incoming = poll_vec[0].sock->Recv(1024, false);
                if (incoming == NULL)
                {
                    // bad stuff happened
                    ERROR("recv error: %s", strerror(errno));
                }
                else
                {
                    // we got some data yay
                    printf("The reply is: %s\n", incoming->c_str());
                }
            }
        }

        int ret3 = sock.Disconnect();
        if (ret3 < 0)
        {
            // bad stuff happened
            if (ret3 == -1)
            {
                // you might actually be able to ignore these errors
                // but we'll print them anyway
                ERROR("disconnect error: %s", strerror(errno));
            }
            else
            {
                ERROR("programmer is doing it wrong");
            }
        }

    }

    return 0;


}
