#ifndef _ASMDECODEPARSER_H_
#define _ASMDECODEPARSER_H_

using namespace std;

#include <iostream>
#include <fstream>
#include "Opcode.h"
#include <vector>
#include <cctype>
#include <sstream>
#include <stdlib.h>
#include <string> 
#include "Instruction.h"
#include "RegisterTable.h"



/* This class reads in an encoded MIPS assembly file instructions, checks its syntax if its correct 
 * and accesses the instructions using a list. 
 * If the file is syntactically correct, this class will return a list 
 * of decoded Instructions (one for each instruction from the file)  This
 * list of Instructions can be iterated through.
 */
//Nicholas Taylor 
class ASMDecodeParser
{
  	public:

  	//Constructor takes in the Mips Assembly file and checks if the format of the file is correct. 
    //Then initializes the vector of instructions. 
  	ASMDecodeParser(string filename); 

  	// Returns true if the file specified was syntactically correct.  Otherwise,
  	// returns false.
  	bool isFormatCorrect() { return myFormatCorrect; }
    
    //Gets the next instruction to decode. 
  	Instruction getNextInstruction();

	private:
	//Used as a index for the vector to obtain the next instruction. 
	int myIndex;

	//Vector of strings containing the instructions. 
	vector<Instruction> myInstructions; 

  //Using an OpcodeTable object for accessing the class public methods for decoding. 
  OpcodeTable opcodes;                     

	//Checks the file to see if the format of the string is correct. 
  bool correctStringFormat(string &str);

  //Converts binary to decimal with 2 complementary. 
  int twoCompBinaryToDecimal(string bin);

  //Converts binary to decimal regularly.
  int binaryToDecimal(string bin);

  //Takes in a encoded MIPS assembly instruction and performs a decoding of it. 
  string decode(Instruction i);

  //Parsing method for ITYPE functions, using an instruction object. 
  //Returns the string decoding of the ITYPE function. 
  string parseIType(Instruction i);

  //Parsing method for JTYPE functions, using an instruction object. 
  //Returns the string decoding of the JTYPE function. 
  string parseJType(Instruction i); 

  //Parsing method for RTYPE functions, using an instruction object. 
  //Returns the string decoding of the RTYPE function. 
  string parseRType(Instruction i);

  //Takes a jump address and converts it into its Hex Address. 
  string convertJumpAddToHexAddress(string str);

  //This is to convert the branch target address encoding to its hex addresss
  string convertBranchAddToHexAddress(string str);

  //Initializes the instruction object content. 
  void setInstructValues(string str, Instruction &i);

  //Used to indicate if the format of the file is correct. 
	bool myFormatCorrect;

  //trims the string of whitespaces. 
  string trim(string str, string whitespace); 
};
#endif 