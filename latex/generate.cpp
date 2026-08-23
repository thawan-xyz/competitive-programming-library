#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

const string NO_PRINT = "noprint";
const string ROOT_PATH = "../";

bool print_all = false;

struct FileEntry {
    string rel_path_sort;
    string subfolder;
    string file_name;
    string full_path;
};

vector<string> split(const string& line, char delimiter) {
    vector<string> result;
    string current;
    for (char character : line) {
        if (character == delimiter) {
            if (!current.empty()) result.push_back(current);
            current.clear();
        } else {
            current += character;
        }
    }
    if (!current.empty()) result.push_back(current);
    return result;
}

set<string> get_flags(const string& file) {
    ifstream fin(file.c_str());
    string line;
    if (!getline(fin, line)) return {};
    fin.close();

    size_t start = line.find('[');
    size_t end = line.rfind(']');
    if (start == string::npos || end == string::npos || start >= end) return {};

    vector<string> flags = split(line.substr(start + 1, end - start - 1), ',');
    return set<string>(flags.begin(), flags.end());
}

void print_code_file(const string& file) {
    cout << "\\begin{lstlisting}\n";
    ifstream fin(file.c_str());
    string line;
    int line_count = 0;

    while (getline(fin, line)) {
        if (line_count == 0 && !line.empty() && line.front() == '[' && line.back() == ']') {
            line_count++;
            continue;
        }

        string clean_line = "";
        for (unsigned char character : line) {
            if ((character >= 32 && character <= 126) || character == '\t' || character >= 128) {
                clean_line += character;
            }
        }
        
        cout << clean_line << "\n";
        line_count++;
    }
    fin.close();
    cout << "\\end{lstlisting}\n\n";
}

void print_raw_file(const string& file) {
    ifstream fin(file.c_str());
    string line;
    while (getline(fin, line)) {
        cout << line << "\n";
    }
    fin.close();
}

void print_escaped_string(const string& text) {
    for (char character : text) {
        if (character == '^') {
            cout << "\\^{}";
        } else if (character == '&' || character == '%' || character == '_' || character == '#') {
            cout << '\\' << character;
        } else {
            cout << character;
        }
    }
}

bool print_listing(const string& display_name, const string& file, bool is_inside_subfolder) {
    set<string> flags = get_flags(file);

    if (!print_all && flags.count(NO_PRINT)) return false;

    if (is_inside_subfolder) {
        cout << "\\subsubsection{";
        print_escaped_string(display_name);
        cout << "}\n";
    } else {
        cout << "\\refstepcounter{subsection}%\n";
        cout << "\\subsection*{{\\scriptsize\\bfseries\\thesubsection\\quad ";
        print_escaped_string(display_name);
        cout << "}}\n";
        cout << "\\addcontentsline{toc}{subsubsection}{\\protect\\numberline{\\thesubsection}";
        print_escaped_string(display_name);
        cout << "}\n";
    }

    print_code_file(file);
    return true;
}

bool is_valid_file(const fs::path& filepath) {
    string ext = filepath.extension().string();
    for (char& character : ext) character = tolower(character);

    if (ext == ".pdf" || ext == ".o" || ext == ".out" || ext == ".exe" || 
        ext == ".png" || ext == ".jpg" || ext == ".zip" || ext == ".tar") {
        return false;
    }
    return true;
}

void dfs(vector<FileEntry>& files, const string& base_path, const string& current_path, bool extra = false) {
    if (!fs::exists(current_path)) return;

    for (const auto& entry : fs::directory_iterator(current_path)) {
        string filename = entry.path().filename().string();
        if (filename.empty() || filename[0] == '.') continue;

        if (entry.is_directory()) {
            dfs(files, base_path, entry.path().string(), extra);
        } else if (entry.is_regular_file()) {
            if (!is_valid_file(entry.path())) continue;

            fs::path rel_path = fs::relative(entry.path(), base_path);
            string sort_key = (rel_path.parent_path() / rel_path.stem()).string();
            string display_name = entry.path().stem().string();
            
            string subfolder = rel_path.parent_path().string();
            if (subfolder == ".") subfolder = "";

            if (!extra) {
                files.push_back({sort_key, subfolder, display_name, entry.path().string()});
            } else {
                print_listing(filename, entry.path().string(), false);
            }
        }
    }
}

void print_section(const string& section_name) {
    cout << "\n\\vspace{0.8em}\n\\hrule\n\\vspace{0.5em}\n";
    cout << "\\section{" << section_name << "}\n\n";
}

void print_subsection_header(const string& subfolder_name) {
    cout << "\\subsection{";
    print_escaped_string(subfolder_name);
    cout << "}\n";
}

string to_lower(string text) {
    for (char& character : text) {
        if (character >= 'A' && character <= 'Z') character ^= 32;
    }
    return text;
}

int main(int argc, char** argv) {
    if (argc > 1 && string(argv[1]) == "--printall") {
        print_all = true;
        cerr << "Printing all files..." << endl;
    }

    print_raw_file("header.tex");

    if (fs::exists(ROOT_PATH)) {
        vector<fs::path> directories;
        for (const auto& entry : fs::directory_iterator(ROOT_PATH)) {
            if (entry.is_directory()) {
                string dir_name = entry.path().filename().string();
                if (dir_name.empty() || dir_name[0] == '.' || dir_name == "latex" || dir_name == "pdf" || dir_name == "extra") continue;
                directories.push_back(entry.path());
            }
        }

        sort(directories.begin(), directories.end(), [](const fs::path& a, const fs::path& b) {
            return a.filename().string() < b.filename().string();
        });

        for (const auto& dir_path : directories) {
            string dir_name = dir_path.filename().string();

            print_section(dir_name);

            vector<FileEntry> files;
            dfs(files, dir_path.string(), dir_path.string());

            sort(files.begin(), files.end(), [](const FileEntry& a, const FileEntry& b) {
                return to_lower(a.rel_path_sort) < to_lower(b.rel_path_sort);
            });

            cerr << "> " << dir_name << endl;
            string current_subfolder = "";
            for (const auto& item : files) {
                bool is_inside_subfolder = !item.subfolder.empty();

                if (is_inside_subfolder && item.subfolder != current_subfolder) {
                    current_subfolder = item.subfolder;
                    print_subsection_header(current_subfolder);
                } else if (!is_inside_subfolder) {
                    current_subfolder = "";
                }

                bool printed = print_listing(item.file_name, item.full_path, is_inside_subfolder);
                if (printed) {
                    cerr << "  | " << item.file_name << endl;
                }
            }
            cerr << endl;
        }
    }

    if (fs::exists(ROOT_PATH + "extra")) {
        print_section("extra");
        cerr << "> extra" << endl;
        vector<FileEntry> files;
        dfs(files, ROOT_PATH + "extra", ROOT_PATH + "extra", true);
        cerr << endl;
    }

    cout << "\\end{multicols}\n";
    cout << "\\end{document}\n";
    return 0;
}
