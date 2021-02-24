#include<cstdio>
#include<iostream>
#include"VirtualMachine.h"

int main () {
	yvm::VirtualMachine vm(1024);
	yvm::Instruction inst;
	inst.opcode = yvm::OpCodes::nop;
	inst.ops_num = 0;
	inst.dtype = yvm::DataTypes::none;
	uint8 _size = 0;
	_size += vm.encode_instruction(inst, _size);

	inst.opcode = yvm::OpCodes::mov;
	inst.dtype = yvm::DataTypes::byte;
	inst.ops_num = 2;
	inst.operands[0].op_type = yvm::OperandTypes::constant;
	inst.operands[0].value = 1025;
	inst.operands[1].op_type = yvm::OperandTypes::reg_int;
	inst.operands[1].reg_idx = 3;
	_size += vm.encode_instruction(inst, _size);

	vm.run();
	vm.run();
	return 0;
}