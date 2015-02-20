#include "socket_server.h"
#include "logger.h"
#include "key_names.h"

int keyboard = 0;
int count = 0;
int event_size = sizeof(struct input_event);
int bytes_read = 0;
struct input_event event[64];
struct parse_key *key = NULL;

void init_logger()
{
    // Open the keyboard input device for listening
    keyboard = open(KEYBOARD_DEVICE, O_RDONLY);
    if (keyboard == -1)
    {
        fprintf(stderr, "Unable to open keyboard\n");
        exit(EXIT_FAILURE);
    }
}

void log_key(KeyState *state)
{    
    // Read a keypress
    bytes_read = read(keyboard, event, event_size * 64);
    // Loop through the generated events
    for (count = 0; count < (bytes_read / event_size); count++)
    {
        if (EV_KEY == event[count].type)
        {
            // Find the correct name of the keypress. This is O(n) :-(
            for (key = key_names; key->name != NULL; key++)
            {
                if (key->value == (unsigned) event[count].code)
                {
                    if (event[count].value == KEY_PRESS)
                    {
                        strcpy(state->key, key->name);
                        strcpy(state->state, "PRESS");
                    } else if (event[count].value == KEY_RELEASE) {
                        strcpy(state->key, key->name);
                        strcpy(state->state, "RELEASE");
                    } else {
                        strcpy(state->state, "NO_CHANGE");
                    }

                    break;
                }
            }
        }
    }
}
