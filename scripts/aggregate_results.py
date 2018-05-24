#!/usr/bin/python

import sys
import os
import csv

directory = "../results/agents/"


resultFiles = [f for f in os.listdir(directory) if f.startswith("result_")]
resultFiles.sort(key = lambda f: int(f.split('_')[1].split('.')[0]))

fout = open(directory + "results.csv", "w")
first = True

for filename in resultFiles :
  if filename.startswith("result_") :
  	with open(directory+filename,"rb") as f:
  		if not first:
  			f.next()
  		else:
  			first = False

		for line in f:
			fout.write(line)

  	f.close()

fout.close()
