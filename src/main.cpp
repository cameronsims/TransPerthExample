#include "Trainstation.h"
#include "Trainsystem.h"
#include "TrainLine.h"
#include "TrainSystemFile.h"

#include "html_generation.h"
#include "xml_generation.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>


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

    // Sort the values
    auto lam = [&](const transperth::TrainStation& l, const transperth::TrainStation& r) { return l.ID < r.ID; };
    std::sort(tsys.stations.begin(), tsys.stations.end(), lam);


    // XML

    std::ofstream output("./output.xml");
    transperth::xml::generate_xml(tsys, output);

    // HTML

    std::ofstream index("./html/index.html");
    std::ofstream stations("./html/stations.html");


    std::ifstream head("./html/premade/document-head.html");
    std::string headTxt = fstream_to_string(head);

    std::ifstream foot("./html/premade/document-foot.html");
    std::string footTxt = fstream_to_string(foot);
    
    transperth::html::create_index_page(tsys, index, headTxt, footTxt);
    transperth::html::create_stations_page(tsys.stations, stations, headTxt, footTxt);
    transperth::html::create_trainline_pages(tsys, tsys.lines, headTxt, footTxt);

    return 0;
}