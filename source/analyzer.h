#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>
#include "reel.h"

class Analyze {
    public: 
        static std::vector<Reel> filterByHashtag (const std::vector<Reel>& reels, 
        const std::string& hashtag);
};

#endif