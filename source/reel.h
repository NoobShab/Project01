#ifndef REEL_H
#define REEL_H

#include <string> 

struct Reel {
    long long reels_id;
    int views;
    int likes;
    int comments;
    std::string hashtag;
    std::string timestamp;

    int engagement() const {
        return likes + comments;
    }
};

#endif