//
// Created by lchin on 4/20/2025.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "csv.h"
using namespace std; 

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

    vector<song> merge(vector<song>& L, vector<song>& R, string P) {
        vector<song> result;
        int i,j;
        i=0;
        j=0;

        while(i < L.size() && j < R.size()) {
            if(P == "popularity") {
                if(L[i].popularity > R[j].popularity) {
                    result.push_back(L[i]);
                    i++;
                }
                else {
                    result.push_back(R[j]);
                    j++;
                }
            } else if(P == "liveness") {
                if(L[i].liveness > R[j].liveness) {
                    result.push_back(L[i]);
                    i++;
                }
                else {
                    result.push_back(R[j]);
                    j++;
                }
            }
        }

        while(i < L.size()) {
            result.push_back(L[i]);
            i++;
        }
        while(j < R.size()) {
            result.push_back(R[j]);
            j++;
        }

        return result;
    }

    vector<song> mergeSort(std::vector<song>& songs, string P) {
        if(songs.size() <= 1) {
            return songs;
        }

        int Mid = songs.size() / 2;

        vector<song> L(songs.begin(), songs.begin() + Mid);
        vector<song> R(songs.begin() + Mid, songs.end());

        vector<song> SL = mergeSort(L,P);
        vector<song> SR = mergeSort(R,P);
        return merge(SL, SR, P);
    }


};

#endif //MUSICDATA_H
