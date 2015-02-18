#include "pacdrive.h"

HIDInterface *pac;

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
