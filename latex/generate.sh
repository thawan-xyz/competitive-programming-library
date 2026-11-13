#!/bin/bash
# Generate: builds ../pdf/notebook.pdf from the library
# Use: bash generate.sh ["title"] | build/ keeps the compiled generate and the page numbers of the last build
set -e
mkdir -p build ../pdf
[ build/generate -nt generate.cpp ] || g++ -std=c++20 generate.cpp -o build/generate
build/generate "$@" > build/notebook.tex
# runs pdflatex again only while the page numbers in notebook.aux change, at most 3 times
for pass in 1 2 3; do
    echo "Compiling PDF [$pass]..."
    cp build/notebook.aux build/old.aux 2> /dev/null || true
    pdflatex -interaction=batchmode -output-directory=build build/notebook.tex > /dev/null || true
    cmp -s build/notebook.aux build/old.aux && break
done
mv build/notebook.pdf ../pdf/
echo "Done! Notebook saved at ../pdf/notebook.pdf"
