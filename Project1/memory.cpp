#include "common.h"
#include "memory.h"

namespace virtual_machine_nsp {
    void memory_tp::ReadMemoryFromFile(std::string filename, int beginning_address) {
        // Read from the file
        // TO BE DONE
        std::ifstream input_file(filename);//输入文件
        std::string line;//文件的一行
        int address_offset = 0;
        if (input_file.is_open()) {
            while (std::getline(input_file, line)) {
                //先删注释：
                auto comment_position = line.find(";");
                if (comment_position != std::string::npos) {//这一行有注释
                    line = line.substr(0, comment_position);//删除注释
                }
                line = Trim(line);//删除左右端空格
                if (line.size() == 0) {//如果是空行，重新寻找
                    continue;
                }
                //删除字符串中间的空格
                std::string::iterator it;     //指向string类的迭代器
                for (it = line.begin(); it != line.end(); it++){
                    if (*it == '\t' || *it == '\n' || *it == '\r' || *it == '\f'|| *it == '\v' || *it == ' '){
                        line.erase(it);          //删除it处的一个字符
                        it = line.begin();
                    }
                }
                memory[beginning_address + address_offset] = TranslateInstruction(line);
                address_offset++;
            }
        }
        else {
            std::cout << "打开文件失败" << std::endl;
            // @ Input file read error
            return ;
        }
    }

    int16_t memory_tp::GetContent(int address) const {
        // get the content
        // TO BE DONE
        int16_t a = memory[address];//临时
        return a;
    }

    int16_t& memory_tp::operator[](int address) {
        // get the content
        // TO BE DONE
        return memory[address];
    }
}; // virtual machine namespace
