@echo off
echo Compiling Sports Tournament Simulator...

REM Create directories
if not exist "build" mkdir build
if not exist "build\core" mkdir build\core
if not exist "build\ui" mkdir build\ui
if not exist "bin" mkdir bin
if not exist "data" mkdir data

REM Compile core files
echo Compiling core files...
g++ -std=c++17 -Wall -Isrc -c src/core/Player.cpp -o build/core/Player.o
g++ -std=c++17 -Wall -Isrc -c src/core/Team.cpp -o build/core/Team.o
g++ -std=c++17 -Wall -Isrc -c src/core/Match.cpp -o build/core/Match.o
g++ -std=c++17 -Wall -Isrc -c src/core/Scorecard.cpp -o build/core/Scorecard.o
g++ -std=c++17 -Wall -Isrc -c src/core/PointsTable.cpp -o build/core/PointsTable.o
g++ -std=c++17 -Wall -Isrc -c src/core/Tournament.cpp -o build/core/Tournament.o
g++ -std=c++17 -Wall -Isrc -c src/core/FileManager.cpp -o build/core/FileManager.o

REM Compile UI files
echo Compiling UI files...
g++ -std=c++17 -Wall -Isrc -c src/ui/MainScreen.cpp -o build/ui/MainScreen.o
g++ -std=c++17 -Wall -Isrc -c src/ui/TeamRegistrationScreen.cpp -o build/ui/TeamRegistrationScreen.o
g++ -std=c++17 -Wall -Isrc -c src/ui/MatchFixturesScreen.cpp -o build/ui/MatchFixturesScreen.o
g++ -std=c++17 -Wall -Isrc -c src/ui/StandingsScreen.cpp -o build/ui/StandingsScreen.o
g++ -std=c++17 -Wall -Isrc -c src/ui/InteractiveMatchScreen.cpp -o build/ui/InteractiveMatchScreen.o
g++ -std=c++17 -Wall -Isrc -c src/ui/matchresultscreen.cpp -o build/ui/matchresultscreen.o
g++ -std=c++17 -Wall -Isrc -c src/ui/playerlistscreen.cpp -o build/ui/playerlistscreen.o
g++ -std=c++17 -Wall -Isrc -c src/ui/tournamentwinnerscreen.cpp -o build/ui/tournamentwinnerscreen.o

REM Compile main
echo Compiling main.cpp...
g++ -std=c++17 -Wall -Isrc -c src/main.cpp -o build/main.o

REM Link everything
echo Linking...
g++ build/core/*.o build/ui/*.o build/main.o -o bin/tournament.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

if %errorlevel% == 0 (
    echo.
    echo Build successful!
    echo Executable: bin\tournament.exe
    echo.
    echo To run: bin\tournament.exe
) else (
    echo.
    echo Build failed!
)

pause