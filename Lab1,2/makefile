vowel : count_vowels_exe
	./count_vowels_exe

count_vowels_exe : count_vowels.o 	master.o
	gcc -o count_vowels_exe count_vowels.o master.o

count_vowels.o : count_vowels.c
	gcc -c count_vowels.c

master.o : master.c
	gcc -c master.c

clean :
	rm -f *.o
	rm count_vowels_exe
	rm count_consonants_exe

consonant : count_consonants_exe
	./count_consonants_exe

count_consonants_exe : count_consonants.o 	master.o
	gcc -o count_consonants_exe count_consonants.o master.o
	
count_consonants.o : count_consonants.c
	gcc -c count_consonants.c
