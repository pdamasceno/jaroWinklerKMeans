#include "KMeansClustering.h"
#include "jaroWinkler.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <random>
#include <sstream>
#include <ctime>
#include <iomanip>

KMeansClustering::KMeansClustering(std::size_t k, std::string list) :
    kParameter(k),
    fileList(std::move(list)),
    datapointContainer(),
    clusterCentroidContainer(),
    clusterContainer() {}

void KMeansClustering::Run() {
    unsigned int iter = 0;

    InitializeContainers();

    while(iter < 100) {
        bool done = true;

        // Setting datapoints to clusters
        for (Datapoint& datapoint : datapointContainer) {
            double bestDistance = -1;
            int bestClusterId = -1;

            // Getting best cluster
            for (Datapoint& cluster : clusterCentroidContainer) {
                double distance = jaroWinklerDistance(datapoint.GetFile(), cluster.GetFile());
                datapoint.SetDistance(distance);

                if (distance > bestDistance) {
                    bestDistance = distance;
                    bestClusterId = cluster.GetClusterId();
                }
            }

            if (datapoint.GetClusterId() != bestClusterId) {
                // Removing datapoint from any other cluster before adding to the best one
                for (int i = 0; i < kParameter; i++) {
                    if (clusterCentroidContainer.at(i).GetClusterId() == datapoint.GetClusterId()) {
                        auto it = std::find(std::begin(clusterContainer.at(i)), std::end(clusterContainer.at(i)), datapoint);
                        if (it != std::end(clusterContainer.at(i))) {
                            clusterContainer.at(i).erase(it);
                        }
                    }
                }

                // Adding datapoint to cluster
                datapoint.SetClusterId(bestClusterId);
                clusterContainer.at(bestClusterId).push_back(datapoint);

                done = false;
            }
        }

        // Calculating new centroids
        for (int i = 0; i < kParameter; i++) {
            double sum = 0.0;
            std::string fileName;

            for (Datapoint& datapoint : clusterContainer.at(i)) {
                sum += datapoint.GetDistance();
            }

            if (!clusterContainer.at(i).empty()) {
                double newCentroidDistance = sum / clusterContainer.at(i).size();
                double previousDifference = std::numeric_limits<double>::max();

                // Finding datapoint closest to new centroid distance
                for (const Datapoint& datapoint : clusterContainer.at(i)) {
                    double difference = fabs(datapoint.GetDistance() - newCentroidDistance);
                    if (difference < previousDifference) {
                        fileName = datapoint.GetFile();
                        previousDifference = difference;
                    }
                }
            }

            clusterCentroidContainer.at(i).SetFile(fileName);
        }

        if (done) {
            std::cout << "Finished in " << iter + 1 << " iterations" << std::endl;
            return;
        }

        iter++;
    }
}

bool KMeansClustering::ReadFileList() {
    std::string line;

    std::ifstream readStream(fileList);
    if (!readStream.is_open()) {
        return false;
    }

    while(std::getline(readStream, line)) {
        if (!line.empty()) {
            Datapoint datapoint(line);
            datapointContainer.push_back(datapoint);
        }
    }

    return true;
}

bool KMeansClustering::InitializeContainers() {
    // Initializing datapointContainer
    ReadFileList();

    // Initializing clusterContainer
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<std::size_t> randomNumber(0, datapointContainer.size() - 1);

    for (int i = 0; i < kParameter; i++) {
        std::vector<Datapoint> container;
        clusterContainer.insert(std::make_pair(i, container));

        Datapoint cluster = datapointContainer.at(randomNumber(generator));
        cluster.SetClusterId(i);
        clusterCentroidContainer.push_back(cluster);
    }
}

void KMeansClustering::WriteResultToFile() {
    auto time = std::time(nullptr);

    std::stringstream outputFile;
    outputFile << "../outputs/outputK" << kParameter << "_" << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S") << ".txt";

    std::ofstream writeStream(outputFile.str());
    if (writeStream.is_open()) {
        for (int i = 0; i < kParameter; i++) {
            writeStream << "Cluster " << i + 1 << std::endl;

            for (Datapoint& datapoint : clusterContainer.at(i)) {
                writeStream << datapoint.GetFile() << std::endl;
            }

            writeStream << std::endl;
        }
    }
}