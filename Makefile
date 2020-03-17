ANALYSIS="-*,cert-*,clang-analyzer-*,modernize-*,performance-*,cppcoreguidelines-*,google-*,bugprone-*,misc-*"


compile : *.cpp *.hh
	${CXX} --std=c++11 *.cpp -o testdigraph


test: testdigraph
	./testdigraph

help:
	@echo "make [compile] : compile testdigraph"
	@echo "make test      : compile and run testdigraph"
	@echo "make format    : compile and run testdigraph"
	@echo "make analyze   : clang-tidy code analysis"

format :
	clang-format -i -style=file *.cpp *.hh

clean :
	rm -f testdigraph *.orig *.plist

analyze :
	clang-tidy-8 --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp

fix :
	clang-tidy-8 --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp -fix
