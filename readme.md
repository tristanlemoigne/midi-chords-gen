# MIDI EMITTER
This project generates procedural chords progressions.
Windows only

## TODO 
- Fix generation
- Update Readme
- Make a standalone binary
- Create a first release

ABLETON
- Fix clock output with TD

TD
- Check is Sleeping
- Clean file
- add mapping tool
- perform interface
- performance optimisation

DOC
- Create 3 virtual midi ports using loop midi : LEAPDATA CLOCK NOTES
- Launch genereator before TD & Ableton to prevent errors
- Take care to select proper CmakeLists.txt configuration for cmake
- Leap motion library folder

Generate executable : 
mkdir build
cd build
cmake ..
cmake --build . ou cmake --build . --clean-first

Run executable :
`.\Debug\main` 

Build release : 
cmake --build . --target ALL_BUILD --config Release
