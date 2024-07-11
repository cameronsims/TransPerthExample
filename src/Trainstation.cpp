#include "Trainstation.h"

void transperth::TrainStation_init(TrainStation* ts, int id, const std::string& name, bool hasBus, bool isSpecial, bool hasAirport) {
    ts->ID = id;
    ts->name = name;
    ts->hasBusServices = hasBus;
    ts->isSpecial = isSpecial;
    ts->hasAirport = hasAirport;
}

void transperth::TrainStation_connect(TrainStation* left, TrainStation* right, int weight, TrainStation::ConnectionType type) {
    TrainStation::Link llink, rlink;

    llink.connection = right;
    llink.type = type;
    llink.weight = weight;

    rlink.connection = left;
    rlink.type = type;
    rlink.weight = weight;

    bool lExists = false;
    const int lID = llink.connection->ID;
    for (size_t i = 0; i < left->links.size(); i++) {
        if (left->links[i].connection->ID == lID) {
            lExists = true;
            break;
        }
    }

    bool rExists = false;
    const int rID = rlink.connection->ID;
    for (size_t i = 0; i < right->links.size(); i++) {
        if (right->links[i].connection->ID == rID) {
            rExists = true;
            break;
        }
    }

    if (!lExists)
        left ->links.push_back(llink);

    if (!rExists)
        right->links.push_back(rlink);
}