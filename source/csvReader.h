#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string> 
#include "reel.h"

class CSVReader {
    public: 
        static std::vector<Reel> readCSV(const std::string& filename);
};

#endif