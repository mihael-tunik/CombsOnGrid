cmake_minimum_required(VERSION 3.29)

project(combs_on_grid)

set(SOURCES
   src/comb_gen.cpp
   src/condition.cpp
   src/hash.cpp
   src/utils.cpp
)

set(TARGET_MAIN
   src/combs_on_grid.cpp
)

set(TARGET_REDUCER
   src/reducer.cpp
)

set(CMAKE_CXX_FLAGS "-Ofast -ffast-math")

add_executable(combs_on_grid ${TARGET_MAIN} ${SOURCES})
add_executable(reducer ${TARGET_REDUCER} ${SOURCES})

target_include_directories(combs_on_grid
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
