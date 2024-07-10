#include "Trainstation.h"
#include "Trainsystem.h"
#include "TrainLine.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "TrainSystemFile.h"

void set_station_header(std::ostream& os) {
    os << "<tr><td>ID</td><td>Name</td><td>Bus Station</td><td>Event Station</td><td>Airport Station</td><td>Terminals</td></tr>";
}
void add_station(std::ostream& os, const transperth::TrainStation& ts) {

    auto lam = [&](bool b) { 
        const std::string s = (b ? "True" : "False");
        os << "<td class=\"" << s << "\">" << s << "</td>";
    };

    os << "<tr><td>" << ts.ID << "</td><td>" << ts.name << "</td>";
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

std::string fstream_to_string(std::istream& in) {
    std::string txt;
    while (!in.eof()) {
        std::string temp;
        in >> temp;
        txt += (temp + " ");
    }
    return txt;
}

int main() {
    
    std::ifstream f("./stations/Stations.csv");
    if (!f.good()) {
        return -1;
    }

    transperth::TrainSystem tsys;
    
    while (!f.eof()) {
        std::string line;
        std::getline(f, line);
        transperth::parse_station(tsys, line);
    }

    transperth::read_trainlines(tsys);


    // XML

    std::ofstream output("./output.xml");
    output << "<Trainsystem>\n";

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
    output << "</Trainsystem>\n";






    // HTML

    std::ofstream index("./html/index.html");
    std::ofstream stations("./html/stations.html");


    std::ifstream head("./html/document-head.html");
    std::string headTxt = fstream_to_string(head);

    std::ifstream foot("./html/document-foot.html");
    std::string footTxt = fstream_to_string(foot);
    
    index << headTxt;
    stations << headTxt;
    

    stations << "<div>TransPerth Stations</div>";
    stations << "<table>";
    set_station_header(stations);
    for (size_t i = 0; i < tsys.stations.size(); i++) {
        add_station(stations, tsys.stations[i]);
    }
    stations << "</table>";

    
    index << "<a href=\"./stations.html\">Stations</a><p/>";
    for (size_t i = 0; i < tsys.lines.size(); i++) {
        const transperth::TrainLine line = tsys.lines[i];
        const std::vector<int>& stops = line.stops;

        index << "<a href=\"./" << line.name << ".html\">" << line.name << "</a></p>";
        
        std::ofstream os("./html/" + line.name + ".html");
        os << headTxt;
        os << "<div>TransPerth Stations</div>";
        os << "<table>";
        set_station_header(os);

        // Print all Stations
        
        for (size_t j = 0; j < stops.size(); j++) {
            // Look through our original vector
            size_t location = -1;
            for (size_t k = 0; k < tsys.stations.size(); k++) {
                if (stops[j] == tsys.stations[k].ID) {
                    location = k;
                    break;
                }
            }
            if (location != -1) {
                add_station(os, tsys.stations[location]);
            }
        }

        os << "</table>";
        os << footTxt;
    }




    index << footTxt;
    stations << footTxt;


    return 0;
}