foo:	main.o	hw1.o
	gcc -o a.out main.o hw1.o validate_64.o
%o: %.c
	gcc -c -o $@ $<
clean:
	rm main.o hw1.o a.out
