#!/bin/bash
# Generate: builds ../pdf/notebook.pdf from the library
# Use: bash generate.sh ["title"] [-black] [-half] [-compact]
set -e
trap 'rm -rf temp' EXIT
mkdir -p temp ../pdf
half=false
for arg in "$@"; do [ "$arg" = "-half" ] && half=true; done
steps=$($half && echo 3 || echo 2)
g++ -std=c++20 generate.cpp -o temp/generate
temp/generate "$@" > temp/notebook.tex
echo "compiling pdf [1/$steps]..."
pdflatex -interaction=batchmode -draftmode -output-directory=temp temp/notebook.tex > /dev/null || true
echo "compiling pdf [2/$steps]..."
pdflatex -interaction=batchmode -output-directory=temp temp/notebook.tex > /dev/null || true
if $half; then
    echo "compiling pdf [3/3]..."
    cat > temp/half.tex << 'TEX'
\documentclass{article}
\usepackage[a4paper, landscape]{geometry}
\usepackage{pdfpages}
\usepackage{xcolor}
\AddToHook{shipout/foreground}{\put(0.5\paperwidth, -\paperheight){\color{black!45}\rule{0.5pt}{\paperheight}}}
\begin{document}
\includepdf[pages=-, nup=2x1, noautoscale, delta=0 0]{temp/notebook.pdf}
\end{document}
TEX
    pdflatex -interaction=batchmode -output-directory=temp temp/half.tex > /dev/null || true
    mv temp/half.pdf temp/notebook.pdf
fi
mv temp/notebook.pdf ../pdf/
echo "notebook saved at ../pdf/notebook.pdf"
