all: parallelHttpTest test

parallelHttpTest: parallelHttpTest.cpp
	g++ -g -Wall parallelHttpTest.cpp -I../../ -lcurl -lpthread  -o parallelHttpTest
test: test.cpp
	g++ test.cpp -I../../ -lcurl -o test
