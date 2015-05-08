import random

dat = [240] * 51
for x in range(1,21):
	dat[x] = dat[x-1] + random.randint(-2,10)
for x in range(22,30):
	dat[x] = dat[x-1] + random.randint(-2,2)
for x in range(31,38):
	dat[x] = dat[x-1] + random.randint(-10,2)
for x in range(39,51):
	dat[x] = dat[x-1] + random.randint(-2,2)

f = open('alt.txt','w')
for d in dat:
	f.write(str(d) + ",")
f.close()
	
