cmake_minimum_required(VERSION 3.18)
project(NGU_TeamBook LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    include(CTest)

    # TODO: docs and pdf-version
endif()

set(PROJECT_INCLUDE_DIR "include/ngu_teambook")

include(FetchContent)

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR NGU_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()