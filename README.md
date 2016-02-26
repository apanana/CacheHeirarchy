# CacheHeirarchy
#### Alex C. Pan and Erik O. Lopez

##Design
####The Code:
The C code for running benchmarks can be found in cache.c. To test the access times of a specified buffer size, first an array of 64-bit integers of the specified size is created. Then the access time for a specified number of iterations is found using CLOCK_MONOTONIC_RAW measures the overall time of all the accesses. This is total time is then averaged to find the mean time to access a random element in the buffer.
Checking cache sizes with cpuid was straightforward. I followed what was laid out in the manual and the implementation of this can be found in cache_asm.c. This was essentially just making sure we shift bits correctly to interpret data stored inside of the registers by calling cpuid.
####Reducing error:
To reduce the effects of possible interruptions from the hardware of the OS, we increase the number of iterations so that the effects are negligable on the mean. We also run iterations without a GUI on a polyopia machine without anything else running to reduce inteference from other sources. To make sure we are mainly measuring access times (and not other operations), the only operation within the timed for-loop is updating a value. To reduce the prefetching capabilities of the cache, we make sure that these accesses are random and set the random seed with system time.
####Data Collection:
A script was used to run specified buffer sizes and iterations. The buffer sizes were from 2^10 to 2^26, since I noticed weird behavior with running our C code for very numbers of iterations on low buffer sizes. This behavior was similar to what happened when we attempted to run high numbers of iterations on large buffer sizes (>=2^26). In both cases, the code became significantly faster as we reached increased the number of iterations (we increased iterations by factors of 10), and found that, contrary to expectations, the code started running faster at higher numbers of iterations. Since the code ran as expected and returned values that looked reasonable within reasonable bounds on iteration sizes, we would speculate that the speed-ups were caused by pre-fetching, and so we capped the buffer sizes and iteration numbers to avoid this behavior. 
The iteration numbers are specified by the equation iters = 11 - (size//3). In other words, we reduce the buffer size by a factor of ten every three increases in buffer size. This is to reduce the amount of runtime for each call of the program while still running enough iterations to keep the error signal low in the final avg.
Just to be sure that nothing totally wierd is happening, we run each specified buffer size and iteration 100 times and then took the average. In the raw data for these runs, we actually started noticing evidence of the prefetching we were attempting to avoid by capping the iteration numbers. This will be discussed in some more detail later.

##Analysis
####Graph of Average Access Times
![alt tag](https://github.com/apanana/CacheHeirarchy/blob/master/Graph.png)


##CPUID
These are the results from calling inline cpuid:
####L1: 32kb
####L2: 262kb
####L3: 10485kb
For more details, check cache_asm.txt 

How these compare with our estimates:


##Comparison of Times
The performance numbers we measured are similar to the slides in class (page 5 of Memory Hierachy Slides). We compare our results to the slides rather than from http://norvig.com/21-days.html#answers due to the website having a table of more dated cache access times. To restate the access times from class, we have a fetch time of 1-2 ns latency for L1, 3-5 ns latency for L2, and 7-12 latency for L3, and 60-90 ns latency for Dram which is main memory. While our graph shows the jumps from L1 to L2 and L2 to L3 clearly, the jump to main memory becomes a little unclear.
