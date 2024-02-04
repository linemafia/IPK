#include <iostream>
#include "flags.hh"

int main(int argc, char* argv[]){
    // Initialisieren der Flags
    Flags flags = Flags(argc, argv, "./config.txt");

    // Registrieren von Flags: Somit wird definiert, wonach in Configs
    // und den Kommandozeilenargumenten gesucht werden soll
    flags.registerBool("someBool");
    flags.registerBool("anotherBool");

    flags.registerString("someString");
    flags.registerString("anotherString");

    flags.registerRange("someRange");
    flags.registerRange("anotherRange");

    flags.registerString("unsetString");
    flags.registerRange("unsetRange");
    

    // Lesen der beiden Quellen (impliziert setzen der Flags)
    flags.readConfig(); // Erst alle Werte aus der Config-Datei lesen...
    flags.readArgs(); // ...dann Werte, die explizit angegeben wurden überschreiben.

    // Auslesen der Flags (dies wäre in einem echten Programm natürlich komplizierter)
    std::cout << "someBool: " << flags.getBool("someBool") << std::endl;
    std::cout << "anotherBool: " << flags.getBool("anotherBool") << std::endl;

    std::cout << "someString: " << flags.getString("someString") << std::endl;
    std::cout << "anotherString: " << flags.getString("anotherString") << std::endl;

    auto someRange = flags.getRange("someRange");
    std::cout << "someRange: " << someRange[0] << " - " << someRange[1] << std::endl;
    auto anotherRange = flags.getRange("anotherRange");
    std::cout << "anotherRange: " << anotherRange[0] << " - " << anotherRange[1] << std::endl;

    try{
        auto unset = flags.getString("unsetString");
        std::cout << "IF YOU CAN READ THIS, SOMETHING WENT WRONG!" << std::endl;
    } catch (std::invalid_argument& e){
        std::cout << "wanted error: " << e.what() << std::endl;
    }

    try{
        auto unset = flags.getRange("unsetRange");
        std::cout << "IF YOU CAN READ THIS, SOMETHING WENT WRONG!" << std::endl;
    } catch (std::invalid_argument& e){
        std::cout << "wanted error: " << e.what() << std::endl;
    }

    try{
        auto wrong = flags.getBool("someString");
        std::cout << "IF YOU CAN READ THIS, SOMETHING WENT WRONG!" << std::endl;
    } catch (std::invalid_argument& e){
        std::cout << "wanted error: " << e.what() << std::endl;
    }

}