#include "cpu/exec/helper.h"

/***************** disp 16 *********************/
make_helper(cmova_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.CF == 0 && cpu.ZF == 0)
        reg_w(op_dest->reg) = op_src->val;
    print_asm("cmova %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovae_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.CF == 0 || cpu.ZF == 1)
        reg_w(op_dest->reg) = op_src->val;
    print_asm("cmovae %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovb_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.CF == 1 && cpu.ZF == 0)
        reg_w(op_dest->reg) = op_src->val;
    print_asm("cmovb %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovbe_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.CF == 1 || cpu.ZF == 1)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovbe %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmove_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.ZF == 1)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmove %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovne_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.ZF == 0)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovne %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovg_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.SF == cpu.OF && cpu.ZF == 0)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovg %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovge_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.SF == cpu.OF || cpu.ZF == 1)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovge %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovl_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.SF != cpu.OF && cpu.ZF == 0)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovl %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovle_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.SF != cpu.OF || cpu.ZF == 1)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovle %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovno_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.OF == 0)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovno %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovnp_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.PF == 0)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovnp %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovns_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.SF == 0)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovns %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovo_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.OF == 1)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovo %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovp_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.PF == 1)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovp %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovs_w) {
	int len = decode_rm2r_w(eip + 1);
    if(cpu.SF == 1)
        reg_w(op_dest->reg) = op_src->val;
	print_asm("cmovs %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

/***************** disp 32 *********************/
make_helper(cmova_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.CF == 0 && cpu.ZF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmova %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovae_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.CF == 0 || cpu.ZF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovae %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovb_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.CF == 1 && cpu.ZF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovb %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovbe_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.CF == 1 || cpu.ZF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovbe %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmove_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.ZF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmove %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovne_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.ZF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovne %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovg_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.SF == cpu.OF && cpu.ZF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovg %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovge_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.SF == cpu.OF || cpu.ZF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovge %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovl_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.SF != cpu.OF && cpu.ZF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovl %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovle_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.SF != cpu.OF || cpu.ZF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovle %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovno_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.OF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovno %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovnp_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.PF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovnp %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovns_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.SF == 0)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovns %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovo_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.OF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovo %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovp_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.PF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovp %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

make_helper(cmovs_l) {
	int len = decode_rm2r_l(eip + 1);
    if(cpu.SF == 1)
        reg_l(op_dest->reg) = op_src->val;
	print_asm("cmovs %s,%s", op_src->str, op_dest->str);
    return len + 1;
}

/***************** helper v *********************/
make_helper(cmova_v) {
    if(ops_decoded.is_operand_size_16)
        return cmova_w(eip);
    else
        return cmova_l(eip);
}

make_helper(cmovae_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovae_w(eip);
    else
        return cmovae_l(eip);
}

make_helper(cmovb_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovb_w(eip);
    else
        return cmovb_l(eip);
}

make_helper(cmovbe_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovbe_w(eip);
    else
        return cmovbe_l(eip);
}

make_helper(cmove_v) {
    if(ops_decoded.is_operand_size_16)
        return cmove_w(eip);
    else
        return cmove_l(eip);
}

make_helper(cmovne_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovne_w(eip);
    else
        return cmovne_l(eip);
}

make_helper(cmovg_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovg_w(eip);
    else
        return cmovg_l(eip);
}

make_helper(cmovge_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovge_w(eip);
    else
        return cmovge_l(eip);
}

make_helper(cmovl_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovl_w(eip);
    else
        return cmovl_l(eip);
}

make_helper(cmovle_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovle_w(eip);
    else
        return cmovle_l(eip);
}

make_helper(cmovno_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovno_w(eip);
    else
        return cmovno_l(eip);
}

make_helper(cmovnp_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovnp_w(eip);
    else
        return cmovnp_l(eip);
}

make_helper(cmovns_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovns_w(eip);
    else
        return cmovns_l(eip);
}

make_helper(cmovo_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovo_w(eip);
    else
        return cmovo_l(eip);
}

make_helper(cmovp_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovp_w(eip);
    else
        return cmovp_l(eip);
}

make_helper(cmovs_v) {
    if(ops_decoded.is_operand_size_16)
        return cmovs_w(eip);
    else
        return cmovs_l(eip);
}
