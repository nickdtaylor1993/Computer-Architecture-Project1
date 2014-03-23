#include "ASMDecodeParser.h"
//Nicholas Taylor 


ASMDecodeParser::ASMDecodeParser(string filename)
//Constructor takes in the Mips Assembly file and checks if the format of the file is correct. 
//Then initializes the vector of instructions. 
{
  	//Creates an instruction object. 
  	Instruction i; 
  
  	//Init the bool variable as true. 
  	myFormatCorrect = true;

  	//Creates fstream object to open file. 
  	fstream in;

  	//Opens the file and converts it into a c-string. 
  	in.open(filename.c_str());

  	//If the file does not open then format is bad. 
  	if(in.bad()){
    	myFormatCorrect = false;
  	}


  	//Otherwise go through the file.
  	else
  	{
  		//init string. 
  		string line = "";

  		//Gets each line in the file. 
  		while( getline(in, line))
  		{  
			//Calls correctStringFormat method on the string from the file.	
  			if(correctStringFormat(line))
  			{	
  				//Sets the instruction object with the values from the encoded instruction.
  				setInstructValues(line, i); 

  				//Stores the decoded instruction into an String. 
  				string decoding = decode(i); 

  				//Sets the instruction object decoding. 
  				i.setDecoding(decoding); 

  				//Sets the instruction object encoding. 
  				i.setEncoding(line);

  				//Adds the instruction into the vector list. 
  				myInstructions.push_back(i);
  			}

  			//If the correctStringFormat is false. 
  			else
  			{	
  				//set the bool variable as false. 
  				myFormatCorrect = false; 

  				//Break out of the loop. 
  				break;
  			}  
  		}
  	}
}

Instruction ASMDecodeParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
  //Returns the instruction. 
{

  	//If the index is less than the vector size
  	//increment the index then returns the instruction. 
  	if(myIndex < (int)(myInstructions.size())){
    	myIndex++;
    	return myInstructions[myIndex-1];
  	}
  
  	//Else set the instruction instance to its default and return it. 
  	Instruction i;
  	return i;

}



bool ASMDecodeParser::correctStringFormat(string &str)
//Checks the file to see if the format of the string is correct.
//Returns a boolean if its correct or not. 
{
	//gets rid of white space. 
  	str = trim(str, " ");
 
	//If the string length is 32 then proceeds to the checking format. 
	if(str.length() == 32)
	{
		//Goes through each character in the string. 
		for(int i = 0; i < str.length()-1; i++)
		{
			//If the char value in the string equals either a '0' or a '1' proceed. 
			if((str.at(i) == '0') || (str.at(i) == '1'))
			{
				
				continue; 
			}

			//Otherwise myFormatCorrect is false and return false. 
			else
			{	
				myFormatCorrect = false; 
				return false; 
			}
		}
		 
	//No errors returns true. 
	return true; 
	}

	//If string is not 32 characters long return false. 
	else
		return false; 	
}



int ASMDecodeParser::twoCompBinaryToDecimal(string bin)
//Converts binary strings in two's complement that can represent negative and positive numbers. 
//Returns an int. 
{
  	//Inits the values. 
  	int result = 0;
  	int bit = 0;  

  	//Goes through the string. 
  	for(int i =1;  i<= bin.length(); i++)
  	{
    	//if on the first bit 
	    if(i == 1)
	    {
      		//takes the value of the first bit of string. 
      		bit = (int) (bin.at(i-1) - '0');

      		//takes the value and negates it
      		int negative = (-1) * pow(2, bin.length() - i);

      		//Adds it to the result. 
      		result+= bit * negative; 
    	}
    
    	//otherwise
    	else
    	{
      		//Takes bit from string. 
      		bit = (int) (bin.at(i-1) - '0');

      		//raises by 2 at its position and adds to result.  
      		result+= bit * pow(2, bin.length() - i);
    	} 
  	}
  return result; 
}

   
int ASMDecodeParser::binaryToDecimal(string bin)
//Converts binary string to decimal.
//Returning an int. 
{
  	//Init the values. 
  	int result = 0;
  	int bit = 0;  

  	//Goes through the string. 
  	for(int i =1;  i<= bin.length(); i++)
  	{
    
      	//Takes bit from string. 
      	bit = (int) (bin.at(i-1) - '0');

      	//raises by 2 at its position and adds to result.  
      	result+= bit * pow(2, bin.length() - i);
    
  	}
  return result; 
}


string ASMDecodeParser::decode(Instruction i)
//Takes a encoded string and performs the decoding of it. 
//returns the string. 
{
  	//init string for decoding.
  	string decoding = "";

  	//Gets the opcode from the instruction. 
  	Opcode o = i.getOpcode(); 

  	//Gets the Instance Type of the opcode. 
  	InstType t = opcodes.getInstType(o); 

  	//If the instruction type of string is RTYPE 
  	if(t == RTYPE)
  	{
    	//Calls the parser method for RTYPE instructions and returns string. 
    	decoding = parseRType(i);
  	}
  
	//If the instruction type of string is ITYPE
	else if(t == ITYPE)
	{
	    //Calls the parser method for ITYPE instructions and returns string. 
	    decoding = parseIType(i);
	}

	    //If the instruction type of string is JTYPE
	else 
	{
	    //Calls the parser method for JTYPE instructions and returns string. 
	    decoding = parseJType(i); 
	}

  //Returns the decoding. 
  return decoding; 
}


string ASMDecodeParser::parseIType(Instruction i)
//Parsing method for ITYPE functions, using an instruction object. 
//Returns the string decoding of the ITYPE function. 
{
  
  	//Gets the opcode of the instruction. 
  	Opcode o = i.getOpcode(); 

  	//If the object is undefined print error message. 
  	if(o == UNDEFINED)
  	{
  		cerr << "Undefined Instruction" << endl; 
  		exit(1); 
  	}

  	//Gets the name of the encoded instruction. 
  	string name = opcodes.getName(o); 
  
  	//Gets the rs position of the encoded instruction. 
  	int rsPos = opcodes.RSposition(o);

  	//Gets the rt position of the encoded instruction. 
  	int rtPos = opcodes.RTposition(o);

  	//Gets the imm position of the encoded instruction. 
  	int immPos = opcodes.IMMposition(o);

  	//Used for finding the correct position of each operand in the instruction. 
  	int currPosition = 0;

  	//The number of operands of the instruction. 
  	int numOps = opcodes.numOperands(o); 

  	//Using a stringstream to create the string of the decoded instruction. 
  	stringstream ss; 

  	//adds name to the stringstream. 
  	ss << name << " "; 

  	//flag used to indicate if their is a label in the instruction. 
  	bool flag; 

  	//Used to determine if their is a label in this I-Type instruction. 
  	if(opcodes.isIMMLabel(o))
    	flag = true;
  
  	//Their is no label in the instruction. 
  	else
    	flag = false;  

  	//While the current position is less than the number of operands in the instruction
  	//or if their is a label in the instruction continue loop. 
  	while(currPosition < numOps|| flag == true)
  	{   
    	//using a infinite loop to find the the operand for the correct positions. 
    	while(true)
    	{
        	//if rsPosition is equal to the currentPosition
        	if(rsPos == currPosition)
        	{
          		//convert the rsField to decimal.
          		int newRS = i.getRS(); 

          		//If the currPosition is less than the number of operands
          		if(currPosition < numOps)
          		{
            		//add the register into the string with comma at end. 
            		ss << "$" << newRS << ", ";

            		//increment
            		currPosition++;
            		break; 
          		}

          		//else at the last operand. 
          		else
          		{
            		//just add register with no comma at end. 
            		ss << "$" << newRS; 

            		//increment
            		currPosition++;
            		break; 
          		}
       		}

        	//if rt register is equal to currPosition
        	else if(rtPos == currPosition)
        	{
          		//convert to decimal rtField. 
          		int newRT = i.getRT(); 

          		//If not the last register in instruction. 
          		if(currPosition < numOps )
          		{
            		//add register and add comma to end. 
            		ss << "$" << newRT << ", ";

            		//increment
            		currPosition++; 
            		break; 
          		}

          		//if the last register in instruction.
          		else
          		{
            		//add register and no comma at end. 
            		ss << "$" << newRT;

            		//increment 
            		currPosition++;
            		break; 
         		}
        	}

        	//If the immPosition equals currPosition and currPosition is 1
        	//Case where the immediate field is a offset.   
        	else if ((immPos == currPosition) && currPosition == 1)
        	{
          		//convert the imm to decimal.
          		int newImm = i.getImmediate(); 

          		//convert the rs to decimal. 
          		int newRS = i.getRS(); 

          		//add the imm and register and use imm as a offset. 
          		ss << newImm << "(" << "$" << newRS << ")";

          		//increment by 2 
          		currPosition+=2; 
          		break; 
        	}

        	//Regular immediate field that is not a offset or target address
        	else if((immPos == currPosition))
        	{
          		//convert imm to decimal
          		int newImm = i.getImmediate(); 

          		//add imm
          		ss << newImm; 

          		//increment
          		currPosition++; 
          		break; 
        	}

        	//Case to check if the immediate field is a Label. 
        	else if((immPos == -1) && ((currPosition == 1) || (currPosition == 2)))
        	{         
         	 	//add address to stream.
          		ss << i.getImmediateAddress();

          		//label is now false. 
          		flag = false;  
          		break; 
        	}
        
        	//otherwise leave space
        	else 
        	{
          		//adds space to stream
          		ss << " "; 

          		//increment 
          		currPosition++;    
          		break; 
        	}    
      	}
    }  

    //takes the stringstream obj and convers to string then returns the string. 
    string result = ss.str(); 
    return result; 
}

string ASMDecodeParser::parseRType(Instruction i)
//Parsing method for RTYPE functions, using an instruction object. 
//Returns the string decoding of the RTYPE function. 
{

  	//Gets the opcode for the R-Type function. 
  	Opcode o = i.getOpcode(); 
  
  	//If the instruction is UNDEFINED print error message. 
  	if(o == UNDEFINED)
  	{
  		cerr << "Undefined Instruction" << endl; 
  		exit(1); 
  	}

  	//Gets the name of function. 
  	string name = opcodes.getName(o); 

  	//Gets rs position of function.  
  	int rsPos = opcodes.RSposition(o); 

  	//Gets rt position of function. 
  	int rtPos = opcodes.RTposition(o);

  	//Gets rd position of function. 
  	int rdPos = opcodes.RDposition(o); 

  	//Gets imm position of function. 
  	int immPos = opcodes.IMMposition(o);

  	//used to track correct positions of registers. 
  	int currPosition = 0; 

  	//Stringstream object 
  	stringstream ss;  

  	//Number of operands in the instruction. 
  	int numOps = opcodes.numOperands(o);

  	//adds name of instruction. 
  	ss << name << " "; 


  	//while currPosition is less than number of operands. 
  	while(currPosition < numOps)
  	{
    	while (true)
    	{
        	//if rd position equal currPosition
        	if(rdPos == currPosition)
        	{
          		//convert the register to decimal.
          		int newRD = i.getRD(); 

          		//if not the last operand 
          		if(currPosition+1 < numOps)
          		{
            		//add to stream and add comma at end. 
             		ss << "$" << newRD << ", ";

             		//increment
             		currPosition++;
					break; 
          		}

          		//last operand.
          		else
          		{
            		//add register to stream
            		ss << "$" << newRD;

            		//increment
            		currPosition++;
            		break; 
          		}
        	}

        	//if rs position equals currPosition. 
        	else if(rsPos == currPosition)
        	{
          		//convert rs to decimal. 
          		int newRS = i.getRS(); 

          		//if not the last register 
          		if(currPosition+1 < numOps)
          		{
            		//add to stream and add comma. 
            		ss << "$" << newRS << ", ";

            		//increment. 
            		currPosition++;
            		break;  
          		}

          		//Last register. 
          		else
          		{
            		//add register no comma. 
            		ss << "$" << newRS; 

            		currPosition++; 
            		break; 
          		}
        	}

        	//if rt position equals currPosition. 
        	else if(rtPos == currPosition)
        	{
          		//convert rt to decimal. 
          		int newRT = i.getRT(); 

          		//if not the last register. 
          		if(currPosition+1 < numOps)
          		{
            		//add register and comma.
            		ss << "$" << newRT << ", ";

            		//increment. 
            		currPosition++;
            		break;  
          		}

          		//if the last register. 
          		else
          		{
            		//add register. 
            		ss << "$" << newRT;

            		//increment.  
            		currPosition++;
            		break;  
          		}
        	}

        	//if imm equals currPosition
        	else if (immPos == currPosition)
        	{
          		//convert imm to decimal. 
          		int newImm = i.getImmediate(); 

          		//If not the last operand 
           		if(currPosition+1 < numOps)
           		{
              		//add to stream and comma
              		ss << newImm << ", ";

              		//increment. 
              		currPosition;
              		break;  
           		}

           		//if the last operand
          		else
           		{
              		//add to stream. 
              		ss << newImm;

              		//increment. 
              		currPosition++;
              		break;  
           		}
        	}

        	//no operand in this position
       	 	else 
        	{
          		//add empty space
          		ss << " "; 

          		//increment
          		currPosition++;    
          		break; 
        	}
      	}
    }

    //convert stream to string and store in string result. 
    string result = ss.str(); 
    return result; 
}
     
string ASMDecodeParser::parseJType(Instruction i)
//Parsing method for JTYPE functions, using an instruction object. 
//Returns the string decoding of the JTYPE function. 
{
  	//Gets the opcode of the opcode
  	Opcode o = i.getOpcode(); 

  	//If the instruction is undefined print error message. 
  	if(o == UNDEFINED)
  	{
  		cerr << "Undefined Instruction" << endl; 
  		exit(1); 
  	}

  	//Gets the function name. 
  	string name = opcodes.getName(o); 
  
  	//using a stringstream 
  	//adds name. 
  	stringstream ss; 
  	ss << name << " "; 
 
  	//Adds to stream. 
  	ss << i.getImmediateAddress(); 

  	//convert the sstream object to a string and return the string in result. 
  	string result = ss.str(); 
  	return result;
}


string ASMDecodeParser::convertJumpAddToHexAddress(string str)
//Takes a jump address and converts it into its Hex Address.
{
  	//flag
  	bool flag = false; 
  
  	//init dec value. 
  	int dec = 0; 

  	//used for holding the four bits in coverting to hex. 
  	string fourBit = "";

  	//adds two 0's to end of address string. 
  	string binary = str + "00";

  	//using stringstream object
  	stringstream ss;
  	ss << "0x"; 
  	//Goes through the 28bits in groups of 4 and converts to hex. 
  	for(int i = 0; i <= binary.length()-4; i+=4)
  	{
    	//Grabs a group of 4bits. 
    	fourBit= string(binary.begin()+i,binary.end()+(i-24));
    
    	//converts the four bits to binary. 
    	dec = binaryToDecimal(fourBit);

    	//if the dec doesnt equal 0 make flag true. 
    	//Used to eliminate extra 0's in front. 
    	if(dec != 0 && flag != true)
    	{
      		flag = true; 
    	}

    	//if flag is true. 
    	if(flag)
      		//add hex into the stream. 
      		ss << hex << dec;

    	//otherwise continue iteration. 
    	else
      		continue; 
  	}
  	//convert the stringstream into a string then assign it into the result and return. 
  	string result = ss.str(); 
  	return result; 
}	


string ASMDecodeParser::convertBranchAddToHexAddress(string str)
//This is to convert the branch target address encoding to its hex addresss
{
  	//flag used to make sure no pre 0's in the string. 
  	bool flag = false;

  	//init decimal 
  	int dec = 0; 

  	//used for the four bits in the string. 
  	string fourBit = ""; 


  	//Using a stringstream object 
  	stringstream tmp; 

  	//adds two 0's in front of the encoded string and two 0's at end of the encoded string. 
  	tmp << "00" << str << "00";

  	//convert the sstring object to string then assign it into a string called binary. 
  	string binary = tmp.str(); 

  	//Creates another stringstream object for the hex and adds 0x
  	stringstream ss;
  	ss << "0x"; 

  	//goes by groups of 4 and converts each to its hex form. 
  	for(int i = 0; i <= binary.length()-4; i+=4)
  	{
    	//Gets the four bits in the string. 
    	fourBit= string(binary.begin()+i,binary.end()+(i-16));

    	//converts the fourBit string into its decimal form. 
    	dec = binaryToDecimal(fourBit);
  

    	//If dec does not equal 0 flag is set true. 
    	//Used to eliminate extra 0's in front. 
    	if(dec != 0 && flag != true)
      		flag = true; 
    	

    	//used to eliminate pre 0's in address
    	//adds the hex value into the stream. 
    	if(flag)
      		ss << hex << dec;

    	//otherwise continue iteration. 
    	else
      		continue; 
  	}

  	//converst the stringstream object to a string and assigns to the result then returns. 
  	string result = ss.str(); 
  	return result; 
}


void ASMDecodeParser::setInstructValues(string str, Instruction &i)
//gets appropriate values for the instruction then calls instruction class set values. 
{	
	//Inits all the values.
	Opcode myOpcode; 
	Register myRS = -1; 
	Register myRT = -1;
	Register myRD = -1;
	int myImmediate = -1; 
	string myImmediateAddress = ""; 
	 
	//Gets the opcode value using the encoded string instruction. 
	Opcode o = opcodes.getOpcode2(str); 
	 
	//Gets the instant type of the instruction. 
	InstType type = opcodes.getInstType(o);

	//RTYPE instruction. 
	if(type == RTYPE)
	{
  		//Grabs rsField of encoded instruction.  
  		string rs  = string(str.begin()+6, str.end()-21); 

  		//Grabs rtField of encoded instruction. 
  		string rt = string(str.begin()+11, str.end()-16);

  		//Grabs rdField of encoded instruction. 
  		string rd = string(str.begin()+16, str.end()-11);

  		//Grabs shamtField of encoded instruction. 
  		string shamt = string(str.begin()+21, str.end()-6);

  		//Sets the opcode.
  		myOpcode = o; 

  		//Sets the rs.
  		myRS = binaryToDecimal(rs);

  		//Sets the rt.
  		myRT = binaryToDecimal(rt);

  		//sets the rd.
  		myRD = binaryToDecimal(rd);

  		//sets the imm.
  		myImmediate = twoCompBinaryToDecimal(shamt); 

  		//Calls the setValue method and inits all of the data fields in the instruction.
  		i.setValues(myOpcode,myRS,myRT,myRD,myImmediate, myImmediateAddress); 
	}

	//ITYPE instruction. 
	else if(type == ITYPE)
	{
		//If the instruction has a label.
		if(opcodes.isIMMLabel(o))
		{
			//Grab the immediate field of the instruction.
			string immediateField = string(str.begin()+16,str.end());

			//Converts the encoded address into its hexadecimal form. 
			string hex = convertBranchAddToHexAddress(immediateField);

			//sets immediateAdress
			myImmediateAddress = hex; 
		}

		//Regular immediate.
		else
		{
			//Grabs immediateField of encoded string.
  			string immediateField = string(str.begin()+16,str.end());
  
  			//Using two's complemant for negative or positive immediate values and sets it to imm field. 
  			myImmediate = twoCompBinaryToDecimal(immediateField); 
		}

  		//Grabs rsField of encoded string.
  		string rs = string(str.begin()+6, str.end()-21);

  		//Grabs rtField of encoded string. 
  		string rt = string(str.begin()+11,str.end()-16);

  		//sets the opcode.
  		myOpcode = o; 

  		//sets the rs.
  		myRS = binaryToDecimal(rs);

  		//sets the rt. 
  		myRT = binaryToDecimal(rt);
 		
 		//Calls the setValue method and inits all of the data fields in the instruction.
  		i.setValues(myOpcode,myRS,myRT,myRD,myImmediate,myImmediateAddress); 
	}

	//JTYPE instruction. 
	else if(type == JTYPE)
	{
		//Sets the opcode. 
		myOpcode = o; 

		//Grabs the addressField of the encoded string. 
  		string addressField = string(str.begin()+6,str.end());

  		//Calls the jump address conversion method to convert the jump address to hex address. 
  		string hex = convertJumpAddToHexAddress(addressField);

  		//sets the imm address. 
  		myImmediateAddress = hex; 

  		//Calls the setValue method and inits all of the data fields in the instruction.
		i.setValues(myOpcode,myRS,myRT,myRD,myImmediate,myImmediateAddress);
	}

	//UNDEFINED
	else
	{
		//Sets the opcode. 
		myOpcode = o; 

		//Calls the setValue method and inits all of the data fields in the instruction.
		i.setValues(myOpcode,myRS,myRT,myRD,myImmediate,myImmediateAddress); 
	}
}

string ASMDecodeParser::trim(string str, string whitespace)
//trims the string of whitespaces. 
{
   	//Gets the first position of an 0 or 1 in the string. 
   	int strBegin = str.find_first_of("01");
    
   	//Gets the last position that a 0 or 1. 
   	int strEnd = str.find_last_of("01");
  
   	//Gets the range of the beginning white space and end of the white space. 
   	int strRange = strEnd - strBegin+1;

   	//Returns the substring without whitespace. 
   	return str.substr(strBegin, strRange);
}