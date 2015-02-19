#include "pacdrive.h"

HIDInterface *pac;
char ledbytes[2];

bool match_pac(struct usb_dev_handle *usbdev) {
   return
       ((usb_device(usbdev)->descriptor.idVendor == VENDOR_ID_ULTIMARC) &&
       (usb_device(usbdev)->descriptor.idProduct == PRODUCT_ID_PACDRIVE));
}

void init_pac() {
  hid_return ret;
  HIDInterfaceMatcher matcher = { VENDOR_ID_ULTIMARC,
                                  PRODUCT_ID_PACDRIVE,
                                  (void *)match_pac
                                };


  // This does a malloc under the covers.  
  // Make sure to hid_delete_HIDInterface()...  that's close_pac for us
  pac = hid_new_HIDInterface();
  if (pac == NULL) {
      fprintf(stderr, "init_pac(): failed to get a new HID interface... d'oh\n");
  }

  ret = hid_force_open(pac, 0, &matcher, 3);

  if (ret != HID_RET_SUCCESS) {
    fprintf(stderr, "init_pac(): hid_force_open failed with return code %d\n", ret);
  }
}

void set_led_state(int led, int state) {
    PacData pacdata;
    char mask, *byteptr;
    int result = -1;

    memset(&pacdata, 0, sizeof(PacData));

    if (led < BYTE2_LED_INDEX_START) {
        mask = 1 << (led - BYTE1_LED_INDEX_START);
        byteptr = &ledbytes[1];
    } else {
        byteptr = &ledbytes[0];
        mask = 1 << (led - BYTE2_LED_INDEX_START);
    }

    if (state) {
        *byteptr = *byteptr | mask;
    } else { 
        *byteptr = *byteptr & ~mask;
    }

    pacdata.Data[0] = ledbytes[0];
    pacdata.Data[1] = ledbytes[1];

    result = hid_set_output_report(pac, PAC_PATH_IN, PAC_PATHLEN, (char *)&pacdata, sizeof(PacData));

    if (result == HID_RET_SUCCESS) {
        result = 0;
    } else {
        fprintf(stderr, "Error result of sending output report: %d\n", result);
    }
}

void close_pac() {
   usb_release_interface(pac->dev_handle, 0);
   hid_close(pac);
   hid_delete_HIDInterface(&pac);  
}

