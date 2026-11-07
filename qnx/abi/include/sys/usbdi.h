/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_USBDI_H
#define BMW_QNX_USBDI_H
#include <stddef.h>
#include <stdint.h>
#ifndef EOK
#define EOK 0
#endif

#define USB_VERSION 0x0110
#define USBD_VERSION 0x0101
#define USBD_CONNECT_WAIT 60
#define USBD_CONNECT_WILDCARD 0xffffffffu
#define USBD_TIME_INFINITY 0xffffffffu
#define _USBDI_NFUNCS 3
#define USB_DESC_DEVICE 1
#define USB_DESC_CONFIGURATION 2
#define USB_DESC_INTERFACE 4
#define USB_DESC_ENDPOINT 5
#define USB_ATTRIB_BULK 2
#define USB_ENDPOINT_IN 0x80
#define USB_TYPE_VENDOR 0x40
#define USB_RECIPIENT_DEVICE 0
#define USB_DIRECTION_HOST 0x80
#define USB_DIRECTION_DEVICE 0
#define URB_DIR_IN 1
#define URB_DIR_OUT 2
#define URB_DIR_NONE 3
#define URB_SHORT_XFER_OK 4
#define USBD_URB_STATUS_MASK 0xff000000u
#define USBD_USB_STATUS_MASK 0x00ffffffu
#define USBD_STATUS_CMP 0x01000000u
#define USBD_STATUS_TIMEOUT 0x04000000u
#define USBD_STATUS_STALL 4
#define USBD_STATUS_DEV_NOANSWER 5

struct usbd_connection;
struct usbd_device;
struct usbd_desc_node;
struct usbd_urb;
struct usbd_pipe;

typedef struct {
    uint32_t vendor, device, dclass, subclass, protocol;
} usbd_device_ident_t;
typedef struct {
    uint8_t path, devno;
    uint16_t generation;
    usbd_device_ident_t ident;
    uint32_t config, iface, alternate;
} usbd_device_instance_t;
typedef struct {
    uint32_t nentries;
    void (*insertion)(struct usbd_connection *, usbd_device_instance_t *);
    void (*removal)(struct usbd_connection *, usbd_device_instance_t *);
    void (*event)(struct usbd_connection *, usbd_device_instance_t *, uint16_t);
} usbd_funcs_t;
typedef struct {
    const char *path;
    uint16_t vusb, vusbd;
    uint32_t flags;
    int32_t argc;
    char **argv;
    uint32_t evtbufsz;
    usbd_device_ident_t *ident;
    usbd_funcs_t *funcs;
    uint16_t connect_wait;
    uint8_t evtprio;
    uint8_t bmw_reserved[13];
} usbd_connect_parm_t;

typedef struct {
    uint8_t bLength, bDescriptorType, bEndpointAddress, bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} usbd_endpoint_descriptor_t;
typedef struct {
    uint8_t bLength, bDescriptorType, bInterfaceNumber, bAlternateSetting;
    uint8_t bNumEndpoints, bInterfaceClass, bInterfaceSubClass, bInterfaceProtocol, iInterface;
} usbd_interface_descriptor_t;
typedef union {
    usbd_endpoint_descriptor_t endpoint;
    usbd_interface_descriptor_t interface;
    uint16_t bmw_private_storage[9];
} usbd_descriptors_t;

#ifdef __cplusplus
extern "C" {
#endif
int usbd_connect(usbd_connect_parm_t *, struct usbd_connection **);
int usbd_disconnect(struct usbd_connection *);
int usbd_attach(struct usbd_connection *, usbd_device_instance_t *, size_t, struct usbd_device **);
int usbd_detach(struct usbd_device *);
int usbd_reset_device(struct usbd_device *);
int usbd_open_pipe(struct usbd_device *, usbd_descriptors_t *, struct usbd_pipe **);
int usbd_close_pipe(struct usbd_pipe *);
int usbd_abort_pipe(struct usbd_pipe *);
struct usbd_urb *usbd_alloc_urb(struct usbd_urb *);
struct usbd_urb *usbd_free_urb(struct usbd_urb *);
void *usbd_alloc(size_t);
void usbd_free(void *);
int usbd_setup_bulk(struct usbd_urb *, uint32_t, void *, uint32_t);
int usbd_setup_vendor(struct usbd_urb *, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, void *, uint32_t);
int usbd_io(struct usbd_urb *, struct usbd_pipe *, void (*)(struct usbd_urb *, struct usbd_pipe *, void *), void *, uint32_t);
int usbd_urb_status(struct usbd_urb *, uint32_t *, uint32_t *);
usbd_descriptors_t *usbd_parse_descriptors(struct usbd_device *, struct usbd_desc_node *, uint8_t, int, struct usbd_desc_node **);
usbd_interface_descriptor_t *usbd_interface_descriptor(struct usbd_device *, uint8_t, uint8_t, uint8_t, struct usbd_desc_node **);
#ifdef __cplusplus
}
#endif
#endif
