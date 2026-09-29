#include "gdt.h"
#include "../memory.h"

static struct gdt gdt;
static struct gdt_pointer gdtr;
static struct tss kernel_tss;


static void gdt_set_entry(
    struct gdt_entry *entry,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t granularity
)
{
    entry->limit_low = limit & 0xffff;
    entry->base_low = base & 0xffff;
    entry->base_middle = (base >> 16) & 0xff;

    entry->access = access;

    entry->granularity =
        ((limit >> 16) & 0x0f) |
        (granularity & 0xf0);

    entry->base_high = (base >> 24) & 0xff;
}


static void gdt_set_tss(
    struct gdt_tss_entry *entry,
    uint64_t base,
    uint32_t limit
)
{
    entry->limit_low = limit & 0xffff;

    entry->base_low = base & 0xffff;
    entry->base_middle = (base >> 16) & 0xff;
    entry->base_high = (base >> 24) & 0xff;

    entry->access = 0x89;

    entry->granularity =
        (limit >> 16) & 0x0f;

    entry->base_upper = (uint32_t)(base >> 32);

    entry->reserved = 0;
}

void gdt_init(void)
{
    /*
     * Null descriptor.
     */
    gdt_set_entry(
        &gdt.entries[0],
        0,
        0,
        0,
        0
    );

    /*
     * Kernel code segment.
     *
     * 0x9A:
     *   Present
     *   Ring 0
     *   Code
     *   Readable
     *
     * 0x20:
     *   Long-mode code segment
     */
    gdt_set_entry(
        &gdt.entries[1],
        0,
        0,
        0x9A,
        0x20
    );

    /*
     * Kernel data segment.
     *
     * 0x92:
     *   Present
     *   Ring 0
     *   Writable data
     */
    gdt_set_entry(
        &gdt.entries[2],
        0,
        0,
        0x92,
        0x00
    );

    /*
     * User code segment.
     *
     * 0xFA:
     *   Present
     *   Ring 3
     *   Code
     *   Readable
     *
     * 0x20:
     *   Long-mode code segment
     */
    gdt_set_entry(
        &gdt.entries[3],
        0,
        0,
        0xFA,
        0x20
    );

    /*
     * User data segment.
     *
     * 0xF2:
     *   Present
     *   Ring 3
     *   Writable data
     */
    gdt_set_entry(
        &gdt.entries[4],
        0,
        0,
        0xF2,
        0x00
    );

    /*
     * Clear the TSS.
     */
    memset(
        &kernel_tss,
        0,
        sizeof(kernel_tss)
    );

    /*
     * The kernel stack will be assigned here later.
     *
     * For now we leave rsp0 unset.
     */
    kernel_tss.rsp0 = 0;

    /*
     * Disable the TSS I/O bitmap for now.
     */
    kernel_tss.io_map_base =
        sizeof(kernel_tss);

    /*
     * Create the TSS descriptor.
     */
    gdt_set_tss(
        &gdt.tss,
        (uint64_t)&kernel_tss,
        sizeof(kernel_tss) - 1
    );

    /*
     * Prepare GDTR.
     */
    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = (uint64_t)&gdt;
    gdt_load(&gdtr);
}
