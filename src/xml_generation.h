#include "TrainSystem.h"

#include <iostream>

namespace transperth {
    namespace xml {

        void generate_stations(const transperth::TrainSystem& tsys, std::ostream& output);
        void generate_trainlines(const transperth::TrainSystem& tsys, std::ostream& output);

        void generate_xml(const transperth::TrainSystem& tsys, std::ostream& output);
    }
}