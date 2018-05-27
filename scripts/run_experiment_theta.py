#!/usr/bin/python

import sys
import os
from time import sleep

max_theta = 10
repetitions = 100
problem_counter = 0

executable = "../build/experiment_theta "

for theta in range(1, max_theta+1):
	for repetition in range(repetitions):
		command = executable + str(theta) + " " + str(problem_counter)
		os.system(command)
		problem_counter += 1