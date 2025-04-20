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
    std::string trackName;
    std::string trackGenre;
    float popularity;
    float danceability;
    float liveness;

    song(std::string artistName, std::string trackName, std::string trackGenre, float popularity, float danceability, float liveness) {
        this->artistName = artistName;
        this->trackName = trackName;
        this->trackGenre = trackGenre;
        this->popularity = popularity;
        this->danceability = danceability;
        this->liveness = liveness;
    }
};

class MusicData{
private:
public:
    std::vector<song> data;
    MusicData() {
        csv::CSVReader reader("music.csv");
        for (csv::CSVRow& row : reader) {
            std::string artistName = row["artists"].get<>();
            std::string trackName = row["track_name"].get<>();
            std::string trackGenre = row["track_genre"].get<>();
            float popularity = row["popularity"].get<float>();
            float danceability = row["danceability"].get<float>();
            float liveness = row["liveness"].get<float>();

            data.emplace_back(artistName, trackName, trackGenre, popularity, danceability, liveness);
        }
    }

};

#endif //MUSICDATA_H
