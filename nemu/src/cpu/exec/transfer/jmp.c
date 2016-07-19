#include "cpu/exec/helper.h"

make_helper(jmp_i_b) {
    int8_t rel = instr_fetch(eip + 1, 1);
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
    printf("jmp b 0x%x\n", cpu.eip);
    print_asm("jmp 0x%x", (int32_t)cpu.eip + (int32_t)rel + 2);
    return 2;
}

make_helper(jmp_i_w) {
    int16_t rel = instr_fetch(eip + 1, 2);
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
    print_asm("jmp 0x%x", (int32_t)cpu.eip + (int32_t)rel + 3);
    return 3;
}

make_helper(jmp_i_l) {
    int32_t rel = instr_fetch(eip + 1, 4);
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
    printf("jmp l 0x%x\n", cpu.eip);
    print_asm("jmp 0x%x", (int32_t)cpu.eip + (int32_t)rel + 5);
    return 5;
}

make_helper(jmp_rm_w) {
    int len = decode_rm_w(eip + 1);
    int16_t rel = op_src->val;
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
    print_asm("jmp 0x%x", (int32_t)cpu.eip + (int32_t)rel + len + 1);
    return len + 1;
}

make_helper(jmp_rm_l) {
    int len = decode_rm_l(eip + 1);
    int32_t rel = op_src->val;
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;
    print_asm("jmp 0x%x", (int32_t)cpu.eip + (int32_t)rel + len + 1);
    return len + 1;
}

/* for instruction encoding overloading */
make_helper_v(jmp_i)
make_helper_v(jmp_rm)
