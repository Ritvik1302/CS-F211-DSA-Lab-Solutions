runStackWithArray: stackDriver.o stack_array.o
	gcc -o runStackWithArray stackDriver.o stack_array.o
	./runStackWithArray
runStackWithLL: stackDriver.o stack_ll.o linked_list.o
	gcc -o runStackWithLL stackDriver.o stack_ll.o linked_list.o
	./runStackWithLL
readFileWithArrayStack: heap_usage.o stack_array.o 
	gcc -o readFileWithArrayStack stack_array.o heap_usage.o
	./readFileWithArrayStack small.csv
readFileWithLLStack: heap_usage.o stack_ll.o linked_list.o
	gcc -o readFileWithLLStack stack_ll.o linked_list.o heap_usage.o
	./readFileWithLLStack small.csv
heap_usage.o: heap_usage.c
	gcc -c heap_usage.c
linked_list.o: linked_list.c
	gcc -c linked_list.c
stackDriver.o: stackDriver.c stack.h
	gcc -c stackDriver.c
stack_array.o: stack_array.c stack.h
	gcc -c stack_array.c
stack_ll.o: stack_ll.c linked_list.h
	gcc -c stack_ll.c
clean:
	rm -f *.o runStackWithArray