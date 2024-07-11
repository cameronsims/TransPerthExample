#include "xml_generation.h"

void transperth::xml::generate_stations(const transperth::TrainSystem& tsys, std::ostream& output) {
    output << "    <Stations>";
    for (size_t i = 0; i < tsys.stations.size(); i++) {
        const transperth::TrainStation& station = tsys.stations[i];
        const std::vector<transperth::TrainStation::Link>& links = station.links;
        output << "        <Station id=\"" << station.ID
            << "\" name=\"" << station.name
            << "\" bus=\"" << station.hasBusServices
            << "\" special=\"" << station.isSpecial
            << "\" airport=\"" << station.hasAirport << "\"";

        if (station.hasAirport) {
            output << " terminals=\"";
            for (size_t j = 0; j < station.terminals.size(); j++) {
                output << station.terminals[j] << ((j - 1 >= station.terminals.size()) ? " " : "\"");
            }
        }

        output << ">\n";

        for (size_t j = 0; j < links.size(); j++) {
            const transperth::TrainStation::Link& link = links[j];
            output << "            <StationLink type=\"" << (int)link.type << "\" id=\"" << link.connection->ID << "\" weight=\"" << link.weight << "\"/>\n";
        }
        output << "        </Station>\n";
    }
    output << "    </Stations>\n";
}

void transperth::xml::generate_trainlines(const transperth::TrainSystem& tsys, std::ostream& output) {
    output << "    <Trainlines>\n";
    for (size_t i = 0; i < tsys.lines.size(); i++) {
        const transperth::TrainLine& line = tsys.lines[i];
        const std::vector<int>& v = line.stops;

        output << "        <Trainline name=\"" << line.name << "\">\n";
        for (size_t i = 0; i < v.size(); i++) {
            output << "            <Trainstop id=\"" << v[i] << "\"/>\n";
        }

        output << "        </Trainline>\n";
    }
    output << "    </Trainlines>\n";
}

void transperth::xml::generate_xml(const transperth::TrainSystem& tsys, std::ostream& output) {
    output << "<Trainsystem>\n";
    transperth::xml::generate_stations(tsys, output);
    transperth::xml::generate_trainlines(tsys, output);
    output << "</Trainsystem>\n";
}