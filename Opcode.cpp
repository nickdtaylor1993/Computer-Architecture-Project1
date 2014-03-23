#include "Opcode.h"

//Nicholas Taylor 

OpcodeTable::OpcodeTable()
// Initializes all the fields for every instruction in Opcode enum
{
  myArray[ADD].name = "add";  myArray[ADD].numOps = 3;   myArray[ADD].rdPos = 0;  myArray[ADD].rsPos = 1;  myArray[ADD].rtPos = 2;   myArray[ADD].immPos = -1;  myArray[ADD].instType = RTYPE; myArray[ADD].op_field = "000000"; myArray[ADD].funct_field = "100000";
 
  myArray[ADDI].name = "addi"; myArray[ADDI].numOps = 3; myArray[ADDI].rdPos = -1; myArray[ADDI].rsPos = 1; myArray[ADDI].rtPos = 0; myArray[ADDI].immPos = 2; myArray[ADDI].instType = ITYPE; myArray[ADDI].op_field = "001000"; myArray[ADDI].funct_field = ""; 

  myArray[MULT].name = "mult"; myArray[MULT].numOps = 2; myArray[MULT].rdPos = -1; myArray[MULT].rsPos = 0; myArray[MULT].rtPos = 1; myArray[MULT].immPos = -1; myArray[MULT].instType = RTYPE; myArray[MULT].op_field = "000000"; myArray[MULT].funct_field = "011000"; 

  myArray[MFLO].name = "mflo"; myArray[MFLO].numOps = 1; myArray[MFLO].rdPos = 0; myArray[MFLO].rsPos = -1; myArray[MFLO].rtPos = -1; myArray[MFLO].immPos = -1;  myArray[MFLO].instType = RTYPE; myArray[MFLO].op_field = "000000"; myArray[MFLO].funct_field = "010010";
    
  myArray[SRA].name = "sra"; myArray[SRA].numOps = 3; myArray[SRA].rdPos = 0; myArray[SRA].rsPos = -1; myArray[SRA].rtPos = 1; myArray[SRA].immPos = 2; myArray[SRA].instType = RTYPE; myArray[SRA].op_field = "000000"; myArray[SRA].funct_field = "000011";
    
  myArray[SLT].name = "slt"; myArray[SLT].numOps = 3; myArray[SLT].rdPos = 0; myArray[SLT].rsPos = 1; myArray[SLT].rtPos = 2; myArray[SLT].immPos = -1; myArray[SLT].instType = RTYPE; myArray[SLT].op_field = "000000"; myArray[SLT].funct_field = "101010";
    
  myArray[LB].name = "lb"; myArray[LB].numOps = 3; myArray[LB].rdPos = -1; myArray[LB].rsPos = 2; myArray[LB].rtPos = 0; myArray[LB].immPos = 1; myArray[LB].instType = ITYPE; myArray[LB].op_field = "100000"; myArray[LB].funct_field = "";
    
  myArray[J].name = "j"; myArray[J].numOps = 1; myArray[J].rdPos = -1; myArray[J].rsPos = -1; myArray[J].rtPos = -1; myArray[J].immPos = 0; myArray[J].instType = JTYPE; myArray[J].immLabel = true; myArray[J].op_field = "000010"; myArray[J].funct_field = "";

  myArray[JAL].name = "jal"; myArray[JAL].numOps = 1; myArray[JAL].rdPos = -1; myArray[JAL].rsPos = -1; myArray[JAL].rtPos = -1; myArray[JAL].immPos = 0; myArray[JAL].instType = JTYPE; myArray[JAL].immLabel = true; myArray[JAL].op_field = "000011"; myArray[JAL].funct_field = "";
  
  myArray[BEQ].name = "beq"; myArray[BEQ].numOps = 2; myArray[BEQ].rdPos = -1; myArray[BEQ].rsPos = 0; myArray[BEQ].rtPos = 1; myArray[BEQ].immPos = -1; myArray[BEQ].instType = ITYPE; myArray[BEQ].immLabel = true; myArray[BEQ].op_field = "000100"; myArray[BEQ].funct_field = ""; 
}

Opcode OpcodeTable::getOpcode(string str)
// Given a valid MIPS assembly assembly mnemonic, returns an Opcode which represents the 
// template for that instruction.
{
  for(int i = 0; i < (int)UNDEFINED; i++){
    if(myArray[i].name == str){
      return (Opcode)i;
    }
  }
  return UNDEFINED;
}

string OpcodeTable::getName(Opcode o)
//Using an opcode gets the name associated with it. 
//Returns an String. 
{
  return myArray[o].name; 
}

Opcode OpcodeTable::getOpcode2(string str)
// Given a valid MIPS assembly binary string,  returns an Opcode which represents the 
// template for that instruction.
// Returns an Opcode. 
{  
  //Gets the opcode of the string. 
  string opStr = string(str.begin(),str.end()-26);

  //Goes through the Opcode Table to search for the correct instruction. 
  for(int i = 0; i < (int)UNDEFINED; i++)
  {

    //If the opcodestring is equal to the opcodeField
    if(myArray[i].op_field == opStr)
    {
      //If the instant type is RTYPE 
      if(myArray[i].instType == RTYPE)
      {
         //Grab the function field of the string. 
         string functField = string(str.begin()+26, str.end());

         //If the functionField equals the strings functionField.
         if(myArray[i].funct_field == functField)
         {
            //Return the opcode. 
            return (Opcode)i;
         }
      }

      //Else if the instType is a JTYPE. 
      else if(myArray[i].instType == JTYPE)
      {
        //Return the opcode. 
        return (Opcode)i; 
      }

      //If the opcode is ITYPE Case. 
      else
        return (Opcode)i;
    }
    //continue the loop. 
    else
      continue; 
  }
  //Opcode was not found therefore undefined instruction. 
  return UNDEFINED; 
}

int OpcodeTable::numOperands(Opcode o)
// Given an Opcode, returns number of expected operands.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].numOps;
}


int OpcodeTable::RSposition(Opcode o)
// Given an Opcode, returns the position of RS field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rsPos;
}

int OpcodeTable::RTposition(Opcode o)
// Given an Opcode, returns the position of RT field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rtPos;
}

int OpcodeTable::RDposition(Opcode o)
// Given an Opcode, returns the position of RD field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rdPos;
}

int OpcodeTable::IMMposition(Opcode o)
// Given an Opcode, returns the position of IMM field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].immPos;
}



InstType OpcodeTable::getInstType(Opcode o)
// Given an Opcode, returns instruction type.
{
  if(o < 0 || o > UNDEFINED)
    return (InstType)-1;
  return myArray[o].instType;
}

string OpcodeTable::getOpcodeField(Opcode o)
// Given an Opcode, returns a string representing the binary encoding of the opcode
// field.
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].op_field;
}

string OpcodeTable::getFunctField(Opcode o)
// Given an Opcode, returns a string representing the binary encoding of the function
// field.
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].funct_field;
}

bool OpcodeTable::isIMMLabel(Opcode o)
// Given an Opcode, returns true if instruction expects a label in the instruction.
// See "J".
{
  if(o < 0 || o > UNDEFINED)
    return false;
  return myArray[o].immLabel;
}
