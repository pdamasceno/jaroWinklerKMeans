#ifndef JAROWINKLERKMEANS_DATAPOINT_H
#define JAROWINKLERKMEANS_DATAPOINT_H

#include <string>

class Datapoint {
public:
    Datapoint() = default;
    Datapoint(std::string fileName);
    bool operator==(const Datapoint& other) const;

    void SetFile(std::string fileName);
    std::string GetFile() const;

    void SetClusterId(int id);
    int GetClusterId() const;

    void SetDistance(double distanceToCentroid);
    double GetDistance() const;
    void ResetDistance();

private:
    std::string file;
    int clusterId;
    double distance;
};

#endif //JAROWINKLERKMEANS_DATAPOINT_H
