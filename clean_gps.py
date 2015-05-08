import csv

clean = open('clean_gps.txt','w')
with open('gps2.txt','r') as file:
	csv_f = csv.reader(file)
	for row in csv_f:
		clean.write('%.8f'%(float(row[0])) + "," + '%.8f'%(float(row[1])) + ",")
clean.close()
