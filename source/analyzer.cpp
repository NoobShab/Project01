#include "analyzer.h"
#include <algorithm>

std::unordered_map<std::string, HashtagStats>
Analyze::rankHashtagsByEngagement(const std::vector<Reel>& reels){
    std::unordered_map<std::string, HashtagStats> table;
    // const std::vector<Reel>& reels,
    // const std::string& hashtag) {
        //     std::vector<Reel> result;
        
        for(const auto& r : reels){
            auto& stats = table[r.hashtag];

            stats.totalViews += r.views;
            stats.totalLikes += r.likes;
            stats.totalComments += r.comments;

            stats.engagementScore += r.likes + (2 * r.comments);
            stats.reelCount++;
        }

    for(auto& [hashtag, stats] : table){
        if(stats.reelCount > 0){
            stats.avgViews = static_cast<double> (stats.totalViews) / stats.reelCount;
            stats.avgLikes = static_cast<double> (stats.totalLikes) / stats.reelCount;
            stats.avgComments = static_cast<double> (stats.totalComments) / stats.reelCount;
        }
    }   
        return table;
    }
  
std::vector<EmergingHashtags> Analyze :: getTopEmergingHashtags(
    const std::unordered_map<std::string, HashtagStats>& table) {
        std::vector<EmergingHashtags> result;
        
        for(const auto& [tag, stats] : table) {
            if(stats.reelCount < 3) continue; 
            
            double score = static_cast<double>(stats.engagementScore) /
            stats.reelCount;

            result.push_back({tag, score, stats});
        }

        std::sort(result.begin(), result.end(), [](
        const EmergingHashtags& a, const EmergingHashtags& b){
            return a.emergenceScore > b.emergenceScore;
        });

        return result;
    }

/*
// Single hashtag search : option [3]
HashtagStats analyzeSingleHashtag(
    const std::string& hashtag,
    const std::vector<Post>& posts) {
        HashtagStats stats{};
        stats.hashtag = hashtag;
        
        long validPosts = 0;
        
        for(const auto& post : posts){
            stats.totalViews += post.views;
            stats.totalLikes += post.likes;
            stats.totalComments += post.comments;
            validPosts++;
        }
        
        stats.postCount = validPosts;
        
        if (validPosts > 0){
            stats.avgViews = static_cast<double>(stats.totalViews) / validPosts;
            stats.avgLikes = static_cast<double>(stats.totalLikes) / validPosts;
            stats.avgComments = static_cast<double>(stats.totalComments) / validPosts;
        }
        
        stats.engagementScore = stats.totalLikes + (2 * stats.totalComments); 
        // (stats.avgLikes * 0.5) +
        // (stats.avgComments * 0.3) +
        // (stats.avgViews * 0.2);
        
        return stats;
    }
    */

std::vector<HashtagStats> Analyze::getRankedHashtags(
    const std::unordered_map<std::string, HashtagStats>& hashtagMap
){
    std::vector<HashtagStats> ranked;

    for(const auto& pair : hashtagMap){
        HashtagStats stats = pair.second;
        stats.hashtag = pair.first;
        ranked.push_back(stats);
    }

    std::sort(ranked.begin(), ranked.end(), 
    [](const HashtagStats& a, const HashtagStats& b){
        return a.engagementScore > b.engagementScore;
    });

    return ranked;
}