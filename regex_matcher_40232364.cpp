#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
#include<string>
#include<regex>

using namespace std;

/**
 * @class TrieNode
 * @brief A class representing a node in a trie structure. It is used as a building block for the
 *        DictionaryMatcher class to efficiently store and manage a dictionary of words.
*/
class TrieNode {
    // Allow DictionaryMatcher to access private members
    friend class DictionaryMatcher;
    private:
        // This private array of child nodes representing possible characters
        // Usage: The children array is utilized to efficiently store child nodes representing
        // possible characters. Each element corresponds to a character's presence in the node.
        TrieNode* children[26];
        // A flag indicating if this node represents the end of a word
        // Usage: The isEndOfWord flag is set to true if the current node represents the end of a word.
        bool isEndOfWord;

        /**
         * @brief Constructor for TrieNode class.
         * Initializes the TrieNode object with child pointers and end-of-word flag.
         */
        TrieNode() {
            for (int i = 0; i < 26; ++i) {
                children[i] = nullptr;
            }
            isEndOfWord = false;
        }
};

/**
 * @class DictionaryMatcher
 * @brief A class that loads a dictionary from a file, matches words against a regex pattern,
 *        finds Longest Common Subsequence (LCS) of matched words, and saves the LCS to an
 *        output file.
 */
class DictionaryMatcher : public TrieNode{
    private:
        // This private member stores the regular expression string provided in the input.
        // Usage: It is used to match the trie words against the given regex string.
        string regexString;
        // This private member stores the regular expression pattern provided in the input.
        // Usage: It is used to match the dictionary words against the given regex pattern.
        regex regexPattern;
        // This private member stores the words that match the regex pattern after matching.
        // Usage: It is used to collect the matching words for further processing.
        vector<string> matchedWords;
        // This private member stores is counter for keeping track of matches.
        // Usage: It is used to store counter to match just 3 regex strings.
        int successfulMatches;

        /**
         * @brief Removes leading and trailing spaces from the given string.
         * @param str The input string to be trimmed.
         * @return Modifies the original string to remove leading and trailing spaces.
         */
        void trim(string& str) {
            str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
        }

        /**
         * @brief Inserts a word into the trie structure.
         * @param word The word to be inserted into the trie.
         * @return None.
         */
        void insertWord(const std::string& word) {
            TrieNode* current = this;
            for (char c : word) {
                int index = c - 'a';
                if (!current->children[index]) {
                    current->children[index] = new TrieNode();
                }
                current = current->children[index];
            }
            current->isEndOfWord = true;
        }

        /**
         * @brief Matches a word against a regular expression pattern.
         * @param word The word to be matched against the regular expression pattern.
         * @return True if the word matches the pattern, otherwise false.
         */
        bool matchWithRegex(const string& word) {
            // return regex_match(word, regexattern);
            int m = word.length();
            int n = regexString.length();
            
            // Create a 2D table to store the matching results
            vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
            
            // Base case is empty string
            dp[0][0] = true;
            
            for (int j = 1; j <= n; j++) {
                if (regexString[j - 1] == '*') {
                    dp[0][j] = dp[0][j - 2];
                }
            }
            
            // Fill the remaining positions of the table
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    if (word[i - 1] == regexString[j - 1] || regexString[j - 1] == '.') {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                    else if (regexString[j - 1] == '*') {
                        dp[i][j] = dp[i][j - 2]; // case 1
                        
                        if (regexString[j - 2] == '.' || regexString[j - 2] == word[i - 1]) {
                            dp[i][j] = dp[i][j] || dp[i - 1][j]; // case 2
                        }
                    }
                }
            }
            
            return dp[m][n];
        }

        /**
         * @brief Traverses the trie, matches words with a regex pattern, and collects successful matches.
         * 
         * This function performs a depth-first traversal of the trie structure, beginning from the provided
         * node (or the root if no node is specified). For each encountered node representing the end of a
         * word, it attempts to match the word formed by the path from the root to the current node against
         * the stored regular expression pattern. If the word matches the pattern and the successful match
         * count is below 3, the word is added to the list of matchedWords, and the successful match count
         * is incremented. The traversal continues for each child node.
         * 
         * @param node The starting node for traversal. If not provided, the root node is used.
         * @param prefix The accumulated prefix formed during traversal from the root to the current node.
         */
        void traverseTrieAndMatch(TrieNode* node = nullptr, string prefix = "") {
            if (node == nullptr) {
                node = this;
                prefix = "";
            }

            if (node->isEndOfWord) {
                if (successfulMatches < 3 && matchWithRegex(prefix)) {
                    matchedWords.push_back(prefix);
                    successfulMatches++;
                }
            }

            for (int i = 0; i < 26; ++i) {
                if (node->children[i]) {
                    char c = 'a' + i;
                    traverseTrieAndMatch(node->children[i], prefix + c);
                }
            }
        }

        /**
         * @brief Initiates the process of matching words against a regex pattern.
         */
        void matchRegex() {
            traverseTrieAndMatch();
        }
        
        /**
         * @brief Finds the Longest Common Subsequence (LCS) of two given words.
         * @param W1 The first word.
         * @param W2 The second word.
         * @return The LCS of the two words as a string.
         */
        string lcsOf2Words(const string& W1, const string& W2) {
            const int m = W1.length();
            const int n = W2.length();

            // Create a 2-dimensional array to store the lengths of LCS
            int dp[m + 1][n + 1];

            // Initialize the base case (empty strings)
            for (int i = 0; i <= m; ++i)
                dp[i][0] = 0;
            for (int j = 0; j <= n; ++j)
                dp[0][j] = 0;

            // Compute the LCS using dynamic programming
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (W1[i - 1] == W2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }

            // Reconstruct the LCS
            string lcs = "";
            int i = m, j = n;
            while (i > 0 && j > 0) {
                if (W1[i - 1] == W2[j - 1]) {
                    lcs = W1[i - 1] + lcs;
                    i = i - 1;
                    j = j - 1;
                } else if (dp[i - 1][j] > dp[i][j - 1]) {
                    i = i - 1;
                } else {
                    j = j - 1;
                }
            }

            return lcs;
        }

        /**
         * @brief Finds the Longest Common Subsequence (LCS) of three given words.
         * @param W1 The first word.
         * @param W2 The second word.
         * @param W3 The third word.
         * @return The LCS of the three words as a string.
         */
        string lcsOf3Words(const string& W1, const string& W2, const string& W3) {
            const int m = W1.length();
            const int n = W2.length();
            const int p = W3.length();

            // Create a 3-dimensional array to store the lengths of LCS
            int dp[m + 1][n + 1][p + 1];

            // Initialize the base case (empty strings)
            for (int i = 0; i <= m; ++i)
                for (int j = 0; j <= n; ++j)
                    dp[i][j][0] = 0;

            for (int j = 0; j <= n; ++j)
                for (int k = 0; k <= p; ++k)
                    dp[0][j][k] = 0;

            for (int i = 0; i <= m; ++i)
                for (int k = 0; k <= p; ++k)
                    dp[i][0][k] = 0;

            // Compute the LCS using dynamic programming
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    for (int k = 1; k <= p; ++k) {
                        if (W1[i - 1] == W2[j - 1] && W2[j - 1] == W3[k - 1]) {
                            dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                        } else {
                            dp[i][j][k] = max({ dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1] });
                        }
                    }
                }
            }

            // Reconstruct the LCS
            string lcs = "";
            int i = m, j = n, k = p;
            while (i > 0 && j > 0 && k > 0) {
                if (W1[i - 1] == W2[j - 1] && W2[j - 1] == W3[k - 1]) {
                    lcs = W1[i - 1] + lcs;
                    i = i - 1;
                    j = j - 1;
                    k = k - 1;
                } else if (dp[i - 1][j][k] > dp[i][j - 1][k] && dp[i - 1][j][k] > dp[i][j][k - 1]) {
                    i = i - 1;
                } else if (dp[i][j - 1][k] > dp[i][j][k - 1]) {
                    j = j - 1;
                } else {
                    k = k - 1;
                }
            }

            return lcs;
        }

        /**
         * @brief Calls respective LCS functions to find LCS of matched words.
         * @param None
         * @return The LCS of at most three matched words as a string.
         */
        string findLCSofAtmost3Words() {
            int n = matchedWords.size();

            // If there is only one word present in the matchedwords vector then that word itself is LCS.
            // If there are two words present then call function to find LCS of 2 words
            // If there are three or more words take LCS of first 3 words
            if(n == 1)
                return matchedWords[0];
            else if(n == 2)
                return lcsOf2Words(matchedWords[0], matchedWords[1]);
            else
                return lcsOf3Words(matchedWords[0], matchedWords[1], matchedWords[2]); 
        }
    
    public:
        /**
         * @brief Constructor for the DictionaryMatcher class.
         * 
         * This constructor initializes a new instance of the DictionaryMatcher class. It sets the
         * regexString and regexPattern to an empty string and the successfulMatches count to 0, preparing the
         * instance for loading dictionary words, matching with regex patterns, and processing
         * successful matches.
         */
        DictionaryMatcher() {
            regexString = "";
            regexPattern = "";
            successfulMatches = 0;
            matchedWords.clear();
        }

        /**
         * @brief Loads dictionary from the input file.
         * @param filename The filename of the input text file containing the dictionary and regex pattern.
         * @return None. The trie is populated with words, and regexPattern is set with the provided regex.
         */
        void loadDictionary(const string& filename) {
            // open file and save the words
            ifstream inputFile(filename);
            if(!inputFile.is_open()) {
                cout << "Error in opening the input file: " << filename << endl;
                return;
            }

            int n;
            inputFile >> n;
            inputFile.ignore();     //Ignore the newline after n
            
            for(int i = 0; i < n; i++) {
                string word;
                getline(inputFile, word);
                trim(word);
                for (char& c : word) {
                    c = std::tolower(c);
                }
                insertWord(word);
            }

            getline(inputFile, regexString);
            try {
                regexPattern = regex(regexString, regex_constants::icase);
            } catch (const std::regex_error& error) {
                cout << "There is error in regular expression."<< endl;
                exit(0);
            }

            inputFile.close();
            // Match the regex from the trie.
            matchRegex();
        }

        /**
         * @brief Displays the words that match the regex pattern.
         * @param None (The matchedWords vector should be already populated).
         * @return None. The matched words are displayed on the console.
         */
        void displayMatches() {
            if(matchedWords.size() == 0) {
                cout << "There are no matching words for the given regular expression." << endl;
                return;
            }
            cout << "The words that match to the given regex pattern are as follow:\n" << endl;
            for(const string& word : matchedWords) {
                cout << word << endl;
            }
        }

        /**
         * @brief Finds LCS and saves it to the output file.
         * @param filename The filename of the output text file to store the LCS result.
         * @return The LCS result is written to the output text file.
         */
        void findLCS(const string& filename) {
            string lcs;
            if(matchedWords.size() == 0) {
                lcs = "There are no matching words for the given regular expression.";
            }
            else {
                lcs = findLCSofAtmost3Words();
                if(lcs.size() == 0) {
                    lcs = "There is no LCS for top 3 words sorted lexicographically";
                }
            }

            // open output file and write LCS
            ofstream outputFile(filename);
            if(outputFile.is_open()) {
                outputFile << lcs;
                outputFile.close();
                cout << "\nThe output is successfully stored in " + filename << endl;
            }
            else {
                cout << "Error in opening the output file: " << filename << endl;
                return;
            }
        }
};

/**
 * @brief Driver function that loads the dictionary, performs regex matching, displays the matches,
 *        finds LCS of matched words, and saves the LCS to the output file.
 * @param None.
 * @return 0 on successful execution.
 */
int main() {
    // change the input and output filenames here
    string input = "input.txt";
    string output = "output.txt";

    // Generate the instance of DictionaryMatcher and perform the respective operations
    DictionaryMatcher matcher;
    matcher.loadDictionary(input);
    matcher.displayMatches();
    matcher.findLCS(output);
    return 0;
}