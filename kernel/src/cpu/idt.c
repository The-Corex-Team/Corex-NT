#include "idt.h"
#include "gdt.h"
#include "../console/console.h"
static struct idt_entry idt[IDT_ENTRY_COUNT];
static struct idt_pointer idtr;

static const char *exception_names[32] = {
    "Divide Error",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

static void idt_set_gate(
    uint8_t vector,
    uint64_t handler,
    uint16_t selector,
    uint8_t ist,
    uint8_t type_attributes
)
{
    struct idt_entry *entry = &idt[vector];

    entry->offset_low =
        (uint16_t)(handler & 0xffff);

    entry->selector = selector;

    entry->ist = ist & 0x07;

    entry->type_attributes = type_attributes;

    entry->offset_middle =
        (uint16_t)((handler >> 16) & 0xffff);

    entry->offset_high =
        (uint32_t)((handler >> 32) & 0xffffffff);

    entry->reserved = 0;
}

void exception_handler(uint64_t vector)
{
    console_write("EXCEPTION: ");
    console_write(exception_names[vector]);
    console_write("\n");

    for (;;) {
        __asm__ volatile ("cli; hlt");
    }
}

void idt_init(void)
{
    /*
     * Start with an empty IDT.
     */
    for (uint16_t i = 0; i < IDT_ENTRY_COUNT; i++) {
        idt[i].offset_low = 0;
        idt[i].selector = 0;
        idt[i].ist = 0;
        idt[i].type_attributes = 0;
        idt[i].offset_middle = 0;
        idt[i].offset_high = 0;
        idt[i].reserved = 0;
    }
	
    idt_set_gate(0,(uint64_t)divide_error_handler, GDT_KERNEL_CODE, 0, 0x8E);
    /*
     * Tell the CPU where our IDT is.
     */
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint64_t)&idt[0];
    idt_load(&idtr);

}
