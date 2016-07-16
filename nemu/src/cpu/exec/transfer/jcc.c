#include "cpu/exec/helper.h"

make_helper(ja_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("ja %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.CF == 0 && cpu.ZF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jae_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jae %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.CF == 0 || cpu.ZF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jb_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jb %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.CF == 1 && cpu.ZF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jbe_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jbe %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.CF == 1 || cpu.ZF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(je_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("je %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.ZF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jne_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jne %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.ZF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jg_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jg %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.SF == cpu.OF && cpu.ZF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jge_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jge %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.SF == cpu.OF || cpu.ZF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jl_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jl %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.SF != cpu.OF && cpu.ZF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jle_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jl %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.SF != cpu.OF || cpu.ZF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jno_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jno %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.OF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jnp_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jnp %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.PF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jns_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jns %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.SF == 0)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jo_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jo %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.OF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(jp_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("jp %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.PF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}

make_helper(js_rel8) {
	int8_t rel = instr_fetch(eip + 1, 1);
    print_asm("js %x", (int32_t)cpu.eip + (int32_t)rel + 2);
    if(cpu.SF == 1)
        cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
	return 2;
}
