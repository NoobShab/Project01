#include <iostream> 
#include <iomanip>
#include "csvReader.h"
#include "analyzer.h"

void printHead(){
    std::cout<< "-------------------Welcome to the `Fitness` Reel Sort-------------------";
    std::cout<< "\n\t\tSort as per their %Engagements%";
    std::cout<< "\n------------------------------------------------------------------------\n\n";
}

int main(){


    auto reels = CSVReader::readCSV("/Users/shuvojoti/Doc/RSP/GitDemo/Project01/data/finalReelsData.csv");
    std::string hashtags;

    // Input
    printHead();
    std::cout << "Enter hashtag: ";
    std::cin >> hashtags;;
    std::cout << "\n";


    // Table headings
    std::cout << std::left <<
              std::setw(6) << "Rank" <<
              std::setw(22) << "Reel ID" <<
              std::setw(10) << "Views" <<
              std::setw(10) << "Likes" <<
              std::setw(12) << "Comments" <<
              std::setw(12) << "Engagement" <<
              '\n';
std::cout << std::string(40, '-');
std::cout << '\n';

    auto filter = Analyze::filterByHashtag(reels, hashtags);

    std::sort(filter.begin(), filter.end(), [](Reel& a, Reel& b){
        return a.engagement() > b.engagement();
    });

    for(int i{0}; i < std::min(5, static_cast<int>(filter.size())); i++){
        const auto& r = filter[i];
/*
        if(r.views >= 100000) 
            std::cout << std::left << std::setw(6)
                      << r.views/1000 << "K\n";
        else if(r.views >= 10000 && r.views < 100000) 
            std::cout << r.views/100 << "K\n";
        else if(r.views >= 1000 && r.views < 10000) 
            std::cout << r.views/10 << "K\n"; 
*/

        std::cout << std::left <<
                std::setw(6) << (i + 1) <<
                std::setw(22) << r.reels_id <<
                std::setw(10) << r.views <<
                std::setw(10) << r.likes <<
                std::setw(12) << r.comments <<
                std::setw(12) << r.engagement() <<
                '\n';   
    }

    // Computing stats
    int totalViews{0}, totalEngagement{0};

    for(const auto& r : filter){
        totalViews += r.views;
        totalEngagement += r.engagement();
    }

    double avgViews = (double)totalViews / filter.size();
    double avgEngagement = (double)totalEngagement / filter.size();

    // Summary statistics
    std::cout << std::string(50, '-');
    std::cout << "\nSummary Statistics:\n\n";
    std::cout << "* Total reels analyzed: " << filter.size() << '\n';
    std::cout << "* Average views: " << (int)avgViews << '\n';
    std::cout << "* Average engagement: " << (int)avgEngagement << '\n';


    // Generating insights
    std::cout << "\nInsights:\n\n";

    if(!filter.empty()){
        const auto& top = filter[0];
        std::cout << "* Top reel has " << 
                    top.engagement() <<
                    " engagements, which is " <<
                    (top.engagement() * 100 / (int) avgEngagement) <<
                    "% above average.\n\n";
    }

    if(avgViews >= 100000)
        std::cout << ">> The hashtag shows strong visibility potential.\n";
    else if(avgViews >= 0 && avgViews < 100000)
        std::cout << ">> This hashtag shows moderate visibility.\n";

    // if filter empty
    if(filter.empty())
        std::cout << "No reels found for hashtag: #" << hashtags << '\n';

    return 0;
    
}