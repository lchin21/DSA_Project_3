#include <iostream>
#include <vector>
#include "musicData.h"

int main() {
    MusicData musicData;
    std::string genre;
    std::string sortParameter;
    int numberOfQueriedSongs;

    std::unordered_set<std::string> availableGenres = {"world-music","turkish","trance","synth-pop","swedish",
        "songwriter","ska","singer-songwriter","show-tunes","sertanejo","sad","romance","rockabilly",
        "rock-n-roll","reggaeton","r-n-b","psych-rock","salsa","progressive-house","power-pop","pop",
        "samba","party","pagode","new-age","minimal-techno","pop-film","metalcore","metal","mandopop",
        "malay","latin","mpb","j-dance","sleep","iranian","techno","dub","drum-and-bass","kids",
        "deep-house","opera","j-rock","dance","j-pop","hardcore","country","disney","study","indie",
        "classical","goth","piano","detroit-techno","tango","afrobeat","acoustic","idm","ambient","blues",
        "children","alt-rock","rock","alternative","dubstep","spanish","indie-pop","disco","comedy","death-metal",
        "grunge","brazil","forro","k-pop","club","british","cantopop","guitar","reggae","latino",
        "anime","bluegrass","edm","chill","punk-rock","funk","black-metal","electro","trip-hop",
        "dancehall","breakbeat","electronic","emo","hard-rock","soul","j-idol","garage","folk",
        "groove","heavy-metal","german","french","gospel","grindcore","jazz","happy","hardstyle",
        "chicago-house","hip-hop","punk","honky-tonk","house","industrial","indian"};

    std::cout<<"Welcome to the song Ranker"<<std::endl;
    std::cout<<"Enter a Genre. To skip, press enter, to see a list of available genres, enter \"list\""<<std::endl;
    std::getline(std::cin, genre);
    // genre can be "/n" or "[valid genre]"

    // get genre from user
    while(true) {
        if (genre == "") {
            break;
        } else if(genre == "list") {
            for(auto it = availableGenres.begin(); it != availableGenres.end(); it++) {
                std::cout<<*it<<std::endl;
            }
            std::cout<<"Enter a Genre. To skip, press enter, to see a list of available genres, enter \"list\""<<std::endl;
        } else if(availableGenres.find(genre) == availableGenres.end()) {
            std::cout<<"Genre does not exist. To skip, press enter, to see a list of available genres, enter \"list\""<<std::endl;
        } else {
            break;
        }
        std::getline(std::cin, genre);
    }

    std::cout<<"Do you want to sort by popularity or liveness?"<<std::endl;

    while(true) {
        std::getline(std::cin, sortParameter);
        if (sortParameter == "popularity" || sortParameter == "liveness") {
            break;
        } else {
            std::cout<<"Invalid Entry. Do you want to sort by popularity or liveness?"<<std::endl;
        }
    }

    while(true) {
        std::cout<<"How many songs do you want?"<<std::endl;
        std::string temp;
        std::getline(std::cin, temp);
        numberOfQueriedSongs = std::stoi(temp);
        if(numberOfQueriedSongs > 0) {
            break;
        }
        std::cout<<"Enter an integer greater than 0."<<std::endl;
    }

    std::cout<<"Top " << numberOfQueriedSongs << " songs ";

    if (genre != "") {
        std::cout<<"in the "<< genre<<" genre ";
    }

    std::vector<song> constrainedSongs;
    if(genre != "\n") {
        for(song song : musicData.data) {
            if(song.trackGenre == genre) {
                constrainedSongs.push_back(song);
            }
        }
    }

    std::cout<<"sorted by "<<sortParameter<<std::endl;

    // call sort functions here

    std::vector<song> results;
    std::chrono::duration<double> quicksortTime;
    std::chrono::duration<double> mergesortTime;

    if (sortParameter == "popularity") {
        auto start = std::chrono::high_resolution_clock::now();
        results = musicData.quick_sort_by_popularity(numberOfQueriedSongs);
        auto end = std::chrono::high_resolution_clock::now();
        quicksortTime = end - start;

    } else if(sortParameter == "liveness") {
        auto start = std::chrono::high_resolution_clock::now();
        results = musicData.quick_sort_by_liveness(numberOfQueriedSongs);
        auto end = std::chrono::high_resolution_clock::now();
        quicksortTime = end - start;
    }

    std::cout<<"Quick Sort time: "<<quicksortTime.count()<<"seconds"<<std::endl;

    for (int i = 0; i < results.size(); i++) {
        std::cout<<i<<". ";
        std::cout<<results[i].trackName<<std::endl;
    }
}




//Quick test for quicksort

// int main() {
//     MusicData md;
//
//     const int N = 10;
//
//
//     auto topLively = md.quick_sort_by_liveness(N);
//     std::cout << "Top " << N << " songs by liveness:\n";
//     for (int i = 0; i < (int)topLively.size(); ++i) {
//         const auto &s = topLively[i];
//         std::cout
//             << i+1 << ". "
//             << s.trackName << " — " << s.artistName
//             << " (liveness=" << s.liveness
//             << ", popularity=" << s.popularity
//             << ")\n";
//     }
//
//     std::cout << "\n";
//
//
//     auto topPopular = md.quick_sort_by_popularity(N);
//     std::cout << "Top " << N << " songs by popularity:\n";
//     for (int i = 0; i < (int)topPopular.size(); ++i) {
//         const auto &s = topPopular[i];
//         std::cout
//             << i+1 << ". "
//             << s.trackName << " — " << s.artistName
//             << " (popularity=" << s.popularity
//             << ", liveness=" << s.liveness
//             << ")\n";
//     }
//
//     return 0;
// }
