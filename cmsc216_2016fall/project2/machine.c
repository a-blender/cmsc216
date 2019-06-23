/* Anna Blendermann, ablender, 114474025, 0104 */
/* I pledge on my honorthat  I have not given or received any unauthorized */
/* assistance on this project */

/* this is a simple C program for reading machine instructions */
/* we're using the Strawberry Tart, 16-bit processor, two-word instructs */
#include <stdio.h>
#include "machine.h"


/* PRINT_INSTRUCTION takes an assembly instruction and prints the struct */
/* fields that correspond to the opcode, with spaces between */
void print_instruction (Instruction instr) {
  const char* codes[] = {"plus", "minus", "times", "div", "neg", "and", "or",
			 "not", "li", "lw", "sw", "move", "cmp", "read",
			 "write", "halt"};
  
  /* assume all params are valid - opcode displayed */
  if ((instr.opcode >= 0 && instr.opcode < 4) ||
     (instr.opcode > 4 && instr.opcode < 7)) {
    printf("%s R%d R%d R%d", codes[instr.opcode], instr.reg1, instr.reg2,
	   instr.reg3);
  }
  else if (instr.opcode == 4 || instr.opcode == 7 || instr.opcode == 11) {
    printf("%s R%d R%d", codes[instr.opcode], instr.reg1, instr.reg2);
  }
  else if (instr.opcode > 7 && instr.opcode < 11) {
    /* add leading zeros for the memory address */
    printf("%s R%d %05d", codes[instr.opcode], instr.reg1, instr.addr_or_imm);
  }
  else if (instr.opcode == 12) {
    printf("%s %d R%d R%d %05d", codes[instr.opcode], instr.comparison,
	   instr.reg1, instr.reg2, instr.addr_or_imm);
  }
  else if (instr.opcode == 13 || instr.opcode == 14) {
    printf("%s R%d", codes[instr.opcode], instr.reg1);
  }
  else if (instr.opcode == 15) {
    printf("%s", codes[instr.opcode]);
  }
} /* end of print_instructions method */


/* DISASSEMBLE takes an array of assembly instructions from memory, and */
/* breaks them down into (opcode, comp, reg1, reg2, reg3, address), and */
/* adds those parts to an array of Instruction structs */
int disassemble (const Machine_word memory[], int starting_addr, int num_instrs,
		Instruction instrs[], int *const valid_instrs) {
  
  if (memory != NULL && instrs != NULL && valid_instrs != NULL
      && starting_addr % 4 == 0 && (starting_addr + num_instrs*4) <= 16383
      && num_instrs >= 0 && num_instrs <= 4096) {
    
    int x, instrs_count = 0; /* starting memory address, instrs count */
    *valid_instrs = 0; /* variable for num of valid instructions */
    
    if (!starting_addr && !num_instrs) {
      return 1; /* valid params but no instructions disassembled */
    }
    
    for (x = starting_addr; x < num_instrs*2; x = x+2) {
      
      /* disassemble instruction by bitshifting to get codes */     
      if (valid_instruction(memory[x], memory[x+1])) {
	
	/* shift bits to find codes for word1 */
	instrs[instrs_count].opcode = memory[x] >> 12;
	instrs[instrs_count].comparison = (memory[x] & 3584) >> 9;
	instrs[instrs_count].reg1 = (memory[x] & 448) >> 6;
	instrs[instrs_count].reg2 = (memory[x] & 56) >> 3;
	instrs[instrs_count].reg3 = memory[x] & 7;

	/* add memory address from addr_or_imm field for word2 */
	instrs[instrs_count].addr_or_imm = memory[x+1];
      
        instrs_count += 1; /* increment instruction count */
	*valid_instrs += 1; /* increment num of valid instrs */
      }     
    } /* end of disassembling ONE instruction */
    
  } /* end of checking for valid params */
  else return 0; /* parameters were not valid */
  
  return 1; /* instructions were disassembled */
} /*end of disassemble function */


/* VALID_INSTRUCTION takes an assembly instruction (two words), and */
/* validates it based on opcode and corresponding bit parts */
int valid_instruction (Machine_word instr_word1, Machine_word instr_word2) {

  int opcode, comp, reg1, reg2, reg3;

  if (instr_word1 == 0 && instr_word2 == 0) {
    return 1; /* short circuit, both words are 0 = valid */
  }
  else {
    opcode = (instr_word1 >> 12);
    comp = (instr_word1 & 3584) >> 9;
    reg1 = (instr_word1 & 448) >> 6;
    reg2 = (instr_word1 & 56) >> 3;
    reg3 = (instr_word1 & 7);
    
    /* check register fields for invalid values !(0-5) */
    if ((reg1 < 0 || reg1 > 5) || (reg2 < 0 || reg2 > 5) ||
       (reg3 < 0 || reg3 > 5))
      return 0;

    /* memory address (if exists), is negative or too large !(0-8192) */
    if (instr_word2 < 0 || instr_word2 >= 16383)
	return 0;
    
    /* memory address (except with opcode=8), is not divisible by four */
    if (opcode != 8 && instr_word2 % 4 != 0)
      return 0;
    
    /* the reg1 operand uses R5 (only used for reg2/reg3) */
    /* exception: sw, cmp, and write (opcodes 10,12,14) may use reg1=R5 */
    if ((opcode != 10 && opcode != 12 && opcode != 14) && reg1 == 5)
      return 0;
  
    /* cmp instruction and comp field is out of range !(0-5) */
    if (opcode == 12 && (comp < 0 || comp > 5))
      return 0;
  } /* end of else statement */

  /* TEST EDGE CASES FROM STRAWBERRY TART TABLE */

  /* case 1: opcodes 0-3, 5-6 = reg1, reg2, reg3 */
  if (((opcode >= 0 && opcode <= 3) || (opcode == 5 || opcode == 6))
     && (comp || instr_word2))
    return 0;

  /* case 2: opcodes 4,7,11 = reg1, reg2 */
  if ((opcode == 4 || opcode == 7 || opcode == 11)
      && (comp || reg3 || instr_word2))
    return 0;
						       
  /* case 3: opcodes 8-10 = reg1, addr_or_imm */
  if ((opcode >= 8 && opcode <= 10) && (comp || reg2 || reg3))
    return 0;

  /* case 4: opcode 12 = everything but r3 */
  if (opcode == 12 && reg3) /* all other fields are fine */
    return 0;
  
  /* case 5: opcode 13-14 = reg1 only */
  if ((opcode == 13 || opcode == 14)
      && (comp || reg2 || reg3 || instr_word2))
    return 0;

  /* case 16: opcode 15 = no fields, everything zero */
  if ((opcode == 15) && (comp || reg1 || reg2 || reg3 || instr_word2))
    return 0;
    
  return 1; /*instruction is completely valid */
} /*end of valid_instruction function */


/* ASSEMBLE takes (opcode, comp, reg1, reg2, reg3, and address) bit parts */
/* and assembles them into an assembly instruction (two words) */
int assemble (unsigned short opcode, unsigned short comparison, unsigned short
	     reg1, unsigned short reg2, unsigned short reg3, unsigned short
	     addr_or_imm, Machine_word *const word1, Machine_word
	     *const word2) {
  
  if ((opcode >= 0 && opcode < 16) && (comparison >= 0 && comparison < 6)
     && (reg1 >= 0 && reg1 < 6) && (reg2 >= 0 && reg2 < 6) &&
     (reg3 >= 0 && reg3 < 6) && addr_or_imm <= 16383) {

    if (word1 != NULL && word2 != NULL) {
      
      /*assemble instructions from given codes */
      *word1 = (opcode << 12) + (comparison << 9) +  (reg1 << 6)
	+ (reg2 << 3) + reg3;
      *word2 = addr_or_imm;

      if (!valid_instruction(*word1, *word2)) {
	return 0; /* assembled instrs may not be valid */
      }
    }
    else return 0;
    
  } /* end of checking for valid params */
  else return 0; /* parameter(s) were invalid */
  
  return 1; /* machine instructions were assembled */
} /* end of assemble function */ 
