#include "Trainstation.h"
#include "Trainsystem.h"
#include "TrainLine.h"

#include <iostream>

namespace transperth {
    namespace html {
        void set_station_header(std::ostream& os);
        void add_station(std::ostream& os, const transperth::TrainStation& ts);

        void create_index_page(const transperth::TrainSystem& tsys, std::ostream& os, const std::string& header, const std::string& footer);
        void create_stations_page(const std::vector<transperth::TrainStation> stations, std::ostream& os, const std::string& header, const std::string& footer);
        void create_trainline_page(const transperth::TrainSystem& tsys, const transperth::TrainLine& line, std::ostream& os, const std::string& header, const std::string& footer);
        void create_trainline_pages(const transperth::TrainSystem& tsys, const std::vector<transperth::TrainLine>& lines, const std::string& header, const std::string& footer);
    }
}