#include "TrainSystem.h"

#include <vector>

void transperth::TrainSystem_connectStation(TrainSystem& ts, int parent, int child, int weight, TrainStation::ConnectionType type) {
    // Location
    size_t lpos = -1;
    size_t rpos = -1;

    // Same
    if (parent == child) {
        return;
    }

    // Check for IDs
    for (size_t i = 0; i < ts.stations.size(); i++) {
        if (ts.stations[i].ID == parent) {
            lpos = i;

            if (rpos != -1) {
                break;
            }
        }

        if (ts.stations[i].ID == child) {
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
    TrainStation_connect(&ts.stations[lpos], &ts.stations[rpos], weight, type);
}
