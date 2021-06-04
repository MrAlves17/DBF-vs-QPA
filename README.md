# DBF-vs-QPA

To run tests, execute these comands:

make
./MAIN -n <ntasks> -u <utilization> -t <TmaxPerTmin> -s <seed> -g -r

g: generate_tasksets (optional)
r: run_tests (optional)

EXAMPLE:

make
./MAIN.out -n 14 -u 0.7 -t 10000 -s 1 -r -g