#include <stddef.h>
#include <stdint.h>

/* VGA text mode buffer at 0xB8000 */
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int vga_row = 0;
int vga_col = 0;

void vga_putc(char c) 
{
    if (c == '\n') 
    {
        vga_col = 0;
        vga_row++;
        return;
    }
    const size_t index = vga_row * VGA_WIDTH + vga_col;
    vga_buffer[index] = (uint16_t)c | (uint16_t)0x0F << 8; // white on black
    vga_col++;
  
    if (vga_col >= VGA_WIDTH)
    {
        vga_col = 0;
        vga_row++;
    }
}

ENTRY(_start)
SECTIONS {
   . = 1M; /* load at 1MB */

   .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

   .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

   .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

   .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }
}

void vga_print(const char* str) 
{
    for (size_t i = 0; str[i]!= '\0'; i++) 
    {
        vga_putc(str[i]);
    }
}

void kernel_main(void) 
{
    vga_print("Hello from my Kernel!\n");
    vga_print("Running in 32-bit protected mode.\n");

    while(1) 
    {
        __asm__ volatile ("hlt"); // idle
    }
}

bits 32
section.multiboot
    align 4
    dd 0x1BADB002 ; magic
    dd 0x00 ; flags
    dd -(0x1BADB002 + 0x00) ; checksum

section.text
global _start
extern kernel_main

_start:
    cli ; disable interrupts
    mov esp, stack_top ; set up stack
    call kernel_main ; call C
    hlt ; halt if kernel returns

section.bss
align 16
stack_bottom:
    resb 16384 ; 16KB stack
stack_top:
