#include "cpu/exec/helper.h"

make_helper(jmp_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;

    print_asm("jmp %x", cpu.eip + 2);
	return 2;
}

make_helper(jmp_rel16) {
	int16_t rel = instr_fetch(eip + 1, 2);
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;

    print_asm("jmp %x", cpu.eip + 3);
	return 3;
}
