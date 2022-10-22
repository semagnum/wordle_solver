#include <array>
#include <string>

std::array<char, 26> frequency {'e', 'a', 'r', 'i', 'o', 't', 'n', 's', 'l', 'c', 'u', 'd', 'p', 'm', 'h', 'g', 'b', 'f', 'y', 'w', 'k',
                      'v', 'x', 'z', 'j', 'q'};

unsigned short frequencyIndex(const std::string &word)
{
    for (auto i = 0; i < frequency.size(); i++)
        for (char c : word)
            if (frequency[i] == c)
                return i;

    return -1;
}