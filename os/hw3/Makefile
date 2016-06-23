foo:	main.o Disk.o hw2.o sema.o FileSystem.o Mount.o 
	gcc -o a.out main.o hw2.o Disk.o sema.o FileSystem.o Mount.o 
%o: %.c
	gcc -c -o $@ $<
clean:
	rm main.o hw2.o a.out Disk.o MY_DISK sema.o FileSystem.o Mount.o
