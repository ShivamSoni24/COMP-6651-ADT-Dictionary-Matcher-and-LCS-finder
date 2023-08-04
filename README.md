# COMP-6651-ADT-Dictionary-Matcher-and-LCS-finder
COMP 6651 - Algorithms Design Techniques Programming Project

## Dictionary Matcher with LCS Finder

This C++ program reads a list of words from an input file, performs regular expression matching on those words, and finds the Longest Common Subsequence (LCS) among the matched words. The matched words are then sorted lexicographically, and the LCS is written to an output file.

### Dependencies

This program uses the C++ Standard Library and requires a C++ compiler that supports C++11 features.

### How to Use

1. Clone the repository or copy the code from the `main.cpp` file.

2. Place the input file (`input.txt`) in the same directory as the program executable.

3. Open the `input.txt` file and provide the following input in the specified format:

```
6
Apple
Maple
Apply
Couple
Pledge
Please
..pl.
```

- The first line contains an integer `n`, representing the number of words in the dictionary.
- The next `n` lines contain the words that form the dictionary.
- The last line contains the regex pattern (`*pl.` in this example) to match against the dictionary words.

4. Run the program.

5. The program will display the words that match the given regex pattern in lexicographic order and write the LCS of at most 3 matched words to the output file (`output.txt`).

### Algorithm/High-level Program Flow

1. Create a class `DictionaryMatcher` to encapsulate the functionalities related to loading the dictionary, matching the regex, finding LCS, and displaying the results.

2. The `DictionaryMatcher` class contains a private member `vector<string> dictionary` to store the words from the input file, `regex regexPattern` to store the regex pattern, and `vector<string> matchedWords` to store the words that match the regex.

3. The program uses dynamic programming to find the LCS of 2 and 3 words.

4. The `findLCSofAtmost3Words` function checks the number of matched words and calls the respective LCS functions accordingly.

5. The program reads the input from `input.txt`, matches the words to the regex pattern, displays the matched words, and finds the LCS before writing it to `output.txt`.

### Time Complexity

The time complexity of the main operations in this code is as follows:

- `loadDictionary`: O(n), where n is the number of words in the dictionary.
- `matchRegex`: O(n * m), where n is the number of words in the dictionary, and m is the average length of the words.
- `lcsOf2Words`: O(m * n), where m and n are the lengths of the two words.
- `lcsOf3Words`: O(m * n * p), where m, n, and p are the lengths of the three words.
- `findLCSofAtmost3Words`: O(k^3), where k is the number of matched words.
- `sort`: O(k * log(k)), where k is the number of matched words.

Overall, the dominant time complexity is O(n * m) due to `matchRegex`, where n is the number of words in the dictionary and m is the average length of the words. The other operations have smaller complexities and do not significantly affect the overall time complexity. However, keep in mind that the complexity for regex matching may vary depending on the complexity of the regex pattern itself.
