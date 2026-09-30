#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRY_COUNT 256

/*
 * 64-bit Interrupt Gate.
 *
 * The CPU uses this structure to find the handler
 * for an interrupt or exception.
 */
struct idt_entry
{
    uint16_t offset_low;

    uint16_t selector;

    uint8_t ist;

    uint8_t type_attributes;

    uint16_t offset_middle;

    uint32_t offset_high;

    uint32_t reserved;
} __attribute__((packed));


/*
 * IDTR structure used by the LIDT instruction.
 */
struct idt_pointer
{
    uint16_t limit;

    uint64_t base;
} __attribute__((packed));


void idt_init(void);
void idt_load(struct idt_pointer *pointer);
void divide_error_handler(void);
void trigger_divide_error(void);
void exception_handler(uint64_t vector);
#endif
