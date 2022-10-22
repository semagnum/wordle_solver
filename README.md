# How to Use

## Create and import a dictionary

I created a text file, `"large_dictionary.txt"`, based on online sources to use as a reference. It should be a list of lowercase-only words separated by new lines. Such as:

```
trees
test
beast
```

If you would like to provide a different filename, you can do so on this line, in `"main.cc"`:
```cpp
auto wordCount = initializeDictionary(dictionary, "large_dictionary.txt", WORD_SIZE);
```
## Compiling the solver

I locally use `g++`, but any compiler should do. I'd highly recommend Gitpod to tinker and run all this in your browser:

[<img src="https://img.shields.io/badge/Run%20with-Gitpod-908a85?logo=gitpod" alt="Run with Gitpod"/>
](https://gitpod.io/#https://github.com/semagnum/wordle_solver)

## Running the solver

Take a guess for the Wordle puzzle you're doing. Based on the results, follow the prompts from the solver. Here's one of my personal examples:

```bash
gitpod /workspace/wordle_solver (main) $ make test
./wordle-solver.exe
4029 words added to dictionary.
Sorting...done
Welcome to Wordle Helper! Enter your guess: flute

Did you guess correctly? (y/N) n

For the letter "f", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
3 # meaning F was grey or incorrect letter
For the letter "l", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
2 # meaning L was yellow or a correct letter but wrong position
For the letter "u", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
3
For the letter "t", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
3
For the letter "e", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
1 # meaning E is green or the correct letter in the correct position
Dictionary: "roble", "gable", "scale", "sable", "salve", "eagle", "dolce", "shale", "exile", "lisle", ... # this shows the top 10 answers based on the sort - take it with a grain of salt, as we did here
Enter your guess: scale

Did you guess correctly? (y/N) n

For the letter "s", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
3
For the letter "c", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
3
For the letter "a", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
1
For the letter "l", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
2
For the letter "e", how correct is it?
        1. Correct letter in correct position
        2. Correct letter in incorrect position
        3. Incorrect letter
1
Dictionary: "leave", 
Enter your guess: leave

Did you guess correctly? (y/N) y
Yay, good job! We did it. # program ends here
```
