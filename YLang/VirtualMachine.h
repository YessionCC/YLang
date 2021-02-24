#pragma once
#include "types.h"

namespace yvm {


	struct Registers {
		uint64 pc;
		uint64 sp;
		uint64 fr;
		uint64 i[64];
		float64 f[64];
	};

	enum class OpCodes: uint8 {
		nop,
		mov,
		push,
		pop,
		add,
		sub,
		mul,
		div,
		jmp
	};

	enum class DataTypes : uint8 {
		none, // no data
		byte,
		word,// 2 byte
		dword,// 4 byte
		qword // 8 byte
	};

	enum class OperandTypes: uint8 {
		reg_int,
		reg_float,
		reg_sp,
		rep_pc,
		reg_flgs,
		constant
	};

	struct Operand {
		OperandTypes op_type;
		uint8 reg_idx;
		uint64 value; //if type is constant

	};

	struct Instruction {
		OpCodes opcode;
		DataTypes dtype;
		uint8 ops_num;
		Operand operands[4];
	};


	class VirtualMachine {
	private:
		Registers _regs;
		uint32 _heap_size;
		uint8 *_heap;


	public:
		VirtualMachine(uint32 heap_size);
		virtual ~VirtualMachine();

		uint8 encode_instruction(Instruction& inst, uint32 addr);

		bool decode_instruction(Instruction& inst);



		bool run();
	};
}



