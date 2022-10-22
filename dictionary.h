#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "frequency.h"

unsigned int initializeDictionary(std::vector<std::string> &dictionary, std::string filename, unsigned int wordSize)
{
    auto wordCount = 0;
    std::fstream dictFile;
    dictFile.open(filename, std::ios::in);
    if (dictFile.is_open())
    {
        std::string line;
        while (getline(dictFile, line))
        {
            std::stringstream ss(line);
            std::string trimmed_string;
            ss >> trimmed_string;
            if (trimmed_string.size() == wordSize)
            {
                dictionary.push_back(trimmed_string);
                wordCount++;
            }
        }
        dictFile.close(); // close the file object.
        return wordCount;
    }
    return 0;
}

void printDictionary(std::vector<std::string> &dictionary, int num)
{
    std::cout << "Dictionary: ";

    if (num <= 0)
        for (auto iter = dictionary.begin(); iter != dictionary.end(); iter++)
            std::cout << "\"" << *iter << "\", ";
    else
    {
        int counter = num;
        for (auto iter = dictionary.begin(); iter != dictionary.end() && counter > 0; iter++)
        {
            std::cout << "\"" << *iter << "\", ";
            counter--;
        }
    }
    std::cout << std::endl;
}