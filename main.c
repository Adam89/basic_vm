#include <stdio.h>
#include <stdbool.h>

bool running = true;

typedef enum {
  A, B, C, D, E, F, IP, SP,
  NUM_OF_REGISTERS
} Registers;

typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT
} InstructionSet;

//test program, should return the value eleven;
const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  HLT,
  10,
  11, 12
};

int stack[256];
int registers[NUM_OF_REGISTERS];

#define sp registers[SP]
#define ip registers[IP]

int fetch() {
  printf("Fetching IP's value is: %d\n", ip);
  printf("The programs num returned is: %d and the const: %c\n", program[2]);
  return program[ip];
}

void eval(int instruction) {
  printf("Return back instruction: %d\n", instruction);

  switch (instruction) {
    case HLT: {
      running = false;
      break;
    }
    case PSH: {
      printf("IP's value is: %d\n", ip);
      stack[++sp] = program[++ip];
      printf("IP's value is: %d\n", ip);
      break;
    }
    case POP: {
      int val_popped = stack[sp--];
      printf("popped %d\n", val_popped);
      break;
    }
    case ADD: {
     int first_popped_val  = stack[sp--];
     int second_popped_val = stack[sp--];

     stack[++sp] = first_popped_val + second_popped_val;
     break;
    }
  }
}

int main() {
  while(running) {
    eval(fetch());
    printf("Am now here and IP's value is: %d\n", ip);
    ip++;
  }
}

