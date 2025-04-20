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
    //Added a default constructor to song
    song() = default;
    std::string artistName;
    std::string trackName;
    std::string trackGenre;
    float popularity;
    float danceability;
    float liveness;

    song(const std::string &artistName,
         const std::string &trackName,
         const std::string &trackGenre,
         float popularity,
         float danceability,
         float liveness)
        : artistName(artistName),
          trackName(trackName),
          trackGenre(trackGenre),
          popularity(popularity),
          danceability(danceability),
          liveness(liveness)
    {}
};

class MusicData {
public:
    std::vector<song> data;

    MusicData() {
        csv::CSVReader reader("music.csv");
        for (csv::CSVRow &row : reader) {
            data.emplace_back(
                row["artists"].get<>(),
                row["track_name"].get<>(),
                row["track_genre"].get<>(),
                row["popularity"].get<float>(),
                row["danceability"].get<float>(),
                row["liveness"].get<float>()
            );
        }
    }
//2 Quick sort functions, one for sorting by liveness, the other for popularity
    std::vector<song> quick_sort_by_liveness(int N) {
        std::vector<song> arr = data;
        quick_sort_liveness(arr.begin(), arr.end());
        if ((int)arr.size() > N) arr.resize(N);
        return arr;
    }

    std::vector<song> quick_sort_by_popularity(int N) {
        std::vector<song> arr = data;
        quick_sort_popularity(arr.begin(), arr.end());
        if ((int)arr.size() > N) arr.resize(N);
        return arr;
    }

private:
    //template to allow any type of data to be passed through
    //both versions of sort use median of three method to choose a pivot
    template<typename RandomIt>
    void quick_sort_liveness(RandomIt first, RandomIt last) {
        if (last - first < 2) return;
        auto midIt = first + (last - first) / 2;
        song pivot = *first;
        song midElem = *midIt;
        song lastElem = *(last - 1);
        if (first->liveness > midElem.liveness) {
            if (midElem.liveness > lastElem.liveness) pivot = midElem;
            else if (first->liveness > lastElem.liveness) pivot = lastElem;
            else pivot = *first;
        } else {
            if (first->liveness > lastElem.liveness) pivot = *first;
            else if (midElem.liveness > lastElem.liveness) pivot = lastElem;
            else pivot = midElem;
        }
        RandomIt left = first, right = last - 1;
        while (left <= right) {
            while (left->liveness > pivot.liveness) ++left;
            while (pivot.liveness > right->liveness) --right;
            if (left <= right) {
                std::iter_swap(left, right);
                ++left; --right;
            }
        }
        quick_sort_liveness(first, right + 1);
        quick_sort_liveness(left, last);
    }

    template<typename RandomIt>
    void quick_sort_popularity(RandomIt first, RandomIt last) {
        if (last - first < 2) return;
        auto midIt = first + (last - first) / 2;
        song pivot = *first;
        song midElem = *midIt;
        song lastElem = *(last - 1);
        if (first->popularity > midElem.popularity) {
            if (midElem.popularity > lastElem.popularity) pivot = midElem;
            else if (first->popularity > lastElem.popularity) pivot = lastElem;
            else pivot = *first;
        } else {
            if (first->popularity > lastElem.popularity) pivot = *first;
            else if (midElem.popularity > lastElem.popularity) pivot = lastElem;
            else pivot = midElem;
        }
        RandomIt left = first, right = last - 1;
        while (left <= right) {
            while (left->popularity > pivot.popularity) ++left;
            while (pivot.popularity > right->popularity) --right;
            if (left <= right) {
                std::iter_swap(left, right);
                ++left; --right;
            }
        }
        quick_sort_popularity(first, right + 1);
        quick_sort_popularity(left, last);
    }
};

#endif // MUSICDATA_H
