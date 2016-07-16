#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute () {
	DATA_TYPE result = op_dest->val - op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	panic("please implement me");

	print_asm_template2();
}

make_instr_helper(a2imm)
make_instr_helper(rm2imm)
make_instr_helper(rm2r)
make_instr_helper(r_rm)

#include "cpu/exec/template-end.h"
