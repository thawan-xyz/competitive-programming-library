#!/bin/bash
set -e

: "${TEAM_NAME:=Team of One}"
: "${MEMBERS:=Thawan}"
: "${UNIVERSITY:=UFPE}"

trap 'rm -f generate env.tex notebook.{tex,aux,toc,out,log}' EXIT

mkdir -p ../pdf

cat > env.tex << EOF
\def\teamname{$TEAM_NAME}
\def\teammembers{$MEMBERS}
\def\teamuni{$UNIVERSITY}
EOF

g++ generate.cpp -std=c++20 -O2 -o generate
./generate "$@" > notebook.tex

for pass in 1 2; do
  echo "Compiling PDF [$pass/2]..."
  pdflatex -interaction=batchmode notebook.tex > /dev/null || true
done

mv notebook.pdf ../pdf/
echo "Done! Notebook saved at ../pdf/notebook.pdf"
