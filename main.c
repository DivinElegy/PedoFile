#include "pacdrive.h"
#include "socket_server.h"
#include "logger.h"
#include "lightmaps.h"

#include "main.h"

int main (int argc, char* argv[])
{
    struct lightmap *map = NULL;
    KeyState key_state;
    char keycode[100];
    bzero(keycode, 100);

    init_logger();
    init_pac();
    start_socket_server(SOCKET_SERVER_PORT);

    while (1)
    {
        update_clients();
        log_key(&key_state);

        if(strcmp("NO_CHANGE",key_state.state) != 0)
        {
            sprintf(keycode, "%s_%s", key_state.key, key_state.state);

            for (map = light_map; map->key != NULL; map++)
            {
                if (strcmp(map->key, key_state.key) == 0)
                {
		   fprintf(stderr, "state is %d", strcmp("PRESS", key_state.state) ? 1 : 0);
                   //use mapping and state to call set_led_state(map->led, state)
                   break;
                }
            }

            write_socket(keycode);
        }
    }

    return 0;
}
