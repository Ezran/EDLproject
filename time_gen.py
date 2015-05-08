import random

times = [5000] * 51
for x in range(1,51):
	times[x] = times[x-1] + random.randint(3500,6500)

f = open('times.txt','w')
for d in times:
	f.write(str(d) + ",")
f.close()
