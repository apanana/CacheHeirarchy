import os
sys.stdout = open('data.txt', 'w')


size = 4
while size <= 26:

	i = 0
	iters = 9-((size+1)//4)
	print("size:","2^"+str(size),"and iters:","10^"+str(iters),sep='')
	out = "./a.out "+str(2**size)+" "+str(10**iters)

	while i < 100:
		os.system(out)
		i = i+1

	size = size+1
