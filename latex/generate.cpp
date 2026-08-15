#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <array>
#include <memory>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

#define RED "\033[0;31m"
#define RESET "\033[0m"

bool LOOK_FOR_HASH_IN_FILE = false;
int HASH_LEN = 3;

string NO_HASH = "nohash";
string NO_PRINT = "noprint";

string root_path = "../";

bool print_all = false;

bool is_comment(string line) {
    while (line.size() && (line[0] == ' ' || line[0] == '\t')) line = line.substr(1);
    if (line.empty()) return true;
    if (line.size() >= 2 && line.substr(0, 2) == "//") return true;
    if (line.size() >= 2 && line.substr(0, 2) == "/*") return true;
    return false;
}

vector<string> split(string line, char delimiter) {
    vector<string> result;
    string current;
    line.push_back(delimiter);
    for (char character : line) {
        if (character == delimiter) {
            if (!current.empty()) result.push_back(current);
            current.clear();
            continue;
        }
        current += character;
    }
    return result;
}

set<string> get_flags(string file) {
    ifstream fin(file.c_str());
    string line;
    if (!getline(fin, line)) return {};
    fin.close();
    while (line.size() && line[0] != '[') line = line.substr(1);
    if (line.empty() || line.back() != ']') return {};
    vector<string> flags = split(line.substr(1, line.size() - 2), ',');
    return set<string>(flags.begin(), flags.end());
}

void print_code_file(string file, bool extra = false) {
    cout << "\\begin{lstlisting}\n";
    ifstream fin(file.c_str());
    string line;
    int line_count = 0;

    while (getline(fin, line)) {
        if (line_count == 0 && !line.empty() && line[0] == '[' && line.back() == ']') {
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

void print_raw_file(string file, bool extra = false) {
    ifstream fin(file.c_str());
    string line;
    while (getline(fin, line)) {
        cout << line << "\n";
    }
    fin.close();
}

void print_escaped_string(string text) {
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

bool print_listing(string display_name, string file, bool extra = false) {
    set<string> flags = get_flags(file);

    if (!print_all && flags.count(NO_PRINT)) return false;

    cout << "\\subsection{";
    print_escaped_string(display_name);
    cout << "}\n";

    print_code_file(file, extra);
    return true;
}

bool is_valid_file(const fs::path& filepath) {
    string ext = filepath.extension().string();
    for (char& c : ext) c = tolower(c);

    if (ext == ".pdf" || ext == ".o" || ext == ".out" || ext == ".exe" || 
        ext == ".png" || ext == ".jpg" || ext == ".zip" || ext == ".tar") {
        return false;
    }
    return true;
}

struct FileEntry {
    string rel_path_sort;
    string file_name;
    string full_path;
};

void dfs(vector<FileEntry>& files, string base_path, string current_path, bool extra = false) {
    if (!fs::exists(current_path)) return;

    for (const auto& entry : fs::directory_iterator(current_path)) {
        string filename = entry.path().filename().string();
        if (filename[0] == '.') continue;

        if (entry.is_directory()) {
            dfs(files, base_path, entry.path().string(), extra);
        } else if (entry.is_regular_file()) {
            if (!is_valid_file(entry.path())) continue;

            fs::path rel_path = fs::relative(entry.path(), base_path);
            string sort_key = (rel_path.parent_path() / rel_path.stem()).string();
            string display_name = entry.path().stem().string();

            if (!extra) {
                files.push_back({sort_key, display_name, entry.path().string()});
            } else {
                print_listing(filename, entry.path().string(), extra && (filename != "vimrc"));
            }
        }
    }
}

void print_section(string section_name) {
    cout << "\n\\vspace{0.8em}\n\\hrule\n\\vspace{0.5em}\n";
    cout << "\\section{" << section_name << "}\n\n";
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

    print_raw_file("header.tex", true);

    if (fs::exists(root_path)) {
        vector<fs::path> directories;
        for (const auto& entry : fs::directory_iterator(root_path)) {
            if (entry.is_directory()) {
                string dir_name = entry.path().filename().string();
                if (dir_name[0] == '.' || dir_name == "latex" || dir_name == "pdf" || dir_name == "extra") continue;
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

            sort(files.begin(), files.end(), [&](const FileEntry& f1, const FileEntry& f2) {
                return to_lower(f1.rel_path_sort) < to_lower(f2.rel_path_sort);
            });

            cerr << "> " << dir_name << endl;
            for (const auto& item : files) {
                bool printed = print_listing(item.file_name, item.full_path);
                if (printed) {
                    cerr << "  | " << item.file_name << endl;
                }
            }
            cerr << endl;
        }
    }

    if (fs::exists(root_path + "extra")) {
        print_section("extra");
        cerr << "> extra" << endl;
        vector<FileEntry> files;
        dfs(files, root_path + "extra", root_path + "extra", true);
        cerr << endl;
    }

    cout << "\\end{document}\n";
    return 0;
}
