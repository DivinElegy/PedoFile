#include "pacdrive.h"
#include "socket_server.h"
#include "logger.h"
#include "main.h"

int main (int argc, char* argv[])
{
    char keycode[100];
    bzero(keycode, 100);
    init_logger();
    start_socket_server(SOCKET_SERVER_PORT);
    init_pac();

    while (1)
    { 
        update_clients();
        log_key(keycode);

        if(strcmp("NO_CHANGE",keycode) != 0)
        {
	    write_socket(keycode);
        }
    }

    return 0;
}
