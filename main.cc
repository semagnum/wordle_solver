#include <set>
#include <string>
#include <iostream>
#include <array>
#include "dictionary.h"

const unsigned int WORD_SIZE = 5;

enum correctnessType
{
    CORRECT_POSITION,
    WRONG_POSITION,
    WRONG_LETTER
};

void parseGuess(std::set<std::string> &dictionary, std::string &guess)
{
    std::array<correctnessType, WORD_SIZE> status;
    for (unsigned int index = 0; index < WORD_SIZE; index++)
    {
        unsigned int numResponse = 4;
        while (numResponse > 3 || numResponse == 0)
        {
            std::cout << "For the letter \"" << guess[index] << "\", how correct is it?" << std::endl;
            std::cout << "\t" << CORRECT_POSITION + 1 << ". Correct letter in correct position" << std::endl;
            std::cout << "\t" << WRONG_POSITION + 1 << ". Correct letter in incorrect position" << std::endl;
            std::cout << "\t" << WRONG_LETTER + 1 << ". Incorrect letter" << std::endl;

            std::cin >> numResponse;
        }

        correctnessType response = (correctnessType)(numResponse - 1);

        status[index] = response;
    }

    for (unsigned int index = 0; index < WORD_SIZE; index++)
    {
        correctnessType response = status[index];
        auto letter = guess[index];

        if (response == CORRECT_POSITION) // erase all words where the letter at that position doesn't match
        {
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                if (word[index] != letter)
                    it = dictionary.erase(it);
                else
                    ++it;
            }
        }
        // if it's the incorrect position
        // for each dictionary word
        // if word contains letter and that letter's position isn't already a CORRECT_POSITION, keep
        else if (response == WRONG_POSITION)
        {
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                bool foundLetter = false;
                for (int i = 0; i < word.length(); ++i)
                {
                    if (word[i] == letter && status[i] != CORRECT_POSITION)
                    {
                        foundLetter = true;
                        break;
                    }
                }
                if (foundLetter)
                    ++it;
                else
                    it = dictionary.erase(it);
            }
        }
        // if it's the incorrect letter
        // for each dictionary word
        // if word contains letter and that letter's position isn't already CORRECT_POSITION or INCORRECT_POSITION, exclude
        else if (response == WRONG_LETTER)
        {
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                if (word[index] == letter)
                    it = dictionary.erase(it);
                else
                    ++it;
            }
        }
    }
}

int main()
{
    std::set<std::string> dictionary;

    auto wordCount = initializeDictionary(dictionary, "large_dictionary.txt", WORD_SIZE);
    std::cout << wordCount << " words added to dictionary." << std::endl;

    std::cout << "Welcome to Wordle Helper! ";

    while (true)
    {
        std::string guess = "";
        while (guess.size() != WORD_SIZE)
        {
            std::cout << "Enter your guess: ";
            std::cin >> guess;
        }

        std::string finishResp;
        std::cout << std::endl
                  << "Did you guess correctly? (y/N) ";
        std::cin >> finishResp;

        if (finishResp[0] == 'y' || finishResp[0] == 'Y')
            break;

        std::cout << std::endl;

        parseGuess(dictionary, guess);

        printDictionary(dictionary, 10);
    }
    std::cout << "Yay, good job! We did it." << std::endl;
    return 0;
}