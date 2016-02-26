# CacheHeirarchy
#### Alex C. Pan and Erik O. Lopez

###Design
The C code for running benchmarks can be found in cache.c. To test the access times of a specified buffer size, first an array of 64-bit integers of the specified size is created. Then the access time for a specified number of iterations is found using CLOCK_MONOTONIC_RAW measures the overall time of all the accesses. This is total time is then averaged to find the mean time to access a random element in the buffer. 
To reduce the effects of possible interruptions from the hardware of the OS, we increase the number of iterations so that the effects are negligable on the mean. To make sure we are mainly measuring access times (and not other operations), the only operation within the timed for-loop is updating a value. To reduce the prefetching capabilities of the cache, we make sure that these accesses are random and set the random seed with system time.

###Analysis
![alt tag](https://github.com/apanana/CacheHeirarchy/blob/master/Graph.png)"Graph of Average Access Times"

###CPUID
These are the results from calling inline cpuid:
L1: 32kb
L2: 262kb
L3: 10485kb
For more details, check cache_asm.txt 

How these compare with our estimates:


####Comparison of Times
How our results compare against norvig.com:
