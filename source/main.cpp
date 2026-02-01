#include <iostream> 
#include <iomanip>
#include "csvReader.h"
#include "analyzer.h"

// Helper function to format numbers with commas
std::string formatNumber(long long num) {
    std::string str = std::to_string(num);
    int insertPosition = str.length() - 3;
    while(insertPosition > 0) {
        str.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    return str;
}

int main(){


    auto reels = CSVReader::readCSV("/Users/shuvojoti/Doc/RSP/GitDemo/Project01/data/reelsArrangement.csv");
    auto hashtagTable = Analyze::rankHashtagsByEngagement(reels);

    std::cout << "\n---------------------------------------------\n";
    std::cout << "\t\tInstaSort: Fitness\n";
    std::cout << "Engineering Focused Data Analysis Tool\n";
    std::cout << "\n---------------------------------------------\n";
    std::cout << "Total reels processed: " << formatNumber(reels.size()) << '\n';
    std::cout << "---------------------------------------------\n";

    int choice; 

    bool run = true;
    while(run){

        std::cout << "[1] Top Hashtags by Engagement\n";
        std::cout << "[2] Top Emerging Hashtags\n";
        std::cout << "[3] Hashtag Research\n";
        std::cout << "[4] Exit\n\n";

        std::cout << "Enter choice: ";
        std::cin >> choice;

        if(choice == 4) break;

        // for choice[1]: rankedHashtags
        if(choice == 1){
            auto ranked = Analyze::getRankedHashtags(hashtagTable);

            std::cout << "\n\t\tInstaSort: High performing hashtags by total engagements\n";
            // std::cout << "\nHigh Performing hashtags by total engagements\n";
            std::cout << "----------------------------------------------------------------------------\n";
            std::cout << std::left << std::setw(6) << "Rank"
                                   << std::setw(15) << "Hashtag"
                                   << std::setw(8) << "Reels"
                                   << std::setw(13) << "Views"
                                   << "Engagement\n";
            
            for(int i = 0; i < std::min(5, static_cast<int>(ranked.size())); i++){
                std::cout << std::setw(6) << i + 1
                          << std::setw(15) << ranked[i].hashtag
                          << std::setw(8) << ranked[i].reelCount
                          << std::setw(13) << formatNumber(ranked[i].totalViews)
                          << formatNumber(ranked[i].engagementScore)
                          << "\n";
            }
            std::cout << '\n';
        }

        // for choice [2] : Emerging Hashtags
        else if(choice == 2){
            auto emerging = Analyze::getTopEmergingHashtags(hashtagTable);

            std::cout << "\n\t\tInstaSort: Top ~Emerging~ Hashtags\n\n";
            std::cout << "--------------------------------------------\n";
            std::cout << std::left
                      << std::setw(6) << "Rank"
                      << std::setw(17) << "Hashtag"
                      << std::setw(8) << "Reels"
                      << "Avg Engagement\n";
            std::cout << "--------------------------------------------\n";
            
            for(int i = 0; i < std::min(5, static_cast<int>(emerging.size())); i++){
                std::cout << std::setw(6) << i + 1
                          << std::setw(17) << emerging[i].hashtag
                          << std::setw(8) << emerging[i].stats.reelCount
                          << std::fixed << std::setprecision(2)
                          << emerging[i].emergenceScore
                          << "\n";
            }

            std::cout << "----------------------------------------------------\n";
            std::cout << "Insights:\n";
            std::cout << "* These hashtags concentrate in top 10% of engaging hashtags\n";
            std::cout << "* A bit different than the conventional ones, these tags are emerging within reach and interaction\n";
            std::cout << "----------------------------------------------------\n";
            // std::cout << "====================================================\n";

        }
        
        // choice 3: hashtag research
        else if(choice == 3){
            // Input
            std::string hashtags;
            std::cout << "Enter hashtag: ";
            std::cin >> hashtags;


            auto result = hashtagTable.find(hashtags);

                if(result == hashtagTable.end()){
                    std::cout << "No data found for #" << hashtags << "\n\n";
                    continue;
                }
                
                const HashtagStats& stats = (*result).second;

                std::cout << "\n--------------------------------------------\n";
                std::cout << "\n\t\tInstaSort: Hashtag Analysis\n";
                std::cout << "--------------------------------------------\n";

                std::cout << "Reels analyzed: " << stats.reelCount << '\n';
                std::cout << "Total views: " << formatNumber(stats.totalViews) << '\n';
                std::cout << "Total engagement: " << formatNumber(stats.engagementScore) << '\n' << '\n';
                std::cout << "Average engagement: " << formatNumber(stats.engagementScore / stats.reelCount) << '\n' << '\n';
            }

            char cont;
            std::cout << "Do you wish to continue?\nPress 'y' to continue; 'x' or any other character to exit.\n";
            std::cin >> cont; 

            cont = std::tolower(cont);

            if(cont != 'y')
                break;
        }
        std::cout << "\nAnalysis complete. Exiting..\n\n";
        return 0;
    }