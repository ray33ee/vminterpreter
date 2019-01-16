/*
 * main.cxx
 * 
 * Copyright 2019 Will <Will@DESKTOP-PL3AG0U>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <stdio.h>
#include "functions.h"

#include <fstream>

const int REGISTER_COUNT = 30;


int start_machine(std::ifstream* file, int* registers, Flags* flags)
{
	using namespace std;
	//Allocate registers
	//int registers[REGISTER_COUNT];
	
	//Flags flags(false, false);
	
	//int timeout = 1000;
	
	//Get the op code pointed to by the program counter (PC)
	while (!file->eof())
	{
		//Current bytecode
		int fetch;
		
		//Buffer for arguments
		int args[20];
		
		//Fetch opcode
		file->read((char*)&fetch, sizeof(fetch));
		
		printf("code: %x\n", fetch);
		
		//Calculate number of arguments for this opcode
		int argcount = (fetch / 256);
		
		cout << "    arg count: " << argcount << endl;
		
		//Populate args with the required number of arguments for opcode
		file->read((char*)args, sizeof(int) * argcount);
		
		cout << "    Args: ";
		for (int i = 0; i < argcount; ++i)
			cout << args[i] << ", ";
		cout << endl;
		
		//Decode and execute instruction
		switch (fetch)
		{
			case 0x0:
				instr_nop();
				break;
			case 0x0102:
				if (!flags->equal)
					file->seekg(args[0] * sizeof(int)); //Seek to jump location
				break;
			case 0x0107:
				instr_dec_vi(args, registers, flags);
				break;
			case 0x0246:
				instr_store_vi_li(args, registers);
				break;
			case 0x0247:
				instr_store_vf_lf(args, registers);
				break;
			case 0x0300:
				instr_add_vi_vi_vi(args, registers, flags);
				break;
			case 0x0301:
				instr_add_vf_vf_vf(args, registers, flags);
				break;
			case 0x0310:
				instr_mul_vi_vi_li(args, registers, flags);
				break;
			case 0x0311:
				instr_mul_vf_vf_lf(args, registers, flags);
				break;
				
		}
		
		std::cout << "    registers: ";
		
		for (int i = 0; i < 5; ++i)
			printf("%i ", registers[i]);
			
		printf("%f\n", hardConvert(registers[5]));
			
	}
	
	//printf("Program counter: %i\n", program_counter);
	
	
	//Execute the instruction, referencing first argument by PC+1, second by PC+2, etc.
	//Incremement Program counter accordingly
	
	return 0;
}

int main(int argc, char **argv)
{
	using namespace std;
	
	char* path = argv[1];
	int registers[30];
	ifstream* bytecodes;
	
	Flags flags(false, false);
	
	//Get the file path from command line args
	if (argc != 2)
	{
		cout << "Error: Invalid number of command line arguments." << endl;
		return 1;
	}
	
	//Load contents into memory
	//file = fopen(path, "rb");
	//codecount = getFileSize(file) / sizeof(*bytecodes);
	//bytecodes = new int[codecount];
	
	bytecodes = new ifstream(path, ifstream::binary);
	
	
	//fread(bytecodes, sizeof(*bytecodes), codecount, file);
	
	/*codecount = 1;
	bytecodes = new int[codecount];
	
	bytecodes[0] = 0x246;
	bytecodes[1] = 0x4;
	bytecodes[2] = 0x64;*/
	
	
	
	start_machine(bytecodes, registers, &flags);
	
	return 0;
}

