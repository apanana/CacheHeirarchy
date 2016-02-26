# CacheHeirarchy
#### Alex C. Pan and Erik O. Lopez

###Design
####The Code:
The C code for running benchmarks can be found in cache.c. To test the access times of a specified buffer size, first an array of 64-bit integers of the specified size is created. Then the access time for a specified number of iterations is found using CLOCK_MONOTONIC_RAW measures the overall time of all the accesses. This is total time is then averaged to find the mean time to access a random element in the buffer.
Checking cache sizes with cpuid was straightforward. I followed what was laid out in the manual and the implementation of this can be found in cache_asm.c. This was essentially just making sure we shift bits correctly to interpret data stored inside of the registers by calling cpuid.
####Reducing error:
To reduce the effects of possible interruptions from the hardware of the OS, we increase the number of iterations so that the effects are negligable on the mean. To make sure we are mainly measuring access times (and not other operations), the only operation within the timed for-loop is updating a value. To reduce the prefetching capabilities of the cache, we make sure that these accesses are random and set the random seed with system time.
####Data Collection:

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
The performance numbers we measured are similar to the slides in class (page 5 of Memory Hierachy Slides). We compare our results to the slides rather than from http://norvig.com/21-days.html#answers due to the website having a table of more dated cache access times. To restate the access times from class, we have a fetch time of 1-2 ns latency for L1, 3-5 ns latency for L2, and 7-12 latency for L3, and 60-90 ns latency for Dram which is main memory. While our graph shows the jumps from L1 to L2 and L2 to L3 clearly, the jump to main memory becomes a little unclear.
