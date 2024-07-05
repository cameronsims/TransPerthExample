#ifndef TRAINSYSTEM_H
#define TRAINSYSTEM_H

#include "Trainstation.h"
#include "Trainline.h"

#include <memory>

namespace transperth {

    class TrainSystem {
    public:
        TrainSystem();

        void addStation(const TrainStation& ts);
        void connectStation(int parent, int child, TrainStation::ConnectionType type);
        const TrainStation& getStation(int id) const;

        void addLine(const TrainLine& line);
        const TrainLine& getLine   (const std::string& name) const;
    private:
        std::vector<TrainStation> stations;
        std::vector<TrainLine> lines;
    };

}

#endif