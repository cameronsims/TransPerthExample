#ifndef TRAINSYSTEM_H
#define TRAINSYSTEM_H

#include "Trainstation.h"
#include "Trainline.h"

#include <memory>

namespace transperth {

    typedef struct {
        std::vector<TrainStation> stations;
        std::vector<TrainLine> lines;
    } TrainSystem;

    void TrainSystem_connectStation(TrainSystem& ts, int parent, int child, int weight, TrainStation::ConnectionType type);
}

#endif