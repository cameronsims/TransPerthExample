#ifndef TRAINLINE_H
#define TRAINLINE_H

#include <string>
#include <vector>

namespace transperth {
    
    typedef struct {

        /// The name of the train line
        std::string name;

        /// The IDs of stops (must be in-order)
        std::vector<int> stops;

    } TrainLine;

}

#endif