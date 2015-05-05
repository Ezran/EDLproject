import random

dat = [150] * 150
for x in range(1,150):
	dat[x] = dat[x-1] + random.randint(-10,10)

f = open('alt.txt','w')
for d in dat:
	f.write(str(d) + '\n')
f.close()
	
