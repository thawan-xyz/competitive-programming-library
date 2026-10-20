#!/bin/bash

: ${TEAM_NAME:="Team of One"}
: ${MEMBERS:="Thawan"}
: ${UNIVERSITY:="UFPE"}
: ${CODE_FONT:=""}

mkdir -p ../pdf

font_available() {
  printf '%s\n' \
    '\documentclass{article}' \
    '\usepackage{fontspec}' \
    "\\setmonofont{$1}" \
    '\begin{document}\ttfamily x\end{document}' > probe.tex
  xelatex -interaction=batchmode -halt-on-error probe.tex > /dev/null 2>&1
  local status=$?
  rm -f probe.tex probe.aux probe.log probe.pdf
  return $status
}

find_code_font() {
  command -v xelatex > /dev/null 2>&1 || return 1
  local candidates=("Consolas" "Menlo" "Droid Sans Mono")
  [ -n "$CODE_FONT" ] && candidates=("$CODE_FONT")
  for font in "${candidates[@]}"; do
    if font_available "$font"; then
      echo "$font"
      return 0
    fi
  done
  return 1
}

cat > env.tex << EOF
\def\teamname{$TEAM_NAME}
\def\teammembers{$MEMBERS}
\def\teamuni{$UNIVERSITY}
EOF

ENGINE=pdflatex
FONT=$(find_code_font)
if [ -n "$FONT" ]; then
  ENGINE=xelatex
  printf '\\def\\codefontname{%s}\n' "$FONT" >> env.tex
  echo "Code font: $FONT (xelatex)"
else
  echo "Code font: default monospace (pdflatex)"
fi

g++ generate.cpp -std=c++20 -O2 -o generate

echo "Generating notebook structure..."
./generate $1 > notebook.tex

echo "Compiling PDF [1/2]..."
$ENGINE -interaction=batchmode notebook.tex > /dev/null 2>&1

echo "Compiling PDF [2/2]..."
$ENGINE -interaction=batchmode notebook.tex > /dev/null 2>&1

mv notebook.pdf ../pdf

rm -f tmp.cpp generate notebook.aux notebook.toc notebook.out notebook.log notebook.xdv missfont.log env.tex notebook.tex

echo "Done! Notebook saved at ../pdf/notebook.pdf"
