#include <pgte.h>
#include <mm.h>

#define KERNEL_STACK 0xF0000000

struct pmap kernel_pmap;

/*
 * At this time, we don't have the malloc() function setup so declare
 * these kernel mappings statically.
 */
struct vm_mapping kernel_code;
struct vm_mapping kernel_stack;
struct vm_mapping kernel_data;

/**
 * This function setups up the kernel page tables to map to the link
 * address.
 *
 * @param mem_start, the start of memory that should be page aligned.
 * @param kern_va, The page aligned link address.
 * @returns the PA of the page tables to be put in TTBR1/0.
 * @note This function should be called with the MMU off and with a
 * temporary stack set.
 */
pt_entry_t *setup_pg_tables(phys_addr_t mem_start, vm_offset_t kern_va)
{
	pt_entry_t section = 0;
	pt_entry_t *pdp = (pt_entry_t*)(mem_start + 0x4000);
	unsigned int kmem = inclin(0);
	unsigned int current_phys_addr = 0;

	for (unsigned int i = 0; i < SC_MASK; i++)
		pdp[i] = section;

	/*
	 * Setup the section to point to point to the PA of the kernel
	 * code.
	 */
	section = 2;
	section |= mem_start;
	section |= ARM_SC_BUF | ARM_SC_CACHE;
	section |= ARM_SC_AP_0 | ARM_SC_AP_1;

	/*
	 * Map to the kernel link address.
	 */
	pdp[lin2pgidx(kern_va)] = section;

	/*
	 * Create a 1:1 transition mapping.
	 */
	pdp[lin2pgidx(mem_start)] = section;

	return pdp;
}

vm_offset_t post_mmu_setup(phys_addr_t mem_start,
			   vm_offset_t kern_va,
			   phys_addr_t pdp_pa)
{
	pt_entry_t section;
	pt_entry_t *pdp;

	mem_start &= ~PAGE_MASK;
	kern_va &= ~PAGE_MASK;

	/*
	 * Now the pdp will be the PA of the tables.  We need to
	 * convert that to a VA before we remove the transition
	 * mapping.
	 */
	vm_offset_t pdp_va = pdp_pa + (kern_va - mem_start);
	pdp = (pt_entry_t *)pdp_va;

	/*
	 * Remove the transition mapping.
	 */
	pdp[lin2pgidx(mem_start)] = 0;


	/*
	 * Map a page for the kernel stack.
	 */
	section = 2;
	section |= inclin(mem_start);
	section |= ARM_SC_BUF | ARM_SC_CACHE;
	section |= ARM_SC_AP_0 | ARM_SC_AP_1;
	pdp[lin2pgidx(KERNEL_STACK)] = section;

	/*
	 * Map a page for the kernel data.
	 */
	section = 2;
	section |= inclin(inclin(mem_start));
	section |= ARM_SC_BUF | ARM_SC_CACHE;
	section |= ARM_SC_AP_0 | ARM_SC_AP_1;
	pdp[lin2pgidx(inclin(kern_va))] = section;
	data_start = inclin(kern_va);

	/*
	 * Setup the kernel mapping structs.
	 */
	kernel_code.page = &pdp[lin2pgidx(kern_va)];
	kernel_code.pa = mem_start;
	kernel_code.va = kern_va;
	kernel_code.name = "Kernel code";
	kernel_code.next = &kernel_stack;

	kernel_stack.page = &pdp[lin2pgidx(KERNEL_STACK)];
	kernel_stack.pa = inclin(mem_start);
	kernel_stack.va = inclin(kern_va);
	kernel_stack.name = "Kernel stack";
	kernel_stack.next = &kernel_data;

	kernel_data.page = &pdp[lin2pgidx(inclin(kern_va))];
	kernel_data.va = inclin(kern_va);
	kernel_data.name = "Kernel data";
	kernel_data.next = 0;

	kernel_pmap.base = pdp;
	kernel_pmap.next = 0;
	kernel_pmap.mappings = &kernel_code;

	return KERNEL_STACK | PAGE_MASK;
}
