#include <string>
#include <vector>

using std::vector;

vector<int> GetZFunction(const std::string &str) {
    static int length;
    length = str.length();
    vector<int> z_func(length);

    int left = 0, right = -1;
    for (int index = 1; index < length; ++index) {
        if (index < right) {
            z_func[index] = std::min(z_func[index - left], right - index + 1);
        }
        while (index + z_func[index] < length
               && str[index + z_func[index]] == str[z_func[index]]) {
            ++z_func[index];
        }
        if (right < index + z_func[index] - 1) {
            right = index + z_func[index] - 1;
            left = index;
        }
    }
    return z_func;
}

