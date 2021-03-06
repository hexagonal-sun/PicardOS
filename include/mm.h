/*
 * Memory maintenance functions and types.
 */

#include <pgte.h>

typedef unsigned long vm_offset_t;
typedef unsigned long phys_addr_t;

vm_offset_t data_start;
phys_addr_t mem_start;

struct vm_mapping;

struct pmem
{
	phys_addr_t addr;
	struct pmem *next;
	struct pmem *prev;
	struct vm_mapping *vmap;
};

struct vm_mapping
{
	pt_entry_t *page;
	struct pmem *phys;
	vm_offset_t va;
	char *name;
	struct vm_mapping *next;
};

struct pmap
{
	pt_entry_t *base; /* Page list */
	struct pmap *next;/* Next mapping */
	struct vm_mapping *mappings; /* List of mappings */
};

extern struct pmap kernel_pmap;

void *malloc(unsigned int sz);
