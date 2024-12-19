#include <vector>
#include <string>
#include <fstream>
#include <stdint.h>

std::vector<std::string> load(std::ifstream& source_file, std::vector<std::pair<std::string, uint16_t>>& pos){
    std::vector<std::string> data;

    std::string line, code, name;
    uint16_t PC= 0;
    while(getline(source_file, line)){  // get one line
        code= line.substr(0, line.find(';'));  // strip any comments

        size_t temp= line.find(':');
        if(temp!= line.npos){
            code= line.substr(temp+1, line.length());
            name= line.substr(0, temp);
            pos.push_back({name, PC});
        }

        if(code.length()==0) continue; 

        data.push_back(code);
        PC++;
    }
}