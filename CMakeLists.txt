cmake_minimum_required(VERSION 3.29)
project(Data_Structures_Final)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(Data_Structures_Final
        src/main.cpp
        src/AVL.cpp
        src/BST.cpp
        src/BTree.cpp
        src/Heap.cpp
        src/GUIManager.cpp
        src/Menu.cpp
        src/PriorityQueue.cpp
        src/RedBlack.cpp
        src/StackQueue.cpp
)


# Link SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(Data_Structures_Final sfml-graphics sfml-window sfml-system)