#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

vector<string> toDoList; // declare a vector to hold the to-do list

void print_list(const vector<string>& tasks) { // function to print the to-do list
    cout << "To Do List:" << endl;
    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i] << endl; // print each task with its corresponding number
    }
    cout << endl;
}

void saveListToFile() { // function to save the to-do list to a file
    ofstream file("to_do_list.txt"); // open a file stream for writing

    if (file.is_open()) {
        for (const string& task : toDoList) {
            file << task << endl; // write each task to the file
        }

        cout << "To-do list saved to file." << endl;
    }
    else {
        cout << "Error: Unable to save to-do list to file." << endl;
    }

    file.close(); // close the file stream
}

void loadListFromFile() { // function to load the to-do list from a file
    ifstream file("to_do_list.txt"); // open a file stream for reading
    string task;

    if (file.is_open()) {
        while (getline(file, task)) {
            toDoList.push_back(task); // add each task from the file to the vector
        }

        cout << "To-do list loaded from file." << endl;
    }
    else {
        cout << "Error: Unable to load to-do list from file." << endl;
    }

    file.close(); // close the file stream
}

int main() {
    loadListFromFile(); // load the to-do list from file

    string input;

    while (true) { // loop indefinitely
        system("cls"); // clears console before printing the to-do list and prompt
        print_list(toDoList); // print the to-do list
        cout << "Enter a task to add it to the list, or enter a task number to remove it: ";
        getline(cin, input); // read user input

        if (input.empty()) { // if user input is empty, continue to next iteration of loop
            continue;
        }

        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false; // check if input is a number
                break;
            }
        }

        if (isNumber) { // if input is a number
            int index = stoi(input) - 1; // convert input to integer and subtract 1 to get index
            if (index >= 0 && index < toDoList.size()) { // check if index is within range
                toDoList.erase(toDoList.begin() + index); // remove task at specified index
            }
        }
        else { // if input is not a number
            toDoList.push_back(input); // add input as new task to to-do list
        }

        saveListToFile(); // save the updated to-do list to file
    }

    return 0;
}
