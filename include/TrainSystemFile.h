#ifndef TRAINSYSTEMFILE_H
#define TRAINSYSTEMFILE_H

#include "TrainSystem.h"

namespace transperth {
    void parse_station(transperth::TrainSystem& tsys, const std::string& line);
    void add_file(transperth::TrainSystem& tsys, transperth::TrainLine& line, const std::string& fileName);
    void read_trainlines(transperth::TrainSystem& tsys);
}

#endif