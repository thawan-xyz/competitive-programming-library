#!/bin/bash

: ${TEAMNAME:="essa caiu no concurso de coveiro"}
: ${MEMBERS:="Thawan"}
: ${UNIVERSITY:="UFPE"}

mkdir -p ../pdf

cat > env.tex <<EOF
\def\teamname{$TEAMNAME}
\def\teammembers{$MEMBERS}
\def\teamuni{$UNIVERSITY}
EOF

g++ -std=c++17 -o generate_latex generate_latex.cpp -O2
./generate_latex $1 > notebook.tex

pdflatex -interaction=nonstopmode notebook.tex
pdflatex -interaction=nonstopmode notebook.tex

mv notebook.pdf ../pdf

rm -f tmp.cpp generate_latex notebook.aux notebook.toc notebook.out notebook.log env.tex notebook.tex
