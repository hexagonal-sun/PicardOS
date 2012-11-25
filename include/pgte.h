#ifndef	_PGTE_H_
#define _PGTE_H_

/*
 *	arm 32-bit Small-Page and section descriptors
 */

typedef unsigned long	pt_entry_t;

#define SC_SHIFT	20	/* small-page descriptor shift */
#define SC_MASK		0xfff	/* mask for small-page descriptor index */
#define SP_SHIFT	12	/* section shift */
#define SP_MASK		0xfffff	/* mask for section index */

#define PAGE_MASK	0xfffff
#define PAGE_SHIFT	SC_SHIFT

/*
 *	Convert linear offset to page descriptor index
 */
#define lin2pgidx(a)	(((a) >> SC_SHIFT) & SC_MASK)

/*
 *	Convert page descriptor index to linear address
 */
#define pgidx2lin(a)	((vm_offset_t)(a) << SC_SHIFT)

#define inclin(a)	((a) + (1 << SC_SHIFT))
/*
 *	Hardware small-page bit definitions
 */

#define ARM_SP_XN		0x00000001
#define ARM_SP_BUF		0x00000004
#define ARM_SP_CACHE		0x00000008
#define ARM_SP_AP_0		0x00000010
#define ARM_SP_AP_1		0x00000020
#define ARM_SP_TEX_0		0x00000040
#define ARM_SP_TEX_1		0x00000080
#define ARM_SP_TEX_2		0x00000100
#define ARM_SP_AP_2		0x00000200
#define ARM_SP_S		0x00000400
#define ARM_SP_NG		0x00000800
#define ARM_SP_PFN		0xfffff000

/*
 *	Hardware section bit definitions
 */
#define ARM_SC_BUF		0x00000004
#define ARM_SC_CACHE		0x00000008
#define ARM_SC_XN		0x00000010
#define ARM_SC_DOMAIN_1		0x00000020
#define ARM_SC_DOMAIN_2		0x00000040
#define ARM_SC_DOMAIN_3		0x00000080
#define ARM_SC_DOMAIN_4		0x00000100
#define ARM_SC_AP_0		0x00000400
#define ARM_SC_AP_1		0x00000800
#define ARM_SC_TEX_0		0x00001000
#define ARM_SC_TEX_1		0x00002000
#define ARM_SC_TEX_2		0x00004000
#define ARM_SC_AP_2		0x00008000
#define ARM_SC_S		0x00010000
#define ARM_SC_NG		0x00020000
#define ARM_SC_NS		0x00080000
#define ARM_SC_PFN		0xfff00000

#endif	/* _PGTE_H_ */
