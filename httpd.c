#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 1

#include "protocol-server.h"

static void on_data(server_pt srv, int fd)
{
    static char reply[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 12\r\n"
        "Connection: keep-alive\r\n"
        "Keep-Alive: timeout=2\r\n"
        "\r\n"
        "Hello World!";
    char buff[1024];

    if (Server.read(srv, fd, buff, 1024))
        Server.write(srv, fd, reply, sizeof(reply));
}

void timer_task(){}

void on_init(server_pt srv)
{
    Server.run_every(srv, 1, -1, (void *) timer_task, srv);
}

int main(int argc, char *argv[])
{
    struct Protocol protocol = { .on_data = on_data };
    start_server(.protocol = &protocol,
                 .timeout = 2,
                 .on_init = on_init,
                 .threads = THREAD_COUNT);
    return 0;
}
