#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

class Spellchecker{
private:
    std::string _alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::vector<std::list<std::string>> _hash_table;
    static const int TABLE_SIZE = 1000;

    int hash_function(const std::string &word) {
        // Generates a hash index for the string `word` by iterating over each character
        // Also ensures that the result fits within the bounds of the hash table
        unsigned long hash = 0;
        for (size_t i = 0; i < word.length(); ++i) {
            if (i % 2 == 0) {
                hash += (word[i] << (i % 4));
            } else {
                hash ^= (word[i] >> (i % 3));
            }
        }
        return static_cast<int>(hash % TABLE_SIZE);
    }

    void add_word(const std::string &word) {
        // Adds the word stored in "word" to the hash table at the calculated hash index
        int index = hash_function(word);
        _hash_table[index].push_back(word);
    }

    bool is_correct_spelling(std::string &s) {
        // Checks if the word "s" exists in the hash table and returns true if found, false if not
        int index = hash_function(s);
        for (const auto &stored_word : _hash_table[index]) {
            if (stored_word == s) {
                return true;
            }
        }
        return false;
    }

    bool found(std::string &s, std::vector<std::string> &v){
        // Checks for occurrence of string in vector.
        // Used to prevent duplicates in "suggested_spelling".
        for (auto &i : v) {
            if (i == s){
                return true;
            }
        }
        return false;
    }

    void swapping(std::string &s, std::vector<std::string> &suggested_spelling){
        // Swaps adjacent letters in the word and adds to "suggested_spelling"
        // if found in hash table

        for (int i = 0; i < s.size()-1; ++i) {
            std::swap(s[i], s[i+1]); //Swaps adjacent letters
            if (is_correct_spelling(s) && !found(s, suggested_spelling)){
                suggested_spelling.push_back(s);
            }
            std::swap(s[i+1], s[i]); //Swaps letters back
        }
    }

    void insertion(std::string &s, std::vector<std::string> &suggested_spelling){
        // Inserts every letter in the alphabet between the letters in input word
        // and adds to "suggested_spelling" if found in hash table

        for (int i = 0; i < s.size()+1; ++i) {

            for (auto &j : _alphabet) {
                // Adds part of s before i to temp, then adds alphabet, then adds part of s after i
                std::string temp = s.substr(0, i) + j + s.substr(i);
                if (is_correct_spelling(temp) && !found(temp, suggested_spelling)){
                    suggested_spelling.push_back(temp);
                }
            }
        }
    }

    void deleting(std::string &s, std::vector<std::string> &suggested_spelling){
        // Removes each letter in the word, one at a time
        // and adds to "suggested_spelling" if found in hash table

        for (int i = 0; i < s.size(); ++i) {
            std::string temp = s;
            temp.erase(temp.begin() + i);
            if (is_correct_spelling(temp) && !found(temp, suggested_spelling)){
                suggested_spelling.push_back(temp);
            }
        }
    }

    void replacement(std::string &s, std::vector<std::string> &suggested_spelling){
        // Replaces each letter one at a time with every letter in the alphabet
        // and adds to "suggested_spelling" if found in hash table

        for (int i = 0; i < s.size(); ++i) {
            std::string temp = s;

            for (auto &j : _alphabet) {
                temp[i] = j;
                if (is_correct_spelling(temp) && !found(temp, suggested_spelling)){
                    suggested_spelling.push_back(temp);
                }
            }
        }
    }

    void phonetic(std::string &s, std::vector<std::string> &suggested_spelling){
        // Checks for common phonetic substitutions such as "ph" for "f" or "gh" for "f".
        // One word substitution such as "c" for "k" are covered by replacement().

        // Example: enouf will be transformed to enouph and enough (they are between the same "{}")
        // in wich case enouph and enough wil be checked if is found in hash table
        std::vector<std::vector<std::string>> phonetics =
                {
                        {"f", "ph", "gh"},              // /f/ sound
                        {"k", "c", "ck", "ch", "q"},    // /k/ sound
                        {"s", "c", "sc", "ps"},         // /s/ sound
                        {"sh", "ti", "ci", "ssi", "ch"},// /sh/sound
                        {"j", "dg", "ge", "gi"},        // /j/ sound
                        {"z", "s", "x"},                // /z/ sound
                        {"n", "kn", "gn"},              // /n/ sound
                        {"r", "wr"},                    // /r/ sound
                        {"oo", "ue", "ew", "ough"},     // /u/ sound
                        {"i", "igh", "y", "ie"}         // /ai/sound
                };

        for (auto &p : phonetics) {

            //p[i] is the substring being looked for
            //p[j] is the substring that is to replace p[i]
            for (int i = 0; i < p.size(); ++i) {
                for (int j = 0; j < p.size(); ++j) {
                    if (p[i] != p[j]){
                        // No point replacing one substr with another

                        std::size_t pos = 0;
                        for (auto &k : s) {
                            // Finds position of substr, adds all of s before substr to temp,
                            // adds new substr to temp, adds all of s after substr to temp.
                            // Twice per loop was easier to implement, breaks when no more substr

                            pos = s.find(p[i], pos);
                            if (pos == std::string::npos){
                                break;
                            }
                            std::string temp = s.substr(0, pos);
                            temp += p[j];
                            temp+= s.substr(pos + p[i].size(), s.size());
                            if (is_correct_spelling(temp) && !found(temp, suggested_spelling)){
                                suggested_spelling.push_back(temp);
                            }


                            std::size_t pos2 = s.find(p[i], pos + p[i].size());
                            if (pos2 == std::string::npos){
                                break;
                            }
                            temp = s.substr(0, pos2);
                            temp += p[j];
                            temp += s.substr(pos2 + p[i].size(), s.size());
                            if (is_correct_spelling(temp) && !found(temp, suggested_spelling)){
                                suggested_spelling.push_back(temp);
                            }
                            pos = pos2 + p[i].size();
                        }
                    }
                }
            }
        }
    }

    void repeating(std::string &s, std::vector<std::string> &suggested_spelling){
        // Removes repeated characters in the word
        std::string temp;
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0 || s[i] != s[i - 1]) {
                temp += s[i];
            }
        }
        if (is_correct_spelling(temp) && !found(temp, suggested_spelling)){
            suggested_spelling.push_back(temp);
        }
    }

public:

    explicit Spellchecker(std::vector<std::string> &correct_spelling) : _hash_table(TABLE_SIZE) {
        for (const auto &word : correct_spelling) {
            add_word(word);  // Populate the hash table with words
        }
    }

    static std::string to_lower(std::string &s){
        std::string temp;
        for (auto &i : s) {
            temp += (char)std::tolower((int)i);
        }
        return temp;
    }

    static bool input_valid(std::string &s){
        // Checks for spaces, numbers
        // Checks if all characters are present in _alphabet
        // Case doesn't matter, lowercased before lookup in hash table

        if (s.empty()){
            std::cout <<"Input cannot be empty." <<std::endl;
            return false;
        }
        for (auto &c : s) {
            if (c == ' '){
                std::cout <<"Input one word at a time seperated by the enter-key." <<std::endl;
                std::cout <<"Individual words can't contain spaces." <<std::endl;
                return false;
            }
            if ((int)c < 0 || (int)c > 127){
                // Has only support for ASCII characters. char with an int value outside of ASCII
                // will display a warning when passed to isalpha() and isdigit()
                // Happens for single chars such as "§" with an int value of -62, as well ass ÆØÅ
                std::cout <<"The word must only consist of letters from the english alphabet." <<std::endl;
                return false;
            }
            if (isdigit(c)){
                std::cout <<"Words cannot contain numbers." <<std::endl;
                return false;
            }
            if (!std::isalpha(c)){
                std::cout <<"The word must only consist of letters from the english alphabet." <<std::endl;
                return false;
            }

        }

        return true;
    }

    std::vector<std::string> spellcheck(std::string &s){
        // Returns a vector that contains words that might be the correct
        // spelling of the input word

        std::vector<std::string> suggested_spelling;
        std::string temp = to_lower(s);

        if (is_correct_spelling(temp)){
            return {temp};
        }

        swapping(temp, suggested_spelling);
        insertion(temp, suggested_spelling);
        deleting(temp, suggested_spelling);
        replacement(temp, suggested_spelling);
        phonetic(temp, suggested_spelling);
        repeating(temp, suggested_spelling);

        return suggested_spelling;
    }

};






int main() {

    // Make sure correct_spelling follows rules set in input_valid().
    // All examples of correct spelling should be in lowercase.
    std::vector<std::string> correct_spelling = {
            "hello", "hell", "help", "world", "spell", "checker", "apple",
            "banana", "computer", "program", "phone", "photo", "good", "nation",
            "well", "reach", "through", "light", "tie", "nation", "gnome", "write"
    };
// Phonetics currently implemented in phonetic()
//    {"f", "ph", "gh"},              // /f/ sound
//    {"k", "c", "ck", "ch", "q"},    // /k/ sound
//    {"s", "c", "sc", "ps"},         // /s/ sound
//    {"sh", "ti", "ci", "ssi", "ch"},// /sh/sound
//    {"j", "dg", "ge", "gi"},        // /j/ sound
//    {"z", "s", "x"},                // /z/ sound
//    {"n", "kn", "gn"},              // /n/ sound
//    {"r", "wr"},                    // /r/ sound
//    {"oo", "ue", "ew", "ough"},     // /u/ sound
//    {"i", "igh", "y", "ie"}         // /ai/sound


    auto spellck = new Spellchecker(correct_spelling);

    std::cout <<"# Input a word. Space or number will throw error." <<std::endl;
    std::cout <<"# Suggested spelling will ignore use of capitalization, but will still check spelling of capitalized input." <<std::endl;
    std::cout <<"# Hit enter-key without inputting a word to exit application." <<std::endl;

    while(true){
        std::cout <<"-Input word-" <<std::endl;
        std::string input;

        std::getline(std::cin, input);

        if (input.empty()){
            break;
        }

        if (!Spellchecker::input_valid(input)){
            continue;
        }

        std::cout <<"=====Spell Checker=====" <<std::endl;
        std::vector<std::string> suggested_spelling = spellck->spellcheck(input);

        if (suggested_spelling.size() == 1 && suggested_spelling[0] == Spellchecker::to_lower(input)){
            std::cout <<"Word \""<<input <<"\" has correct spelling." <<std::endl;
            std::cout <<std::endl <<std::endl;

        } else if (suggested_spelling.empty()){
            std::cout <<"Word \""<<input <<"\" might have a spelling error," <<std::endl;
            std::cout <<"but no alternative spelling was found." <<std::endl;
            std::cout <<std::endl <<std::endl;

        } else{
            std::cout <<"Word \""<<input <<"\" might have a spelling error." <<std::endl;
            std::cout <<"Did you mean: ";
            for (auto &j : suggested_spelling) {
                std::cout <<j <<",";
            }
            std::cout <<std::endl <<std::endl;
        }






    }

    delete spellck;
    return 0;
}