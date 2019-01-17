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


#include <iostream> //cout
#include <fstream> //ifstream
#include <stdio.h> //printf
#include <cstdlib> //std::rand
#include <ctime> //std::time
#include <list> //std::list - linked list

#include "functions.h"
#include "physics.h"

const int REGISTER_COUNT = 30;

std::list<PhysicsObject>::iterator iteratorConvert(int num)
{
	return *(std::list<PhysicsObject>::iterator*)&num;
}

int iteratorConvert(std::list<PhysicsObject>::iterator it)
{
	return *(int*)&it;
}

int start_machine(std::ifstream* file, int* registers, Flags* flags, std::list<PhysicsObject>* phys)
{
	using namespace std;
	
	//Get the op code pointed to by the program counter (PC)
	while (true)
	{
		
		
		//Current bytecode
		int fetch;
		
		//Buffer for arguments
		int args[20];
		
		list<PhysicsObject>::iterator it;
		
		//Fetch opcode
		file->read((char*)&fetch, sizeof(fetch));
		
		if (file->eof())
			break;
		
		printf("code %x at %i\n", fetch, (int)file->tellg());
		
		printf("    flags: %i %i %i %i\n", file->good(), file->eof(), file->fail(), file->bad());
		
		
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
			//Zero argument functions
			case 0x0:
				instr_nop();
				break;
			
			//Single argument functions
			case 0x0100: //jmp_li
				file->seekg(args[0] * sizeof(int)); //Seek to jump location
				break;
			case 0x0101: //je_li
				if (flags->equal)
					file->seekg(args[0] * sizeof(int)); //Seek to jump location
				break;
			case 0x0102: //jne_li
				if (!flags->equal)
					file->seekg(args[0] * sizeof(int)); //Seek to jump location
				break;
			case 0x0103: //jl_li
				if (flags->sign)
					file->seekg(args[0] * sizeof(int)); //Seek to jump location
				break;
			case 0x0104: //jle_li
				if (!flags->sign)
					file->seekg(args[0] * sizeof(int)); //Seek to jump location
				break;
			case 0x0105: //external_li
				
				break;
			case 0x0106: //elapsed_vi
				
				break;
			case 0x0107:
				instr_dec_vi(args, registers, flags);
				break;
			case 0x0108:
				instr_inc_vi(args, registers, flags);
				break;
			case 0x0109:
				instr_random_vi(args, registers);
				break;
			case 0x010A:
				instr_random_vf(args, registers);
				break;
			case 0x010B:
				instr_random_vv(args, registers);
				break;
			case 0x0111:
				instr_test_vi(args, registers, flags);
				break;
			case 0x0112:
				instr_test_vf(args, registers, flags);
				break;
			case 0x0113:
				instr_test_vv(args, registers, flags);
				break;
			case 0x0114:
				it = iteratorConvert(registers[args[0]]);
				
				printf("    %f %f %f\n", it->getMass(), it->getXPos(), it->getYPos());
				break;
				
				
			case 0x0200:
				instr_sin_vf_vf(args, registers);
				break;
			case 0x0201:
				instr_cos_vf_vf(args, registers);
				break;
			case 0x0202:
				instr_tan_vf_vf(args, registers);
				break;
			case 0x0203:
				instr_abs_vi_vi(args, registers);
				break;
			case 0x0204:
				instr_abs_vf_vf(args, registers);
				break;
			case 0x0205:
				instr_norm_vf_vf(args, registers);
				break;
			case 0x0206:
				instr_norm_vf_vf(args, registers);
				break;
			case 0x0207:
				instr_ln_vf_vf(args, registers);
				break;
			case 0x0208:
				instr_exp_vf_vf(args, registers);
				break;
			case 0x0209:
				instr_floor_vf_vf(args, registers);
				break;
			case 0x020A:
				instr_ceil_vf_vf(args, registers);
				break;
			case 0x020B:
				instr_sqrt_vf_vf(args, registers);
				break;
			case 0x020C:
				instr_neg_vi_vi(args, registers);
				break;
			case 0x020D:
				instr_neg_vf_vf(args, registers);
				break;
				
				
			case 0x0240:
				instr_store_vi_li(args, registers);
				break;
			case 0x0241:
				instr_store_vf_lf(args, registers);
				break;
			case 0x0242:
				instr_store_vi_vi(args, registers);
				break;
			case 0x0243:
				instr_store_vi_vf(args, registers);
				break;
			case 0x0244:
				instr_store_vf_vi(args, registers);
				break;
			case 0x0245:
				instr_store_vf_vf(args, registers);
				break;
				
			case 0x0246:
				instr_cmp_vi_li(args, registers, flags);
				break;
			case 0x0247:
				instr_cmp_vf_lf(args, registers, flags);
				break;
			case 0x0248:
				instr_cmp_vi_vi(args, registers, flags);
				break;
			case 0x0249:
				instr_cmp_vi_vf(args, registers, flags);
				break;
			case 0x024A:
				instr_cmp_vf_vi(args, registers, flags);
				break;
			case 0x024B:
				instr_cmp_vf_vf(args, registers, flags);
				break;
			
				
			case 0x0300:
				instr_add_vi_vi_vi(args, registers, flags);
				break;
			case 0x0301:
				instr_add_vf_vf_vf(args, registers, flags);
				break;
			case 0x0302:
				instr_add_vv_vv_vv(args, registers, flags);
				break;
			case 0x0303:
				instr_add_vi_vi_li(args, registers, flags);
				break;
			case 0x0304:
				instr_add_vf_vf_lf(args, registers, flags);
				break;
				
			case 0x0305:
				instr_sub_vi_vi_vi(args, registers, flags);
				break;
			case 0x0306:
				instr_sub_vf_vf_vf(args, registers, flags);
				break;
			case 0x0307:
				instr_sub_vv_vv_vv(args, registers, flags);
				break;
			case 0x0308:
				instr_sub_vi_vi_li(args, registers, flags);
				break;
			case 0x0309:
				instr_sub_vf_vf_lf(args, registers, flags);
				break;
			case 0x030A:
				instr_sub_vi_li_vi(args, registers, flags);
				break;
			case 0x030B:
				instr_sub_vf_lf_vf(args, registers, flags);
				break;
				
			case 0x030C:
				instr_mul_vi_vi_vi(args, registers, flags);
				break;
			case 0x030D:
				instr_mul_vf_vf_vf(args, registers, flags);
				break;
			case 0x030E:
				instr_mul_vv_vv_vf(args, registers, flags);
				break;
			case 0x030F:
				instr_mul_vv_vv_lf(args, registers, flags);
				break;
				
			case 0x0310:
				instr_mul_vi_vi_li(args, registers, flags);
				break;
			case 0x0311:
				instr_mul_vf_vf_lf(args, registers, flags);
				break;
				
				
				
			case 0x0400:
			
				registers[args[0]] = iteratorConvert(phys->insert(phys->end(), PhysicsObject(1.0f, Vector2f(0.4f, 0.0f))));
				break;
				
			default:
				printf("Error: Bytecode 0x%08X not recognised. Aborting VM\n", fetch);
				return 1;
				
		}
		
		cout << "    registers: ";
		
		for (int i = 0; i < 4; ++i)
			printf("%i ", registers[i]);
			
		printf("%g\n", hardConvert(registers[4]));
			
	}
	
	//Clear eof and error flags
	file->clear();
	
	//Reset stream 
	file->seekg(0);
	
	return 0;
}

void validator()
{
	int args[20];
	int reg[30];
	Flags flags(false, false);
	
	//Use resister 0 for first arg
	args[0] = 0;
	args[1] = 1;
	
	reg[1] = hardConvert(1.33f);
	reg[2] = 0;
	
	instr_store_vf_vf(args, reg);
	
	printf("Integer: %i\n", reg[0]);
	printf("Float  : %g\n", hardConvert(reg[0]));
	
}


int main(int argc, char **argv)
{
	using namespace std;
	
	char* setup_path = argv[1];
	char* loop_path = argv[2];
	
	int registers[30];
	
	list<PhysicsObject> phys_obj;
	
	ifstream setup(setup_path, ifstream::binary);
	ifstream loop(loop_path, ifstream::binary);
	
	srand(time(nullptr));
	
	Flags flags(false, false);
	
	//Get the file path from command line args
	if (argc != 3)
	{
		cout << "Error: Invalid number of command line arguments. Aborting VM." << endl;
		return 1;
	}
	
	cout << "START SETUP ROUTINE" << endl;
	if (start_machine(&setup, registers, &flags, &phys_obj))
		return 1;
		
	cout << "START LOOP ROUTING" << endl;
	
	for (int i = 0; i < 10; ++i)
	{
		if (start_machine(&loop, registers, &flags, &phys_obj))
			return 1;
	}
	
	
	
	return 0;
}

