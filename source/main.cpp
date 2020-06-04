#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include "KMeansClustering.h"
#include "jaroWinkler.hpp"

int main(int argc, char **argv) {
   int opt;
   std::size_t kParameter;
   std::string fileName;

    while((opt = getopt(argc, argv, "k:f:")) != -1) {
        switch(opt) {
            case 'k': {
                kParameter = atoi(optarg);
                break;
            }
            case 'f': {
                fileName.assign(optarg);
                break;
            }
            case ':': {
                std::cout << "One or more options without value" << std::endl;
                break;
            }
            case '?': {
                std::cout << optopt << " is not a valid option" << std::endl;
                break;
            }
            default: {
                std::cout << "Unknown" << std::endl;
                break;
            }
        }
    }

    KMeansClustering clustering(kParameter, fileName);
    std::cout << "Starting k means clustering..." << std::endl;
    clustering.Run();
    std::cout << "Writing to output file..." << std::endl;
    clustering.WriteResultToFile();
    std::cout << "Done!" << std::endl;

    return 0;
}