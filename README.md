# Sports Tournament Simulator

An Object-Oriented C++ application that simulates a complete sports tournament. The system handles everything from player and team management to live match simulation and points table calculation, all presented through a graphical user interface.

## Core Features
* **Player & Team Management:** Dynamically create and manage teams and individual player rosters.
* **Match Simulation:** Run games and generate detailed post-match scorecards.
* **Points Table Calculation:** Automatically update tournament standings based on match outcomes.
* **Graphical UI & Audio:** Fully interactive frontend built with SFML, featuring welcome screens, fixture displays, and winner announcements alongside background audio.

## Tech Stack
* **Language:** C++
* **Libraries:** SFML (Graphics, Window, Audio, System)
* **Architecture:** Object-Oriented Programming (OOP), separating core backend logic from frontend UI rendering.

## How to Build

Using `g++` (ensure SFML libraries are correctly linked in your environment or use the provided `compile.bat`):
```bash
g++ src/*.cpp -o SportsTournamentSimulator
