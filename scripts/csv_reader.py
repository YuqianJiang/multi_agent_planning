#!/usr/bin/python

import sys
import os
import csv

directory = sys.argv[1]
x_name = sys.argv[2]
y_name = sys.argv[3]

csvFiles = os.listdir(directory)

s = [0] * 50
count = [0] * 50

for filename in csvFiles :
  if filename.startswith("results") :
    with open(directory+filename,"rb") as f:
      reader = csv.DictReader(f)
      for row in reader :
        count[int(row[x_name])] += 1
        s[int(row[x_name])] += float(row[y_name])
        if int(row["timed_out"]) == 1 :
          print filename

for i in range(1,50) :
  if count[i] != 0 :
    #print str(i) + " " + str(s[i]/count[i]) + " " + str(count[i])
    print str(s[i]/count[i])