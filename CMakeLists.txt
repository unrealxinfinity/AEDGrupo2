cmake_minimum_required(VERSION 3.23)
project(projetoGrupo2)

set(CMAKE_CXX_STANDARD 17)


add_executable(projetoGrupo2 main.cpp header/CSVReader.h src/CSVReader.cpp header/Flight.h src/Airport.cpp header/Airport.h src/Flights.cpp header/graph.h src/Graph.cpp header/City.h src/City.cpp header/Airline.h src/Airline.cpp)
include_directories(header src)
