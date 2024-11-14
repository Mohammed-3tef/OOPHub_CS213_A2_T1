/*
File: A2_T1_S19_20231143.cpp
Purpose: Solving Problem 2
Author: Mohammed Atef Abd El-Kader
ID: 20231143
TA: Eng. Ahmed Ihab
Date: 15 Nov 2024
Version: 1.0
*/

/*
---> Problem (2): Document Similarity with String Sets :
    Calculates document similarity using a StringSet class, which stores unique words from each document while ignoring punctuation
    and case. It supports adding, removing, and performing union and intersection operations on sets. Document similarity is
    measured with the binary cosine coefficient, producing a score between 0 and 1, where 1 indicates high similarity.
    The program includes functions to test these features, allowing users to load documents and evaluate their similarity.

---> GitHub Repo Link: https://github.com/Mohammed-3tef/OOPHub_CS213_A2_T1
        (It's private now, and it will be public after 25 Nov 2024 ISA).
        But now you can look at some photos of the repo in this link: https://drive.google.com/drive/folders/1uyIkiQ9Rr44Bo0zCeyOBZWrh3_f1hSI8?usp=drive_link
        If you like it, don't forget the bonus :)
*/

#include <bits/stdc++.h>
using namespace std;

vector<string> splitWords (string& line, vector<string>& words) {
    string word;        // The word that will be inserted into the set.

    // Split the line into words.
    for (char character : line){

        // If the character is a space, insert the word into the set and clear the word.
        if (isspace(character)) {
            // If the word is not found in the set, insert it.
            if (find(words.begin(), words.end(), word) == words.end()) {
                words.push_back(word);
            }
            word.clear();
        }

        // If the character is a punctuation, continue.
        else if (ispunct(character)) continue;

        // If the character is a letter, add it to the word.
        else {
            word += islower(character) ? character : tolower(character);
        }
    }

    // Insert the last word.
    if (!word.empty()) words.push_back(word);
    return words;               // Return the set of words.
}

class StringSet{
private:
    vector<string> words;
public:
    // Constructors
    StringSet() = default;

    // Load the file and insert the words into the set.
    explicit StringSet(ifstream& file) {
        string line;
        while (true) {
            if (file.is_open()) {
                cout << "Loading the File..." << endl;
                // Read the file line by line and insert the words into the set.
                while (getline(file, line)) {
                    splitWords(line, words);
                }

                // Close the file.
                cout << "The File is Loaded Successfully..." << endl << endl;
                file.close();
                break;
            }

                // If the user enters an invalid file path.
            else {
                cout << "The File Doesn't Exist..." << endl << endl;
                cout << "Enter the File Path Again :";
                string filePath;
                getline(cin, filePath);
                file.open(filePath);
            }
        }
    }

    // Split the line into words and insert them into the set.
    explicit StringSet(string& currentLine) {
        splitWords(currentLine, words);
        cout << "The Sentence is Loaded Successfully..." << endl << endl;
    }

    // Add a word to the set.
    void addString (string& currentWord) {
        // If the word is found in the set, don't insert it.
        if (find(words.begin(), words.end(), currentWord) != words.end()) {
            cout << "The Word is Already Found..." << endl << endl;
            return;
        }

        // Convert the word to lowercase and Insert the word into the set.
        for (char& character : currentWord) {
            character = tolower(character);
        }
        words.push_back(currentWord);
        cout << "The Word is Added Successfully..." << endl << endl;
    }

    // Remove a word from the set.
    void removeString (string& currentWord) {
        for (char& character : currentWord) {
            character = tolower(character);
        }

        // If the word is found in the set, remove it.
        if (find(words.begin(), words.end(), currentWord) != words.end()) {
            words.erase(remove(words.begin(), words.end(), currentWord), words.end());
            cout << "The Word is Removed Successfully..." << endl << endl;
        }
        else cout << "The Word is Not Found..." << endl << endl;
    }

    // Clear the set.
    void clearSet() {
        words.clear();
        cout << "The Set is Cleared..." << endl << endl;
    }

    // Get the number of words in the set.
    int numberOfWords() {return int(words.size());}

    // Display the set.
    void displaySet (const string& typeOfSet = "Set") {
        if (words.empty()) cout << "The Set is Empty..." << endl << endl;
        else {
            cout << "The " << typeOfSet << " is: " << endl << "[";
            for(const auto& word : words) {
                cout << word << (word != *words.rbegin() ? ", " : "]");
            }
            cout << endl << endl;
        }
    }

    // Perform the union operation between two sets.
    StringSet operator + (StringSet& secondSet) {
        StringSet unionSet;
        // Insert the words of the first set.
        for (const string& myWord : words) {
            if (find(unionSet.words.begin(), unionSet.words.end(), myWord) == unionSet.words.end()) unionSet.words.push_back(myWord);
        }
        // Insert the words of the second set.
        for (const string& myWord : secondSet.words) {
            if (find(unionSet.words.begin(), unionSet.words.end(), myWord) == unionSet.words.end()) unionSet.words.push_back(myWord);
        }
        return unionSet;
    }

    // Perform the intersection operation between two sets.
    StringSet operator * (StringSet& secondSet) {
        StringSet intersectionSet;
        for (const string& myWord : words) {
            // If the word is found in the second set, insert it into the intersection set.
            if (find(secondSet.words.begin(),secondSet.words.end(), myWord) != secondSet.words.end()) {
                intersectionSet.words.push_back(myWord);
            }
        }
        return intersectionSet;
    }

    double computesSimilarity(StringSet& secondSet) {
        // Calculate the numerator of the binary cosine coefficient.
        StringSet intersectionSet = *this * secondSet;
        int numerator = intersectionSet.numberOfWords();

        // Calculate the denominator of the binary cosine coefficient.
        double denominator = sqrt(int(words.size())) * sqrt(int(secondSet.words.size()));

        // Calculate the binary cosine coefficient.
        return 100 * double(numerator) / denominator;
    }
};

int main () {
    cout << "\tAhlan Ya User Ya Habibi..." << endl;
    StringSet mySet;
    while (true) {
        cout << "Choose:" << endl;
        cout << " 1) Load the file.\n 2) Enter the sentence.\n 3) Perform Operations.\n 4) Exit Program." << endl;
        cout << "Enter Your Choice :";
        string firstChoice;
        getline(cin, firstChoice);

        // If the user wants to load the file.
        if (firstChoice == "1") {
            string firstFilePath;
            cout << endl << "Enter the File Path :";
            getline(cin, firstFilePath);
            ifstream file(firstFilePath);
            mySet = StringSet(file);
        }

        // If the user wants to enter a sentence.
        else if (firstChoice == "2") {
            string currentLine;
            cout << endl << "Enter the Sentence :";
            getline(cin, currentLine);
            mySet = StringSet(currentLine);
        }

        // If the user wants to perform operations.
        else if (firstChoice == "3") {
            cout << endl;
            while (true) {
                cout << "Choose:" << endl;
                cout << " 1) Add a word.\n"
                        " 2) Remove a word.\n"
                        " 3) Clear the set.\n"
                        " 4) Display the set.\n"
                        " 5) Perform Union.\n"
                        " 6) Perform Intersection.\n"
                        " 7) Number of Words.\n"
                        " 8) Computes The Similarity.\n"
                        " 9) Back." << endl;
                cout << "Enter Your Choice :";
                string secondChoice;
                getline(cin, secondChoice);

                // If the user wants to add a word.
                if (secondChoice == "1") {
                    cout << "Enter the word you want to add :";
                    string currentWord; getline(cin, currentWord);
                    mySet.addString(currentWord);
                }
                // If the user wants to remove a word.
                else if (secondChoice == "2") {
                    cout << "Enter the word you want to remove :";
                    string currentWord; getline(cin, currentWord);
                    mySet.removeString(currentWord);
                }
                // If the user wants to clear the set.
                else if (secondChoice == "3") {
                    mySet.clearSet();
                }
                // If the user wants to display the set.
                else if (secondChoice == "4") {
                    mySet.displaySet();
                }
                // If the user wants to perform the union operation.
                else if (secondChoice == "5") {
                    StringSet mySecondSet;
                    while (true) {
                        // Ask the user to enter the file path or the sentence.
                        cout << endl << "Which will you input ??" << endl;
                        cout << " 1) Enter the file path.\n 2) Enter the sentence."<< endl;
                        cout << "Enter Your Choice :";
                        string thirdChoice; getline(cin, thirdChoice);

                        // If the user wants to load the file.
                        if (thirdChoice == "1") {
                            string firstFilePath;
                            cout << endl << "Enter the Second File Path :";
                            getline(cin, firstFilePath);
                            ifstream file(firstFilePath);
                            mySecondSet = StringSet(file);
                            break;
                        }

                            // If the user wants to enter a sentence.
                        else if (thirdChoice == "2") {
                            string currentLine;
                            cout << endl << "Enter the Second Sentence :";
                            getline(cin, currentLine);
                            mySecondSet = StringSet(currentLine);
                            break;
                        }

                            // If the user enters an invalid choice.
                        else cout << "Please, Enter a valid choice..." << endl;
                    }

                    // Perform the union operation.
                    StringSet unionSet = mySet + mySecondSet;
                    unionSet.displaySet("Union Set");
                }
                // If the user wants to perform the intersection operation.
                else if (secondChoice == "6") {
                    StringSet mySecondSet;
                    while (true) {
                        // Ask the user to enter the file path or the sentence.
                        cout << endl << "Which will you input ??" << endl;
                        cout << " 1) Enter the file path.\n 2) Enter the sentence."<< endl;
                        cout << "Enter Your Choice :";
                        string thirdChoice; getline(cin, thirdChoice);

                        // If the user wants to load the file.
                        if (thirdChoice == "1") {
                            string firstFilePath;
                            cout << endl << "Enter the Second File Path :";
                            getline(cin, firstFilePath);
                            ifstream file(firstFilePath);
                            mySecondSet = StringSet(file);
                            break;
                        }

                        // If the user wants to enter a sentence.
                        else if (thirdChoice == "2") {
                            string currentLine;
                            cout << endl << "Enter the Second Sentence :";
                            getline(cin, currentLine);
                            mySecondSet = StringSet(currentLine);
                            break;
                        }

                        // If the user enters an invalid choice.
                        else cout << "Please, Enter a valid choice..." << endl;
                    }

                    // Perform the intersection operation.
                    StringSet intersectionSet = mySet * mySecondSet;
                    intersectionSet.displaySet("Intersection Set");
                }
                // If the user wants to get the number of words in the set.
                else if (secondChoice == "7") {
                    cout << endl << "The Number of Words in the Set is: " << mySet.numberOfWords() << endl << endl;
                }
                // If the user wants to compute the similarity.
                else if (secondChoice == "8") {
                    StringSet mySecondSet;
                    while (true) {
                        // Ask the user to enter the file path or the sentence.
                        cout << endl << "Which will you input ??" << endl;
                        cout << " 1) Enter the file path.\n 2) Enter the sentence."<< endl;
                        cout << "Enter Your Choice :";
                        string thirdChoice; getline(cin, thirdChoice);

                        // If the user wants to load the file.
                        if (thirdChoice == "1") {
                            string firstFilePath;
                            cout << endl << "Enter the Second File Path :";
                            getline(cin, firstFilePath);
                            ifstream file(firstFilePath);
                            mySecondSet = StringSet(file);
                            break;
                        }

                            // If the user wants to enter a sentence.
                        else if (thirdChoice == "2") {
                            string currentLine;
                            cout << endl << "Enter the Second Sentence :";
                            getline(cin, currentLine);
                            mySecondSet = StringSet(currentLine);
                            break;
                        }

                            // If the user enters an invalid choice.
                        else cout << "Please, Enter a valid choice..." << endl;
                    }

                    StringSet intersectionSet = mySet * mySecondSet;
                    // Compute the similarity between the two sets.
                    cout << "The Similarity between the Two Sets = \n(" << intersectionSet.numberOfWords() << ") / (sqrt("<< mySet.numberOfWords() << ") * sqrt(" << mySecondSet.numberOfWords() << ")) = " << mySet.computesSimilarity(mySecondSet) << "%" << endl << endl;
                }
                // If the user wants to go back.
                else if (secondChoice == "9") {
                    cout << "Back to the Main Menu..." << endl << endl;
                    break;
                }
                // If the user enters an invalid choice.
                else cout << "Please, Enter a valid choice..." << endl << endl;
            }
        }

        // If the user wants to exit the program.
        else if (firstChoice == "4") {
            cout << "\n\t==> Thanks for using my program.." << endl;
            cout << "\t\t==> See You Later...." << endl;
            break;
        }

        // If the user enters an invalid choice.
        else cout << "Please, Enter a valid choice..." << endl << endl;
    }
    return 0;
}