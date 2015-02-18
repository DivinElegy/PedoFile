#include <errno.h>
#include <fcntl.h>
#include <hid.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <usb.h>

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

void init_pac();

/* Set the LED states */
int set_led_state(PacData *data);

/* Called when completely done talking to pac -- the is the opposite of init_pac*/
void cleanup_pac(void);

/* Close the HID after done doing get/set */
int close_pac();


