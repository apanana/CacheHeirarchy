// Benchmarking the Memory Heirarchy
// Using cpuid to find out cache sizes
#include <stdio.h>
#include <stdint.h>


int main(){
	// Use a loop to check all 4 levels
	int i;
	for(i=0;i<4;++i){
		// inputting 4 into %eax gives us back cache parameters for a cache
		// level specified in %ecx (pg 267)
		// setting level to i
		int lvl = i;
		// reset a,b,c,d each iteration of the loop
		uint32_t a=0, b=0, c=0, d=0;
		__asm__(
			"movl $4, %%eax;"
			"movl %4, %%ecx;"
			"cpuid;"
			"movl %%eax, %0;"
			"movl %%ebx, %1;"
			"movl %%ecx, %2;"
			"movl %%edx, %3;"
			:"+r" (a), "+r" (b), "+r" (c), "+r" (d)
			:"r" (lvl)
			:"eax", "ebx", "ecx", "edx"
			);

		// Cache level
		printf("Cache level: %d\n",lvl);

		// register ecx: Sets
		// Sets: ecx + 1
		uint32_t sets = c;
		printf("Sets: %d\n",sets);


		// register ebx: Line size, Partitions, Ways of associativity.
		// use mod to grab specified number of bits
		// Line Size: ebx[11:0] + 1
		uint32_t l_size = b & 0xfff;
		// Partitions: ebx[21:12] + 1
		uint32_t parts = (b >> 12) & 0x3ff;
		// Ways of Associativity: ecx[31:22] + 1
		uint32_t ways = (b >> 22) & 0x3ff;
		printf("Line Size: %d\nPartitions: %d\nWays of Associativity: %d\n",l_size,parts,ways);


		// Cachsize = (Ways + 1) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)
		uint64_t cache = (ways + 1) * (parts + 1) * (l_size + 1) * (sets + 1);
		printf("Cache Size: %llu\t",(long long unsigned)cache);
		cache = cache/1000;
		printf("which is %llu kb\n",(long long unsigned)cache);
	}
	return 0;
}