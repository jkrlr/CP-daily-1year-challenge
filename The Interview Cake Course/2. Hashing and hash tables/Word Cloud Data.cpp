/* Breakdown
    This challenge has several parts. Let's break them down.

    1. Splitting the words from the input string
    2. Populating the unordered map with each word
    3. Handling words that are both uppercase and lowercase in the input string */

/* Solution
In our solution, we make two decisions:

    1. We use a class. This allows us to tie our methods together, calling them on instances of our class instead of passing references.
    2. To handle duplicate words with different cases, we choose to make a word uppercase in our unordered map only if it is always uppercase in the original string. 
        While this is a reasonable approach, it is imperfect (consider proper nouns that are also lowercase words, like "Bill" and "bill"). 

To split the words in the input string and populate an unordered map of the unique words to the number of times they occurred, we:

    1. Split words by spaces and ellipses—making sure to include hyphens surrounded by characters. 
        We also include all apostrophes (which will handle contractions nicely but will break possessives into separate words).
    2. Populate the words in our unordered map as they are identified, checking if the word is already in our unordered map in its current case or another case.*/


// Time = O(n), Space = O(n)
#include<bits/stdc++.h>
using namespace std;
class WordCloudData
{
private:
    unordered_map<string, size_t> wordsToCounts_;

    void populateWordsToCounts(const string& inputString)
    {
        // iterates over each character in the input string, splitting
        // words and passing them to addWordToHashMap()

        size_t currentWordStartIndex = 0;
        size_t currentWordLength = 0;

        for (size_t i = 0; i < inputString.length(); ++i) {
            char character = inputString[i];

            // if we reached the end of the string we check if the last
            // character is a letter and add the last word to our hash map
            if (i == inputString.length() - 1) {
                if (isalpha(character)) {
                    if (currentWordLength == 0) {
                        currentWordStartIndex = i;
                    }
                    ++currentWordLength;
                }
                if (currentWordLength > 0) {
                    string currentWord = inputString.substr(currentWordStartIndex, currentWordLength);
                    addWordToHashMap(currentWord);
                }
            }

            // if we reach a space we know we're at the end of a word
            // so we add it to our hash map and reset our current word
            else if (character == ' ') {
                if (currentWordLength > 0) {
                    string currentWord = inputString.substr(currentWordStartIndex, currentWordLength);
                    addWordToHashMap(currentWord);
                    currentWordLength = 0;
                }
            }

            // we want to make sure we split on ellipses so if we get two periods in
            // a row we add the current word to our hash map and reset our current word
            else if (character == '.') {
                if (i < inputString.length() - 1 && inputString[i + 1] == '.') {
                    if (currentWordLength > 0) {
                        string currentWord = inputString.substr(currentWordStartIndex, currentWordLength);
                        addWordToHashMap(currentWord);
                        currentWordLength = 0;
                    }
                }
            }

            // if the character is a letter or an apostrophe, we add it to our current word
            else if (isalpha(character) || character == '\'') {
                if (currentWordLength == 0) {
                    currentWordStartIndex = i;
                }
                ++currentWordLength;
            }

            // if the character is a hyphen, we want to check if it's surrounded by letters
            // if it is, we add it to our current word
            else if (character == '-') {
                if (i > 0 && isalpha(inputString[i - 1])
                        && isalpha(inputString[i + 1])) {
                    ++currentWordLength;
                }
                else if (currentWordLength > 0) {
                    string currentWord = inputString.substr(currentWordStartIndex, currentWordLength);
                    addWordToHashMap(currentWord);
                    currentWordLength = 0;
                }
            }
        }
    }

    void addWordToHashMap(const string& word)
    {
        // if the word is already in the hash map we increment its count
        auto it = wordsToCounts_.find(word);
        if (it != wordsToCounts_.end()) {
            ++it->second;
        }

        // if a lowercase version is in the hash map,
        // we know our input word must be uppercase
        // but we only include uppercase words if they're always uppercase
        // so we just increment the lowercase version's count
        else if ((it = wordsToCounts_.find(toLowerCase(word))) != wordsToCounts_.end()) {
            ++it->second;
        }

        // if an uppercase version is in the hash map,
        // we know our input word must be lowercase.
        // since we only include uppercase words if they're always uppercase,
        // we add the lowercase version and give it the uppercase version's count
        else if ((it = wordsToCounts_.find(capitalize(word))) != wordsToCounts_.end()) {
            size_t newCount = it->second + 1;
            wordsToCounts_.erase(it);
            wordsToCounts_.insert(make_pair(word, newCount));
        }

        // otherwise, the word is not in the hash map at all, lowercase or uppercase
        // so we add it to the hash map
        else {
            wordsToCounts_.insert(make_pair(word, 1));
        }
    }

    static string toLowerCase(const string& word)
    {
        string result = word;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    static string capitalize(const string& word)
    {
        string result = word;
        result[0] = toupper(result[0]);
        return result;
    }

public:
    WordCloudData (const string& inputString)
    {
        populateWordsToCounts(inputString);
    }

    const unordered_map<string, size_t> getWordsToCounts() const
    {
        return wordsToCounts_;
    }
};

/*  Complexity
Runtime and memory cost are both O(n). 
This is the best we can do because we have to look at every character in the input string and we have to return an unordered map of every unique word. 
We optimized to only make one pass over our input and have only one O(n) data structure.*/

/* Bonus:
1. We haven't explicitly talked about how to handle more complicated character sets. 
    How would you make your solution work with unicode input? What changes need to be made to handle silly sentences like these:

    I'm singing ♬ on a ☔ day.

    ☹ + ☕ = ☺.

2. We limited our input to letters, hyphenated words and punctuation. 
   How would you expand your functionality to include numbers, email addresses, twitter handles, etc.?
3. How would you add functionality to identify phrases or words that belong together but aren't hyphenated? ("Fire truck" or "Interview Cake")
4. How could you improve your capitalization algorithm?
5. How would you avoid having duplicate words that are just plural or singular possessives? */

/* What We Learned
To handle capitalized words, there were lots of heuristics and approaches we could have used, each with their own strengths and weaknesses. 
Open-ended questions like this can really separate good engineers from great engineers.*/