#include "utils.h"

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

std::vector<std::array<int, 2>> readCol(const char* pFile) {
    std::vector<std::array<int, 2>> result;
    std::ifstream f;
    std::string line;
    std::string content = "";

    f.open(pFile);
    if (f.is_open())
    {
        while (getline(f, line))
        {
            if (line[0] == 'e') {
                std::array<int, 2> t = { stoi(split(line, ' ')[1]) , stoi(split(line, ' ')[2]) };
                result.push_back(t);
            }
        }
        f.close();
    }

    return result;
}
