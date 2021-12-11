#include "common.h"

namespace virtual_machine_nsp {
    const int kInstructionLength = 16;//一条指令的长度
    //翻译指令，把16个数的指令转为16位的int
    inline int16_t TranslateInstruction(std::string& line) {
        // TODO: translate hex mode
        int flag = 0;//判断是否是十六进制代码
        for (int i = 0; i < line.size(); i++) {
            if ((line[i] >= '2' && line[i] <= '9') || (line[i] >= 'a' && line[i] <= 'f') || (line[i] >= 'A' && line[i] <= 'F')) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            int num[4] = { 0 };
            for (int i = 0; i < line.size(); i++) {//获取数字
                if (line[i] >= 'a' && line[i] <= 'f') {
                    num[i] = int(line[i] - 'a') + 10;
                }
                else if (line[i] >= 'A' && line[i] <= 'F') {
                    num[i] = int(line[i] - 'A') + 10;
                }
                else {
                    num[i] = int(line[i] - '0');
                }
            }
            std::string new_line = "";
            for (int i = 3; i >= 0; i--) {
                while (num[i] > 0) {
                    new_line = std::to_string(num[i] % 2) + new_line;
                    num[i] = num[i] / 2;
                }
                while (new_line.size() < (4 - i) * 4) {
                    new_line = "0" + new_line;
                }
            }
            line = new_line;
        }
        int16_t result = 0;
        if (line.size() == kInstructionLength) {
            for (int index = 0; index < kInstructionLength; ++index) {
                result = (result << 1) | (line[index] & 1);
            }
        }
        return result;
    }

    const int kVirtualMachineMemorySize = 0xFFFF;//虚拟机内存大小

    class memory_tp {
    private:
        int16_t memory[kVirtualMachineMemorySize];

    public:
        memory_tp() {
            memset(memory, 0, sizeof(int16_t) * kVirtualMachineMemorySize);//初始化为0
        }
        // Managements
        //冲文件中读内存
        void ReadMemoryFromFile(std::string filename, int beginning_address = 0x3000);
        int16_t GetContent(int address) const;
        int16_t& operator[](int address);//重载[]运算符
        //删除空格
        inline std::string& LeftTrim(std::string& s, const char* t = " \t\n\r\f\v") {
            // TO BE DONE
            s.erase(0, s.find_first_not_of(t));
            return s;
        }

        // trim from right
        inline std::string& RightTrim(std::string& s, const char* t = " \t\n\r\f\v") {
            // TO BE DONE
            s.erase(s.find_last_not_of(t) + 1);
            return s;
        }

        // trim from left & right
        inline std::string& Trim(std::string& s, const char* t = " \t\n\r\f\v") {
            return LeftTrim(RightTrim(s, t), t);
        }
    };

}; // virtual machine nsp