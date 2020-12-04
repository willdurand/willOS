#include "ethernet.h"
#include <core/debug.h>
#include <net/arp.h>
#include <stdlib.h>
#include <string.h>

void ethernet_receive_frame(net_interface_t* interface,
                            uint8_t* data,
                            uint32_t len)
{
  ethernet_header_t* frame_header = malloc(sizeof(ethernet_header_t));
  memcpy(frame_header, data, sizeof(ethernet_header_t));
  frame_header->ethertype = NTOHS(frame_header->ethertype);

  DEBUG("received frame from: %02x:%02x:%02x:%02x:%02x:%02x on interface=%d",
        frame_header->src_mac[0],
        frame_header->src_mac[1],
        frame_header->src_mac[2],
        frame_header->src_mac[3],
        frame_header->src_mac[4],
        frame_header->src_mac[5],
        interface->id);

  switch (frame_header->ethertype) {
    case ETHERTYPE_ARP:
      arp_receive_packet(interface,
                         &data[sizeof(ethernet_header_t)],
                         len - sizeof(ethernet_header_t));
      break;
    default:
      DEBUG("unsupported ethernet frame: type=%d", frame_header->ethertype);
  }

  free(frame_header);
  // This is because `data` gets allocated in the driver code.
  free(data);
}

void ethernet_transmit_frame(net_interface_t* interface,
                             uint8_t dst_mac[6],
                             uint16_t ethertype,
                             uint8_t* data,
                             uint32_t len)
{
  ethernet_header_t header = { .ethertype = HTONS(ethertype) };
  memcpy(header.src_mac, interface->mac, 6);
  memcpy(header.dst_mac, dst_mac, 6);

  uint32_t frame_len = sizeof(ethernet_header_t) + len;

  uint8_t* frame = (uint8_t*)calloc(1, frame_len);
  memcpy(frame, &header, sizeof(ethernet_header_t));
  memcpy(frame + sizeof(ethernet_header_t), data, len);

  interface->driver->transmit_frame(frame, frame_len);

  free(frame);
}