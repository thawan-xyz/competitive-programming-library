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
using namespace std;
namespace fs = filesystem;

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

string get_algorithm_name(string file) {
    return fs::path(file).stem().string();
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

bool print_listing(string sub_name, string file, bool extra = false) {
    set<string> flags = get_flags(file);

    if (!print_all && flags.count(NO_PRINT)) return false;

    cout << "\\subsection{";
    if (!extra) print_escaped_string(get_algorithm_name(file));
    else print_escaped_string(sub_name);
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

void dfs(vector<pair<string, string>>& files, string path, bool extra = false) {
    if (!fs::exists(path)) return;

    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            if (!is_valid_file(entry.path())) continue;

            string filename = entry.path().filename().string();
            string full_path = entry.path().string();

            if (filename[0] == '.') continue;

            if (!extra) {
                files.emplace_back(filename, full_path);
            } else {
                print_listing(filename, full_path, extra && (filename != "vimrc"));
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
        cerr << "Printing all files..." << endl << endl;
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

            vector<pair<string, string>> files;
            dfs(files, dir_path.string());

            sort(files.begin(), files.end(), [&](const auto& f1, const auto& f2) {
                return to_lower(get_algorithm_name(f1.second)) < to_lower(get_algorithm_name(f2.second));
            });

            cerr << "=== " << dir_name << " ===" << endl;
            for (auto [file, file_path] : files) {
                bool printed = print_listing(file, file_path);
                if (printed) cerr << "  " << get_algorithm_name(file_path) << endl;
            }
            cerr << endl;
        }
    }

    if (fs::exists(root_path + "extra")) {
        print_section("extra");
        vector<pair<string, string>> files;
        dfs(files, root_path + "extra", true);
    }

    cout << "\\end{document}\n";
    return 0;
}
