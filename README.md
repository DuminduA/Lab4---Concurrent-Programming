# Multiply Matrices
this lab assignment we have learned how to use “parallel for” and optimize a matrix-matrix multiplication to
gain better performance.

# Tasks
- Sequential matrix-matrix multiplication.
- Parallel matrix-matrix multiplication using a “parallel for” loop.
- Optimized parallel matrix-matrix multiplication according to the cpu architecture.
- Analyze execution times
>Note: Only the time spent for matrix multiplication is calculated

# Instruction to Compile and Execute this program
## Step 1 - Prerequisites
Open the command prompt or the terminal in the project folder.
Windows users, make sure to have a C/C++ compiler like MinGW or TDM-GCC installed in the machine, and proper environment variables set.
Also we need OpenMp library to run the program. you can download it here.http://tdm-gcc.tdragon.net/ make sure to tick the openMp when 
it asking what to install.

## Step 2 - Compile
Run the following command to compile the application.
Make sure to include openmp using ```-fopenmp``` and make sure to enable c++11 features using ```-std=c++11``` options.

##### Sequential implementation
```bash
g++ sequential.cpp matrixOp.cpp util.cpp -o sequential -fopenmp -std=c++11
```

##### Parallel implementation
```bash
g++ parallel.cpp matrixOp.cpp util.cpp -o parallel -fopenmp -std=c++11
```

##### Optimized implementation - tiled matrix multiplication
```bash
g++ optimized_method_3.cpp matrixOp.cpp util.cpp -o optimized_3 -O2 -fopenmp -std=c++11

##### Optimized implementation - transpose
```bash
g++ optimized_code_2.cpp matrixOp.cpp util.cpp -o optimized_2 -O2 -fopenmp -std=c++11

##### Optimized implementation - OpenMp scheduling
```bash
g++ optimized_code.cpp matrixOp.cpp util.cpp -o optimized_1 -O2 -fopenmp -std=c++11
```
>Note: Since the implementation use the features enabled by the O2 optimization and use that to gain additional performance
as described in the report, when compiling the optimized version use O2 optimization by adding the '-O2' flag.

## Step 3 - Run
Above command will create a executable file in the same directory.
Double click and open it (windows)
Or execute following command in the terminal (linux)
```bash
./<file_name>
```

## Step 4 - Program arguments
when executing the program will ask for user inputs.
1. Need to specify the matrix size.
2. Do not need to specify the matrix size

first choice will allow you to select a matrix size but only one execution will run
second choice will chose matrix sizes automatically in the multiples of 200 upto 2000

you need to enter the sample size. the program will iterate this number of times. 

Program will output the method you used and average time, standard deviation and number of samples needed to achieve 95% 
confidence and 5% accuracy.

sequential.cpp - sequential run of the program
parallel.cpp - parallel run of the program
optimized_code.cpp - usage of openMp scheduling
optimized_code_2 - usage of transpose to optimize
optimized_method_3 - usage of tiled matrix multiplication.