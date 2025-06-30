#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits> 

// Helper: removes extra spaces from start and end of a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Loads books from books.txt and adds them to the hash table
void loadBooks(HashTable& ht) {
    std::ifstream file("books.txt");
    if (!file) {
        std::cout << "books.txt not found.\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string title, author, genre;
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, genre, ',');

        ht.insert(trim(title), trim(author) + " - " + trim(genre));
    }

    std::cout << "Books loaded from books.txt.\n";
}

int main() {
    HashTable ht(10); // Create a hash table with 10 slots
    int choice;

    do {
        // Menu
        std::cout << "\nLibrary Menu:\n";
        std::cout << "1. Load books from file\n";
        std::cout << "2. Search for a book by title\n";
        std::cout << "3. Display hash table\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        // Clear leftover input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // from this point on it will print the indicated thing by the number the use will be using
        // I believe that this part will be easier for searching through the hashtable and anything used by the user. 

        if (choice == 1) {
            loadBooks(ht);
        } else if (choice == 2) {
            std::string title;
            std::cout << "Enter book title: ";
            getline(std::cin, title);
            title = trim(title);

            std::string* result = ht.search(title);
            if (result)
                std::cout << "Found: " << *result << "\n";
            else
                std::cout << "That book is not in the system.\n";
        } else if (choice == 3) {
            std::cout << "\nLibrary Catalog:\n";
            ht.display();
        } else if (choice == 4) {
            std::cout << "Hope to see you soon.\n";
        } else {
            std::cout << "Invalid choice, please choose a number between 1-4.\n";
        }

    } while (choice != 4);

    return 0;
}