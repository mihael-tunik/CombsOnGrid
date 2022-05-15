project(combs_on_grid)

set(SOURCES
   src/comb_gen.cpp
   src/combs_on_grid.cpp
   src/condition.cpp
   src/hash.cpp
   src/utils.cpp
)

add_executable(combs_on_grid ${SOURCES})

target_include_directories(combs_on_grid
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
