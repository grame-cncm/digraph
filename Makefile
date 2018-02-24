all : *.cpp *.hh
	${CXX} --std=c++11 *.cpp -o testdigraph

format :
	clang-format -i -style=file *.cpp *.hh

clean :
	rm *.orig *.plist
