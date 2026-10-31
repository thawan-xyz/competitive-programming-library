# Competitive Programming Library

A library of algorithms and data structures for competitive programming, organized by topic. The repository includes a generator that turns all of its content into a PDF notebook for use in contests.

## Structure

| Folder | Content |
| --- | --- |
| `combinatorial/` | Combinatorics and counting |
| `dynamic-programming/` | Dynamic programming and its optimizations |
| `extra/` | General techniques and utilities |
| `geometry/` | Computational geometry |
| `graph/` | Graphs and trees |
| `math/` | General mathematics, transforms and algebra |
| `number-theory/` | Number theory and modular arithmetic |
| `square-root/` | Square root decomposition techniques |
| `string/` | String algorithms and data structures |
| `structs/` | Data structures |
| `latex/` | Notebook generator |
| `pdf/` | Generated notebook and reference material |

Each content folder may have subfolders. `.cpp` files contain code and `.tex` files contain theory and formulas.

## Conventions

Most code files start with a three-line header:

```cpp
// Name: what the structure or algorithm does
// Time: time complexity | Space: space complexity
// Note: dependencies, usage conventions and remarks
```

The code assumes the contest template, with `#define int long long`, `float` defined as `double` or `long double`, and the names `int128`, `inf`, `mod` and `rng` where used. Dependencies between files are stated in the `Note` field.

## Notebook

### Requirements

- `g++` with C++20 support
- `pdflatex` (TeX Live) with the packages used in `latex/header.tex`

### Usage

The script must be run from the `latex/` folder:

```bash
cd latex
./generate.sh                       # default title: Competitive Programming Library
./generate.sh "Thawan's Notebook"   # custom title
```

The title is optional. The output is saved to `pdf/notebook.pdf`.

### How it works

1. `generate.sh` writes the title to `env.tex`, compiles `generate.cpp` and runs it, producing `notebook.tex`.
2. `generate.cpp` reads `header.tex`, which defines the document layout, and walks the root folders in alphabetical order, skipping `latex/`, `pdf/` and hidden folders.
3. Each folder becomes a section. All of its files, including those in subfolders, are added to the section in alphabetical order of their path. Each item is titled with the file name without its extension, along with the subfolder it is in.
4. `.tex` files are included as LaTeX text. All other files are printed as code. Images, PDFs, binaries and archives are skipped.
5. Before the content, a table of contents is generated with every section and item numbered.
6. `pdflatex` runs twice, temporary files are removed and the PDF is moved to `pdf/`.

Code indentation is reduced to two spaces per level and consecutive blank lines are merged into one, to save space.

### Customization

| File | Purpose |
| --- | --- |
| `latex/header.tex` | Document layout: page, columns, fonts, colors and table of contents |
| `latex/logo.png` | Image to the left of the title |
| `latex/team.png` | Image to the right of the title |

To create a new section, create a folder in the root. To add an item, add a file to the corresponding folder.
