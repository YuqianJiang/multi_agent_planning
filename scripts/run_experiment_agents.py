#!/usr/bin/python

import sys
import os
from time import sleep

max_agents = 20
repetitions = 100
problem_counter = 0

executable = "../build/experiment_agents "

for numAgents in range(2, max_agents+1):
	for repetition in range(repetitions):
		command = executable + str(numAgents) + " " + str(problem_counter)
		os.system(command)
		problem_counter += 1