/* (c) Larry Herman, 2016.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

#define NUM_BYTES (16 * 1024) 
#define BYTES_PER_WORD 2
#define WORDS_PER_INSTRUCTION 2
#define NUM_WORDS (NUM_BYTES / BYTES_PER_WORD)
#define NUM_INSTRUCTIONS (NUM_WORDS / WORDS_PER_INSTRUCTION)
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5

typedef unsigned short Machine_word;

typedef enum { PLUS, MINUS, TIMES, DIV, NEG, AND, OR, NOT, LI, LW, SW,
               MOVE, CMP, READ, WRITE, HALT } Opcode;

typedef enum { LT, LE, GT, GE, EQ, NE } Comparison;

typedef struct {
  Opcode opcode;
  Comparison comparison;
  unsigned short reg1;
  unsigned short reg2;
  unsigned short reg3;
  unsigned short addr_or_imm;
} Instruction;

void print_instruction(Instruction instr);
int disassemble(const Machine_word memory[], int starting_addr, int num_instrs,
                Instruction instrs[], int *const valid_instrs);
int valid_instruction(Machine_word instr_word1, Machine_word instr_word2);
int assemble(unsigned short opcode, unsigned short comparison,
             unsigned short reg1, unsigned short reg2, unsigned short reg3,
             unsigned short addr_or_imm, Machine_word *const word1,
             Machine_word *const word2);
