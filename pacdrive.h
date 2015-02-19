#include <errno.h>
#include <fcntl.h>
#include <hid.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <usb.h>
#include <string.h>

#define PAC_USB_TIMEOUT	100

#define VENDOR_ID_ULTIMARC       0xD209
#define PRODUCT_ID_IPAC_USB      0x0301 
#define PRODUCT_ID_PACDRIVE      0x1500

#define PAC_DATA_HEADER_LEN 2
#define PAC_DATA_DATA_LEN   2

typedef struct _PAC_DATA_BLOCK {
    char Header[PAC_DATA_HEADER_LEN];
    char Data[PAC_DATA_DATA_LEN];
} PacData;


/* used by libhid to send/recv reports (input/output reports)*/
/* very simple paths, thankfully (from lsusb -vvv) */
#define PAC_PATHLEN 1
static int const PAC_PATH_IN[PAC_PATHLEN] =  { 0x00090001 };
static int const PAC_PATH_OUT[PAC_PATHLEN] = { 0x0008004b };

#define BYTE1_LED_INDEX_START   1
#define BYTE1_LED_INDEX_END     8
#define BYTE2_LED_INDEX_START   9
#define BYTE2_LED_INDEX_END     16

#define LED_INDEX_START         BYTE1_LED_INDEX_START
#define LED_INDEX_END           BYTE2_LED_INDEX_END

void init_pac();
void set_led_state(int led, int state);
void cleanup_pac();
void close_pac();


