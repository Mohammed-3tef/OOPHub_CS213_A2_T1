#include <bits/stdc++.h>
using namespace std;

set<string> splitWords (string& line, set<string>& words) {
    string word;
    for (char character : line){
        if (isspace(character)) {
            words.insert(word);
            word.clear();
        }
        else if (ispunct(character)) continue;
        else {
            islower(character) ? character : tolower(character);
            word += character;
        }
    }
    if (!word.empty()) words.insert(word);
    return words;
}

class StringSet{
private:
    set<string> words;
public:
    StringSet() {}
    StringSet(ifstream& file) {
//        ifstream file(firstFilePath);
        string line;
        while (true) {
            if (file.is_open()) {
                while (getline(file, line)) {
                    splitWords(line, words);
                }

                // Close the files
                cout << "Loading Done !!" << endl;
                file.close();
                break;
            }

                // If the user enters an invalid file path.
            else cout << "The File Doesn't Exist..." << endl << endl;
        }
    }

    StringSet(string& currentLine) {
        splitWords(currentLine, words);
    }

    void addString (string& currentWord) {
        words.insert(currentWord);
    }

    void removeString (string& currentWord) {
        words.erase(currentWord);
    }

    void clearSet() {
        words.clear();
    }

    int numberOfWords() {
        return words.size();
    }

    void displaySet () {}
};

int main () {
    cout << "Ahlan Ya User Ya Habibi..." << endl;
    StringSet mySet;
    while (true) {
        cout << "Choose:" << endl;
        cout << " 1) Load the file.\n 2) Enter the sentence.\n 3) Operations.\n 4) Exit Program." << endl;
        cout << "Enter Your Choice :";
        string choice; cin >> choice;

        if (choice == "1") {
            string firstFilePath;
            getline(cin, firstFilePath);
            ifstream file(firstFilePath);
//            mySet(currentLine);
        }

        else if (choice == "2") {
            string currentLine;
            getline(cin, currentLine);
//            mySet(currentLine);
        }

        else if (choice == "3") {

        }

        else if (choice == "4") {
            break;
        }

        else cout << "Please, Enter a valid choice..." << endl;
    }
    return 0;
}