#include "Instruction.h"

//Nicholas Taylor 

Instruction::Instruction()
//Default constuctor initializes the data fields. 
{
    myOpcode = UNDEFINED;
    myRS = myRT = myRD = NumRegisters;
}

Instruction::Instruction(Opcode op, Register rs, Register rt, Register rd, int imm, string immediateAddress)
// You can specify all the fields to initialize the Instruction
{
    //Calls the setValue instruction method. 
    setValues(op, rs, rt, rd, imm, immediateAddress);
}

void Instruction::setValues(Opcode op, Register rs, Register rt, Register rd, int imm, string immediateAddress)
//Allows the user to set values of the instruction.
{

  //Sets the opcode. 
  myOpcode = op;
  //If the opcode is undefined 
  if(op < 0 || op >= UNDEFINED)
    myOpcode = UNDEFINED;

  //sets the rs. 
  myRS = rs;
  //if the rs is undefined. 
  if(rs < 0 || rs >= NumRegisters)
    myRS = NumRegisters;

  //sets the rt.
  myRT = rt;
  //If the rt is undefined. 
  if(rt < 0 || rt >= NumRegisters)
    myRT = NumRegisters;

  //sets the rd. 
  myRD = rd;
  //If the rd is undefined. 
  if(rd < 0 || rd >= NumRegisters)
    myRD = NumRegisters;

  //sets the imm
  myImmediate = imm;

  //Sets the immAddress. 
  myImmediateAddress = immediateAddress;  
}

string Instruction::getString()
// Returns a string which represents all of the fields 
{
  stringstream s ;
  s << "OP: \t" << myOpcode << "\t" << "RD: " << myRD << "\t" << 
    "RS: " << myRS << "\t" << "RT: " << "\t" << myRT << "\t" <<
    "Imm: " << myImmediate;
  
  return s.str();
  
}

