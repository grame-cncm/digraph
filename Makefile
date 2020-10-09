ANALYSIS="-*,cert-*,clang-analyzer-*,modernize-*,performance-*,cppcoreguidelines-*,google-*,bugprone-*,misc-*,-google-runtime-references,-cppcoreguidelines-avoid-magic-numbers,-modernize-use-trailing-return-type"


testdigraph : *.cpp *.hh
	${CXX} -Wall -Wshadow -O1 -g --std=c++11 *.cpp -o testdigraph


test: testdigraph
	./testdigraph

help:
	@echo "make [testdigraph] : compile testdigraph"
	@echo "make test          : compile and run testdigraph"
	@echo "make format        : compile and run testdigraph"
	@echo "make analyze       : clang-tidy code analysis"

format :
	clang-format -i -style=file *.cpp *.hh

clean :
	rm -f testdigraph *.orig *.plist

analyze :
	clang-tidy --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp

fix :
	clang-tidy --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp -fix
