#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include "musicData.h"

int main() {
    MusicData musicData;
    std::string genre;
    std::string sortParameter;
    std::string sortOrder;
    int numberOfQueriedSongs;

    std::unordered_set<std::string> availableGenres = {
        "world-music","turkish","trance","synth-pop","swedish",
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
        "chicago-house","hip-hop","punk","honky-tonk","house","industrial","indian"
    };

    std::cout << "Welcome to the Song Sort-Scovery\n";
    std::cout << "Enter a Genre. To skip, press enter, to see a list of available genres, enter \"list\"\n";
    std::getline(std::cin, genre);
    while (true) {
        if (genre.empty()) break;
        if (genre == "list") {
            for (auto &g : availableGenres) std::cout << g << "\n";
            std::cout << "Enter a Genre… or \"list\" again:\n";
        } else if (!availableGenres.count(genre)) {
            std::cout << "Genre does not exist. Try again or press enter to skip:\n";
        } else break;
        std::getline(std::cin, genre);
    }


    std::vector<song> constrainedSongs;
    if (!genre.empty()) {
        for (auto &s : musicData.data)
            if (s.trackGenre == genre)
                constrainedSongs.push_back(s);
    } else {
        constrainedSongs = musicData.data;
    }


    std::cout << "Sort by popularity, danceability, liveness or duration?\n";
    while (true) {
        std::getline(std::cin, sortParameter);
        if (sortParameter == "popularity"
         || sortParameter == "danceability"
         || sortParameter == "liveness"
         || sortParameter == "duration") break;
        std::cout << "Invalid. Choose: popularity, danceability, liveness, duration.\n";
    }


    std::cout << "Sort by most or the least " << sortParameter << "?\n";
    std::cout << "Note: Selecting most prints the highest values of your sorting choice first\n";
    while (true) {
        std::getline(std::cin, sortOrder);
        if (sortOrder == "most" || sortOrder == "least") break;
        std::cout << "Invalid. Enter \"most\" or \"least\":\n";
    }


    std::cout << "How many songs do you want?\n";
    while (true) {
        std::string tmp;
        std::getline(std::cin, tmp);
        numberOfQueriedSongs = std::stoi(tmp);
        if (numberOfQueriedSongs > 0) break;
        std::cout << "Enter an integer greater than 0.\n";
    }

    std::cout << "\nloading...\n\n";
    std::vector<song> quickResults, mergeResults;
    std::chrono::duration<double> qt, mt;


    {
        auto t0 = std::chrono::high_resolution_clock::now();
        if (sortOrder == "most") {
            quickResults = musicData.quick_sort_subset(
                constrainedSongs,
                sortParameter,
                numberOfQueriedSongs
            );
        } else {
            auto fullDesc = musicData.quick_sort_subset(
                constrainedSongs,
                sortParameter,
                (int)constrainedSongs.size()
            );
            std::vector<song> bottom(
                fullDesc.end() - numberOfQueriedSongs,
                fullDesc.end()
            );
            quickResults = { bottom.rbegin(), bottom.rend() };
        }
        qt = std::chrono::high_resolution_clock::now() - t0;
    }


    {
        auto t0 = std::chrono::high_resolution_clock::now();
        auto fullMerge = musicData.mergeSort(constrainedSongs, sortParameter);
        if (sortOrder == "most") {
            mergeResults = fullMerge;
            if ((int)mergeResults.size() > numberOfQueriedSongs)
                mergeResults.resize(numberOfQueriedSongs);
        } else {
            std::vector<song> bottom(
                fullMerge.end() - numberOfQueriedSongs,
                fullMerge.end()
            );
            mergeResults = { bottom.rbegin(), bottom.rend() };
        }
        mt = std::chrono::high_resolution_clock::now() - t0;
    }


    std::cout << "Top " << numberOfQueriedSongs
              << (genre.empty() ? " songs " : " songs in the \"" + genre + "\" genre ")
              << sortOrder << " " << sortParameter << "\n\n";

    std::cout << "Quick Sort time: " << qt.count() << " seconds\n";
    std::cout << "Merge Sort time: " << mt.count() << " seconds\n\n";

    //Quick Sort Results
    std::cout << "Quick Sort Results\n";
    for (int i = 0; i < (int)quickResults.size(); ++i) {
        auto &s = quickResults[i];
        std::cout << (i+1) << ". " << s.trackName
                  << " by " << s.artistName << " — ";
        if (sortParameter == "popularity")        std::cout << "Popularity: " << s.popularity << "\n";
        else if (sortParameter == "danceability") std::cout << "Danceability: " << s.danceability << "\n";
        else if (sortParameter == "liveness")     std::cout << "Liveness: " << s.liveness << "\n";
        else /* duration */                        std::cout << "Duration: " << s.duration_ms << " ms\n";
    }

    //Merge Sort Results
    std::cout << "\nMerge Sort Results\n";
    for (int i = 0; i < numberOfQueriedSongs; ++i) {
        auto &s = mergeResults[i];
        std::cout << (i+1) << ". " << s.trackName
                  << " by " << s.artistName << " — ";
        if (sortParameter == "popularity")        std::cout << "Popularity: " << s.popularity << "\n";
        else if (sortParameter == "danceability") std::cout << "Danceability: " << s.danceability << "\n";
        else if (sortParameter == "liveness")     std::cout << "Liveness: " << s.liveness << "\n";
        else std::cout << "Duration: " << s.duration_ms << " ms\n";
    }

    return 0;
}
