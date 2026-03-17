#!/bin/bash

# 1. Save this file (e.g., as 'run.sh') in the same folder as main.cpp.
# 2. Make it executable in the terminal by typing:
#    chmod +x run.sh
# 3. Whenever you want to compile and run, type:
#    ./run.sh

g++ -std=c++20 main.cpp -o main && ./main
