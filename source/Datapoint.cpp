#include "Datapoint.h"

Datapoint::Datapoint(std::string fileName) :
    file(std::move(fileName)),
    clusterId(-1),
    distance(-1) {}

bool Datapoint::operator==(const Datapoint &other) const {
    return this->GetFile() == other.GetFile();
}

void Datapoint::SetFile(std::string fileName) {
    file = std::move(fileName);
}

std::string Datapoint::GetFile() const{
    return file;
}

void Datapoint::SetClusterId(int id) {
    clusterId = id;
}

int Datapoint::GetClusterId() const {
    return clusterId;
}

void Datapoint::SetDistance(double distanceToCentroid) {
    distance = distanceToCentroid;
}

double Datapoint::GetDistance() const {
    return distance;
}

void Datapoint::ResetDistance() {
    distance = -1;
}





