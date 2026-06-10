cmake_minimum_required(VERSION 3.25)

project(FakeRewards VERSION 1.0.0 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode.git
    GIT_TAG v3.0.0-beta.1
)
FetchContent_MakeAvailable(Geode)

add_geode_mod(
    ${PROJECT_NAME}
    GD
    SOURCES
        src/main.cpp
)
