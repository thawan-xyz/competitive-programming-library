#!/bin/bash
# Generate: builds ../pdf/notebook.pdf from the library
# Use: bash generate.sh ["title"] | /tmp/notebook keeps the compiled generate and the page numbers of the last build
set -e
b=/tmp/notebook
mkdir -p $b ../pdf
[ $b/generate -nt generate.cpp ] || g++ -std=c++20 generate.cpp -o $b/generate
$b/generate "$@" > $b/notebook.tex
# runs pdflatex again only while the page numbers in notebook.aux change, at most 3 times
for pass in 1 2 3; do
    echo "compiling pdf [$pass]..."
    cp $b/notebook.aux $b/old.aux 2> /dev/null || true
    pdflatex -interaction=batchmode -output-directory=$b $b/notebook.tex > /dev/null || true
    cmp -s $b/notebook.aux $b/old.aux && break
done
mv $b/notebook.pdf ../pdf/
echo "notebook saved at ../pdf/notebook.pdf"
