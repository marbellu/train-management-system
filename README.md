# Train Management System
## Project overview

This project is an implementation of a train station management system, developed as part of an algorithms course. The system manages train stations, their regional organization, and train routes, with a focus on efficient data handling and search operations. The implementation is split between main data structure handling (```datastructures.cc/hh```) and the program interface (```mainprogram.cc/hh```), with a graphical interface implemented using Qt (```mainwindow.cc/hh/ui```).

## Features

The system allows users to:
  - Manage train stations with their locations and schedule information
  - Organize stations into hierarchical regions and subregions
  - Track train departures and arrivals at different stations
  - Search for stations based on various criteria (alphabetically, by distance)
  - Find routes between stations using different search algorithms
  - View and manage regional relationships between stations

## Prerequisites
To build and run this project, you need:

  - A modern C++ compiler 
  - Qt Framework installed (the project uses Qt for GUI)
  - qmake (comes with Qt installation)
  - Valgrind (optional, for memory testing on Linux)

## Getting Started

1. Build the project:
   ```
   qmake
   make
   ```
2. Try out the system using provided example data:
   ```
   ./prg1 example-data/example_stations.txt
   ```

## Testing

The project comes with comprehensive test data in multiple categories:
  - ```example-data/``` contains sample data files to explore the system's functionality
  - ```functionality-compulsory/``` and ```integration-compulsory/``` contain the main test cases
  - Additional optional test cases are available in the  ```-optional``` folders

Memory testing can be performed using Valgrind:
```
valgrind --leak-check=full ./prg1 [test_file]
```
