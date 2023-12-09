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
bool createUser(DataBankType& dataBank, const std::string& userName, const std::string& password) {
    if (dataBank.count(userName)) {
        return false;
    }
    dataBank[userName] = hashPassword(password);
    return true;
}

// b)
bool authenticateUser(DataBankType& dataBank, const std::string& userName, const std::string& password) {
    DataBankType::iterator itFindUser = dataBank.find(userName);
    if (itFindUser == dataBank.end())
        return false;
    if (itFindUser -> second == hashPassword(password))
        return true;
    return false;
}


int main() {
    int n;
    DataBankType databank;
    std::cin >> n;
    for (int i = 0; i < n; i ++) {
        std::string username, password;
        std::cin >> username >> password;
        std::cout << createUser(databank, username, password) << std::endl;
    }
    std::cout << "==========================";
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i ++) {
        std::string username, password;
        std::cin >> username >> password;
        std::cout << authenticateUser(databank, username, password) << std::endl;
    }
}