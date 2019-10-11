ANALYSIS="-*,cert-*,clang-analyzer-*,modernize-*,performance-*,cppcoreguidelines-*,google-*,bugprone-*,misc-*"


testdigraph : *.cpp *.hh
	${CXX} --std=c++11 *.cpp -o testdigraph

format :
	clang-format -i -style=file *.cpp *.hh

clean :
	rm -f testdigraph *.orig *.plist

analyze :
	clang-tidy-8 --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp

fix :
	clang-tidy-8 --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp -fix
