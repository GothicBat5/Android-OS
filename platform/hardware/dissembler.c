#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "disassembler.h"
#include "next/apf_defs.h"
#include "next/apf.h"
  
int main(void) 
{
  uint32_t program_len = 0;
  uint8_t program[10000];
  // Read in hex program bytes
  int byte;
  while (scanf("%2x", &byte) == 1 && program_len < sizeof(program)) 
  {
      program[program_len++] = byte;
  }
  const u8 v6_marker = JMP_OPCODE << 3 | 1;
  const bool is_v6 = (program[0] & 0b11111001) == v6_marker;
  
  if (is_v6) 
  {
      printf("APFv6 program:\n");
  } 
  else {
      printf("APFv4 program:\n");
  }
  for (uint32_t pc = 0; pc < program_len + 2;) 
  {
      const disas_ret ret = apf_disassemble(program, program_len, &pc, is_v6);
      printf("%s%s\n", ret.prefix, ret.content);
  }
}
