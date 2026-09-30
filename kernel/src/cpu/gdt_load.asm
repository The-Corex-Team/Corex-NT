bits 64

global gdt_load
global tss_load
global idt_load
global divide_error_handler
global trigger_divide_error

extern exception_handler

section .text

gdt_load:
    lgdt [rdi]

    push qword 0x08
    lea rax, [rel .reload_cs]
    push rax
    retfq

.reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax

    ret

tss_load:
    mov ax, 0x28
    ltr ax
    ret

idt_load:
    lidt [rdi]
    ret
divide_error_handler:
    cli
    xor rdi, rdi
    call exception_handler

.halt:
    hlt
    jmp .halt

trigger_divide_error:
    xor rax, rax
    xor rdx, rdx
    xor rcx, rcx
    div rcx
    ret
