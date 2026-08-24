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
bool is_first_code_file = true;

struct file_entry {
    string rel_path_sort;
    string file_name;
    string full_path;
};

string strip_extension(const string& filename) {
    fs::path p(filename);
    string ext = p.extension().string();
    string ext_lower = ext;
    for (char& character : ext_lower) character = tolower(character);

    if (ext_lower == ".cpp" || ext_lower == ".py" || ext_lower == ".java") {
        return p.stem().string();
    }
    return filename;
}

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
    cout << "\\end{lstlisting}\n";
    cout << "\\par\\vspace{1pt}\\hrule height 0.2pt\\vspace{2pt}\n";
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

bool print_listing(const string& raw_file_name, const string& file) {
    set<string> flags = get_flags(file);

    if (!print_all && flags.count(NO_PRINT)) return false;

    string display_name = strip_extension(raw_file_name);

    if (is_first_code_file) {
        cout << "\\par\\vspace{2pt}\\hrule height 0.4pt\\vspace{2pt}\n";
        is_first_code_file = false;
    }

    cout << "\\addtofilelist{";
    print_escaped_string(display_name);
    cout << "}\n";

    cout << "\\refstepcounter{subsection}%\n";
    cout << "\\subsection*{{\\scriptsize\\bfseries\\thesubsection\\quad \\underline{";
    print_escaped_string(display_name);
    cout << "}}}\n";
    cout << "\\addcontentsline{toc}{subsection}{\\protect\\numberline{\\thesubsection}";
    print_escaped_string(display_name);
    cout << "}\n";

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

void dfs(vector<file_entry>& files, const string& base_path, const string& current_path) {
    if (!fs::exists(current_path)) return;

    for (const auto& entry : fs::directory_iterator(current_path)) {
        string filename = entry.path().filename().string();
        if (filename.empty() || filename[0] == '.') continue;

        if (entry.is_directory()) {
            dfs(files, base_path, entry.path().string());
        } else if (entry.is_regular_file()) {
            if (!is_valid_file(entry.path())) continue;

            fs::path rel_path = fs::relative(entry.path(), base_path);
            string sort_key = rel_path.string();
            string display_name = entry.path().filename().string();

            files.push_back({sort_key, display_name, entry.path().string()});
        }
    }
}

void register_section_silent(const string& section_name) {
    cout << "\n\\refstepcounter{section}\n";
    cout << "\\addcontentsline{toc}{section}{\\protect\\numberline{\\thesection}" << section_name << "}\n";
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

            register_section_silent(dir_name);

            vector<file_entry> files;
            dfs(files, dir_path.string(), dir_path.string());

            sort(files.begin(), files.end(), [](const file_entry& a, const file_entry& b) {
                return to_lower(a.rel_path_sort) < to_lower(b.rel_path_sort);
            });

            for (const auto& item : files) {
                print_listing(item.file_name, item.full_path);
            }
        }
    }

    if (fs::exists(ROOT_PATH + "extra")) {
        register_section_silent("extra");
        vector<file_entry> files;
        dfs(files, ROOT_PATH + "extra", ROOT_PATH + "extra");
        for (const auto& item : files) {
            print_listing(item.file_name, item.full_path);
        }
    }

    cout << "\\end{multicols*}\n";
    cout << "\\end{document}\n";
    return 0;
}
