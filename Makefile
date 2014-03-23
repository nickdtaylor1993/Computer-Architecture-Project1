# makefile
# use to compile and test the assembler ASM for the STACK computer and
# its various components

DEBUG_FLAG= -DDEBUG -g -Wall
CFLAGS=-DDEBUG -g -Wall


.SUFFIXES: .cpp .o

.cpp.o:
	g++ $(CFLAGS) -c $<


ASM: ASM.o Instruction.o Opcode.o  ASMDecodeParser.o
	g++ -o ASM ASM.o Opcode.o ASMDecodeParser.o Instruction.o

ASMDecodeParser.o: ASMDecodeParser.h Opcode.h RegisterTable.h Instruction.h 

Instruction.o: Opcode.h RegisterTable.h Instruction.h 

Opcode.o: Opcode.h 



clean:
	/bin/rm -f ASM *.o core


