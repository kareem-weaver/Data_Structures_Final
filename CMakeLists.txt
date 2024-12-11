cmake_minimum_required(VERSION 3.29)
project(DataStructuresFinalTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataStructuresFinalTest src/main.cpp
        src/GUIManager.cpp
        src/AVL.cpp
        src/BST.cpp
        src/Menu.cpp
        src/PriorityQueue.cpp
        RedBlack.cpp
        src/Stack.cpp)
