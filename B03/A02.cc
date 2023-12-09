#include <iostream>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::size_t> DataBankType;

// c)
std::size_t hashPassword(const std::string & password) {
    std::hash<std::string> converter;
    return converter(password);
}

// a)
bool createUser(DataBankType& dataBank, const std::string& userName, const size_t password) {
    if (dataBank.count(userName)) {
        return false;
    }
    dataBank[userName] = password;
    return true;
}

// a)
bool authenticateUser(DataBankType& dataBank, const std::string& userName, const size_t password) {
    DataBankType::iterator itFindUser = dataBank.find(userName);
    if (itFindUser == dataBank.end())
        return false;
    if (itFindUser -> second == password)
        return true;
    return false;
}

// d)
void listUsers(DataBankType& dataBank) {
    std::cout << "List of users (<Username>, <Hashed Password>) :" << std::endl;
    for (DataBankType::iterator it = dataBank.begin(); it != dataBank.end(); it ++) {
        std::cout << it -> first << ", " << it -> second << std::endl;
    }
}


// b)
int main() {
    DataBankType databank;
    std::string hint = "hint: 1 - sign up; 2 - log in; 3 - quit ";
    std::string question = "What do you want to do? ";
    std::string success = "Operation succeeded ";
    std::string fail = "Operation failed ";
    
    while (true) {
        std::cout << question << std::endl;
        int action = 0;
        while ((1 > action) || (3 < action)) {
            std::cout << hint << std::endl;
            std::cin >> action;
        }
        if (action == 1) { // sign up
            std::cout << "Enter a new username: " << std::endl;
            std::string username;
            std::cin >> username;
            std::cout << "Enter a password: " << std::endl;
            std::string password;
            std::cin >> password;
            if (createUser(databank, username, hashPassword(password)))
                std::cout << success << std::endl;
            else 
                std::cout << fail << std::endl;
        } else if (action == 2) { // log in
            std::cout << "Enter your username: " << std::endl;
            std::string username;
            std::cin >> username;
            std::cout << "Enter your password: " << std::endl;
            std::string password;
            std::cin >> password;
            if (authenticateUser(databank, username, hashPassword(password)))
                std::cout << success << std::endl;
            else 
                std::cout << fail << std::endl;
        } else { // quit
            std::cout << success << std::endl;
            break;
        }
        std::cout << std::endl;
    }
}