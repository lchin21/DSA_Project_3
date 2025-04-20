//
// Created by lchin on 4/20/2025.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "csv.h"

#ifndef MUSICDATA_H
#define MUSICDATA_H

struct song {
    std::string artistName;
    float artistLongitude;
    float artistLatitude;
    float loudness;
    int releaseYear;
    std::string terms;

    song(std::string name, float longitude, float latitude, float loudness, int releaseYear, std::string terms) {
        artistName = name;
        artistLongitude = longitude;
        artistLatitude = latitude;
        this->loudness = loudness;
        this->releaseYear = releaseYear;
        this->terms = terms;
    }
};

class MusicData{
private:
public:
    std::vector<song> data;
    MusicData() {
        csv::CSVReader reader("music.csv");
        for (csv::CSVRow& row : reader) {
            std::string artistName = row["artist.name"].get<>();
            float artistLongitude = row["artist.longitude"].get<float>();
            float artistLatitude = row["artist.latitude"].get<float>();
            float loudness = row["song.loudness"].get<float>();
            int releaseYear = row["song.year"].get<int>();
            std::string terms = row["artist.terms"].get<>();

            data.emplace_back(artistName, artistLongitude, artistLatitude, loudness, releaseYear, terms);
        }
    }

};

#endif //MUSICDATA_H
