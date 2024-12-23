#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

#include <defs.hpp>
#include <cpu.hpp>


inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");

inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");

inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");

std::vector<std::string> load(std::ifstream& source_file, std::vector<std::pair<std::string, uint16_t>>& pos);

std::string fetch(uint16_t PC, std::vector<std::string> code);

std::vector<std::string> load(std::ifstream& source_file, std::vector<std::pair<std::string, uint16_t>>& pos);

int decode_op(std::string op);

std::vector<std::string> tokenize(std::string inst);

uint32_t find_in(std::string op, std::vector<std::pair<std::string, uint16_t>>& jmps);

uint32_t decode_operand(std::string op, std::vector<std::pair<std::string, uint16_t>>& jmps);

std::vector<uint32_t> decode(std::string inst, std::vector<std::pair<std::string, uint16_t>>& jmps);