#include "ip_math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int mask_to_int(char mask_value) {
  unsigned int mask = 0xFFFFFFFF;
  char host_bit = MAX_MASK_LEN - mask_value;

  for (int i = 0; i < host_bit; ++i) {
    UNSET_BIT(mask, i); // mask &= ~(1 << i);
  }
  return mask;
}

static unsigned int (*sep_ip(const char *ip_addr))[4] {
  int i = 0;
  static unsigned int octets[4];
  char *temp = malloc(strlen(ip_addr) + 1);
  strcpy(temp, ip_addr);

  char *token = strtok(temp, ".");
  while (token) {
    octets[i] = atoi(token);
    token = strtok(NULL, ".");
    ++i;
  }
  return &octets;
}

static unsigned int ip_to_int(const char *ip_addr) {
  unsigned int rc = 0;
  unsigned int(*octets)[4] = sep_ip(ip_addr);
  for (int i = 0; i < 4; ++i) {
    (*octets)[i] <<= (8 * (3 - i));
    rc += (*octets)[i];
  }
  return rc;
}

static char *int_to_ip(unsigned int int_ip) {
  size_t used = 0;
  unsigned int ip_arr[4];
  char *ip = (char *)malloc(16);
  if (!ip)
    return NULL;

  memset(ip_arr, '\0', 16);
  ip_arr[0] = int_ip >> 8 * 3;
  ip_arr[1] = (int_ip >> 8 * 2) - (ip_arr[0] << 8);
  ip_arr[2] = (int_ip >> 8 * 1) - (ip_arr[0] << 8 * 2) - (ip_arr[1] << 8);
  ip_arr[3] =
      int_ip - (ip_arr[0] << 8 * 3) - (ip_arr[1] << 8 * 2) - (ip_arr[2] << 8);

  for (int i = 0; i < 4; ++i) {
    sprintf(ip, "%s.%d", ip, ip_arr[i]);
  }
  return ip + 1;
}

static char *get_broadcast_ip(const char *ip_addr, char mask) {
  unsigned int int_ip = ip_to_int(ip_addr);
  unsigned int int_mask = mask_to_int(mask);
  unsigned int network_ip = int_ip & int_mask;
  unsigned int broadcast_ip = network_ip | ~int_mask;

  return int_to_ip(broadcast_ip);
}

static char *get_network_id(const char *ip_addr, char mask) {
  unsigned int int_ip = ip_to_int(ip_addr);
  unsigned int int_mask = mask_to_int(mask);
  unsigned int network_ip = int_ip & int_mask;
  return int_to_ip(network_ip);
}

static unsigned int get_subnet_cardinality(const char mask) {
  //- 2: network id + broadcast id
  return pow(2, (MAX_MASK_LEN - mask)) - 2;
}

static int is_subnet_member(const char *network_id, const char mask,
                            const char *ip) {
  char *ip_network_id = get_network_id(ip, mask);
  return (strcmp(network_id, ip_network_id) == 0);
}

void init_ip_utils(IPUtils **self) {
  if (!(*self = (IPUtils *)malloc(sizeof(IPUtils))))
    return;

  (*self)->get_broadcast_addr = get_broadcast_ip;
  (*self)->get_network_id = get_network_id;
  (*self)->int_to_ip = int_to_ip;
  (*self)->ip_to_int = ip_to_int;
  (*self)->is_subnet_member = is_subnet_member;
  (*self)->get_subnet_cardinality = get_subnet_cardinality;
}
