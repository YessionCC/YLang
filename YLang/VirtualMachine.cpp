#include "VirtualMachine.h"
#include <cstring>

namespace yvm {

	/*
	Comments: Initializing virtual machine
	@heap_size: heap size with byte
	*/
	VirtualMachine::VirtualMachine(uint32 heap_size) : _heap_size(heap_size) {
		_regs.fr = _regs.pc = 0;
		_regs.sp = heap_size - 1;
		memset(_regs.i, 0, sizeof(_regs.i));
		memset(_regs.f, 0, sizeof(_regs.f));
		_heap = new uint8[heap_size];
	}

	VirtualMachine::~VirtualMachine() {
		delete[] _heap;
		_heap = nullptr;
	}

	/*
	Comments: encode instructions to heap(from top to bottom)
	format: inst_size(1 byte) inst_op_code(1 byte) inst_data_type(1 byte) inst_opr_num(1 byte) operands...
	@addr: starting address
	@return: real size of the instruction which added to the heap
	*/
	uint8 VirtualMachine::encode_instruction(Instruction & inst, uint32 addr) {
		uint8* start_ptr = _heap + addr;
		*(start_ptr + 1) = static_cast<uint8> (inst.opcode);
		*(start_ptr + 2) = static_cast<uint8> (inst.dtype);
		*(start_ptr + 3) = static_cast<uint8> (inst.ops_num);
		uint8 _size = 3;
		for (uint8 i = 0; i < inst.ops_num; i++) {
			*(start_ptr + (++_size)) = static_cast<uint8>(inst.operands[i].op_type);
			if (inst.operands[i].op_type == OperandTypes::constant) {
				uint64* constant_addr = reinterpret_cast<uint64*> (start_ptr + (++_size));
				*constant_addr = inst.operands[i].value;
				_size += sizeof(uint64);
			}
			else if (inst.operands[i].op_type == OperandTypes::reg_int ||
				inst.operands[i].op_type == OperandTypes::reg_float) {
				*(start_ptr + (++_size)) = inst.operands[i].reg_idx;
			}
		}
		*start_ptr = ++_size;//include size of itself
		return _size;
	}

	/*
	Comments: decode instruction where pc register point at (also pc will be moved)
	@inst: output inst
	*/
	bool VirtualMachine::decode_instruction(Instruction & inst) {
		uint8* inst_ptr = _heap + _regs.pc;
		uint8 _size = *inst_ptr, offset = 3;
		inst.opcode = static_cast<OpCodes>(*(inst_ptr + 1));
		inst.dtype = static_cast<DataTypes>(*(inst_ptr + 2));
		inst.ops_num = *(inst_ptr + 3);
		for (uint8 i = 0; i < inst.ops_num; i++) {
			inst.operands[i].op_type = static_cast<OperandTypes>(*(inst_ptr + (++offset)));
			if (inst.operands[i].op_type == OperandTypes::constant) {
				inst.operands[i].value = *(reinterpret_cast<uint64*> (inst_ptr + (++offset)));
				offset += sizeof(uint64);
			}
			else if (inst.operands[i].op_type == OperandTypes::reg_int ||
				inst.operands[i].op_type == OperandTypes::reg_float) {
				inst.operands[i].reg_idx = *(inst_ptr + (++offset));
			}
		}
		_regs.pc += _size;
		return true;
	}

	/*
	Comment: execute one instruction
	*/
	bool VirtualMachine::run() {
		Instruction inst;
		if (!decode_instruction(inst)) return false;
		switch (inst.opcode) {
		case OpCodes::nop: break;
		case OpCodes::mov: break;
		case OpCodes::push: break;
		case OpCodes::pop: break;
		case OpCodes::add: break;
		default: return false;
		}

		return true;
	}


}


