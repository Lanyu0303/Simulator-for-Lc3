#include "register.h"
#include <bitset>    
namespace virtual_machine_nsp {
    std::ostream& operator<<(std::ostream& os, const register_tp& reg) {
        /*
        os << "\e[1mR0\e[0m = " << std::hex << reg[R_R0] << ", ";
        os << "\e[1mR1\e[0m = " << std::hex << reg[R_R1] << ", ";
        os << "\e[1mR2\e[0m = " << std::hex << reg[R_R2] << ", ";
        os << "\e[1mR3\e[0m = " << std::hex << reg[R_R3] << std::endl;
        os << "\e[1mR4\e[0m = " << std::hex << reg[R_R4] << ", ";
        os << "\e[1mR5\e[0m = " << std::hex << reg[R_R5] << ", ";
        os << "\e[1mR6\e[0m = " << std::hex << reg[R_R6] << ", ";
        os << "\e[1mR7\e[0m = " << std::hex << reg[R_R7] << std::endl;
        os << "\e[1mCOND[NZP]\e[0m = " << std::bitset<3>(reg[R_COND]) << std::endl;
        os << "\e[1mPC\e[0m = " << std::hex << reg[R_PC] << std::endl;*/
        os << "R0  " << std::hex << reg[R_R0] << ", ";
        os << "R1  " <<std::hex << reg[R_R1] << ", ";
        os << "R2  " << std::hex << reg[R_R2] << ", ";
        os << "R3  " << std::hex << reg[R_R3] << std::endl;
        os << "R4  " << std::hex << reg[R_R4] << ", ";
        os << "R5  " << std::hex << reg[R_R5] << ", ";
        os << "R6  " << std::hex << reg[R_R6] << ", ";
        os << "R7  " << std::hex << reg[R_R7] << std::endl;
        os << "R_cond  " << std::bitset<3>(reg[R_COND]) << std::endl;
        os << "R_PC  " << std::hex << reg[R_PC] << std::endl;
        return os;
    }
} // virtual machine namespace