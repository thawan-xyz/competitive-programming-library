#!/bin/bash
# Generate: builds ../pdf/notebook.pdf from the library
# Use: bash generate.sh ["title"] [-black] [-half] [-compact] [-modern]
set -e
trap 'rm -rf temp' EXIT
mkdir -p temp ../pdf
half=false
for arg in "$@"; do [ "$arg" = "-half" ] && half=true; done
steps=$($half && echo 3 || echo 2)
args=()
for arg in "$@"; do
    if [ "$arg" != "-modern" ]; then args+=("$arg"); continue; fi
    args+=("-modern")
    find_font() {
        local file=$(fc-list ":family=JetBrains Mono:style=$1" file 2>/dev/null | grep -i "\.ttf" | grep -v "\[" | head -n 1 | cut -d: -f1)
        [ -z "$file" ] && file=$(find ~/.local/share/fonts ~/.fonts ~/Library/Fonts /Library/Fonts /usr/share/fonts \
            /usr/local/share/fonts /c/Windows/Fonts -iname "JetBrainsMono-$1.ttf" 2>/dev/null | head -n 1)
        echo "$file"
    }
    regular=$(find_font Regular)
    bold=$(find_font Bold)
    if [ -n "$regular" ] && command -v ttf2tfm > /dev/null && kpsewhich ec.enc > /dev/null; then
        cp "$regular" temp/JetBrainsMono-Regular.ttf
        cp "${bold:-$regular}" temp/JetBrainsMono-Bold.ttf
        (cd temp && ttf2tfm JetBrainsMono-Regular.ttf -q -T ec.enc jbm-regular.tfm
            ttf2tfm JetBrainsMono-Bold.ttf -q -T ec.enc jbm-bold.tfm) > /dev/null 2>&1 || true
    fi
    if [ -f temp/jbm-regular.tfm ] && [ -f temp/jbm-bold.tfm ]; then
        export TFMFONTS="temp:" TTFONTS="temp:"
        args+=("-jetbrains")
    else
        echo "JetBrains Mono (or ttf2tfm) not found, the code keeps the default font"
    fi
done
g++ -std=c++20 generate.cpp -o temp/generate
temp/generate "${args[@]}" > temp/notebook.tex
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
