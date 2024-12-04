cmake_minimum_required(VERSION 3.29)
project(Data_Structures_Final)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_STANDARD True)
#
#include_directories(include)

add_executable(Data_Structures_Final
        main.cpp
        src/main.cpp
        src/Heap.cpp
        src/BST.cpp
        src/StackQueue.cpp
        src/PriorityQueue.cpp
        src/AVL.cpp
        src/BTree.cpp
        src/RedBlack.cpp
        src/GUIManager.cpp
        src/StackQueue.cpp
)

#add_executable(Data_Structures_Final)

#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
#
#target_link_libraries(Data_Structures_Final sfml-graphics sfml-window sfml-system)