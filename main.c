#include "ip_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  /*Testing get_broadcast_address()*/
  IPUtils *ip_util;
  init_ip_utils(&ip_util);

  {
    printf("Testing Q1..\n");
    char ip_address[PREFIX_LEN + 1], output_buffer[PREFIX_LEN + 1];
    memset(ip_address, 0, PREFIX_LEN + 1);
    memcpy(ip_address, "192.168.2.10", strlen("192.168.2.10"));
    ip_address[strlen(ip_address)] = '\0';
    char mask = 24;
    memset(output_buffer, 0, PREFIX_LEN + 1);
    strcpy(output_buffer, ip_util->get_broadcast_addr(ip_address, mask));
    printf("broadcast address  = %s\n", output_buffer);
    printf("Testing Q1 Done.\n");
  }

  /*Testing get_ip_integer_equivalent()*/
  {
    printf("Testing Q2..\n");
    char ip_address[PREFIX_LEN + 1];
    memset(ip_address, 0, PREFIX_LEN + 1);
    memcpy(ip_address, "192.168.2.10", strlen("192.168.2.10"));
    ip_address[strlen(ip_address)] = '\0';
    unsigned int a = ip_util->ip_to_int(ip_address);
    printf("a = %u\n", a);
    printf("Testing Q2 Done.\n");
  }

  /*Testing get_abcd_ip_format()*/
  {
    char output_buffer[PREFIX_LEN + 1];
    memset(output_buffer, 0, PREFIX_LEN + 1);
    unsigned int a = 2058138165;
    printf("Testing Q3..\n");
    strcpy(output_buffer, ip_util->int_to_ip(a));
    printf("IP address in A.B.C.D format = %s\n", output_buffer);
    printf("Testing Q3 Done.\n");
  }

  /*Testing get_network_id()*/
  {
    printf("Testing Q4..\n");
    char ip_address[PREFIX_LEN + 1], output_buffer[PREFIX_LEN + 1];
    memset(ip_address, 0, PREFIX_LEN + 1);
    memcpy(ip_address, "192.168.2.10", strlen("192.168.2.10"));
    ip_address[strlen(ip_address)] = '\0';
    char mask = 20;
    memset(output_buffer, 0, PREFIX_LEN + 1);
    strcpy(output_buffer, ip_util->get_network_id(ip_address, mask));
    printf("Network Id = %s/%u\n", output_buffer, mask);
    printf("Testing Q4 Done.\n");
  }

  /*Testing get_subnet_cardinality() */
  {
    printf("Testing Q5..\n");
    char mask = 24;
    printf("Cardinality = %u\n", ip_util->get_subnet_cardinality(mask));
    printf("Testing Q5 Done.\n");
  }

  {
    /*Testing check_ip_subnet_membser_ship()*/
    printf("Testing Q6..\n");
    char network_id[PREFIX_LEN + 1];
    strncpy(network_id, "192.168.1.0", strlen("192.168.1.0"));
    network_id[PREFIX_LEN] = '\0';

    char mask = 24;

    char ip_address[PREFIX_LEN + 1];
    strncpy(ip_address, "192.168.1.10", strlen("192.168.1.10"));

    int res = ip_util->is_subnet_member(network_id, mask, ip_address);
    printf("IP Subnet check Result = %s\n",
           res == 0 ? "Membership true" : "Membership false");
    printf("Testing Q6 Done.\n");
  }

  free(ip_util);
}
