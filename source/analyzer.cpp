#include "analyzer.h"

std::vector<Reel> Analyze::filterByHashtag(
    const std::vector<Reel>& reels,
    const std::string& hashtag) {
        std::vector<Reel> result;

        for(const auto& r : reels){
            if(r.hashtag == hashtag)
                result.push_back(r);
        }

        return result;
    }