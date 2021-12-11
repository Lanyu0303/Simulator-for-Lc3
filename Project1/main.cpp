#include "simulator.h"
#include <time.h>
using namespace virtual_machine_nsp;
namespace po = boost::program_options;

bool gIsSingleStepMode = false;
bool gIsDetailedMode = true;
//std::string gInputFileName = "input.txt";
std::string gInputFileName = "";//自己套一层
//std::string gRegisterStatusFileName = "register.txt";
std::string gRegisterStatusFileName = "";
std::string gOutputFileName = "";
int gBeginningAddress = 0x3000;

int main(int argc, char** argv) {
    /*
    po::options_description desc{ "\e[1mLC3 SIMULATOR\e[0m\n\n\e[1mOptions\e[0m" };
    desc.add_options()                                                                             //
        ("help,h", "Help screen")                                                                  //
        ("file,f", po::value<std::string>()->default_value("input.txt"), "Input file")             //
        ("register,r", po::value<std::string>()->default_value("register.txt"), "Register Status") //
        ("single,s", "Single Step Mode")                                                           //
        ("begin,b", po::value<int>()->default_value(0x3000), "Begin address (0x3000)")
        ("output,o", po::value<std::string>()->default_value(""), "Output file")
        ("detail,d", "Detailed Mode");

    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    if (vm.count("file")) {
        gInputFileName = vm["file"].as<std::string>();
    }
    if (vm.count("register")) {
        gRegisterStatusFileName = vm["register"].as<std::string>();
    }
    if (vm.count("single")) {
        gIsSingleStepMode = true;
    }
    if (vm.count("begin")) {
        gBeginningAddress = vm["begin"].as<int>();
    }
    if (vm.count("output")) {
        gOutputFileName = vm["output"].as<std::string>();
    }
    if (vm.count("detail")) {
        gIsDetailedMode = true;
    }*/
    std::cout << "请输入inputFile:" <<std::endl;
    std::cin >> gInputFileName;
    std::cout << "请输入registerFile:" << std::endl;
    std::cin >> gRegisterStatusFileName;
    virtual_machine_tp virtual_machine(gBeginningAddress, gInputFileName, gRegisterStatusFileName);
    int halt_flag = true;
    int time_flag = 0;
    //clock_t start, end;//计时
    while (halt_flag) {
        // Single step
        // TO BE DONEd
        //start = clock();
        if (gIsSingleStepMode) {
            std::cout << "输入任意字符后继续" << std::endl;
            char tempchar;
            std::cin >> tempchar;
        }
        if (virtual_machine.NextStep() == int16_t(0)){
            halt_flag = false;
        }
        if (gIsDetailedMode)
            std::cout << virtual_machine.reg << std::endl;
        ++time_flag;
        //end = clock();
        //std::cout<<"time = "<< double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    }

    std::cout << virtual_machine.reg << std::endl;
    std::cout << "cycle = " << time_flag << std::endl;
    return 0;
}