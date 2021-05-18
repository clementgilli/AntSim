cmake_minimum_required(VERSION 3.0)

project(ant-colony VERSION 0.0.1)

set(SRCS
    src/controllers/manager.cpp
    
    src/models/coord.cpp
    src/models/fourmi.cpp
    src/models/place.cpp

    src/views/affichage.cpp    
)

set(HEADERS

    src/controllers/manager.hpp

    src/models/coord.hpp
    src/models/fourmi.hpp
    src/models/place.hpp

    src/views/affichage.hpp
)

set(TESTS
    tests/test.cpp

    tests/models/coord.cpp
    tests/models/fourmi.cpp
    tests/models/place.cpp

    tests/controllers/manager.cpp
)

set(LIBS
    sfml-system
    sfml-graphics
    sfml-window
)

add_executable(ant_sim src/main.cpp ${SRCS} ${HEADERS})
target_compile_features(ant_sim PRIVATE cxx_std_17)
target_include_directories(ant_sim PUBLIC src/)
target_link_libraries(ant_sim ${LIBS})

# Make test executable

# tests
add_executable(run_tests ${TESTS} ${SRCS} ${HEADERS} tests/doctest.h)
target_compile_features(run_tests PRIVATE cxx_std_17)
target_include_directories(run_tests PUBLIC src/ tests/)
target_link_libraries(run_tests PRIVATE ${LIBS})