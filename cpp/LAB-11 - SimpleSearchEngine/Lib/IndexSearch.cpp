#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <stack>
#include <set>
#include <unordered_map>
#include <cmath>
class IndexSearch {
private:
    std::unordered_map<std::string, bool> words;
    std::unordered_map<std::string, std::vector<std::pair<int, std::vector<int> > > > words_info;
    std::unordered_map<int, std::vector<std::pair<std::string, std::vector<int> > > > docs_info;
    std::unordered_map<int, int> doc_size;
    std::unordered_map<int, std::string> docs_name;
    void to_lowercase(std::string &str) {
        for (int i = 0; i < str.length(); i++) {
            if ('A' <= str[i] && str[i] <= 'Z') {
                str[i] = char('a' + str[i] - 'A');
            }
        }
    }

    static std::string get_word(std::string &str, int &pos) {
        std::string res;

        while (pos < str.length() && str[pos] != ' ') {
            res.push_back(str[pos++]);
        }
        return res;
    }

    std::vector<std::string> convertToPolishNotation(std::string &str) {
        std::stack<std::string> st;
        std::vector<std::string> res;
        words.clear();
        int pos = 0;

        int cnt_words = 0;
        int cnt_operations = 0;
        while (pos < str.length()) {
            if (str[pos] == ' ') {
                pos++;
                continue;
            }

            if (str[pos] == '(') {
                st.emplace("(");
                pos++;
                continue;
            } else if (str[pos] == ')') {
                pos++;
                if (st.empty() || st.top() != "(") {
                    throw std::invalid_argument("incorrect query");
                }
                st.pop();
                continue;
            }

            auto word = get_word(str, pos);
            if (word[word.length() - 1] == ')') {
                pos--;
                word.pop_back();
            }
            if (word == "OR" || word == "AND") {
                cnt_operations++;
                if (!st.empty() && (st.top() == "OR" || st.top() == "AND")) {
                    throw std::invalid_argument("incorrect query");
                }
                st.push(word);
            } else {
                cnt_words++;
                if (st.empty() || (st.top() != "OR" && st.top() != "AND")) {
                    res.push_back(word);
                    words[word] = true;
                } else {
                    res.push_back(word);
                    words[word] = true;
                    res.push_back(st.top());
                    st.pop();
                }
            }
        }

        if (cnt_operations + 1 != cnt_words) {
            throw std::invalid_argument("incorrect query");
        }
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }

        for (auto &it : res) {
            if (it != "OR" && it != "AND") {
                to_lowercase(it);
            }
        }

        return res;
    }

    void read_index(std::ifstream &index) {
        std::string line;

        while (std::getline(index, line)) {
            std::istringstream line_stream(line);
            std::string word;
            line_stream >> word;
            if (words.find(word) == words.end()) {
                continue;
            }

            int docs_cnt = 0;

            line_stream >> docs_cnt;
            std::vector<std::pair<int, std::vector<int> > > vec(docs_cnt);

            for (int i = 0; i < docs_cnt; i++) {
                line_stream >> vec[i].first;
                docs_name[vec[i].first] = "";

                int cnt_represent = 0;
                line_stream >> cnt_represent;

                docs_info[vec[i].first].emplace_back();
                docs_info[vec[i].first].back().first = word;
                docs_info[vec[i].first].back().second.resize(cnt_represent);
                vec[i].second.resize(cnt_represent);


                for (int j = 0; j < cnt_represent; j++) {
                    line_stream >> vec[i].second[j];
                    docs_info[vec[i].first].back().second[j] = vec[i].second[j];
                }
            }

            words_info[word] = vec;
        }

        index.close();
    }

    void read_addfile(std::ifstream &addfile) {
        std::string line;
        std::getline(addfile, line);
        int docs_cnt = std::stoi(line);
        for (int i = 0; i < docs_cnt; i++) {
            std::getline(addfile, line);
            if (docs_name.find(i) == docs_name.end()) {
                continue;
            }

            std::istringstream line_stream(line);
            line_stream >> docs_name[i] >> doc_size[i];
        }

        addfile.close();
    }

    std::vector<int> parse_polish_notation(std::vector<std::string> &polish_notation) {
        std::stack<std::vector<int> > st;
        for (auto &it : polish_notation) {
            if (it == "AND") {
                auto vc1 = st.top(); st.pop();
                auto vc2 = st.top(); st.pop();
                int pos_1 = 0;
                int pos_2 = 0;
                std::vector<int> result;
                while (pos_1 < vc1.size() && pos_2 < vc2.size()) {
                    if (vc2[pos_2] == vc1[pos_1]) {
                        result.push_back(vc1[pos_1++]);
                        pos_2++;
                        continue;
                    }

                    if (vc2[pos_2] < vc1[pos_1]) {
                        pos_2++;
                    } else {
                        pos_1++;
                    }
                }

                st.push(result);
                continue;
            }

            if (it == "OR") {
                auto vc1 = st.top(); st.pop();
                auto vc2 = st.top(); st.pop();
                int pos_1 = 0;
                int pos_2 = 0;
                std::vector<int> result;
                while (pos_1 < vc1.size() || pos_2 < vc2.size()) {
                    if (pos_1 == vc1.size()) {
                        result.push_back(vc2[pos_2++]);
                        continue;
                    }

                    if (pos_2 == vc2.size()) {
                        result.push_back(vc1[pos_1++]);
                        continue;
                    }

                    if (vc2[pos_2] == vc1[pos_1]) {
                        result.push_back(vc1[pos_1++]);
                        pos_2++;
                        continue;
                    }

                    if (vc2[pos_2] < vc1[pos_1]) {
                        result.push_back(vc2[pos_2++]);
                    } else {
                        result.push_back(vc1[pos_1++]);
                    }
                }

                st.push(result);
                continue;
            }

            std::vector<int> vc;
            for (auto &it : words_info[it]) {
                vc.push_back(it.first);
            }
            st.push(vc);
        }

        return st.top();
    }
public:
    std::stringstream SearchDoc(std::string user_in, std::string files_dir) {
        auto polish_notation = convertToPolishNotation(user_in);
        std::ifstream index(files_dir + "index.txt");
        if (!index.is_open()) {
            throw "error in opening index";
        }
        read_index(index);

        std::ifstream addfile(files_dir + "addfile.txt");
        if (!addfile.is_open()) {
            throw "error in opening addfile";
        }
        read_addfile(addfile);

        auto result_docs = parse_polish_notation(polish_notation);

        if (result_docs.empty()) {
            std::stringstream ss;
            ss << "Required documents don`t exists";
            return ss;
        }

        long double dl_average = 0;
        long double k = 1;
        long double b = 0.5;
        auto N = static_cast<long double>(result_docs.size());

        for (auto &it : result_docs) {
            dl_average += doc_size[it];
        }

        dl_average /= N;

        std::set<std::pair<long double, int> > docs_score_heap;
        std::unordered_map<std::string, int> df;

        for (auto &it : result_docs) {
            for (auto &word_info : docs_info[it]) {
                df[word_info.first]++;
            }
        }

        for (auto &it : result_docs) {
            long double total_score = 0;

            for (auto &word_info : docs_info[it]) {
                long double tf = static_cast<double>(word_info.second.size());
                long double score = tf * (k + 1);
                score /= tf + k * (1 - b + b * (static_cast<double>(doc_size[it]) / dl_average));

                score *= logl(N / static_cast<double>(df[word_info.first])) + 1;

                total_score += score;
            }

            docs_score_heap.insert({total_score, it});
        }

        std::stringstream result;

        auto iter = docs_score_heap.end();
        while (iter != docs_score_heap.begin()) {
            iter--;
            result << "Path to document: " << docs_name[(*iter).second] << " " << (*iter).first << std::endl;
            for (auto &word_info : docs_info[(*iter).second]) {
                result << word_info.first << " : ";
                for (auto &represents : word_info.second) {
                    result << represents << " ";
                }
                result << std::endl;
            }
        }

        return result;
    }
};