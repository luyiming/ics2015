#include "cpu/exec/template-start.h"

#define instr push



#if DATA_BYTE == 1

static void do_execute () {
    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, op_src->val);

    print_asm_template1();
}

#endif

#if DATA_BYTE == 2 || DATA_BYTE == 4

static void do_execute () {
    cpu.esp -= DATA_BYTE;
    swaddr_write(cpu.esp, DATA_BYTE, op_src->val);

    print_asm_template1();
}

make_instr_helper(r)
#endif

make_instr_helper(i)



#include "cpu/exec/template-end.h"
