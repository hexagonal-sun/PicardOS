#include <mm.h>
#include <init.h>

#define PHYS_MEM 0x10000000

static struct pmem *used_head;
static struct pmem *free_head;

void add_list(struct pmem *a, struct pmem *b)
{
	struct pmem *tmp = a->next;
	a->next = b;
	b->next = tmp;
	tmp->prev = b;
	b->prev = a;
}

void remove_list(struct pmem *p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
}

void setup_pgalloc()
{
	phys_addr_t end_addr = mem_start + PHYS_MEM;
	phys_addr_t cur_addr = mem_start;
	struct pmem *p;

	// The first three blocks of PRAM are kernel special cases.
	p = malloc(sizeof(*p));
	p->addr = cur_addr;
	p->vmap = (&kernel_pmap)->mappings;
	p->next = p;
	p->prev = p;
	used_head = p;
	cur_addr = inclin(cur_addr);

	p = malloc(sizeof(*p));
	p->addr = cur_addr;
	p->vmap = (&kernel_pmap)->mappings->next;
	add_list(used_head, p);
	cur_addr = inclin(cur_addr);

	p = malloc(sizeof(*p));
	p->addr = cur_addr;
	p->vmap = (&kernel_pmap)->mappings->next->next;
	add_list(used_head, p);
	cur_addr = inclin(cur_addr);

	while (cur_addr != end_addr) {
		p = malloc(sizeof(*p));
		p->addr = cur_addr;
		p->vmap = 0;
		if (free_head)
			add_list(free_head, p);
		else {
			p->next = p;
			p->prev = p;
			free_head = p;
		}
		cur_addr = inclin(cur_addr);
	}
}
system_initcall(setup_pgalloc);

struct pmem * get_mem()
{
	struct pmem *ret = 0;
	if (free_head) {
		ret = free_head;
		free_head = free_head->next;
		remove_list(ret);
	}
	add_list(ret, used_head);
	return ret;
}
