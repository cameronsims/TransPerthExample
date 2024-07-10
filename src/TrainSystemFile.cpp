#include "TrainSystemFile.h"

#include <filesystem>
#include <fstream>

void transperth::parse_station(transperth::TrainSystem& tsys, const std::string& line) {
    if (line.size() > 0) {

        // Check how much commas there are...
        size_t freq = 0;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                freq++;
            }
        }

        size_t first = -1, second = -1, third = -1, fourth = -1;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                if (first == -1) {
                    first = i + 1;
                } else if (second == -1) {
                    second = i + 1;
                } else if (third == -1) {
                    third = i + 1;
                } else if (fourth == -1) {
                    fourth = i + 1;
                }
            }
        }

        if (first != -1 && second != -1 && third != -1) {
            std::string id = line.substr(0, first - 1);
            std::string name = line.substr(first, second - first - 1);
            std::string bus = line.substr(second, third - second - 1);
            std::string special = line.substr(third, fourth - third - 1);

            // Check if there is more commas
            size_t fourthEnd = line.size();
            std::vector<size_t> extraCommas;
            if (freq > 3) {
                for (size_t i = fourth; i < line.size(); i++) {
                    if (line[i] == ',' && fourthEnd == line.size()) {
                        fourthEnd = i;
                    }

                    if (fourthEnd != line.size()) {
                        if (line[i] == ',') {
                            extraCommas.push_back(i);
                        }
                    }

                }
            }

            std::string airport = line.substr(fourth, fourthEnd - fourth);

            transperth::TrainStation tstat;

            if (fourthEnd != line.size() && extraCommas.size() > 0) {
                const size_t end = line.size();
                size_t last = extraCommas[0] + 1;

                for (size_t i = 1; i < extraCommas.size(); i++) {
                    std::string s = line.substr(last, extraCommas[i] - last);
                    last = extraCommas[i] + 1;
                    tstat.terminals.push_back(s);
                }

                tstat.terminals.push_back(line.substr(last, line.size() - last));
            }

            transperth::TrainStation_init(&tstat, std::stod(id), name, std::stod(bus) == 1, std::stod(special) == 1, std::stod(airport) == 1);

            tsys.stations.push_back(tstat);
        }

    }
}

void transperth::add_file(transperth::TrainSystem& tsys, transperth::TrainLine& line, const std::string& fileName) {
    std::ifstream fman(fileName);
    if (!fman.good()) {
        throw - 1;
    }

    std::vector<int> weights;

    while (!fman.eof()) {
        std::string cell;
        std::getline(fman, cell, ',');

        std::stringstream ss(cell);

        int id = -1, weight = -1;
        ss >> id;
        ss >> weight;

        line.stops.push_back(id);
        weights.push_back(weight);
    }

    // Set the name of the Trainline to the last station
    const size_t SIZE = line.stops.size();
    if (SIZE == 0) {
        return;
    }

    const int lastID = line.stops[SIZE - 1];
    line.name = tsys.stations[lastID].name;

    for (size_t i = 0; i < line.stops.size() - 1; i++) {
        const int current = line.stops[i],
                  next = line.stops[i + 1];
        transperth::TrainSystem_connectStation(tsys, current, next, weights[i], transperth::TrainStation::ConnectionType::TRAIN);
    }
}

void transperth::read_trainlines(transperth::TrainSystem& tsys) {
    for (const auto& it : std::filesystem::directory_iterator("./trainlines")) {
        if (it.exists() && it.is_regular_file()) {
            transperth::TrainLine line;

            std::string path = it.path().string();
            add_file(tsys, line, path);

            std::string name;
            size_t eoDirectory = 0,
                eoFileName = path.size();
            for (size_t i = 0; i < path.size(); i++) {
                if (path[i] == '/' || path[i] == '\\') {
                    eoDirectory = i + 1;
                }
                if (path[i] == '.') {
                    eoFileName = i;
                }
            }
            name = path.substr(eoDirectory, eoFileName - eoDirectory);

            const size_t last = line.stops.size() - 1;
            const size_t pos = line.stops[last];
            line.name = name;

            tsys.lines.push_back(line);
        }
    }
}