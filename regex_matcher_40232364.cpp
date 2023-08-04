#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
#include<string>
#include<regex>

using namespace std;

/**
 * @class DictionaryMatcher
 * @brief A class that loads a dictionary from a file, matches words against a regex pattern,
 *        finds Longest Common Subsequence (LCS) of matched words, and saves the LCS to an
 *        output file.
 */
class DictionaryMatcher {
    private:
        // This private member stores the list of words from the input dictionary.
        // Usage: It is used to store and access the dictionary words.
        vector<string> dictionary;
        // This private member stores the regular expression pattern provided in the input.
        // Usage: It is used to match the dictionary words against the given regex pattern.
        regex regexPattern;
        // This private member stores the words that match the regex pattern after matching.
        // Usage: It is used to collect the matching words for further processing.
        vector<string> matchedWords;

        /**
         * @brief Removes leading and trailing spaces from the given string.
         * @param str The input string to be trimmed.
         * @return Modifies the original string to remove leading and trailing spaces.
         */
        void trim(string& str) {
            str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
        }
        
        /**
         * @brief Finds the Longest Common Subsequence (LCS) of two given words.
         * @param W1 The first word.
         * @param W2 The second word.
         * @return The LCS of the two words as a string.
         */
        string lcsOf2Words(const string& W1, const string& W2) {
            // transform(W1.begin(), W1.end(), W1.begin(), ::tolower);
            // transform(W2.begin(), W2.end(), W2.begin(), ::tolower);

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
            // transform(W1.begin(), W1.end(), W1.begin(), ::tolower);
            // transform(W2.begin(), W2.end(), W2.begin(), ::tolower);
            // transform(W3.begin(), W3.end(), W3.begin(), ::tolower);

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
         * @brief Loads dictionary from the input file.
         * @param filename The filename of the input text file containing the dictionary and regex pattern.
         * @return None. The dictionary vector is populated with words, and regexPattern is set with the provided regex.
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
                dictionary.push_back(word);
            }

            // Save the regex pattern
            string regexString;
            getline(inputFile, regexString);
            try {
                regexPattern = regex(regexString, regex_constants::icase);
            } catch (const std::regex_error& error) {
                cout << "There is error in regular expression."<< endl;
                exit(0);
            }
        }
        
        /**
         * @brief Matches the dictionary words against the regex pattern and saves the matched words.
         * @param None (The dictionary vector and regexPattern should be already set).
         * @return None. The matchedWords vector is populated with words that match the regex pattern.
         */
        void matchRegex() {
            for(const string& word : dictionary) {
                if(regex_match(word, regexPattern)) {
                    matchedWords.push_back(word);
                }
            }
            sort(matchedWords.begin(), matchedWords.end());
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
            string lcs = findLCSofAtmost3Words();

            if(lcs.size() == 0) {
                lcs = "There is no LCS for top 3 words sorted lexicographically";
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
    matcher.matchRegex();
    matcher.displayMatches();
    matcher.findLCS(output);
    return 0;
}