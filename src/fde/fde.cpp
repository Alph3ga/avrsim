#include <fde.hpp>

// trim from left
inline std::string& ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t)
{
    return ltrim(rtrim(s, t), t);
}

int find_in(const char** start, const char** end,  std::string key){
    for(const char** iter= start; iter!= end; iter++){
        if(key==*iter){
            return iter- start;
        }
    }
    return end-start;
}

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
            trim(name);
            pos.push_back({name, PC});
        }

        trim(code);

        if(code.length()==0) continue; 

        data.push_back(code);
        PC++;
    }

    return data;
}

std::string fetch(uint16_t PC, std::vector<std::string> code){
    if(PC<0 || PC>= code.size()) return "EOF";
    return code[PC];
}

int decode_op(std::string op){
    for(char c: op){  // convert to lower case
        if(c>='a' && c<='z'){
            c+= 'A'-'a';
        }
    }

    int code= find_in(INST, INST+ INST_SIZE, op);

    if(code== INST_SIZE) return -1;
    return code;
}

std::vector<std::string> tokenize(std::string inst){
    std::string curr= "";
    std::vector<std::string> tokens;
    int len= inst.size();
    for(int i=0; i<len; i++){
        if(inst[i]==' ' || inst[i]==','){
            if(curr.size()!=0) tokens.push_back(curr);
            curr= "";
        }
        else curr+=inst[i];
    }
    if(curr.size()!=0) tokens.push_back(curr);
    return tokens;
}

uint32_t find_in(std::string op, std::vector<std::pair<std::string, uint16_t>>& jmps){
    for(auto [name, pos]: jmps){
        if(name==op) return pos;
    }
    return -1;
}

uint32_t decode_operand(std::string op, std::vector<std::pair<std::string, uint16_t>>& jmps){  // 0000_0000 0000_0000 0000_0000 0000_0000
    uint32_t res=0, pos= 0;

    if((pos=find_in(IO_REG, IO_REG+66, op))!= 66){  // remove hardcoded size later
        res|= (uint8_t)pos;
        return res;
    }

    if((pos=find_in(op, jmps))!=-1) {  // 0000_1111 0000_0000 pppp_pppp pppp_pppp
        res|= 0b1111<< _3_BYTE;
        res|= (uint16_t)pos;
        return res;
    }

    if(op.find('X')!=op.npos){  // 0000_0001 0000_00ii 0000_0000 00qq_qqqq
        res|= 0b01<< _3_BYTE;
        if(op[0]=='-'){ res|= 0b01<< _2_BYTE; }
        if(op.back()=='+'){ res|= 0b10<< _2_BYTE; }
        int dis= std::stoi(op.substr(op.find('+'), op.size()));
        if(dis<0 || dis>63) std::cout<<"Displacement can't be higher than 6 bits.\n"<<std::endl;  // Do proper stuff
        res|= dis;
        return res;
    }
    if(op.find('Y')!=op.npos){  // 0000_0010 0000_000i 0000_0000 00qq_qqqq
        res|= 0b10<< _3_BYTE;
        if(op[0]=='-'){ res|= 0b01<< _2_BYTE; }
        if(op.back()=='+'){ res|= 0b10<< _2_BYTE; }
        int dis= std::stoi(op.substr(op.find('+'), op.size()));
        if(dis<0 || dis>63) std::cout<<"Displacement can't be higher than 6 bits.\n"<<std::endl;  // Do proper stuff
        res|= dis;
        return res;
    }
    if(op.find('Z')!=op.npos){  // 0000_0011 0000_000i 0000_0000 00qq_qqqq
        res|= 0b11<< _3_BYTE;
        if(op[0]=='-'){ res|= 0b01<< _2_BYTE; }
        if(op.back()=='+'){ res|= 0b10<< _2_BYTE; }
        int dis= std::stoi(op.substr(op.find('+'), op.size()));
        if(dis<0 || dis>63) std::cout<<"Displacement can't be higher than 6 bits.\n"<<std::endl;  // Do proper stuff
        res|= dis;
        return res;
    }

    if(op.find('R')!=op.npos || op.find('r')!=op.npos){
        if(op.find(':')!=op.npos){
            //Rd+1:Rd  0000_0100 0000_0000 0000_0000 000d_dddd
            res|= 0b100 << _3_BYTE;
        }
        else{
            res|= 0b101 << _3_BYTE;
        }
        //Rd 0000_0101 0000_0000 0000_0000 000d_dddd
        int num= std::stoi(op.substr(1,op.size()));
        res|= num;

        return res;
    }

    // K8 or K6, 0000_0110 0000_0000 0000_0000 kkkk_kkkk
    res|= 0b110 << _3_BYTE;
    int num= std::stoi(op);
    res|= (uint16_t)num;

    return res;
}

std::vector<uint32_t> decode(std::string inst, std::vector<std::pair<std::string, uint16_t>>& jmps){
    std::vector<uint32_t> decoded;
    std::vector<std::string> tokens= tokenize(inst);

    int opcode= decode_op(tokens[0]);
    if(opcode==-1) return {};

    decoded.push_back((uint32_t)opcode);

    for(int i=1; i<tokens.size(); i++){
        uint32_t val= decode_operand(tokens[i], jmps);
        decoded.push_back(val);
    }

    return decoded;
}

int execute(std::vector<uint32_t> inst, CPU& cpu){
    const uint32_t op= inst[0];

    int ticks;

    if(op>= 107){
        if(op==Operation::NOP || op==Operation::SLEEP){
            ticks= 1;
        }
    }
    else{
        ticks= delegate(inst, cpu);
    }

    return (cpu.ticks+= ticks);
}