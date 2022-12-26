cmake_minimum_required(VERSION 3.23)
project(projetoGrupo2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projetoGrupo2 main.cpp header/airportsGraph.h src/airportGraph.cpp header/CSVReader.h header/Flight.h src/Airport.cpp header/Airport.h src/Flights.cpp)
include_directories(header src)
