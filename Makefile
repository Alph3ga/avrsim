.PHONY: all clean

vpath %.hpp ./include
vpath %.cpp ./src $(sort $(dir $(wildcard ./src/*/)))

targ= cpu fde

obj= $(addsuffix .o, $(targ))

inc= ./include
bin= ./bin

CXXFLAGS= -I $(inc) -g
CXX?= g++

all: avrsim

%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $(bin)/$@ 
%.o : %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $(bin)/$@ 

avrsim: $(obj)
	g++ -I $(inc) src/runner.cpp -g $(addprefix $(bin)/, $(obj)) -o bin/avrsim

clean:
	-rm $(addprefix $(bin)/, $(obj))