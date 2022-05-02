// Marc-Anthony Cross, Alek Dussuau, Benjamin Giang
// COP 3402, Fall 2021
// Assignment 1: VM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAS_LENGTH 500


int base(int L, int *pas, int BP);
void print_execution(int line, char *opname, int *IR, int PC, int BP, int SP, int DP, int *pas, int GP);

int main(int argc, char* argv[]) {
  // PM/0 Initial/Default Values:
  int IC = 0;              // Instruction Counter (increment by 3)
  int pas[MAX_PAS_LENGTH]; // Initial pas index values should be 0


  memset(pas, 0, MAX_PAS_LENGTH*sizeof(int)); // Initializes pas[n] to 0

  // Take in first command line arg as input file name
  char* file = {argv[1]};
  FILE* infile = fopen(file, "r");

  // Read in instructions and insert into PAS until End of File(EOF).
  while (fscanf(infile, "%d %d %d", &pas[IC], &pas[IC + 1], &pas[IC + 2]) != EOF)
  {
    IC += 3;
  }

  printf("\n");

  fclose(infile);

  // PM/0 Initial/Default Values:
  int GP = IC;             // Global Pointer – Points to DATA segment
  int DP = IC - 1;         // Data Pointer – To access variables in Main
  int FREE = IC + 40;      // FREE points to Heap
  int BP = IC;             // Points to base of DATA or activation records
  int PC = 0;              // Stack pointer – Points to top of stack
  int SP = MAX_PAS_LENGTH;
  int halt = 0;            // Halt boolean
  char* opname;
  int line = 0;


  printf("\t\t\t\tPC\tBP\tSP\tDP\tdata\n");
  printf("Initial Values:\t%d\t%d\t%d\t%d\n",PC,BP,SP,DP);

  while(halt != 1) // until halt or for loop until IC (FIX THIS)-----------------------------
  {
    int OP = pas[PC];
    int L = pas[PC+1];
    int M = pas[PC+2];
    int IR[3] = {OP, L, M};

    switch(OP) {
      case 1 : // LIT    0,  M
        // Increment DP by 1, copy M to top of stack.
        if (BP == GP)
        {
          DP += 1;
          pas[DP] = M;
        }
        else
        {
          SP -= 1;
          pas[SP] = M;
        }

        line = PC / 3;
        PC += 3;
        opname = "LIT";
        break;

      case 2: // OPR  0, #
        if (M == 0) // RTN
        {
          line = PC / 3;
          SP = BP + 1;
          BP = pas[SP - 2];
          PC = pas[SP - 3];
          opname = "RTN";
        }
        else if (M == 1) // NEG
        {
          if (BP == GP)
            pas[DP] = -1 * pas[DP];
          else
            pas[SP] = -1 * pas[SP];
            line = PC / 3;
          opname = "NEG";
        }
        else if (M == 2) // ADD
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] + pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] + pas[SP - 1];
          }
          line = PC / 3;
          opname = "ADD";
        }
        else if (M == 3) // SUB
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] - pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] - pas[SP - 1];
          }
          line = PC / 3;
          opname = "SUB";
        }
        else if (M == 4) // MUL
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] * pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] * pas[SP - 1];
          }
          line = PC / 3;
          opname = "MUL";
        }
        else if (M == 5) // DIV
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] / pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] / pas[SP - 1];
          }
          opname = "DIV";
          line = PC / 3;
        }
        else if (M == 6) // ODD
        {
          if (BP == GP)
            pas[DP] = pas[DP] % 2;
          else
            pas[SP] = pas[SP] % 2;
          opname = "ODD";
          line = PC / 3;
        }
        else if (M == 7) // MOD
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] % pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] % pas[SP - 1];
          }
          opname = "MOD";
          line = PC / 3;
        }
        else if (M == 8) // EQL
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] == pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] == pas[SP - 1];
          }
          opname = "EQL";
          line = PC / 3;
        }
        else if (M == 9) // NEQ
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] != pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] != pas[SP - 1];
          }
          opname = "NEQ";
          line = PC / 3;
        }
        else if (M == 10) // LSS
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] < pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] < pas[SP - 1];
          }
          opname = "LSS";
          line = PC / 3;
        }
        else if (M == 11) // LEQ
        {
          if (BP == GP)
          {
            DP -= 1;
            pas[DP] = pas[DP] <= pas[DP + 1];
          }
          else
          {
            SP += 1;
            pas[SP] = pas[SP] <= pas[SP - 1];
          }
          opname = "LEQ";
          line = PC / 3;
        }
        else if (M == 12) // GTR
        {
          if (BP == GP)
          {
            DP = DP - 1;
            pas[DP] = pas[DP] > pas[DP + 1];
          } else {
            SP = SP + 1;
            pas[SP] = pas[SP] > pas[SP - 1];
          }
          opname = "GTR";
          line = PC / 3;
        }
        else if (M == 13) // GEQ
        {
          if (BP == GP)
          {
            DP = DP - 1;
            pas[DP] = pas[DP] >= pas[DP + 1];
          } else {
            SP = SP + 1;
            pas[SP] = pas[SP] >= pas[SP - 1];
          }
          opname = "GEQ";
          line = PC / 3;
        }

        PC += 3;
        break;

      case 3: // LOD L, M
        if (BP == GP)
        {
          DP += 1;
          pas[DP] = pas[GP + M];
        } else {
          if (base(L, pas, BP) == GP){
            SP -= 1;
            pas[SP] = pas[GP + M];
          } else {
            SP -= 1;
            pas[SP] = pas[base(L, pas, BP)-M];
          }
        }

        line = PC / 3;
        PC += 3;
        opname = "LOD";
        break;

      case 4: // STO L, M
        if(BP == GP)
        {
          pas[GP + M] = pas[DP];
          DP -= 1;
        } else {
          if (base(L, pas, BP) == GP){
            pas[GP + M] = pas[SP];
            SP += 1;
          } else {
            pas[base(L, pas, BP) - M] = pas[SP];
            SP += 1;
          }
        }

        line = PC / 3;
        PC += 3;
        opname = "STO";
        break;

      case 5: // CAL   L, M
        line = PC / 3;
				// Increment PC by 3 so called function returns to next instruction.
        PC += 3;

        pas[SP - 1] = base(L, pas, BP); // static link(SL)
        pas[SP - 2] = BP;              // dynamic link (DL)
        pas[SP - 3] = PC;             // return address (RA)
        BP = SP - 1;
        PC = M;

        opname = "CAL";
        break;

      case 6: // INC   0, M
        if (BP == GP)
        {
          DP = DP + M;
        } else {
          SP = SP - M;
        }

        line = PC / 3;
        PC += 3;
        opname = "INC";
        break;

      case 7: // JMP   0, M
        line = PC / 3;
        PC = M;

        opname = "JMP";
        break;

      case 8: // JPC   0, M
        line = PC / 3;
        if (BP == GP)
        {
          if (pas[DP] == 0)
          {
            PC = M;
          }
          DP = DP - 1;
        } else if (pas[SP] == 0)
        {
          {
            PC = M;
          }
          SP = SP + 1;
        }
        else
          PC += 3;

        opname = "JPC";
        break;

      case 9: // SYS
        if (M == 1)
        {
          if (BP == GP)
          {
            printf("Top of Stack Value: %d\n", pas[DP]);
            DP = DP - 1;
          } else {
          printf("Top of Stack Value: %d", pas[SP]);
          SP = SP + 1;
          }
        }

        if(M == 2)
        {
          if(BP == GP)
          {
            DP = DP + 1;
            printf("Please Enter an Integer: ");
            scanf("%d", &pas[DP]);
          } else {
            SP  = SP - 1;
            printf("Please Enter an Integer: ");
            scanf("%d", &pas[SP]);
          }
        }

        if(M == 3)
        {
          halt = 1;
        }

        line = PC / 3;
        opname = "SYS";
        PC += 3;
        break;
    }

    print_execution(line, opname, IR, PC, BP, SP, DP, pas, GP);
		
  }

  return 0;
}

int base(int L, int *pas, int BP) {

  int arb = BP; //arb = activation record base

  while(L>0)
  { //find base L levels down
    arb = pas[arb];
    L--;
  }
  return arb;
}


void print_execution(int line, char *opname, int *IR, int PC, int BP, int SP, int DP, int *pas, int GP){

  int i;

  // print out instruction and registers
  printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t", line, opname, IR[1], IR[2], PC, BP, SP, DP);

  // print data section
  for (i = GP; i <= DP; i++){
    printf("%d ", pas[i]);
  }
  printf("\n");

  // print stack
  printf("\tstack : ");
  for (i = MAX_PAS_LENGTH - 1; i >= SP; i--){
    printf("%d ", pas[i]);
  }
  printf("\n");
}
