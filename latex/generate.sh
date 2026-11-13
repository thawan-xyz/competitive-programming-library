#!/bin/bash
# Generate: builds ../pdf/notebook.pdf from the library
# Use: bash generate.sh ["title"]
set -e
trap 'rm -rf temp' EXIT
mkdir -p temp ../pdf
g++ -std=c++20 generate.cpp -o temp/generate
temp/generate "$@" > temp/notebook.tex
echo "compiling pdf [1/2]..."
pdflatex -interaction=batchmode -draftmode -output-directory=temp temp/notebook.tex > /dev/null || true
echo "compiling pdf [2/2]..."
pdflatex -interaction=batchmode -output-directory=temp temp/notebook.tex > /dev/null || true
mv temp/notebook.pdf ../pdf/
echo "notebook saved at ../pdf/notebook.pdf"
