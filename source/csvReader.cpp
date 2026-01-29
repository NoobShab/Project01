#include <sstream> // for separating files with commas
#include <fstream> // for reading files
#include "csvReader.h"

std::vector<Reel> CSVReader::readCSV(const std::string& filename) {
    std::vector<Reel> reels;
    //input file stream
    // opens the file for reading 
    std::ifstream file(filename); // 'file' points to '<filename>'
    std::string line;

    // Skip header
    // std::getline(source, destination, delimiter)
    std::getline(file, line); // copy to 'line'

    // reads next line from header
    // until file ends, loop continues
    while(std::getline(file,line)){
        std::stringstream ss(line);
        std::string token;
        Reel r;

        std::getline(ss, token, ',');
            r.reels_id = std::stoll(token);
        std::getline(ss, token, ',');
            r.views = std::stoi(token);
        std::getline(ss, token, ',');
            r.likes = std::stoi(token);
        std::getline(ss, token, ',');
            r.comments = std::stoi(token);
        std::getline(ss, token, ',');
            r.hashtag = token;
        std::getline(ss, token, ',');
            r.timestamp = token;
        
        reels.push_back(r);
    }
    return reels;
}