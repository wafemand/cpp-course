/*
Find all occurrences of string argv[2] in file with name argv[1].
Time: O(m + n)
Memory: O(m)
where 	n - size of file
	m - size of string

*/
#include <iostream>
#include <cstdio>
#include <vector>


using namespace std;


template <class T>
class prefix_function{


private:
    vector<size_t> pref_func;
    T str;
    size_t common_size = 0;


    template <typename Tchar>
    size_t calc_next_pf(Tchar new_char){
        size_t ret = common_size;
        while (ret > 0 && new_char != str[ret]){
            ret = pref_func[ret - 1];
        }
        ret += size_t(new_char == str[ret]);
        return ret;
    }


    void build_pf(){
        common_size = 0;
        size_t n = str.size();
        pref_func.resize(n);
        pref_func[0] = 0;
        for (size_t i = 1; i < n; i++){
            pref_func[i] = calc_next_pf(str[i]);
        }
    }


public:
    explicit prefix_function() = default;


    explicit prefix_function(T &st) {
        str = st;
        build_pf();
    }


    size_t get_common_size(){
        return common_size;
    }


    template <typename Tchar>
    void update(Tchar new_char){
        common_size = calc_next_pf(new_char);
    }


    void rebuild(T &new_string){
        str = new_string;
        build_pf();
    }
};


int main(int argc, char *argv[]) {
    if (argc >= 3) {
        FILE *file = fopen(argv[1], "r");
        string word = string(argv[2]);
        prefix_function<string> pf(word);
        char cur_char;
        size_t pos = 0;
        while (fscanf(file, "%c", &cur_char) != -1) {
            pf.update(cur_char);
            if (pf.get_common_size() == word.size()){
                cout << pos - word.size() + 1 << '\n';
            }
            pos++;
        }
    }
    else{
        cout << "error\n";
    }
}
