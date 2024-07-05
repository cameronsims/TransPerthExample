#ifndef TRAINSTATION_H
#define TRAINSTATION_H

#include <string>
#include <vector>

namespace transperth {

    struct TrainStation {

        enum class ConnectionType {
            WALK = 0,
            TRAIN,
            BUS
        };

        typedef struct {
            /// The Pointer to the next station
            TrainStation* connection;
            /// The type of connection
            TrainStation::ConnectionType type;
        } Link;

        /// The ID that the other stops refer to this as
        int ID;
        
        /// The name of the station
        std::string name;

        /// If the station has bus services
        bool hasBusServices;

        /// If the station is a special event station
        bool isSpecial;

        /// The links that the station has
        std::vector<TrainStation::Link> links;

        /// If the station has an airport
        bool hasAirport;

        /// The airport terminals
        std::vector<std::string> terminals;

    };

    void TrainStation_init(TrainStation* ts, int id, const std::string& name = "...", bool hasBus = false, bool isSpecial = false, bool hasAirport = false);
    void TrainStation_connect(TrainStation* left, TrainStation* right, TrainStation::ConnectionType type);

}

#endif