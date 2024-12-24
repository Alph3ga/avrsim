#include <iostream>
#include <fstream>
#include <string>
#include <fde.hpp>
#include <bitset>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv){
    string source_file_name= argv[1];
    std::ifstream source_file(source_file_name);

    std::vector<std::pair<string, uint16_t>> pos;
    std::vector<string> code= load(source_file, pos);

    CPU cpu;

    std::string inst= "NOP";
    std::vector<uint32_t> decoded;
    while(true){
        decoded= decode(inst, pos);
        execute(decoded, cpu);
        inst= fetch(cpu.PC, code);
        if(inst=="EOF") break;
        cpu.PC++;
    }

    return 0;
}