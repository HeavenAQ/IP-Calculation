#ifndef IP_MATH_H
#define IP_MATH_H
#define UNSET_BIT(num, pos) num &= ~(1 << pos)
#define SET_BIT(num, pos) num |= (1 << pos)
#define PREFIX_LEN 15
#define MAX_MASK_LEN 32

typedef struct IPUtils {
  char *(*get_broadcast_addr)(const char *ip_addr, char mask);
  unsigned int (*ip_to_int)(const char *ip_addr);
  char *(*int_to_ip)(unsigned int ip_addr);
  char *(*get_network_id)(const char *ip_addr, char mask);
  unsigned int (*get_subnet_cardinality)(const char mask);
  int (*is_subnet_member)(const char *network_id, const char mask,
                          const char *ip);
} IPUtils;

void init_ip_utils(IPUtils **);
#endif
