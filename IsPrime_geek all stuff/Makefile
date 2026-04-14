CC       :=  /usr/bin/gcc
CCFLAGS  := -Wall -O3

all : IsPrime_geek.exe

IsPrime_geek.exe: IsPrime_geek.c THE50millionprimes_array.c
	$(CC) $(CCFLAGS) -flarge-source-files -o IsPrime_geek.exe IsPrime_geek.c -lm 
