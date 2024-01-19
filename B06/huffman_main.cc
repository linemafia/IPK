#include <iostream>
#include "huffman.hh"

//Prototype
std::string boolVectorToString(const BitVector& boolVector);

// Funktion zum Lesen des Inhalts einer Datei und Speichern in einem String
std::string readFileToString(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        return "";
    }

    // Lese den gesamten Inhalt der Datei in einen String
    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    file.close();

    return fileContent;
}

int main(){
    std::string input = readFileToString("chat_gpt_story_ascii.txt");
    Huffman huff(input);

    huff.print();
    std::cout << std::endl;

    auto gretchenFrage = "Nun sag, wie hast du's mit der Religion?";
    std::cout << "Original: " << gretchenFrage << std::endl;

    BitVector gretchenEncoded;
    huff.encode(gretchenFrage, gretchenEncoded);
    std::cout << "Codiert: " << boolVectorToString(gretchenEncoded) << std::endl;

    auto gretchenRedecoded = huff.decode(gretchenEncoded);
    std::cout << "Decodiert: " << gretchenRedecoded << std::endl; //Nur ein ' verloren, super! :)

    BitVector inputEncoded;
    huff.encode(input, inputEncoded);

    std::cout << "Länge  Original-Text: " << input.size() << " Byte" << std::endl;
    std::cout << "Länge Codierter Text: " << inputEncoded.size() / 8 << " Byte";
    std::cout << " (Lange des Baumes vernachlässigt...)" << std::endl;

    return 0;
}