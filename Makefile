ANALYSIS="-*,cert-*,clang-analyzer-*,modernize-*,performance-*,cppcoreguidelines-*,google-*,bugprone-*,misc-*,-google-runtime-references,-cppcoreguidelines-avoid-magic-numbers"

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
HDR=$(wildcard *.hh)

STD=c++17
INCLUDES=-I . 
WARNINGS=-Wall -Wextra -Wunused -Wunused-function -Wshadow 

testdigraph : $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o : %.cpp
	$(CXX) -MJ $@.json $(INCLUDES) $(WARNINGS) -std=$(STD) -c $< -o $@

compile_commands.json :
	echo '[' > compile_commands.json
	cat *.o.json >> compile_commands.json
	echo '{}]' >> compile_commands.json

test: testdigraph
	./testdigraph

help:
	@echo "make [testdigraph] : compile testdigraph"
	@echo "make test          : compile and run testdigraph"
	@echo "make format        : compile and run testdigraph"
	@echo "make analyze       : clang-tidy code analysis"

format :
	clang-format -MJ -i -style=file ${SRC} ${HDR}

clean :
	rm -f testdigraph *.o *.o.json *.orig *.plist

analyze :
	clang-tidy --extra-arg="--std=${STD}" -checks=${ANALYSIS} -header-filter=.* ${SRC} -- ${INCLUDES}

fix :
	clang-tidy --fix --extra-arg="--std=${STD}" -checks=${ANALYSIS} -header-filter=.* ${SRC} -- ${INCLUDES}