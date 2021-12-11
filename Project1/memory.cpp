#include "common.h"
#include "memory.h"

namespace virtual_machine_nsp {
    void memory_tp::ReadMemoryFromFile(std::string filename, int beginning_address) {
        // Read from the file
        // TO BE DONE
        std::ifstream input_file(filename);//�����ļ�
        std::string line;//�ļ���һ��
        int address_offset = 0;
        if (input_file.is_open()) {
            while (std::getline(input_file, line)) {
                //��ɾע�ͣ�
                auto comment_position = line.find(";");
                if (comment_position != std::string::npos) {//��һ����ע��
                    line = line.substr(0, comment_position);//ɾ��ע��
                }
                line = Trim(line);//ɾ�����Ҷ˿ո�
                if (line.size() == 0) {//����ǿ��У�����Ѱ��
                    continue;
                }
                //ɾ���ַ����м�Ŀո�
                std::string::iterator it;     //ָ��string��ĵ�����
                for (it = line.begin(); it != line.end(); it++){
                    if (*it == '\t' || *it == '\n' || *it == '\r' || *it == '\f'|| *it == '\v' || *it == ' '){
                        line.erase(it);          //ɾ��it����һ���ַ�
                        it = line.begin();
                    }
                }
                memory[beginning_address + address_offset] = TranslateInstruction(line);
                address_offset++;
            }
        }
        else {
            std::cout << "���ļ�ʧ��" << std::endl;
            // @ Input file read error
            return ;
        }
    }

    int16_t memory_tp::GetContent(int address) const {
        // get the content
        // TO BE DONE
        int16_t a = memory[address];//��ʱ
        return a;
    }

    int16_t& memory_tp::operator[](int address) {
        // get the content
        // TO BE DONE
        return memory[address];
    }
}; // virtual machine namespace
