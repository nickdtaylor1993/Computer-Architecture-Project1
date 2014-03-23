#ifndef __OPCODE_H__
#define __OPCODE_H__

using namespace std;

#include <iostream>
#include <string>
#include <sstream> 
#include <math.h>
#include <cstdlib>

//Nicholas Taylor 

// Listing of all supported MIPS instructions
enum Opcode {
  ADD, 
  ADDI, 
  MULT,
  MFLO,
  SRA,
  SLT,
  LB,
  J, 
  JAL,
  BEQ,
  UNDEFINED
};

// Different types of MIPS encodings
enum InstType{
  RTYPE,
  ITYPE,
  JTYPE,
};


/* This class represents templates for supported MIPS instructions.  For every supported
 * MIPS instruction, the OpcodeTable includes information about the opcode, expected
 * operands, and other fields.  
 */
class OpcodeTable{
 public:
  //Constructor for the class which inits all of the OpcodeTable entries.
  OpcodeTable();

  // Given a valid MIPS assembly mnemonic, returns an Opcode which represents a 
  // template for that instruction.
  Opcode getOpcode(string str);
  Opcode getOpcode2(string str);

  // Given an Opcode, returns number of expected operands.
  int numOperands(Opcode o);

  // Given an Opcode, returns the position of RS/RT/RD/IMM field.  If field is not
  // appropriate for this Opcode, returns -1.
  int RSposition(Opcode o);
  int RTposition(Opcode o);
  int RDposition(Opcode o);
  int IMMposition(Opcode o);

  //Gets the name of the Opcode. 
  string getName(Opcode o);

  // Given an Opcode, returns true if instruction expects a label in the instruction.
  // See "J".
  bool isIMMLabel(Opcode o);

  // Given an Opcode, returns instruction type.
  InstType getInstType(Opcode o);

  //Gets 
 // InstType getInstType2(String str);

  // Given an Opcode, returns a string representing the binary encoding of the opcode
  // field.
  string getOpcodeField(Opcode o);

  // Given an Opcode, returns a string representing the binary encoding of the function
  // field.
  string getFunctField(Opcode o);

  

 private:
  
  //Struct of the OpcodeTable entries.
  struct OpcodeTableEntry{
    //name of instruction
    string name;

    //number of operands on instruction.
    int numOps;

    //rd position.
    int rdPos;

    //rs position.
    int rsPos;

    //rt position.
    int rtPos;

    //immediate position.
    int immPos;

    //immediate label. 
    bool immLabel;

    //InstType for type of instruction.
    InstType instType;

    //op_field of instruction.
    string op_field;

    //funct_field of instruction.
    string funct_field;

    //Init the numOps to 0
    //Init rd, rs, rt, imm to -1
    //init immLabel to false. 
    OpcodeTableEntry(){
      numOps = 0; 
      rdPos = rsPos = rtPos = immPos = -1;
      immLabel = false;
    };
  };

  //Creates a array of the OpcodeTableEntries. 
  OpcodeTableEntry myArray[UNDEFINED];
  
};
#endif
