#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using namespace std;

const string NO_PRINT = "noprint";
const string ROOT_PATH = "../";

bool print_all = false;
bool dense = false;
bool raw = false;

struct file_entry {
    int id = 0;
    string name;
    string subdir;
    string path;
    string sort_key;
};

struct section {
    int id = 0;
    string name;
    vector<file_entry> files;
};

string to_lower(string text) {
    for (char& character : text) {
        if (character >= 'A' && character <= 'Z') character ^= 32;
    }
    return text;
}

string trim(const string& text) {
    size_t begin = text.find_first_not_of(" \t\r");
    if (begin == string::npos) return "";
    size_t end = text.find_last_not_of(" \t\r");
    return text.substr(begin, end - begin + 1);
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

string latex_escape(const string& text) {
    string out;
    for (char character : text) {
        switch (character) {
            case '\\': out += "\\textbackslash{}"; break;
            case '^':  out += "\\^{}"; break;
            case '~':  out += "\\~{}"; break;
            case '&': case '%': case '$': case '#': case '_': case '{': case '}':
                out += '\\';
                out += character;
                break;
            default:
                out += character;
        }
    }
    return out;
}

string strip_extension(const string& filename) {
    fs::path p(filename);
    string ext = to_lower(p.extension().string());
    if (ext == ".cpp" || ext == ".py" || ext == ".java" || ext == ".tex") {
        return p.stem().string();
    }
    return filename;
}

set<string> get_flags(const string& file) {
    ifstream fin(file);
    string line;
    if (!getline(fin, line)) return {};

    size_t start = line.find('[');
    size_t end = line.rfind(']');
    if (start == string::npos || end == string::npos || start >= end) return {};

    set<string> flags;
    for (const string& flag : split(line.substr(start + 1, end - start - 1), ',')) {
        flags.insert(trim(flag));
    }
    return flags;
}

bool should_print(const string& file) {
    return print_all || !get_flags(file).count(NO_PRINT);
}

string sanitize_line(const string& line) {
    string clean;
    for (unsigned char character : line) {
        if ((character >= 32 && character <= 126) || character == '\t' || character >= 128) {
            clean += character;
        }
    }
    size_t end = clean.find_last_not_of(" \t");
    return end == string::npos ? "" : clean.substr(0, end + 1);
}

vector<string> read_code_lines(const string& file) {
    ifstream fin(file);
    vector<string> lines;
    string line;
    bool first = true;

    while (getline(fin, line)) {
        string clean = sanitize_line(line);
        if (first) {
            first = false;
            if (clean.size() >= 2 && clean.front() == '[' && clean.back() == ']') continue;
        }
        lines.push_back(clean);
    }
    return lines;
}

void shrink_indent(vector<string>& lines) {
    int unit = 0;
    for (const string& line : lines) {
        if (!line.empty() && line[0] == '\t') return;
        size_t indent = line.find_first_not_of(' ');
        if (indent == string::npos || indent == 0) continue;
        unit = gcd(unit, (int)indent);
    }
    if (unit <= 2 || unit % 2 != 0) return;

    for (string& line : lines) {
        size_t indent = line.find_first_not_of(' ');
        if (indent == string::npos || indent == 0) continue;
        line.erase(0, indent - indent / (unit / 2));
    }
}

void squeeze_blank_lines(vector<string>& lines) {
    vector<string> result;
    bool pending_blank = false;
    for (string& line : lines) {
        if (line.empty()) {
            pending_blank = true;
            continue;
        }
        if (pending_blank && !dense && !result.empty()) result.push_back("");
        pending_blank = false;
        result.push_back(move(line));
    }
    lines = move(result);
}

void print_code_file(const string& file) {
    vector<string> lines = read_code_lines(file);
    if (!raw) {
        shrink_indent(lines);
        squeeze_blank_lines(lines);
    }

    cout << "\\begin{lstlisting}\n";
    for (const string& line : lines) cout << line << "\n";
    cout << "\\end{lstlisting}\n";
}

bool is_valid_file(const fs::path& filepath) {
    string ext = to_lower(filepath.extension().string());
    return !(ext == ".pdf" || ext == ".o" || ext == ".out" || ext == ".exe" ||
             ext == ".png" || ext == ".jpg" || ext == ".zip" || ext == ".tar");
}

void dfs(vector<file_entry>& files, const fs::path& base_path, const fs::path& current_path) {
    if (!fs::exists(current_path)) return;

    for (const auto& entry : fs::directory_iterator(current_path)) {
        string filename = entry.path().filename().string();
        if (filename.empty() || filename[0] == '.') continue;

        if (entry.is_directory()) {
            dfs(files, base_path, entry.path());
        } else if (entry.is_regular_file() && is_valid_file(entry.path())) {
            fs::path rel_path = fs::relative(entry.path(), base_path);

            file_entry item;
            item.name = strip_extension(filename);
            item.subdir = rel_path.parent_path().generic_string();
            item.path = entry.path().string();
            item.sort_key = to_lower(rel_path.generic_string());
            files.push_back(move(item));
        }
    }
}

vector<section> load_sections() {
    vector<fs::path> directories;
    if (fs::exists(ROOT_PATH)) {
        for (const auto& entry : fs::directory_iterator(ROOT_PATH)) {
            if (!entry.is_directory()) continue;
            string dir_name = entry.path().filename().string();
            if (dir_name.empty() || dir_name[0] == '.' || dir_name == "latex" || dir_name == "pdf") continue;
            directories.push_back(entry.path());
        }
    }

    sort(directories.begin(), directories.end(), [](const fs::path& a, const fs::path& b) {
        return a.filename().string() < b.filename().string();
    });

    vector<section> sections;
    int next_section_id = 0, next_file_id = 0;

    for (const fs::path& dir_path : directories) {
        vector<file_entry> files;
        dfs(files, dir_path, dir_path);
        sort(files.begin(), files.end(), [](const file_entry& a, const file_entry& b) {
            return a.sort_key < b.sort_key;
        });

        section sec;
        sec.name = dir_path.filename().string();
        for (file_entry& item : files) {
            if (!should_print(item.path)) continue;
            item.id = ++next_file_id;
            sec.files.push_back(move(item));
        }
        if (sec.files.empty()) continue;

        sec.id = ++next_section_id;
        sections.push_back(move(sec));
    }
    return sections;
}

bool print_raw_file(const string& file) {
    ifstream fin(file);
    if (!fin) return false;
    string line;
    while (getline(fin, line)) cout << line << "\n";
    return true;
}

void print_toc(const vector<section>& sections) {
    if (sections.empty()) return;

    cout << "\\tocbegin\n";
    for (const section& sec : sections) {
        if (sec.id > 1) cout << "\\tocgap\n";
        cout << "\\tocbar{" << sec.id << "}{" << latex_escape(sec.name) << "}\n";

        int count = sec.files.size();
        for (int i = 0; i < count; i++) {
            const file_entry& file = sec.files[i];
            cout << "\\tocitem{" << sec.id << "}{" << file.id << "}{" << latex_escape(file.name) << "}\n";
            if (count >= 2 && (i == 0 || i == count - 2)) cout << "\\nobreak\n";
        }
    }
    cout << "\\tocend\n";
    cout << "\\par\\vspace{1pt}\\hrule height 0.4pt\\vspace{1pt}\n";
}

void print_file(const file_entry& item) {
    string subdir = item.subdir.empty() ? "" : item.subdir + "/";
    cout << "\\filebar{" << item.id << "}{" << latex_escape(item.name) << "}{"
         << latex_escape(subdir) << "}\n";

    if (to_lower(fs::path(item.path).extension().string()) == ".tex") {
        cout << "\\texfile{" << item.path << "}\n";
    } else {
        print_code_file(item.path);
    }
}

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--printall") print_all = true;
        else if (arg == "--dense") dense = true;
        else if (arg == "--raw") raw = true;
        else cerr << "Warning: unknown option " << arg << " (ignored)\n";
    }

    if (!print_raw_file("header.tex")) {
        cerr << "Error: header.tex not found (run from the latex/ directory)\n";
        return 1;
    }

    vector<section> sections = load_sections();
    print_toc(sections);

    int file_count = 0;
    for (const section& sec : sections) {
        cout << "\\secbar{" << sec.id << "}{" << latex_escape(sec.name) << "}\n";
        for (const file_entry& item : sec.files) {
            print_file(item);
            file_count++;
        }
    }

    cout << "\\end{multicols*}\n";
    cout << "\\end{document}\n";

    cerr << file_count << " files in " << sections.size() << " sections\n";
    return 0;
}

