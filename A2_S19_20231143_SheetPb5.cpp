/*
File: A2_T1_S19_20231143_SheetPb5.cpp
Purpose: Solving Problem 5
Author: Mohammed Atef Abd El-Kader
ID: 20231143
TA: Eng. Ahmed Ihab
Date: 25 Nov 2024
Version: 3.0
*/

/*
---> Problem (5): Task Manager :
    A program that displays the processes running on the system. The program reads the output of the "tasklist" command and parses the
    process details (image name, PID, session name, session ID, and memory usage). The user can display the processes, sort them by image
    name, PID, or memory usage, and exit the program.

---> GitHub Repo Link: https://github.com/Mohammed-3tef/OOPHub_CS213_A2_T1
        (It's private now, and it will be public after 25 Nov 2024 ISA).
        If you like it, don't forget the bonus :)
*/

#include <bits/stdc++.h>
using namespace std;

struct Process{
    string imageName;
    int PID {};
    string sessionName;
    int session {};
    string memoryUsage;
};

// Convert the memory usage from string to integer.
int convertMemoryUsage(const string& memoryUsage) {
    int memory = 0;
    // Iterate over the memory usage string and convert it to an integer.
    for (char character : memoryUsage) {
        // If the character is a digit, convert it to an integer. Otherwise, continue to the next character.
        // This is to avoid the commas in the memory usage.
        if (character >= '0' && character <= '9') {
            memory = memory * 10 + (character - '0');
        }
        else {
            continue;
        }
    }
    return memory;
}

class TaskManager {
private:
    vector<Process> processesGroup;
public:

    // Constructor to initialize the processes.
    TaskManager() {
        cin.clear();

        // Execute the tasklist command and parse the output.
        const char* command = "tasklist";
        char buffer[512];

        // Open a pipe to the command
        FILE* pipe = _popen(command, "r");

        // Read the output and parse it
        bool isHeader = true;
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            string line(buffer);

            // Skip the header lines
            if (isHeader) {
                if (line.find("===") != string::npos) {
                    isHeader = false;
                }
                continue;
            }

            // Parse the process details
            istringstream lineStream(line);
            Process process;
            lineStream >> ws;           // Skip leading whitespace

            // Extract fields (name, pid, sessionName, sessionID, memoryUsage)
            if (lineStream >> process.imageName >> process.PID >> process.sessionName >> process.session) {
                getline(lineStream, process.memoryUsage); // Capture the remaining memory usage
                processesGroup.push_back(process);
            }
        }

        // Close the pipe
        _pclose(pipe);
    };

    // Sort the processes by PID.
    void sortedByPID() {
        sort(processesGroup.begin(), processesGroup.end(), ([](auto a, auto b){
            // Compare the PIDs.
            return a.PID < b.PID;
        }));
    }

    // Sort the processes by memory usage.
    void sortedByMemoryUsage() {
        sort(processesGroup.begin(), processesGroup.end(), ([](auto a, auto b){
            // Compare the memory usages.
            return convertMemoryUsage(a.memoryUsage) < convertMemoryUsage(b.memoryUsage);
        }));
    }

    // Sort the processes by image name.
    void sortedByImageName() {
        // Sort the processes by image name.
        sort(processesGroup.begin(), processesGroup.end(), ([](auto a, auto b){
            // Compare the image names.
            for (int i = 0; i < min(a.imageName.size(), b.imageName.size()); ++i) {
                // If the characters are different, return the comparison result.
                // Otherwise, continue to the next character.
                if (a.imageName[i] != b.imageName[i]) {
                    return a.imageName[i] < b.imageName[i];
                }
            }
            return a.imageName.size() < b.imageName.size();
        }));
    }

    void displayProcess () {
        cout << endl << "The Processes are: " << endl;
        cout << "Image Name" << setw(20) << " " << "PID" << " Session Name" << setw(8) << " " << "Session#" << setw(4) << " " << "Mem Usage" << endl;
        cout << setw(25) << setfill('=') << " " << setw(8) << "=" << " " << setw(16) << "=" << " " << setw(11) << "=" << " " << setw(12) << "=" << endl;
        // Display the processes.
        for (const auto& item : processesGroup) {
            cout << setw(24) << setfill(' ') << left << item.imageName.substr(0, 24);
            cout << ' ';
            cout << setw(8) << right << item.PID;
            cout << ' ';
            cout << setw(16) << left << item.sessionName;
            cout << ' ';
            cout << setw(11) << right << item.session;
            cout << setw(10) << right << item.memoryUsage;
            cout << endl;
        }
        cout << endl;
    }
};

int main () {
    cout << "\tAhlan Ya User Ya Habibi..." << endl;
    while (true) {
        cout << "Choose:" << endl;
        cout << " 1) Display Processes.\n"
                " 2) Sort Processes by Image Name.\n"
                " 3) Sort Processes by PID.\n"
                " 4) Sort Processes by Memory Usage.\n"
                " 5) Exit Program." << endl;
        cout << "Enter Your Choice :";
        string firstChoice;
        getline(cin, firstChoice);

        // If the user wants to display the processes.
        if (firstChoice == "1") {
            cin.clear();
            TaskManager taskManger;
            taskManger.displayProcess();
        }

        // If the user wants to sort the processes by image name.
        else if (firstChoice == "2") {
            cin.clear();
            TaskManager taskManger;
            taskManger.sortedByImageName();
            taskManger.displayProcess();
        }

        // If the user wants to sort the processes by PID.
        else if (firstChoice == "3") {
            TaskManager taskManger;
            taskManger.sortedByPID();
            taskManger.displayProcess();
        }

        // If the user wants to sort the processes by memory usage.
        else if (firstChoice == "4") {
            TaskManager taskManger;
            taskManger.sortedByMemoryUsage();
            taskManger.displayProcess();
        }

        // If the user wants to exit the program.
        else if (firstChoice == "5") {
            cout << "\n\t==> Thanks for using my program.." << endl;
            cout << "\t\t==> See You Later...." << endl;
            break;
        }

        // If the user enters an invalid choice.
        else cout << "Please, Enter a valid choice..." << endl << endl;
    }

    return 0;
}