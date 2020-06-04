#ifndef JAROWINKLERKMEANS_KMEANSCLUSTERING_H
#define JAROWINKLERKMEANS_KMEANSCLUSTERING_H

#include <unordered_map>
#include <vector>
#include "Datapoint.h"

class KMeansClustering {
public:
    KMeansClustering() = delete;
    KMeansClustering(std::size_t k, std::string fileName);

    void Run();
    void WriteResultToFile();

private:
    bool ReadFileList();
    bool InitializeContainers();

    int kParameter;
    std::string fileList;
    std::vector<Datapoint> datapointContainer;
    std::vector<Datapoint> clusterCentroidContainer;
    std::unordered_map<int, std::vector<Datapoint>> clusterContainer;
};

#endif //JAROWINKLERKMEANS_KMEANSCLUSTERING_H
