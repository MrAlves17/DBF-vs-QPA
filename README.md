# DBF-vs-QPA

This project was done for Real Time Systems Course at UFBA in 2021.1

It consists of an analysis of schedulability test algorithms based in the article of Zhang and Burns (2009). 

For this purpose, two tests were done:

	1. A comparison between the old method of detecting schedulability (called here as DBF) and the QPA (Quick convergence Processor-demand Analysis). 
	The test measures the number of h(t) calculations for both approaches. The function h(t) stands for Processor Demand Function, that means the
	same thing of DBF (Demand Bound Function).

	2. Analysis of how many times the DBF* (a sufficient method for detecting processor schedulability) proved the task set schedulable and run QPA for
	the	failed cases to check if the task set was schedulable or not.

A report of the results are available at the PDF (Portuguese).

## How to Execute

To run tests, execute this comand in the Terminal:

./run_tests.sh

The tests' results are available at: results/

