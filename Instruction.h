#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "Opcode.h"
#include "RegisterTable.h"
#include <sstream>
#include <string> 

/* This class provides an internal representation for a MIPS assembly instruction.
 * Any of the fields can be queried.  Additionally, the class stores a 32 bit binary
 * encoding and decoding of the MIPS instruction.
 */
//Nicholas Taylor 

class Instruction{
 public:

  //Default instruction for the constructor. 
  Instruction();

  //Constructor which sets the data fields of the Instruction.
  Instruction(Opcode op, Register rs, Register rt, Register rd, int imm, string immediateAddress);
  
  //Deconstructor. 
  ~Instruction() {};

  //Mutator method allowing you to init the data fields of the Instruction.
  void setValues(Opcode op, int rs, int rt, int rd, int imm, string immediateAddress);

  //Accessor methods that return the various fields for the Instruction
  Opcode getOpcode()   { return myOpcode;}
  Register getRS()     { return myRS; };
  Register getRD()     { return myRD; };
  Register getRT()     { return myRT; };
  int getImmediate()   { return myImmediate; };
  string getImmediateAddress() {return myImmediateAddress; };

  // Returns a string which represents all of the fields 
  string getString();

  // Stores the 32 bit binary encoding of MIPS instruction passed in
  void setEncoding(string s) { myEncoding = s;};

  // Returns string representing the 32 binary encoding of MIPS instruction
  string getEncoding() { return myEncoding; };

  void setDecoding(string s) { myDecoding = s;};

  string getDecoding() { return myDecoding;};

 private:
  Opcode myOpcode;
  Register myRS;
  Register myRT;
  Register myRD;
  int myImmediate;
  string myImmediateAddress; 

  string myEncoding;
  string myDecoding; 
};

#endif
