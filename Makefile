all : *.cpp *.hpp
	${CXX} --std=c++11 *.cpp -o testdigraph

format :
	clang-format -i -style=file *.cpp *.hpp

clean :
	rm *.orig *.plist
