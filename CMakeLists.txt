cmake_minimum_required(VERSION 3.25)
project(UNO)

set(CMAKE_CXX_STANDARD 17)

add_executable(UNO "Entities/Game.cpp" "Logic layer/GameRunner.cpp" "Presentation Layer/GameView.cpp" main.cpp Common/Helpers/EnumToStringHelpers.h Entities/Game.cpp)
