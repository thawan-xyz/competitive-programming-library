#!/bin/bash
# Generate: builds ../pdf/notebook.pdf from the library
# Use: bash generate.sh ["title"]
set -e
trap 'rm -f generate notebook.{tex,aux,log,out}' EXIT
g++ -std=c++20 -O2 generate.cpp -o generate
./generate "$@" > notebook.tex
for pass in 1 2; do pdflatex -interaction=batchmode notebook.tex > /dev/null || true; done
mkdir -p ../pdf && mv notebook.pdf ../pdf/
echo "notebook saved at ../pdf/notebook.pdf"
