#include "TrainSystem.h"

#include <vector>

transperth::TrainSystem::TrainSystem() {

}

void transperth::TrainSystem::addStation(const TrainStation& ts) {
    // Set all connections to null
    TrainStation t;
    t.ID = ts.ID;
    t.name = ts.name;
    t.hasBusServices = ts.hasBusServices;
    t.isSpecial = ts.isSpecial;

    // Add value to back of vector
    stations.push_back(t);
}

void transperth::TrainSystem::connectStation(int parent, int child, TrainStation::ConnectionType type) {
    // Location
    size_t lpos = -1;
    size_t rpos = -1;

    // Same
    if (parent == child) {
        return;
    }

    // Check for IDs
    for (size_t i = 0; i < stations.size(); i++) {
        if (stations[i].ID == parent) {
            lpos = i;

            if (rpos != -1) {
                break;
            }
        }

        if (stations[i].ID == child) {
            rpos = i;

            if (lpos != -1) {
                break;
            }
        }
    }

    // Doesn't exist
    if (lpos == -1 || rpos == -1) {
        return;
    }

    // Add a connection
    TrainStation_connect(&stations[lpos], &stations[rpos], type);
}

const transperth::TrainStation& transperth::TrainSystem::getStation(int id) const {

    for (size_t i = 0; i < stations.size(); i++) {
        if (stations[i].ID == id) {
            return stations[i];
        }
    }

    throw 1;
}

void transperth::TrainSystem::addLine(const TrainLine& line) {
    lines.push_back(line);
}

const transperth::TrainLine& transperth::TrainSystem::getLine(const std::string& name) const {
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i].name == name) {
            return lines[i];
        }
    }
    
    throw 2;
}