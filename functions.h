#ifndef VMINTERPRETER_FUNCTIONS
#define VMINTERPRETER_FUNCTIONS

#include <stdio.h> //printf
#include <cstdlib> //std::rand
#include <math.h>

class Flags
{
public:
	unsigned char sign : 1;
	unsigned char equal : 1;
	
	Flags(bool s, bool e) : sign(s), equal(e) {}
} ;

//Dirty cast from int to float
float hardConvert(int num)
{
	return *(float*)&num;
}

//Dirty cast from float back to int
int hardConvert(float num)
{
	return *(int*)&num;
}

void instr_nop() //0x0000
{
	
}

void instr_ret() //0x0001
{
	
}

void instr_dec_vi(int* args, int* reg, Flags* flags) //0x0107
{
	--reg[args[0]];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_inc_vi(int* args, int* reg, Flags* flags) //0x0108
{
	++reg[args[0]];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_random_vi(int* args, int* reg) //0x0109
{
	reg[args[0]] = std::rand();
}

void instr_random_vf(int* args, int* reg) //0x010A
{
	reg[args[0]] = hardConvert((float)std::rand() / RAND_MAX);
}

void instr_random_vv(int* args, int* reg) //0x010B
{
	
}

//Arguments 0x010C to 0x010F are stack arguments. Kinda need to figure out what ima do with the stack first...

//Not really sure if this is needed...
void instr_start_vi(int* args, int* reg) //0x0110
{
	
}

void instr_test_vi(int* args, int* reg, Flags* flags) //0x0111
{
	*flags = Flags(false, reg[args[0]] == 0);
}

void instr_test_vf(int* args, int* reg, Flags* flags) //0x0112
{
	*flags = Flags(false, hardConvert(reg[args[0]]) == 0);
}

void instr_test_vv(int* args, int* reg, Flags* flags) //0x0113
{
	
}

void instr_sin_vf_vf(int* args, int* reg) //0x0200
{
	reg[args[0]] = hardConvert(sinf(hardConvert(reg[args[1]])));
}

void instr_cos_vf_vf(int* args, int* reg) //0x0201
{
	reg[args[0]] = hardConvert(cosf(hardConvert(reg[args[1]])));
}

void instr_tan_vf_vf(int* args, int* reg) //0x0202
{
	reg[args[0]] = hardConvert(tanf(hardConvert(reg[args[1]])));
}

void instr_abs_vi_vi(int* args, int* reg) //0x0203
{
	reg[args[0]] = abs(reg[args[1]]);
}

void instr_abs_vf_vf(int* args, int* reg) //0x0204
{
	reg[args[0]] = hardConvert(abs(hardConvert(reg[args[1]])));
}

void instr_norm_vi_vi(int* args, int* reg) //0x0205
{
	reg[args[0]] = signbit(reg[args[1]]) ? -1 : 1;
}

void instr_norm_vf_vf(int* args, int* reg) //0x0206
{
	reg[args[0]] = hardConvert(signbit(hardConvert(reg[args[1]])) ? -1.0f : 1.0f);
}

void instr_ln_vf_vf(int* args, int* reg) //0x0207
{
	reg[args[0]] = hardConvert(logf(hardConvert(reg[args[1]])));
}

void instr_exp_vf_vf(int* args, int* reg) //0x0208
{
	reg[args[0]] = hardConvert(expf(hardConvert(reg[args[1]])));
}

void instr_floor_vf_vf(int* args, int* reg) //0x0209
{
	reg[args[0]] = hardConvert(floorf(hardConvert(reg[args[1]])));
}

void instr_ceil_vf_vf(int* args, int* reg) //0x020A
{
	reg[args[0]] = hardConvert(ceilf(hardConvert(reg[args[1]])));
}

void instr_sqrt_vf_vf(int* args, int* reg) //0x020B
{
	reg[args[0]] = hardConvert(sqrtf(hardConvert(reg[args[1]])));
}

void instr_neg_vf_vf(int* args, int* reg) //0x020C
{
	reg[args[0]] = hardConvert(-hardConvert(reg[args[1]]));
}

void instr_neg_vi_vi(int* args, int* reg) //0x020D
{
	reg[args[0]] = -reg[args[1]];
}

void instr_store_vi_li(int* args, int* reg) //0x0240
{
	reg[args[0]] = args[1];
}

void instr_store_vf_lf(int* args, int* reg) //0x0241
{
	reg[args[0]] = args[1];
}

void instr_store_vi_vi(int* args, int* reg) //0x0242
{
	reg[args[0]] = reg[args[1]];
}

void instr_store_vi_vf(int* args, int* reg) //0x0243
{
	reg[args[0]] = (int)hardConvert(reg[args[1]]);
}

void instr_store_vf_vi(int* args, int* reg) //0x0244
{
	reg[args[0]] = hardConvert((float)reg[args[1]]);
}

void instr_store_vf_vf(int* args, int* reg) //0x0245
{
	reg[args[0]] = reg[args[1]];
}

void instr_cmp_vi_li(int* args, int* reg, Flags* flags) //0x0246
{
	*flags = Flags(reg[args[0]] < args[1], reg[args[0]] == args[1]);
}

void instr_cmp_vf_lf(int* args, int* reg, Flags* flags) //0x0247
{
	*flags = Flags(hardConvert(reg[args[0]]) < hardConvert(args[1]), 
				   hardConvert(reg[args[0]]) == hardConvert(args[1]));
}

void instr_cmp_vi_vi(int* args, int* reg, Flags* flags) //0x0248
{
	*flags = Flags(reg[args[0]] < reg[args[1]], 
				   reg[args[0]] == reg[args[1]]);
}

void instr_cmp_vi_vf(int* args, int* reg, Flags* flags) //0x0249
{
	*flags = Flags(reg[args[0]] < hardConvert(reg[args[1]]), 
				   reg[args[0]] == hardConvert(reg[args[1]]));
}

void instr_cmp_vf_vi(int* args, int* reg, Flags* flags) //0x024A
{
	*flags = Flags(hardConvert(reg[args[0]]) < reg[args[1]], 
				   hardConvert(reg[args[0]]) == reg[args[1]]);
}

void instr_cmp_vf_vf(int* args, int* reg, Flags* flags) //0x024B
{
	*flags = Flags(hardConvert(reg[args[0]]) < hardConvert(reg[args[1]]), 
				   hardConvert(reg[args[0]]) == hardConvert(reg[args[1]]));
}

//Like start, again, not sure if this is needed
void instr_stop_vi_vi(int* args, int* reg) //0x024C
{
	
}

void instr_add_vi_vi_vi(int* args, int* reg, Flags* flags) //0x0300
{
	reg[args[0]] = reg[args[1]] + reg[args[2]];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_add_vf_vf_vf(int* args, int* reg, Flags* flags) //0x0301
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) + hardConvert(reg[args[2]]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(reg[args[0]]) == 0 );
}

void instr_add_vv_vv_vv(int* args, int* reg, Flags* flags) //0x0302
{
	
}

void instr_add_vi_vi_li(int* args, int* reg, Flags* flags) //0x0303
{
	reg[args[0]] = reg[args[1]] + args[2];
	*flags = Flags( reg[args[0]] < 0, args[0] == 0 );
}

void instr_add_vf_vf_lf(int* args, int* reg, Flags* flags) //0x0304
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) + hardConvert(args[2]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(args[0]) == 0 );
}

void instr_sub_vi_vi_vi(int* args, int* reg, Flags* flags) //0x0305
{
	reg[args[0]] = reg[args[1]] - reg[args[2]];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_sub_vf_vf_vf(int* args, int* reg, Flags* flags) //0x0306
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) - hardConvert(reg[args[2]]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(reg[args[0]]) == 0 );
}

void instr_sub_vv_vv_vv(int* args, int* reg, Flags* flags) //0x0307
{
	
}

void instr_sub_vi_vi_li(int* args, int* reg, Flags* flags) //0x0308
{
	reg[args[0]] = reg[args[1]] - args[2];
	*flags = Flags( reg[args[0]] < 0, args[0] == 0 );
}

void instr_sub_vf_vf_lf(int* args, int* reg, Flags* flags) //0x0309
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) - hardConvert(args[2]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(args[0]) == 0 );
}

void instr_sub_vi_li_vi(int* args, int* reg, Flags* flags) //0x030A
{
	reg[args[0]] = args[1] - reg[args[2]];
	*flags = Flags( reg[args[0]] < 0, args[0] == 0 );
}

void instr_sub_vf_lf_vf(int* args, int* reg, Flags* flags) //0x030B
{
	reg[args[0]] = hardConvert(hardConvert(args[1]) - hardConvert(reg[args[2]]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(args[0]) == 0 );
}

void instr_mul_vi_vi_vi(int* args, int* reg, Flags* flags) //0x030C
{
	reg[args[0]] = reg[args[1]] * reg[args[2]];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_mul_vf_vf_vf(int* args, int* reg, Flags* flags) //0x030D
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) * hardConvert(reg[args[2]]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(reg[args[0]]) == 0 );
}

void instr_mul_vv_vv_vf(int* args, int* reg, Flags* flags) //0x030E
{
	
}

void instr_mul_vv_vv_lf(int* args, int* reg, Flags* flags) //0x030F
{
	
}

void instr_mul_vi_vi_li(int* args, int* reg, Flags* flags) //0x0310
{
	reg[args[0]] = reg[args[1]] * args[2];
	*flags = Flags( reg[args[0]] < 0, reg[args[0]] == 0 );
}

void instr_mul_vf_vf_lf(int* args, int* reg, Flags* flags) //0x0311
{
	reg[args[0]] = hardConvert(hardConvert(reg[args[1]]) * hardConvert(args[2]));
	*flags = Flags( hardConvert(reg[args[0]]) < 0, hardConvert(reg[args[0]]) == 0 );
}

#endif
