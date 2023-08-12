# COMP-6651-ADT-Dictionary-Matcher-and-LCS-finder
COMP 6651 - Algorithms Design Techniques Programming Project

# Dictionary Matcher with LCS Finder

This C++ program reads a list of words from an input file, generates Trie of all words and performs regular expression matching on those words, and finds the Longest Common Subsequence (LCS) among the top 3 matched words. The LCS is then written to an output file.

## Contents
1. [Dependencies](#dependencies)
2. [How to Use](#how-to-use)
3. [Algorithm/High-Level Flow: Dictionary Matcher and LCS Finder](#algorithmhigh-level-flow-dictionary-matcher-and-lcs-finder)
4. [Function Descriptions](#function-descriptions)
5. [Correctness of the Algorithm](#correctness-of-the-algorithm)
6. [Optimality of the Algorithm](#optimality-of-the-algorithm)
7. [Time Complexity](#time-complexity)

## Dependencies

This program uses the C++ Standard Library and requires a C++ compiler that supports C++11 features.

## How to Use

1. Clone the repository or copy the code from the `regex_matcher_40232364.cpp` file.

2. Place the input file (`input.txt`) in the same directory as the program executable.

3. Open the `input.txt` file and provide the following input in the specified format:
    - The first line contains an integer `n`, representing the number of words in the dictionary.
    - The next `n` lines contain the words that form the dictionary.
    - The last line contains the regex pattern (`..pl.` in this example) to match against the dictionary words.

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

4. Run the program.

5. The program will display the words that match the given regex pattern in lexicographic order and write the LCS of at most 3 matched words to the output file (`output.txt`).
    - console output
      ```
      The words that match to the given regex pattern are as follow:

      apple
      apply
      maple

      The output is successfully stored in output.txt
      ```
    - output.txt
      ```
      apl
      ```

## Algorithm/High-Level Flow: Dictionary Matcher and LCS Finder

1. Start

2. Define TrieNode class:
   - Represents a node in the trie structure.

3. Define DictionaryMatcher class (derived from TrieNode):
   - Represents the main functionality for dictionary matching and LCS finding.
   - Load the dictionary from input file and initialize members.
   - Match words against regex pattern using trie traversal.
   - Find LCS of matched words.

4. Inside main function:
   - Initialize input and output filenames.
   - Create an instance of DictionaryMatcher named 'matcher'.
   - Load the dictionary and perform regex matching:
     - Call 'loadDictionary' on 'matcher':
       - Open input file.
       - Read the number of words (n).
       - For each word:
         - Read and trim the word.
         - Insert the word into the trie.
       - Read and compile the regex pattern.
       - Close input file.
       - Call 'matchRegex' to perform trie traversal and regex matching. Regex matching is performed through dynamic programming and it supports `'.'`, `'*'` and alphabets `[a-z][A-Z]`. If 3 matches are found terminate regex matching.

   - Display matched words:
     - Call 'displayMatches' on 'matcher':
       - Check if any words were matched.
       - If matched, display them on the console(this contains top 3 words that are lexicographically  sorted).

   - Find LCS and save it to the output file:
     - Call 'findLCS' on 'matcher':
       - Determine the LCS based on the number of matched words.
       - Open output file.
       - Write the LCS to the output file.
       - Close output file.

5. End

## Function Descriptions
This section contains the list of all the functions generated in the code and their brief descriptions.

1. `TrieNode` class:
   - Private friend class `DictionaryMatcher`.
   - Private members: `children` array, `isEndOfWord` counter.
   - Constructor to initialize children array and isEndOfWord counter which saves the number of occurences of the given word to support duplicates.

2. `DictionaryMatcher` class (derived from `TrieNode`):
   - Private members: `regexPattern`, `matchedWords`, `successfulMatches`.
   - Private member functions:
     - `trim`: Remove leading and trailing spaces from a string.
     - `insertWord`: Insert a word into the trie structure.
     - `matchWithRegex`: Match a word against the regex pattern with the help of dynamic programming to match the string.
     - `traverseTrieAndMatch`: Traverse the trie, match words, and collect successful matches.
     - `matchRegex`: Initiate the matching process.
     - `lcsOf2Words`: Find the Longest Common Subsequence (LCS) of two words.
     - `lcsOf3Words`: Find the LCS of three words.
     - `findLCSofAtmost3Words`: Calls respective LCS functions to find LCS of matched words.

   - Public member functions:
     - Constructor: Initialize regexPattern and successfulMatches.
     - `loadDictionary`: Load dictionary and regex pattern from the input file.
     - `displayMatches`: Display words that match the regex pattern.
     - `findLCS`: Find LCS and save it to the output file.

3. In the main function:
   - Set input and output filenames.
   - Create an instance of `DictionaryMatcher` named `matcher`.
   - Call `loadDictionary` on `matcher` to load the dictionary and perform regex matching.
   - Call `displayMatches` on `matcher` to display the matched words.
   - Call `findLCS` on `matcher` to find LCS of matched words and save it to the output file.

## Correctness of the Algorithm:
- The algorithm ensures that all dictionary words are correctly loaded and trimmed, eliminating extraneous spaces that may lead to incorrect matches.
- The case insensitivity handling ensures that dictionary words are treated uniformly, regardless of their original casing.
- The insertion of words into the trie guarantees the preservation of lexicographical ordering, which aids in correctly finding the top 3 matches.
- The regex pattern compilation and error handling ensure that the provided pattern is valid and ready for matching.
- The trie traversal and regex matching process ensures that only valid words are matched against the regex pattern, preventing false positives.
- Selecting the top 3 lexicographically correct matches through trie traversal guarantees the correct ordering, as the trie inherently stores words in a lexicographical manner.

## Optimality of the Algorithm:
- The algorithm scans all words from the input file to build the trie, ensuring that the entire dictionary is considered.
- The lowercase conversion of words is performed to facilitate case-insensitive matching without introducing unnecessary complexity.
- The natural ordering of the trie structure ensures that the first 3 matches encountered through trie traversal are the top 3 lexicographically correct matches.
- The algorithm saves at most 3 matches, which bounds the output size and reduces memory usage.
- The LCS calculation is optimized by considering the number of matched words, eliminating unnecessary LCS computations.
- Error handling for input and output files ensures reliable I/O operations, preventing unexpected behavior.

## Time Complexity

The time complexity of the algorithm can be analyzed based on the major operations it performs:

1. Loading Dictionary and Building Trie:
    - For each word in the dictionary (n words):
        - Trimming takes $O(k)$, where k is the maximum length of a word.
        - Inserting a word into the trie takes $O(k)$.
    - Total time complexity for loading dictionary and building the trie: $O(n * k)$

2. Regex Matching and Trie Traversal:
    - Traversing the trie for all word takes $O(n * k)$ where $n$ is number of words in Trie and $k$ is the maximum length of the word.
    - The regex matching and dynamic programming table creation have a time complexity of $O(k * l)$, where $k$ is the maximum length of the word and $l$ is the length of the regex pattern.
    - Although the algorithm only consider a maximum of 3 successful matches, the total time complexity for regex matching and trie traversal can go upto $O(n * k * l)$ (In a case where the matches are at the very end).

3. Finding LCS:
    - Finding the LCS of two strings with lengths m and n has a time complexity of $O(m * n)$.
    - In the worst case, when all matched words are used to find the LCS (3 words), the time complexity for finding the LCS of all 3 words is $O(p * q * r)$ with lengths p, q and r respectively

Therefore, the overall time complexity of the algorithm can be summarized as:
- Building Trie: $O(n * k)$
- Regex Matching and Trie Traversal: $O(n * k * l)$
- Finding LCS: $O(k^3)$

**$Time$ $complexity = O(n * k) + O(n * k * l) + O(k^3) 
                = O(n * k * l + k^3)$**
                
- $n$ = number of words in the dictionary
- $k$ = maximum length of the word in the dictionary
- $l$ = length of the regex pattern

The space complexity of the algorithm mainly comes from the trie structure, which uses space proportional to the total number of characters in the dictionary. Other data structures like vectors and regex objects contribute to the space complexity as well, but they are usually smaller compared to the trie for larger dictionaries.

Therefore, the overall space complexity of the algorithm can be summarized as:
- Building Trie: $O(n * k)$

**$Space$ $complexity = O(n * k)$**
- $n$ = number of words in the dictionary
- $k$ = maximum length of the word in the dictionary
