#ifndef GDT_H
#define GDT_H

#include <stdint.h>

/*
 * GDT selectors
 *
 * 0x00 - Null descriptor
 * 0x08 - Kernel code
 * 0x10 - Kernel data
 * 0x18 - User code
 * 0x20 - User data
 * 0x28 - TSS
 */
#define GDT_KERNEL_CODE 0x08
#define GDT_KERNEL_DATA 0x10
#define GDT_USER_CODE   0x18
#define GDT_USER_DATA   0x20
#define GDT_TSS         0x28

#define GDT_ENTRY_COUNT 7


/*
 * Standard 64-bit GDT descriptor.
 *
 * Each normal GDT descriptor is 8 bytes.
 */
struct gdt_entry
{
    uint16_t limit_low;

    uint16_t base_low;

    uint8_t base_middle;

    uint8_t access;

    uint8_t granularity;

    uint8_t base_high;
} __attribute__((packed));


/*
 * 64-bit TSS descriptor.
 *
 * A TSS descriptor occupies two GDT entries (16 bytes).
 */
struct gdt_tss_entry
{
    uint16_t limit_low;

    uint16_t base_low;

    uint8_t base_middle;

    uint8_t access;

    uint8_t granularity;

    uint8_t base_high;

    uint32_t base_upper;

    uint32_t reserved;
} __attribute__((packed));


/*
 * GDTR structure used by the LGDT instruction.
 */
struct gdt_pointer
{
    uint16_t limit;

    uint64_t base;
} __attribute__((packed));


/*
 * 64-bit Task State Segment.
 *
 * rsp0 is the stack used when entering Ring 0
 * from a less privileged level.
 *
 * IST1-IST7 provide dedicated interrupt stacks.
 */
struct tss
{
    uint32_t reserved0;

    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;

    uint64_t reserved1;

    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;

    uint64_t reserved2;

    uint16_t reserved3;

    uint16_t io_map_base;
} __attribute__((packed));


/*
 * Complete Corex NT GDT.
 *
 * The first five entries are normal descriptors.
 * The final descriptor is the 16-byte TSS descriptor.
 */
struct gdt
{
    struct gdt_entry entries[5];

    struct gdt_tss_entry tss;
} __attribute__((packed));


/*
 * Initialize the Corex NT Global Descriptor Table
 * and load the Task Register.
 */
void gdt_init(void);
void gdt_load(struct gdt_pointer *pointer);
#endif
