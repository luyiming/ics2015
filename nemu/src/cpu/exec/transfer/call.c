#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "cpu/exec/template-start.h"
#undef DATA_BYTE

make_helper(call_rel32) {
    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, eip + 5);

    int32_t rel32 = instr_fetch(eip + 1, 4);
    cpu.eip = (int32_t)cpu.eip + rel32;

    print_asm("call %x", cpu.eip + 5);
    return 5;
}


#include "cpu/exec/template-end.h"
