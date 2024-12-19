#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using std::string;

int main(int argc, char** argv){
    uint64_t tick= 0;

    string source_file_name= argv[1];
    std::ifstream source_file(source_file_name);

    while(true){
        // if(fetch(PC)) decode_execute(command);
        // else break;
        // tick++;
    }

    return 0;
}