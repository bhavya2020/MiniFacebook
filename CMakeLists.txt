cmake_minimum_required(VERSION 3.15)
project(MiniFacebookV2)

set(CMAKE_CXX_STANDARD 14)
add_executable(MiniFacebookV2 main.cpp objects/classes/FriendRequest.cpp objects/classes/Mail.cpp objects/classes/Person.cpp objects/classes/Post.cpp objects/classes/Score.cpp)
