#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <sstream>

class IndexBuilder {
private:
	struct Node {
		std::vector<int> docs_id{};
        std::vector<int> docs_line_appears{};
		std::vector<int> count{};
		std::unordered_map<char, Node*> next_char{};

	};

	Node* root;
	
	std::vector<std::filesystem::path> docs_name;
	std::vector<int> docs_word_count;

    static void to_lowercase(std::string &str) {
        for (int i = 0; i < str.length(); i++) {
            if ('A' <= str[i] && str[i] <= 'Z') {
                str[i] = char('a' + str[i] - 'A');
            }
        }
    }

	void rec_deleter(Node* vert) {
		for (auto& it : vert->next_char) {
			rec_deleter(it.second);
		}
		delete vert;
	}

	void rec_write(Node* vert, std::ofstream& out, std::string &word) {

		if (!vert->docs_id.empty()) {
			out << word << " " << vert->docs_id.size() << " ";
			
			int i = 0, pos_docs_line = 0;
			while (i < vert->docs_id.size()) {
				out << vert->docs_id[i] << " " << vert->count[i] << " ";
                int need = vert->count[i];
                while (need) {
                    need--;
                    out << vert->docs_line_appears[pos_docs_line++] << " ";
                }
				i++;
			}

			out << '\n';
		}

        for (auto &it: vert->next_char) {
            word.push_back(it.first);
            rec_write(it.second, out, word);
            word.pop_back();
        }
	}

	void add_str(Node* vert, std::string& str, int pos, int count_line) {
        while(true) {
            if (pos == str.length() || str[pos] == '\0') {
                if (vert->docs_id.empty() || vert->docs_id.back() != docs_name.size()) {
                    vert->docs_id.push_back(static_cast<int>(docs_name.size()));
                    vert->count.push_back(0);
                }

                vert->count.back()++;
                vert->docs_line_appears.push_back(count_line);
                break;
            } else {
                char c = str[pos];

                if (vert->next_char.find(c) == vert->next_char.end()) {
                    vert->next_char[c] = new Node();
                }

                vert = vert->next_char[c];
                pos++;
            }
        }
	}

	void process_file(const std::filesystem::path &file_path) {
		std::ifstream file(file_path);
        if (!file.is_open()) {
            return;
        }

        std::string file_line;
        int word_count = 0;
        int count_line = 1;
        while (std::getline(file, file_line)) {
            std::istringstream stream(file_line);
            std::string word;
            while (stream >> word) {
                if (word.length() > 1000) {
                    continue;
                }
                to_lowercase(word);
                add_str(root, word, 0, count_line);
                word_count++;
            }
            count_line++;
        }
        file.close();
        if (word_count != 0) {
            docs_name.push_back(file_path);
            docs_word_count.push_back(word_count);
        }
	}
	
	void save_docs(std::ofstream& out) {
		out << docs_name.size() << std::endl;
		for (int i = 0; i < docs_name.size(); i++) {
			out << docs_name[i] << " " << docs_word_count[i] << std::endl;
		}
	}

    bool is_banned_file(const std::filesystem::path &file_path) {
        auto str = file_path.string();
        int pos = str.find_last_of('.');

        return str.substr(pos + 1, str.length() - pos - 1) != "bin";
    }
    void read_dir(std::string &path) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            if (entry.is_regular_file() && is_banned_file(entry.path())) {
                process_file(entry.path());
            }
        }
    }

    void save_index(const std::string& path) {
        std::ofstream out(path + "addfile.txt");
        if (!out.is_open()) {
            throw "cannot open an addfile for save";
        }

        std::string word;

        save_docs(out);
        out.close();

        out.open(path + "index.txt");
        if (!out.is_open()) {
            throw "cannot open an index file for save";
        }

        rec_write(root, out, word);

        out.close();
    }

public:
	IndexBuilder() {
		root = new Node();
	}
	~IndexBuilder() {
		rec_deleter(root);
	}

    void build_index(std::string directory_path, std::string dir_save) {
        read_dir(directory_path);
        save_index(dir_save);
    }
};


