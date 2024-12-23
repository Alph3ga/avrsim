#include <chrono>
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

    for(int i=0; i< code.size(); i++){
        cout<< i<< ": "<< code[i]<< '\n';
    }
    cout<<"\n JUMPS: \n";

    for(auto [x, y]: pos){
        cout<< x<< ": "<< "PC "<< y<< '\n';
    }
    cout<< endl;

    uint16_t tick= 0;
    while(true){
        std::string inst= fetch(tick, code);
        if(inst=="EOF") break;
        std::vector<uint32_t> dec= decode(inst, pos);
        cout<< tick<< ": ";
        for(auto x: dec){
            cout<< (std::bitset<32>)x<< ' ';
        }
        cout<< '\n';
        // if(fetch(PC)) decode_execute(command);
        // else break;
        tick++;
    }

    return 0;
}