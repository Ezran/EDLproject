import csv

clean = open('clean_gps.txt','w')
with open('gps.txt','r') as file:
	csv_f = csv.reader(file)
	for row in csv_f:
		clean.write('%.5f'%(float(row[0])) + "," + '%.5f'%(float(row[1])) + ",")
clean.close()
