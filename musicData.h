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

    void merge(std::vector<song>& songs, int L, int R, int Mid, string P) {
        if(P == "popularity") {
            int sizeL = Mid - L + 1;
            int sizeR = R - Mid;

            vector<song> tempA(songs.begin() + L, songs.begin() + Mid + 1);
            vector<song> tempB(songs.begin() + Mid + 1, songs.begin() + R + 1);

            int i,j,k;
            i=0;
            j=0;
            k=L;

            while(i < sizeL && j < sizeR) {
                if(tempA[i].popularity > tempB[j].popularity) {
                    songs[k] = tempA[i];
                    i++;
                }
                else {
                    songs[k] = tempB[j];
                    j++;
                }
                k++;
            }

            while(i < sizeL) {
                songs[k] = tempA[i];
                i++;
                k++;
            }
            while(j < sizeR) {
                songs[k] = tempB[j];
                j++;
                k++;
            }

        } else if(P == "liveness") {
            int sizeL = Mid - L + 1;
            int sizeR = R - Mid;

            vector<song> tempA(songs.begin() + L, songs.begin() + Mid + 1);
            vector<song> tempB(songs.begin() + Mid + 1, songs.begin() + R + 1);

            int i,j,k;
            i=0;
            j=0;
            k=L;

            while(i < sizeL && j < sizeR) {
                if(tempA[i].liveness > tempB[j].liveness) {
                    songs[k] = tempA[i];
                    i++;
                }
                else {
                    songs[k] = tempB[j];
                    j++;
                }
                k++;
            }

            while(i < sizeL) {
                songs[k] = tempA[i];
                i++;
                k++;
            }
            while(j < sizeR) {
                songs[k] = tempB[j];
                j++;
                k++;
            }
        } else {
            return;
        }
    }

    void mergeSort(std::vector<song>& songs, int L, int R, string P) {
        if(P == "popularity") {
            if(L >= R) {
                return;
            }
            int Mid = L + (R - L) / 2;
            mergeSort(songs, L, Mid, "popularity");
            mergeSort(songs, Mid + 1, R, "popularity");
            merge(songs, L, Mid, R);

        } else if(P == "liveness") {
            if(L >= R) {
                return;
            }
            int Mid = L + (R - L) / 2;
            mergeSort(songs, L, Mid, "liveness");
            mergeSort(songs, Mid + 1, R, "liveness");
            merge(songs, L, Mid, R);

        } else {
            return;
        }
    }

};

#endif //MUSICDATA_H
