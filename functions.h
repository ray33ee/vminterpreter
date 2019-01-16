
#include <stdio.h>

class Flags
{
public:
	unsigned char sign : 1;
	unsigned char equal : 1;
	
	Flags(bool s, bool e) : sign(s), equal(e) {}
} ;

float hardConvert(int num)
{
	return *(float*)&num;
}

int hardConvert(float num)
{
	return *(int*)&num;
}

void instr_nop()
{
	
}

void instr_halt()
{
	while(1);
}

void instr_ret()
{
	
}

void instr_dec_vi(int* args, int* reg, Flags* flags) //107
{
	--reg[args[0]];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_store_vi_li(int* args, int* reg) //246
{
	reg[args[0]] = args[1];
	printf("    val: %i\n", args[1]);
}

void instr_store_vf_lf(int* args, int* reg) //247
{
	reg[args[0]] = args[1];
	printf("    STORE: %i\n", (args[0]));
}

void instr_add_vi_vi_vi(int* args, int* reg, Flags* flags) //300
{
	reg[args[0]] = reg[args[1]] + reg[args[2]];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_add_vf_vf_vf(int* args, int* reg, Flags* flags) //301
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) + hardConvert(reg[args[2]]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(reg[args[0]]) == 0 );
}

void instr_mul_vi_vi_li(int* args, int* reg, Flags* flags) //310
{
	reg[args[0]] = reg[args[1]] * args[2];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_mul_vf_vf_lf(int* args, int* reg, Flags* flags) //311
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) * hardConvert(args[2]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(reg[args[0]]) == 0 );
}
