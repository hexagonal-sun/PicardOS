/*
 * Memory maintenance functions and types.
 */

typedef unsigned long vm_offset_t;
typedef unsigned long phys_addr_t;

void *malloc(unsigned int sz);
