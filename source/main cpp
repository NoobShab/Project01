#include <iostream> 
#include "csvReader.h"
#include "analyzer.h"

int main(){
    auto reels = CSVReader::readCSV("finalReelsData.csv");
    std::string hashtags;

    // Input
    std::cout << "Enter hashtag: ";
    std::cin >> hashtags;;

    auto filter = Analyze::filterByHashtag(reels, hashtags);

    std::sort(filter.begin(), filter.end(), [](Reel& a, Reel& b){
        return a.engagement() > b.engagement();
    });

    for(int i{0}; i < std::min(5, static_cast<int>(filter.size())); i++){
        const auto& r = filter[i];
        std::cout << r.reels_id << " | "
                  << r.views << " | "
                  << r.likes << " | "
                  << r.comments << " | "
                  << r.engagement() << "\n";
    }

    return 0;
    
}