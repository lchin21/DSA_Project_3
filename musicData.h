// musicData.h
// Created by lchin on 4/20/2025.

#include <fstream>
#include <iostream>
#include <vector>
#include "csv.h"
using namespace std;

#ifndef MUSICDATA_H
#define MUSICDATA_H

struct song {
    song() = default;

    std::string artistName;
    std::string trackName;
    std::string trackGenre;
    float popularity;
    float duration_ms;
    float danceability;
    float liveness;

    song(const std::string &artistName,
         const std::string &trackName,
         const std::string &trackGenre,
         float popularity,
         float duration_ms,
         float danceability,
         float liveness)
        : artistName(artistName),
          trackName(trackName),
          trackGenre(trackGenre),
          popularity(popularity),
          duration_ms(duration_ms),
          danceability(danceability),
          liveness(liveness) {
    }
};

class MusicData {
public:
    std::vector<song> data;

    MusicData() {
        csv::CSVReader reader("music.csv");
        for (csv::CSVRow &row: reader) {
            data.emplace_back(
                row["artists"].get<>(),
                row["track_name"].get<>(),
                row["track_genre"].get<>(),
                row["popularity"].get<float>(),
                row["duration_ms"].get<float>(),
                row["danceability"].get<float>(),
                row["liveness"].get<float>()
            );
        }
    }

    std::vector<song> quick_sort_by_popularity(int N) {
        auto arr = data;
        quick_sort_popularity(arr.begin(), arr.end());
        if ((int)arr.size() > N) arr.resize(N);
        return arr;
    }
    std::vector<song> quick_sort_by_danceability(int N) {
        auto arr = data;
        quick_sort_danceability(arr.begin(), arr.end());
        if ((int)arr.size() > N) arr.resize(N);
        return arr;
    }
    std::vector<song> quick_sort_by_liveness(int N) {
        auto arr = data;
        quick_sort_liveness(arr.begin(), arr.end());
        if ((int)arr.size() > N) arr.resize(N);
        return arr;
    }
    std::vector<song> quick_sort_by_duration(int N) {
        auto arr = data;
        quick_sort_duration(arr.begin(), arr.end());
        if ((int)arr.size() > N) arr.resize(N);
        return arr;
    }

    vector<song> mergeSort(std::vector<song>& songs, string& P) {
        if (songs.size() <= 1) return songs;
        int Mid = songs.size() / 2;
        vector<song> L(songs.begin(), songs.begin() + Mid);
        vector<song> R(songs.begin() + Mid, songs.end());
        auto SL = mergeSort(L, P);
        auto SR = mergeSort(R, P);
        return merge(SL, SR, P);
    }

    vector<song> quick_sort_subset(const vector<song>& subset,
                               const string& P,
                               int N)
    {
        auto arr = subset;
        if      (P == "popularity")   quick_sort_popularity(arr.begin(), arr.end());
        else if (P == "danceability") quick_sort_danceability(arr.begin(), arr.end());
        else if (P == "liveness")     quick_sort_liveness(arr.begin(), arr.end());
        else if (P == "duration")     quick_sort_duration(arr.begin(), arr.end());
        if ((int)arr.size() > N) arr.resize(N);
        return arr;
    }

private:
    vector<song> merge(vector<song>& L, vector<song>& R, string& P) {
        vector<song> result;
        int i = 0, j = 0;
        while (i < (int)L.size() && j < (int)R.size()) {
            if (P == "popularity") {
                if (L[i].popularity   > R[j].popularity)   result.push_back(L[i++]);
                else                                     result.push_back(R[j++]);
            }
            else if (P == "danceability") {
                if (L[i].danceability > R[j].danceability) result.push_back(L[i++]);
                else                                     result.push_back(R[j++]);
            }
            else if (P == "liveness") {
                if (L[i].liveness     > R[j].liveness)     result.push_back(L[i++]);
                else                                     result.push_back(R[j++]);
            }
            else if (P == "duration") {
                if (L[i].duration_ms   > R[j].duration_ms) result.push_back(L[i++]);
                else                                     result.push_back(R[j++]);
            }
        }
        while (i < (int)L.size()) result.push_back(L[i++]);
        while (j < (int)R.size()) result.push_back(R[j++]);
        return result;
    }


    template<typename AnyData>
    void quick_sort_popularity(AnyData first, AnyData last) {
        if (last - first < 2) return;
        auto midIt    = first + (last - first)/2;
        song pivot    = *first;
        song midElem  = *midIt;
        song lastElem = *(last - 1);
        if (first->popularity > midElem.popularity) {
            if (midElem.popularity > lastElem.popularity) pivot = midElem;
            else if (first->popularity > lastElem.popularity) pivot = lastElem;
        } else {
            if (first->popularity > lastElem.popularity) pivot = *first;
            else if (midElem.popularity > lastElem.popularity) pivot = lastElem;
            else pivot = midElem;
        }
        AnyData left = first, right = last - 1;
        while (left <= right) {
            while (left->popularity > pivot.popularity) ++left;
            while (pivot.popularity > right->popularity) --right;
            if (left <= right) { std::iter_swap(left, right); ++left; --right; }
        }
        quick_sort_popularity(first, right + 1);
        quick_sort_popularity(left, last);
    }


    template<typename AnyData>
    void quick_sort_danceability(AnyData first, AnyData last) {
        if (last - first < 2) return;
        auto midIt    = first + (last - first)/2;
        song pivot    = *first;
        song midElem  = *midIt;
        song lastElem = *(last - 1);
        if (first->danceability > midElem.danceability) {
            if (midElem.danceability > lastElem.danceability) pivot = midElem;
            else if (first->danceability > lastElem.danceability) pivot = lastElem;
        } else {
            if (first->danceability > lastElem.danceability) pivot = *first;
            else if (midElem.danceability > lastElem.danceability) pivot = lastElem;
            else pivot = midElem;
        }
        AnyData left = first, right = last - 1;
        while (left <= right) {
            while (left->danceability > pivot.danceability) ++left;
            while (pivot.danceability > right->danceability) --right;
            if (left <= right) { std::iter_swap(left, right); ++left; --right; }
        }
        quick_sort_danceability(first, right + 1);
        quick_sort_danceability(left, last);
    }


    template<typename AnyData>
    void quick_sort_liveness(AnyData first, AnyData last) {
        if (last - first < 2) return;
        auto midIt    = first + (last - first)/2;
        song pivot    = *first;
        song midElem  = *midIt;
        song lastElem = *(last - 1);
        if (first->liveness > midElem.liveness) {
            if (midElem.liveness > lastElem.liveness) pivot = midElem;
            else if (first->liveness > lastElem.liveness) pivot = lastElem;
        } else {
            if (first->liveness > lastElem.liveness) pivot = *first;
            else if (midElem.liveness > lastElem.liveness) pivot = lastElem;
            else pivot = midElem;
        }
        AnyData left = first, right = last - 1;
        while (left <= right) {
            while (left->liveness > pivot.liveness) ++left;
            while (pivot.liveness > right->liveness) --right;
            if (left <= right) { std::iter_swap(left, right); ++left; --right; }
        }
        quick_sort_liveness(first, right + 1);
        quick_sort_liveness(left, last);
    }


    template<typename AnyData>
    void quick_sort_duration(AnyData first, AnyData last) {
        if (last - first < 2) return;
        auto midIt    = first + (last - first)/2;
        song pivot    = *first;
        song midElem  = *midIt;
        song lastElem = *(last - 1);
        if (first->duration_ms > midElem.duration_ms) {
            if (midElem.duration_ms > lastElem.duration_ms) pivot = midElem;
            else if (first->duration_ms > lastElem.duration_ms) pivot = lastElem;
        } else {
            if (first->duration_ms > lastElem.duration_ms) pivot = *first;
            else if (midElem.duration_ms > lastElem.duration_ms) pivot = lastElem;
            else pivot = midElem;
        }
        AnyData left = first, right = last - 1;
        while (left <= right) {
            while (left->duration_ms > pivot.duration_ms) ++left;
            while (pivot.duration_ms > right->duration_ms) --right;
            if (left <= right) { std::iter_swap(left, right); ++left; --right; }
        }
        quick_sort_duration(first, right + 1);
        quick_sort_duration(left, last);
    }
};

#endif // MUSICDATA_H
