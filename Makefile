all : *.cpp *.hpp
	c++ --std=c++11 *.cpp -o testdigraph

format :
	astyle -A8 -k1 *.cpp *.hpp

clean :
	rm *.orig *.plist
