CC=g++

stacks: StackArray.o StackLinked.o test6.o delimiters.o postfix.o
	$(CC) postfix.o -o stacks

StackArray.o: StackArray.cpp
	$(CC) -c StackArray.cpp

StackLinked.o: StackLinked.cpp
	$(CC) -c StackLinked.cpp

test6.o: test6.cpp
	$(CC) -c test6.cpp

delimiters.o: delimiters.cpp
	$(CC) -c delimiters.cpp

postfix.o: postfix.cpp
	$(CC) -c postfix.cpp

clean:
	-rm -f *.o
	-rm -f $(stacks)