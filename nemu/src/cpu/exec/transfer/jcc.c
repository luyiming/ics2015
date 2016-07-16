#include "cpu/exec/helper.h"

make_helper(je_rel8) {
	int8_t rel8 = instr_fetch(eip + 1, 1);
    print_asm("je %x", (int32_t)cpu.eip + (int32_t)rel8 + 2);

    if(cpu.ZF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel8;

	return 2;
}
