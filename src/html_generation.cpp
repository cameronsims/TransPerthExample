#include "html_generation.h"

#include <fstream>

void transperth::html::set_station_header(std::ostream& os) {
    const std::vector<std::string> NAMES = {
        "ID",
        "Name",
        "Bus Station",
        "Event Station",
        "Airport Station",
        "Terminals"
    };

    os << "<tr class=\"train-cell-header\">";
    for (size_t i = 0; i < NAMES.size(); i++) {
        os << "<td class=\"train-cell-header train-cell\">" << NAMES[i] << "</td>";
    }
    os << "</tr>";
}

void transperth::html::add_station(std::ostream& os, const transperth::TrainStation& ts) {

    auto lam = [&](bool b) {
        const std::string s = (b ? "True" : "False");
        os << "<td class=\"train-cell " << s << "\">" << s << "</td>";
    };

    os << "<tr><td class=\"train-cell train-cell-id\">" << ts.ID << "</td><td class=\"train-cell train-cell-name\">" << ts.name << "</td>";
    lam(ts.hasBusServices);
    lam(ts.isSpecial);
    lam(ts.hasAirport);
    os << "<td>";

    if (ts.hasAirport) {
        for (size_t j = 0; j < ts.terminals.size(); j++) {
            os << ts.terminals[j] << ((ts.terminals.size() - 1 != j) ? ", " : "");
        }
    }
    os << "</td></tr>";
}

void transperth::html::create_index_page(const transperth::TrainSystem& tsys, std::ostream& os, const std::string& header, const std::string& footer) {
    os << header;
    os << "<a href=\"./stations.html\">Stations</a><p/>";

    for (size_t i = 0; i < tsys.lines.size(); i++) {
        const transperth::TrainLine& line = tsys.lines[i];
        os << "<a href=\"./" << line.name << ".html\">" << line.name << "</a><p/>";
    }
    os << footer;
}

void transperth::html::create_stations_page(const std::vector<transperth::TrainStation> stations, std::ostream& os, const std::string& header, const std::string& footer) {
    os << header;
    os << "<div class=\"train-header\">TransPerth Stations</div>";
    os << "<table>";
    for (size_t i = 0; i < stations.size(); i++) {
        add_station(os, stations[i]);
    }
    os << "</table>";
    os << footer;
}

void transperth::html::create_trainline_page(const transperth::TrainSystem& tsys, const transperth::TrainLine& line, std::ostream& os, const std::string& header, const std::string& footer) {
    const std::vector<transperth::TrainStation>& stations = tsys.stations;
    const std::vector<int>& stops = line.stops;

    os << header;
    os << "<div class=\"train-header\">TransPerth Stations</div>";
    os << "<table>";
    set_station_header(os);

    for (size_t j = 0; j < stops.size(); j++) {
        // Look through our original vector
        size_t location = -1;
        for (size_t k = 0; k < stations.size(); k++) {
            if (stops[j] == stations[k].ID) {
                location = k;
                add_station(os, stations[location]);
                break;
            }
        }
    }

    os << "</table>";
    os << footer;
}

void transperth::html::create_trainline_pages(const transperth::TrainSystem& tsys, const std::vector<transperth::TrainLine>& lines, const std::string& header, const std::string& footer) {
    for (size_t i = 0; i < tsys.lines.size(); i++) {

        // Print all Stations
        std::ofstream tlineos("./html/" + lines[i].name + ".html");
        create_trainline_page(tsys, lines[i], tlineos, header, footer);
    }
}
