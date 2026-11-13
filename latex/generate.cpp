// Generate: prints notebook.tex with a section for each folder of the library and a bar for each file
// Use: ./generate "title" > notebook.tex | run from latex/, a .tex comes before the code with the same name
#include <bits/stdc++.h>
using namespace std;
namespace fs = filesystem;

const fs::path root = "..";
const string hash_script = "../extra/hash.py";

struct file {
    string name, folder;
    fs::path path;
};

string escape(const string &s) {
    string res;
    for (char c : s) {
        if (c == '\\') res += "\\textbackslash{}";
        else if (c == '^' or c == '~') res += string("\\") + c + "{}";
        else if (string("&%$#_{}").find(c) != string::npos) res += string("\\") + c;
        else res += c;
    }
    return res;
}

map<fs::path, vector<pair<string, string>>> hashed;

// runs hash.py on every .cpp in a single python, each file ends with a line "\x01"
// hash.py prints each line followed by " [hash]" if it closes a block or by " " otherwise
void load_hashes(const vector<fs::path> &paths) {
    if (paths.empty() or not fs::exists(hash_script)) return;
    string cmd = "python3 -c 'import sys, runpy\nfor f in sys.argv[1:]:\n"
                 "    sys.argv = [\"\", f]; runpy.run_path(\"" + hash_script + "\"); print(\"\\x01\")\n' ";
    for (auto &p : paths) cmd += " \"" + p.string() + "\"";
    FILE *pipe = popen(cmd.c_str(), "r");
    string out;
    char buf[1 << 16];
    for (size_t k; (k = fread(buf, 1, sizeof buf, pipe)) > 0;) out.append(buf, k);
    pclose(pipe);
    istringstream in(out);
    int i = 0;
    for (string line; i < paths.size() and getline(in, line);) {
        if (line == "\x01") i++;
        else hashed[paths[i]].push_back({line.substr(0, line.rfind(' ')), line.substr(line.rfind(' ') + 1)});
    }
}

// {line, hash}
vector<pair<string, string>> read_lines(const fs::path &path) {
    if (hashed.count(path)) return hashed[path];
    vector<pair<string, string>> res;
    ifstream in(path);
    for (string line; getline(in, line);) res.push_back({line, ""});
    return res;
}

// marks the names right before a '(', outside comments, strings and chars, for header.tex to color as functions
string mark_functions(const string &line, bool &block) {
    static const set<string> keywords = {"if", "else", "for", "while", "do", "return", "switch", "case", "catch", "throw",
        "sizeof", "alignof", "decltype", "static_cast", "const_cast", "reinterpret_cast", "dynamic_cast", "and", "or", "not",
        "int", "long", "short", "char", "bool", "float", "double", "void", "auto", "unsigned", "signed", "new", "delete",
        "operator", "template", "typename", "array", "vector", "string", "map", "pair", "tuple", "queue", "deque", "stack",
        "priority_queue", "multiset", "multimap", "unordered_map", "unordered_set"};
    string res;
    for (int i = 0; i < line.size(); ++i) {
        if (block) {
            if (line.compare(i, 2, "*/") == 0) block = false, res += line[i++];
        } else if (line.compare(i, 2, "//") == 0) {
            return res + line.substr(i);
        } else if (line.compare(i, 2, "/*") == 0) {
            block = true, res += line[i++];
        } else if (line[i] == '"' or line[i] == '\'') {
            int j = i + 1;
            while (j < line.size() and line[j] != line[i]) j += line[j] == '\\' ? 2 : 1;
            res += line.substr(i, j - i), i = j;
        } else if (isalnum(line[i]) or line[i] == '_') {
            int j = i;
            while (j < line.size() and (isalnum(line[j]) or line[j] == '_')) j++;
            string word = line.substr(i, j - i);
            if (isdigit(word[0]) or j == line.size() or line[j] != '(' or keywords.count(word)) res += word;
            else res += "(*@\\fn{" + regex_replace(word, regex("_"), "\\_") + "}@*)";
            i = j - 1;
            continue;
        }
        if (i < line.size()) res += line[i];
    }
    return res;
}

void print_code(const fs::path &path) {
    auto lines = read_lines(path);
    int unit = 0;
    bool tabs = false;
    for (auto &[line, h] : lines) {
        erase_if(line, [](unsigned char c) { return c < 32 and c != '\t'; });
        while (not line.empty() and isspace(line.back())) line.pop_back();
        tabs |= line.starts_with('\t');
        if (not line.empty()) unit = gcd(unit, (int) line.find_first_not_of(' '));
    }
    // indentation of 4 spaces becomes 2, blank lines in sequence become one
    vector<pair<string, string>> out;
    for (auto &[line, h] : lines) {
        if (line.empty() and (out.empty() or out.back().first.empty())) continue;
        if (not tabs and unit > 2 and unit % 2 == 0 and not line.empty()) {
            int k = line.find_first_not_of(' ');
            line.erase(0, k - k / (unit / 2));
        }
        out.push_back({line, h});
    }
    while (not out.empty() and out.back().first.empty()) out.pop_back();

    // C++ is the default language of header.tex, setting it again would drop its extra keywords and colors
    string ext = path.extension(), options = ext == ".py" ? "language=Python" : ext == ".sh" ? "language=bash" : "";
    if (ranges::any_of(out, [](auto &p) { return not p.second.empty(); })) options += (options.empty() ? "" : ", ") + string("style=hashed");
    bool block = false;
    if (ext == ".cpp") for (auto &[line, h] : out) line = mark_functions(line, block);
    if (options.find("hashed") == string::npos and ranges::any_of(out, [](auto &p) { return p.first.find("(*@") != string::npos; })) options += (options.empty() ? "" : ", ") + string("style=hashed");
    cout << "\\begin{lstlisting}" << (options.empty() ? "" : "[" + options + "]") << "\n";
    for (auto &[line, h] : out) cout << line << (h.empty() ? "" : "(*@\\codehash{" + h.substr(1, h.size() - 2) + "}@*)") << '\n';
    cout << "\\end{lstlisting}\n";
}

// sections are the folders of the root, files are found recursively and sorted by path, with the .tex first
vector<pair<string, vector<file>>> load_sections() {
    vector<fs::path> folders;
    for (auto &e : fs::directory_iterator(root)) {
        string name = e.path().filename();
        if (e.is_directory() and name[0] != '.' and name != "latex" and name != "pdf") folders.push_back(e.path());
    }
    ranges::sort(folders);
    vector<pair<string, vector<file>>> sections;
    for (auto &folder : folders) {
        vector<pair<string, file>> files;
        for (auto &e : fs::recursive_directory_iterator(folder)) {
            fs::path p = e.path(), rel = fs::relative(p, folder);
            string ext = p.extension(), sub = rel.parent_path();
            if (not e.is_regular_file() or (ext != ".cpp" and ext != ".py" and ext != ".sh" and ext != ".tex")) continue;
            string key = sub + "/" + rel.stem().string() + (ext == ".tex" ? "." : ext);
            ranges::transform(key, key.begin(), ::tolower);
            files.push_back({key, {p.stem(), sub.empty() ? "" : sub + "/", p}});
        }
        if (files.empty()) continue;
        ranges::sort(files, {}, &pair<string, file>::first);
        sections.push_back({folder.filename(), {}});
        for (auto &[key, f] : files) sections.back().second.push_back(f);
    }
    return sections;
}

int main(int argc, char **argv) {
    ifstream header("header.tex");
    if (not header) return cerr << "header.tex not found, run from latex/\n", 1;
    auto sections = load_sections();
    // arguments: the title and -black, which leaves every section in black
    string title = "Competitive Programming Library";
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-black") cout << "\\def\\blacksections{}\n";
        else title = argv[i];
    }
    cout << "\\def\\notebooktitle{" << escape(title) << "}\n";
    cout << "\\def\\numsections{" << sections.size() << "}\n";
    cout << header.rdbuf();
    vector<fs::path> cpps;
    for (auto &[name, files] : sections) for (auto &f : files) if (f.path.extension() == ".cpp") cpps.push_back(f.path);
    load_hashes(cpps);

    // index, a name that repeats in the same folder (like x.tex and x.cpp) appears once, linking to the first
    cout << "\\tocbegin\n";
    for (int s = 0, id = 0; s < sections.size(); ++s) {
        auto &[name, files] = sections[s];
        if (s) cout << "\\tocgap\n";
        cout << "\\tocbar{" << s + 1 << "}{" << escape(name) << "}\n";
        vector<int> items;
        for (int i = 0; i < files.size(); ++i) {
            if (i == 0 or files[i].name != files[i - 1].name or files[i].folder != files[i - 1].folder) items.push_back(i);
        }
        for (int i = 0; i < items.size(); ++i) {
            cout << "\\tocitem{" << s + 1 << "}{" << id + items[i] + 1 << "}{" << escape(files[items[i]].name) << "}\n";
            if (items.size() > 1 and (i == 0 or i == items.size() - 2)) cout << "\\nobreak\n";
        }
        id += files.size();
    }
    cout << "\\tocend\n\\par\\vspace{1pt}\\hrule height 0.4pt\\vspace{1pt}\n";

    int id = 0;
    for (int s = 0; s < sections.size(); ++s) {
        auto &[name, files] = sections[s];
        cout << "\\secbar{" << s + 1 << "}{" << escape(name) << "}\n";
        for (auto &f : files) {
            cout << "\\filebar{" << ++id << "}{" << escape(f.name) << "}{" << escape(f.folder) << "}\n";
            if (f.path.extension() == ".tex") cout << "\\texfile{" << f.path.string() << "}\n";
            else print_code(f.path);
        }
    }
    cout << "\\end{multicols*}\n\\end{document}\n";
    cerr << id << " files in " << sections.size() << " sections\n";
}
