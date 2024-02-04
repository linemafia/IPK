#include <string>
#include <vector>
#include <map>
#include <algorithm> // std::find
#include <stdexcept>
#include <memory>
#include <fstream>

// a)
class Flag {
protected:
    std::string name;
    bool isSet;
public:
    Flag(const std::string& _name) : name(_name), isSet(false) {}
    virtual void parseConfigLine(const std::string& line) = 0;
    virtual void parseArgs(std::vector<std::string>& args) = 0;

    virtual ~Flag() {}
};

// b)
// b_i)
class BoolFlag : public Flag {
private:
    bool value = false;
public:
    BoolFlag(const std::string& name) : Flag(name) {}
    void parseConfigLine(const std::string& line) {
        if (line == "1" || line == "true") {
            isSet = true;
            return;
        }
        throw std::runtime_error("Invalid value for the BoolFlag \"" + name + "\" in config-file");
    }
    void parseArgs(std::vector<std::string>& args) {
        std::vector<std::string>::iterator findIt = std::find(args.begin(), args.end(),"-" + name);
        if (findIt != args.end()) {
            isSet = true;
            args.erase(findIt);
        }
    }
    bool get() const {
        return isSet;
    }
};
// b_ii)
class StringFlag : public Flag {
private:
    std::string value;
public:
    StringFlag(const std::string& name) : Flag(name) {}
    void parseConfigLine(const std::string& line) {
        value = line;
        isSet = true;
    }
    void parseArgs(std::vector<std::string>& args) {
        std::vector<std::string>::iterator findIt = std::find(args.begin(), args.end(),"-" + name);
        if (findIt != args.end()) {
            findIt ++;
            if (findIt == args.end()) {
                throw std::runtime_error("no arguments for a StringFlag after \"-" + name + "\"");
            }
            value = *findIt;
            args.erase(--findIt); // -NAME
            args.erase(findIt); // the argument
            isSet = true;
        }
    }
    std::string get() const {
        if (isSet)
            return value;
        throw std::runtime_error("The StringFlag \"" + name + "\" isn't set");
    }
};
// b_iii)
class RangeFlag : public Flag {
private:
    double val1, val2;
public:
    RangeFlag(const std::string& name) : Flag(name) {}
    void parseConfigLine(const std::string& line) {
        unsigned int spaceI = line.find(" ");
        unsigned int lineLen = line.size();
        if (spaceI >= lineLen) {
            throw std::runtime_error("Wrong number of arguments for the RangeFlag \"" + name + "\" in the config-file (need 2)");
        }
        try {
            val1 = std::stod(line.substr(0, spaceI));
            val2 = std::stod(line.substr(spaceI, lineLen - spaceI));
            isSet = true;
        } catch (const std::exception& e) {
            throw std::runtime_error("Wrong arguments for the RangeFlag \"" + name + "\" in the config-file (need 2 doubles)");
        }
    }
    void parseArgs(std::vector<std::string>& args) {
        std::vector<std::string>::iterator findIt = std::find(args.begin(), args.end(),"-" + name);
        if (findIt != args.end()) {
            try {
                findIt ++;
                val1 = std::stod(*findIt);
                findIt ++;
                val2 = std::stod(*findIt);
                isSet = true;
            } catch (const std::exception& e) {
                throw std::runtime_error("Need 2 double arguments for a RangeFlag after \"-" + name + "\"");
            }
            findIt --; findIt --;
            args.erase(findIt); // -NAME
            args.erase(findIt); // the first argument
            args.erase(findIt); // the second argument
        }
    }
    std::array<double, 2> get() const {
        if (isSet)
            return std::array<double, 2>{val1, val2};
        throw std::runtime_error("The RangeFlag \"" + name + "\" isn't set");
    }
};

// c)
class Flags {
private:
    std::string configPath;
    std::vector<std::string> args;
    std::map<std::string, std::shared_ptr<Flag>> flagRegister;
public:
    // c_i)
    Flags(int argc, char** argv, const std::string& _configPath) : configPath(_configPath), args(argv, argv + argc) {}
    // c_ii)
    void registerBool(const std::string& name) {
        flagRegister[name] = std::make_shared<BoolFlag>(name);
    }
    void registerString(const std::string& name) {
        flagRegister[name] = std::make_shared<StringFlag>(name);
    } 
    void registerRange(const std::string& name) {
        flagRegister[name] = std::make_shared<RangeFlag>(name);
    } 
    // c_iii)
    void readArgs() {
        for (std::map<std::string, std::shared_ptr<Flag>>::iterator it = flagRegister.begin(); it != flagRegister.end(); it ++) {
            it->second->parseArgs(args);
        }
    }
    // c_iv)
    void readConfig() {
        std::ifstream configFile;
        configFile.open(configPath);
        if (!configFile.is_open())
            throw std::runtime_error("Could not open the config-file at \"" + configPath + "\"");
        std::string line;
        while (std::getline(configFile, line)) {
            unsigned int findDots = line.find(":");
            if (findDots == std::string::npos)
                throw std::runtime_error("Invalid line in config-file (no \":\")");
            std::string name = line.substr(0, findDots);
            if (flagRegister.count(name) == 0)
                throw std::runtime_error("No flag with name \"" + name + "\"");
            flagRegister[name]->parseConfigLine(line.substr(findDots + 1));
        }
    }
    // c_v)
    bool getBool(const std::string& name) {
        std::shared_ptr<BoolFlag> boolPtr = std::dynamic_pointer_cast<BoolFlag>(flagRegister[name]);
        if (!boolPtr)
            throw std::runtime_error("Wrong getter: not a BoolFlag");
        return boolPtr -> get();
    }
    std::string getString(const std::string& name) {
        std::shared_ptr<StringFlag> stringPtr = std::dynamic_pointer_cast<StringFlag>(flagRegister[name]);
        if (!stringPtr)
            throw std::runtime_error("Wrong getter: not a StringFlag");
        return stringPtr -> get();
    }
    std::array<double, 2> getRange(const std::string& name) {
        std::shared_ptr<RangeFlag> rangePtr = std::dynamic_pointer_cast<RangeFlag>(flagRegister[name]);
        if (!rangePtr)
            throw std::runtime_error("Wrong getter: not a RangeFlag");
        return rangePtr -> get();
    }
};