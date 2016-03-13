#include <string>
#include <vector>

using std::vector;

vector<int> GetPrefixFunction (const std::string &str) {
    static int length;
    length = str.length();
    vector<int> pref_func(length);

    int end_index = 0;
    for (int cur_index = 1; cur_index < length; ++cur_index) {
        while (end_index != 0 && str[cur_index] != str[end_index]) {
            end_index = pref_func[end_index - 1];
        }
        if (str[end_index] == str[cur_index]) {
            pref_func[cur_index] = end_index + 1;
        }
        end_index = pref_func[cur_index];
    }
    return pref_func;
}

