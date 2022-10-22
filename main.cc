#include <vector>
#include <string>
#include <map>
#include <array>

#include <iostream>
#include <algorithm>

#include "dictionary.h"
#include "correctness.h"
#include "config.h"

void parseGuess(std::vector<std::string> &dictionary, std::string &guess)
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

    std::map<char, unsigned int> correctPositions, wrongPositions, wrongLetters;
    for (unsigned int index = 0; index < WORD_SIZE; index++)
    {
        correctnessType response = status[index];
        auto letter = guess[index];

        if (response == CORRECT_POSITION)
        {
            if (correctPositions.count(letter) == 0)
                correctPositions[letter] = 1;
            else
                correctPositions[letter]++;
            // remove all words from dictionary that do not have this letter in this position
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                if (word[index] == letter)
                    ++it;
                else
                    it = dictionary.erase(it);
            }
        }
        else
        {
            // remove all words from dictionary that have this letter in this (wrong) position
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                if (word[index] == letter)
                    it = dictionary.erase(it);
                else
                    ++it;
            }
        }
        if (response == WRONG_POSITION)
        {
            if (wrongPositions.count(letter) == 0)
                wrongPositions[letter] = 1;
            else
                wrongPositions[letter]++;
        }
        else if (response == WRONG_LETTER)
        {
            if (wrongLetters.count(letter) == 0)
                wrongLetters[letter] = 1;
            else
                wrongLetters[letter]++;
        }
    }

    for (auto item : wrongLetters)
    {
        auto letter = item.first;
        auto count = item.second + correctPositions.count(letter);
        // if no instances of this letter are in wrongPosition, then we know it's not in the word
        if (wrongPositions.count(letter) == 0 && correctPositions.count(letter) == 0)
        {
            // remove all words in dictionary with that letter
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                bool foundLetter = false;
                for (int i = 0; i < word.length(); ++i)
                {
                    if (word[i] == letter)
                    {
                        foundLetter = true;
                        break;
                    }
                }
                if (foundLetter)
                    it = dictionary.erase(it);
                else
                    ++it;
            }
        }
    }

    for (auto item : wrongPositions)
    {
        auto letter = item.first;
        auto count = item.second + correctPositions.count(letter);
        // if there are `n` instances of a letter in wrongPosition and 0 in wrongLetter, then at least `n` of that letter is in the word
        if (wrongLetters.count(letter) == 0)
        {
            // remove all words in dictionary with less than `n` of that letter
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                auto letterCount = 0;
                for (int i = 0; i < word.length(); ++i)
                    if (word[i] == letter)
                        letterCount++;

                if (letterCount < count)
                    it = dictionary.erase(it);
                else
                    ++it;
            }
        }
        // if there are `n` instances of a letter in wrongPosition and 1+ in wrongLetter, then exactly `n` of that letter is in the word
        else
        {
            // remove all words in dictionary with less than `n` of that letter
            for (auto it = dictionary.begin(); it != dictionary.end();)
            {
                auto word = *it;
                auto letterCount = 0;
                for (int i = 0; i < word.length(); ++i)
                    if (word[i] == letter)
                        letterCount++;

                if (letterCount != count)
                    it = dictionary.erase(it);
                else
                    ++it;
            }
        }
    }
}

int main()
{
    std::vector<std::string> dictionary;
    auto wordCount = initializeDictionary(dictionary, "large_dictionary.txt", WORD_SIZE);
    std::cout << wordCount << " words added to dictionary." << std::endl;

    std::cout << "Sorting...";
    std::sort(dictionary.begin(), dictionary.end(), [](std::string s1, std::string s2)
              { return frequencyIndex(s1) < frequencyIndex(s2); });
    std::cout << "done" << std::endl;

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