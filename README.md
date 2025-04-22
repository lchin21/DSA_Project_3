Song Sort-Scovery

A C++ command‑line tool that helps music lovers discover songs by sorting a large dataset of tracks according to popularity, danceability, liveness, or duration and choosing either the most or least of that metric.


Features:

-Load and parse a CSV file of over 100,000 tracks

-Filter by genre (125+ supported genres)

-Sort by four different audio features:

-Popularity (0–100)

-Danceability (0.0–1.0)

-Liveness (0.0–1.0)

-Duration (milliseconds)

-Choose “most” (descending) or “least” (ascending)

-Compare Quick‑Sort vs. Merge‑Sort performance


Requirements:

-A C++17‑compatible compiler

-CMake 3.15 or higher

-A modern terminal (UTF-8 enabled for non ASCII characters)


Running in an IDE (CLION):

1.Open the DSA_Project_3 folder as a project in CLion.

2.Let CLion automatically detect the CMakeLists.txt file and configure the project.

3.Build the project by clicking the build button or selecting the play button.

4.Run the executable by clicking the play button or selecting Run 'DSA_Project_3'.

5.View the console pane in CLion to interact with the program.


DSA_Project_3/

-CMakeLists.txt      # build configuration

-musicData.h         # data loader & sorting algorithms

-main.cpp            # command‑line interface

-music.csv           # dataset of tracks


