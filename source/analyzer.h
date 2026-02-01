#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "reel.h"
// #include "post.h"


struct HashtagStats{
    std::string hashtag;
    int postCount;

    long long totalViews = 0;
    long long totalLikes = 0;
    long long totalComments = 0;
    long long engagementScore = 0;
    int reelCount = 0;

    double avgViews;
    double avgLikes;
    double avgComments;
};

struct EmergingHashtags {
    std::string hashtag;
    double emergenceScore;
    HashtagStats stats;
};

// HashtagStats analyzeSingleHashtag(
//     const std::string& hashtag,
//     const std::vector<Post>& posts);

namespace Analyze {
    std::unordered_map<std::string, HashtagStats>
    rankHashtagsByEngagement(const std::vector<Reel>& reels);
    
    std::vector<EmergingHashtags> getTopEmergingHashtags(
        const std::unordered_map<std::string, HashtagStats>& table);
        
    std::vector<HashtagStats> getRankedHashtags(
        const std::unordered_map<std::string, HashtagStats>& hashtagMap);
            
    // std::vector<HashtagStats> analyzeSingleHashtag(
    //     const std::string& hashtag,
    //     const std::vector<Post>& posts);

};


#endif