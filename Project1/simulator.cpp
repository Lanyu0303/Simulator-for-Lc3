#include "simulator.h"

namespace virtual_machine_nsp {
    template <typename T, unsigned B>
    inline T SignExtend(const T x) {//符号位扩展
        // Extend the number
        // TO BE DONE
        T new_x = x;
        int flag = (new_x >> (B - 1)) & 0b1;
        if (flag == 0) {
            return new_x;
        }
        else {
            T y = 0b1;
            for (int i = 0; i < B; i++) {
                y = y << 1;
            }
            for (int i = 0; i < 16 - B; i++) {
                new_x = new_x | y;
                y = y << 1;
            }
        }
        return new_x;
    }

    void virtual_machine_tp::UpdateCondRegister(int regname) {
        // Update the condition register
        // TO BE DONE
        //OK
        if (reg[regname] > 0) {
            reg[R_COND] = 0b001;
        }
        else if (reg[regname] == 0) {
            reg[R_COND] = 0b010;
        }
        else if(reg[regname] < 0){
            reg[R_COND] = 0b100;
        }
        else {
            std::cout << "Maybe something wrong!" << std::endl;
        }
    }

    void virtual_machine_tp::VM_ADD(int16_t inst) {
        int flag = inst & 0b100000;
        int dr = (inst >> 9) & 0x7;//111
        int sr1 = (inst >> 6) & 0x7;
        if (flag) {
            // add inst number
            int16_t imm = SignExtend<int16_t, 5>(inst & 0b11111);
            reg[dr] = reg[sr1] + imm;
        }
        else {
            // add register
            int sr2 = inst & 0x7;
            reg[dr] = reg[sr1] + reg[sr2];
        }
        // Update condition register
        UpdateCondRegister(dr);
    }

    void virtual_machine_tp::VM_AND(int16_t inst) {
        // TO BE DONE
        int flag = inst & 0b100000;
        int dr = (inst >> 9) & 0x7;//111
        int sr1 = (inst >> 6) & 0x7;
        if (flag) {//为立即数
            int16_t imm = SignExtend<int16_t, 5>(inst & 0b11111);
            reg[dr] = reg[sr1] & imm;
        }
        else {//为寄存器
            int sr2 = inst & 0x7;
            reg[dr] = reg[sr1] & reg[sr2];
        }
        //更新状态寄存器
        UpdateCondRegister(dr);
    }

    void virtual_machine_tp::VM_BR(int16_t inst) {//函数里没有PC自增过程，应该在运行函数前自增
        int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
        int16_t cond_flag = (inst >> 9) & 0x7;
        if (gIsDetailedMode) {
            std::cout << reg[R_PC] << std::endl;
            std::cout << pc_offset << std::endl;
        }
        if (cond_flag & reg[R_COND]) {
            reg[R_PC] += pc_offset;
        }
    }

    void virtual_machine_tp::VM_JMP(int16_t inst) {//包含RET
        // TO BE DONE
        int BaseR = (inst >> 6) & 0x7;
        reg[R_PC] = reg[BaseR];
    }

    void virtual_machine_tp::VM_JSR(int16_t inst) {//包含JSRR
        // TO BE DONE
        int flag = inst & 0b10000000000;
        int16_t TEMP = reg[R_PC];
        if (flag) {//JSR
            int16_t pc_offset = SignExtend<int16_t, 11>(inst & 0x7FF);
            reg[R_PC] += pc_offset;
        }
        else {
            int BaseR = (inst >> 6) & 0x7;
            reg[R_PC] = reg[BaseR];
        }
        reg[R_R7] = TEMP;
    }

    void virtual_machine_tp::VM_LD(int16_t inst) {
        int16_t dr = (inst >> 9) & 0x7;
        int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
        reg[dr] = mem[reg[R_PC] + pc_offset];
        UpdateCondRegister(dr);
    }

    void virtual_machine_tp::VM_LDI(int16_t inst) {
        // TO BE DONE
        int16_t dr = (inst >> 9) & 0x7;
        int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
        reg[dr] = mem[mem[reg[R_PC] + pc_offset]];
        UpdateCondRegister(dr);
    }

    void virtual_machine_tp::VM_LDR(int16_t inst) {
        // TO BE DONE
        int16_t dr = (inst >> 9) & 0x7;
        int16_t BaseR = (inst >> 6) & 0x7;
        int16_t offset = SignExtend<int16_t, 6>(inst & 0x3F);
        reg[dr] = mem[reg[BaseR] + offset];
        UpdateCondRegister(dr);
    }

    void virtual_machine_tp::VM_LEA(int16_t inst) {
        // TO BE DONE
        int16_t dr = (inst >> 9) & 0x7;
        int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
        reg[dr] = reg[R_PC + pc_offset];
        //UpdateCondRegister(dr);
    }

    void virtual_machine_tp::VM_NOT(int16_t inst) {
        // TO BE DONE
        int16_t dr = (inst >> 9) & 0x7;
        int16_t sr = (inst >> 6) & 0x7;
        reg[dr] = ~reg[sr];
        UpdateCondRegister(dr);
    }

    void virtual_machine_tp::VM_RTI(int16_t inst) {
        ; // PASS
    }

    void virtual_machine_tp::VM_ST(int16_t inst) {
        // TO BE DONE
        int16_t sr = (inst >> 9) & 0x7;
        int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
        mem[reg[R_PC] + pc_offset] = reg[sr];
    }

    void virtual_machine_tp::VM_STI(int16_t inst) {
        // TO BE DONE
        int16_t sr = (inst >> 9) & 0x7;
        int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
        mem[mem[reg[R_PC + pc_offset]]] = reg[sr];
    }

    void virtual_machine_tp::VM_STR(int16_t inst) {
        // TO BE DONE
        int16_t sr = (inst >> 9) & 0x7;
        int16_t BaseR = (inst >> 6) & 0x7;
        int16_t pc_offset = SignExtend<int16_t, 6>(inst & 0x3F);
        mem[mem[reg[BaseR] + pc_offset]] = reg[sr];
    }

    void virtual_machine_tp::VM_TRAP(int16_t inst) {
        int trapnum = inst & 0xFF;
        // if (trapnum == 0x25)
        //     exit(0);
        // TODO: build trap program
        if (trapnum == 0x20) {
            char tempchar = ' ';
            std::cout << "现在是TRAP 0x20 GETC，请输入：" << std::endl;
            std::cin >> tempchar;
            reg[R_R0] = int16_t(tempchar);
            return;
        }
        else if (trapnum == 0x21) {
            std::cout << "现在是TRAP 0x21 OUT，输出：" << std::endl;
            std::cout << char(reg[R_R0]) << std::endl;
            return;
        }
        else if (trapnum == 0x23) {
            std::cout << "现在是TRAP 0x23 PUTS，输出：" << std::endl;
            int16_t start_address = reg[R_R0];
            int address_offset = 0;
            char tempchar;
            while (true) {
                tempchar = char(mem[start_address + address_offset]);
                if (tempchar == 0) {
                    break;
                }
                else {
                    std::cout << tempchar << std::endl;
                    address_offset++;
                }
            }
            return;
        }
        else if (trapnum == 0x24) {
            std::cout << "现在是TRAP 0x24 PUTSP，输出：" << std::endl;
            int16_t start_address = reg[R_R0];
            int address_offset = 0;
            char tempchar1;
            char tempchar2;
            while (true) {
                tempchar1 = char(mem[start_address + address_offset] & 0xFF);
                tempchar2 = char((mem[start_address + address_offset] >> 8)& 0xFF);
                if (tempchar1 == 0 && tempchar2 == 0) {
                    break;
                }
                else {
                    std::cout << tempchar1 <<" " << tempchar2 <<" " << std::endl;
                    address_offset++;
                }
            }
        }
        else if (trapnum == 0x25) {
            return;
        }
        else {
            std::cout << "错误的TRAP指令！" << std::endl;
        }
            
    }

    virtual_machine_tp::virtual_machine_tp(const int16_t address, const std::string& memfile, const std::string& regfile) {
        // Read memory
        if (memfile != "") {
            mem.ReadMemoryFromFile(memfile);
        }

        // Read registers
        std::ifstream input_file;
        input_file.open(regfile);
        if (input_file.is_open()) {
            int line_count = std::count(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>(), '\n');
            input_file.close();
            input_file.open(regfile);
            if (line_count >= 8) {
                for (int index = R_R0; index <= R_R7; ++index) {
                    input_file >> reg[index];
                }
            }
            else {
                for (int index = R_R0; index <= R_R7; ++index) {
                    reg[index] = 0;
                }
            }
            input_file.close();
        }
        else {
            for (int index = R_R0; index <= R_R7; ++index) {
                reg[index] = 0;
            }
        }

        // Set address
        reg[R_PC] = address;
        reg[R_COND] = 0;
    }

    void virtual_machine_tp::SetReg(const register_tp& new_reg) {
        reg = new_reg;
    }

    int16_t virtual_machine_tp::NextStep() {
        int16_t current_pc = reg[R_PC];
        reg[R_PC]++;
        int16_t current_instruct = mem[current_pc];
        int opcode = (current_instruct >> 12) & 15;

        switch (opcode) {
        case O_ADD:
            if (gIsDetailedMode) {
                std::cout << "ADD" << std::endl;
            }
            VM_ADD(current_instruct);
            break;
        case O_AND:
            if (gIsDetailedMode) {
                std::cout << "AND" << std::endl;
            }
            VM_AND(current_instruct);
            break;
        case O_BR:
            if (gIsDetailedMode) {
                std::cout << "BR" << std::endl;
            }
            VM_BR(current_instruct);
            break;
        case O_JMP:
            if (gIsDetailedMode) {
                std::cout << "JMP" << std::endl;
            }
            VM_JMP(current_instruct);
            break;
        case O_JSR:
            if (gIsDetailedMode) {
                std::cout << "JSR" << std::endl;
            }
            VM_JSR(current_instruct);
            break;
        case O_LD:
            if (gIsDetailedMode) {
                std::cout << "LD" << std::endl;
            }
            VM_LD(current_instruct);
            break;
        case O_LDI:
            if (gIsDetailedMode) {
                std::cout << "LDI" << std::endl;
            }
            VM_LDI(current_instruct);
            break;
        case O_LDR:
            if (gIsDetailedMode) {
                std::cout << "LDR" << std::endl;
            }
            VM_LDR(current_instruct);
            break;
        case O_LEA:
            if (gIsDetailedMode) {
                std::cout << "LEA" << std::endl;
            }
            VM_LEA(current_instruct);
            break;
        case O_NOT:
            if (gIsDetailedMode) {
                std::cout << "NOT" << std::endl;
            }
            VM_NOT(current_instruct);
            break;
        case O_RTI:
            if (gIsDetailedMode) {
                std::cout << "RTI" << std::endl;
            }
            VM_RTI(current_instruct);
            break;
        case O_ST:
            if (gIsDetailedMode) {
                std::cout << "ST" << std::endl;
            }
            VM_ST(current_instruct);
            break;
        case O_STI:
            if (gIsDetailedMode) {
                std::cout << "STI" << std::endl;
            }
            VM_STI(current_instruct);
            break;
        case O_STR:
            if (gIsDetailedMode) {
                std::cout << "STR" << std::endl;
            }
            VM_STR(current_instruct);
            break;
        case O_TRAP:
            if (gIsDetailedMode) {
                std::cout << "TRAP" << std::endl;
            }
            if ((current_instruct & 0xFF) == 0x25) {
                reg[R_PC] = 0;
            }
            VM_TRAP(current_instruct);
            return 0;
            break;
        default:
            VM_RTI(current_instruct);
            break;
        }

        if (current_instruct == 0) {
            // END
            // TODO: add more detailed judge information
            int16_t next_instruct = mem[reg[R_PC]];
            if (next_instruct == 0) {
                //std::cout << "遇到两行纯零！" << std::endl;
                return int16_t(0);
            }            
        }
        return reg[R_PC];
    }

} // namespace virtual_machine_nsp