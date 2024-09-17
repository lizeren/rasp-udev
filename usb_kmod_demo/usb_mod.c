#include <linux/usb.h>
#include <linux/module.h>
const uint16_t VENDOR_ID  = 0x0951;
const uint16_t PRODUCT_ID  = 0x1666;

/* Define USB device ID table */
static const struct usb_device_id my_usb_table[] = {
    { USB_DEVICE(VENDOR_ID, PRODUCT_ID) },  // Replace VENDOR_ID and PRODUCT_ID with your device's values
    { } /* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, my_usb_table);


/* Probe function: called when the device is connected */
static int my_usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "My custom USB device is connected\n");
    // Initialization code here
    return 0;
}

/* Disconnect function: called when the device is disconnected */
static void my_usb_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "My custom USB device is disconnected\n");
    // Cleanup code here
}
static struct usb_driver my_usb_driver = {
    .name = "my_custom_usb_driver",
    .id_table = my_usb_table,  // Referencing the ID table defined earlier
    .probe = my_usb_probe,     // Function called when the device is plugged in
    .disconnect = my_usb_disconnect, // Function called when the device is unplugged
};

/* Register the USB driver */
static int __init my_usb_init(void)
{
    return usb_register(&my_usb_driver);
}

/* Deregister the USB driver */
static void __exit my_usb_exit(void)
{
    usb_deregister(&my_usb_driver);
}

module_init(my_usb_init);
module_exit(my_usb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Custom USB Driver Module");
