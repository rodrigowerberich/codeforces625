#include <iostream>
#include <string>
#include <chrono>

#include "PreviousLetter.hh"

int main(int argc, char* argv[]){
    
    bool verbose = false;
    bool timeIt = false;
    // Ignore first argv, because it is just the program call
    for(int i = 1; i < argc; i++){
        if(std::string("-v") == argv[i]){
            verbose = true;
        }else if(std::string("-t") == argv[i]){
            timeIt = true;
        }
    }

    // Read the string size
    size_t stringSize = 0;
    std::cin >> stringSize;
    // Read the string itself
    std::string userInput;
    std::cin >> userInput;
    // Getting a string of only the size specified
    auto stringToAnalyze = userInput.substr(0, stringSize);
    if(verbose){
        std::cout << "Read " << stringToAnalyze << std::endl;
    }

    // Starting timer
    using namespace std::chrono;
    std::chrono::_V2::system_clock::time_point start;
    if(timeIt){
        start = high_resolution_clock::now();
    }

    // Algorithm of O(n) complexity of time
    // Just run through the array marking which 
    // letters should not be removed
    // Ex:
    // h g f e g f e d f e d c d c b a
    //       ^       ^       ^       ^ 
    // Removed all the marked letters
    // Ex:
    // edca
    // Repeat until no letter has been removed
    // Ex:
    // e d c a
    //     ^ ^
    // c a
    // ^ ^
    // Each time a letter is removed, count the removal
    bool removedLetter =  true;
    size_t removeCounter = 0;
    while(removedLetter){
        removedLetter = false;
        std::string aux;
        for(size_t i = 0; i < stringToAnalyze.size(); i++){
            auto& currentLetter = stringToAnalyze[i];
            auto previousLetter = PreviousLetter(currentLetter);
            bool keepCurrentLetter = false;
            bool hasAdjacentPrevious = false;
            if(verbose){
                std::cout << "Current letter: " << currentLetter << std::endl;
                std::cout << "Previous letter: " << previousLetter << std::endl;
            }
            if(!previousLetter.valid){
                // The letter 'a' has no previous letter, so it is always kept
                keepCurrentLetter = true;
                if(verbose){
                    std::cout << "Keep all 'a's" << std::endl;
                }
            }else{ 
                if( i!=0 ){
                    // Analyzing if backward neighbour is the previous letter, if it exists
                    auto& adjacentBackwards = stringToAnalyze[i-1];
                    hasAdjacentPrevious = (adjacentBackwards == previousLetter.previous);
                    if(verbose){
                        std::cout << "Adjacent before is " << adjacentBackwards << " and it " << ((hasAdjacentPrevious)?"is":"is not") << " a previous" << std::endl;
                    }
                }
                // No need to check if it is already marked for removal
                if( i!= stringToAnalyze.size()-1 && !hasAdjacentPrevious){
                    // Analyzing if front neighbour is the previous letter, if it exists
                    auto& adjacentForward = stringToAnalyze[i+1];
                    hasAdjacentPrevious = (adjacentForward == previousLetter.previous);
                    if(verbose){
                        std::cout << "Adjacent after is " << adjacentForward << " and it " << ((hasAdjacentPrevious)?"is":"is not") << " a previous" << std::endl;
                    }
                }
            }
            keepCurrentLetter = (!hasAdjacentPrevious || keepCurrentLetter);
            if(keepCurrentLetter){
                if(verbose){
                    std::cout << "Will keep " << currentLetter << std::endl;
                }
                // Push all the letters that will be kept into auxiliary 
                // string instead of removing
                aux += currentLetter;
            }else{
                // If we did not keep the letter it is removed
                if(verbose){
                    std::cout << "Will not keep " << currentLetter << std::endl;
                }
                removedLetter = true;
                removeCounter += 1;
            }
            if(verbose){
                std::cout << "----------------------\n";
            }
        }
        // Move the auxiliary string to replace the old one
        // reducing allocation cost
        stringToAnalyze = std::move(aux);
    }

    // Stopping the timer
    if(timeIt){
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop-start);
        std::cout << "Took " << duration.count() << " microseconds\n";
    }

    // std::cout << stringToAnalyze << std::endl;
    std::cout << removeCounter << std::endl;

    return 0;
}