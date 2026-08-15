#!/bin/bash

: ${TEAMNAME:="Team"}
: ${MEMBERS:="Thawan"}
: ${UNIVERSITY:="UFPE"}

mkdir -p ../pdf

cat > env.tex << EOF
\def\teamname{$TEAMNAME}
\def\teammembers{$MEMBERS}
\def\teamuni{$UNIVERSITY}
EOF

g++ -std=c++17 -o generate generate.cpp -O2

echo "Generating notebook structure..."
./generate $1 > notebook.tex

echo "Compiling PDF [1/3]..."
pdflatex -interaction=batchmode notebook.tex > /dev/null 2>&1

echo "Compiling PDF [2/3]..."
pdflatex -interaction=batchmode notebook.tex > /dev/null 2>&1

echo "Compiling PDF [3/3]..."
pdflatex -interaction=batchmode notebook.tex > /dev/null 2>&1

mv notebook.pdf ../pdf

rm -f tmp.cpp generate notebook.aux notebook.toc notebook.out notebook.log env.tex notebook.tex

echo ""
echo "Done! Notebook saved at ../pdf/notebook.pdf"
