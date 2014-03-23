#include "ASMDecodeParser.h"
#include <iostream>

using namespace std; 

/*
*This file reads in a file with 32bits of encoded MIPS Assembly and decodes it 
*printing out the encoding along with its decoded equivalent one per line. 
*/
//Nicholas Taylor
int main(int argc, char *argv[])
{
	 //Creates a ASMDecodeParser object. 
	 ASMDecodeParser *parser;

	 //If the arguments of the commant line does not include a file, print message
	 //to user and exit program. 
	 if(argc < 2){
      cerr << "Need to specify an assembly file to translate."<<endl;
      exit(1);
    }

    //Init parser object with the filename from command line. 
    parser = new ASMDecodeParser(argv[1]);

  
    //If the isFormatCorrect() returns false then print message to user and 
    //exit program. 
    if(parser->isFormatCorrect() == false){
      cerr << "Format of input file is incorrect " << endl;
      exit(1);
    }

  Instruction i; 

  //Iterate through instructions, printing each encoding.
  i = parser->getNextInstruction();

  //Goes through the vector of Instructions and calls the getEncoding and getDecoding methods
  //printing them.
  while( i.getOpcode() != UNDEFINED)
  {      
    cout <<i.getEncoding() << " " << i.getDecoding() << endl; 
    i = parser->getNextInstruction(); 
  }
  
  //frees the memory. 
  delete parser;
  return 0; 
}