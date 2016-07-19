#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
    DATA_TYPE_S rel = op_src->val;
    cpu.eip = (int32_t)cpu.eip + (int32_t)rel;

	print_asm_template1();
}

make_instr_helper(i)

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(rm)
#endif

#include "cpu/exec/template-end.h"
