#include "pacdrive.h"
#include "socket_server.h"
#include "logger.h"
#include "main.h"

int main (int argc, char* argv[])
{
    char keycode[100];
    bzero(keycode, 100);
    init_logger();
    init_pac();
//    set_led_state(1, 1);
    start_socket_server(SOCKET_SERVER_PORT);

    while (1)
    {
        update_clients();
        log_key(keycode);

        if(strcmp("NO_CHANGE",keycode) != 0)
        {
            fprintf(stderr, "%s\n", keycode);
	    write_socket(keycode);
        }
    }

    return 0;
}
