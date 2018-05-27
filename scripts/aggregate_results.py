#!/usr/bin/python

import sys
import os
import csv

directory = "../results/theta/"


resultFiles = [f for f in os.listdir(directory) if f.startswith("result_")]
resultFiles.sort(key = lambda f: int(f.split('_')[1].split('.')[0]))

fout = open(directory + "results.csv", "w")
fout_average = open(directory + "averages.csv", "w")

first = True

x_name = "theta"
s = [[0 for i in range(12)] for i in range(301)]
count = [0 for i in range(301)]

for filename in resultFiles :
    if filename.startswith("result_") :
        with open(directory+filename,"rb") as f:
            if first:
                line = f.readline()
                fout.write(line)
                fout_average.write(line[11:])
                first = False
            else:
                f.next()

            reader = csv.reader(f)

            for row in reader:
                count[int(row[1])] += 1
                for i in range(2, 14):
                    s[int(row[1])][i-2] += int(row[i])
        f.close()

        with open(directory+filename,"rb") as f:
            f.next()
            for line in f:
                fout.write(line)
        f.close()

for i in range(len(s)):
    if count[i] != 0:
        fout_average.write(str(i))
    	for j in range(12):
    		result = "%.2f" % ((s[i][j])/float(count[i]))
    		fout_average.write("," + result)
    	fout_average.write("\n")

fout.close()
fout_average.close()
