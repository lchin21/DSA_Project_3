#include <iostream>
#include "musicData.h"

int main() {
    MusicData musicData;
    std::cout<<musicData.data[0].artistName<<std::endl;
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
