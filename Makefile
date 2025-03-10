CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test

llrec-test: llrec.o llrec-test.o
	$(CXX) $(CXXFLAGS) -o $@ $^

llrec.o: llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) -c $<

llrec-test.o: llrec-test.cpp llrec.h
	$(CXX) $(CXXFLAGS) -c $<

run: all
	./llrec-test llrec-test1.in

stack: stack-test.cpp stack.h
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: stack-run
stack-run: stack;
	./stack

.PHONY: stack-valgrind
stack-valgrind: stack;
	valgrind --tool=memcheck --leak-check=yes ./stack


.PHONY: valgrind
valgrind: llrec-test
	valgrind --tool=memcheck --leak-check=yes ./llrec-test llrec-test1.in

.PHONY: clean 
clean:
	rm -f *.o rh llrec-test stack *~

