file(ARCHIVE_EXTRACT INPUT "${NGU_TeamBook_SOURCE_DIR}/assets/tests/strings/suffix_array.7z"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/strings")
file(ARCHIVE_EXTRACT INPUT "${NGU_TeamBook_SOURCE_DIR}/assets/tests/strings/lcp.7z"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/strings")
file(ARCHIVE_EXTRACT INPUT "${NGU_TeamBook_SOURCE_DIR}/assets/tests/strings/suffix_tree.7z"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/strings")
file(ARCHIVE_EXTRACT INPUT "${NGU_TeamBook_SOURCE_DIR}/assets/tests/strings/hash.7z"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/strings")


FetchContent_Declare(
        googletest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG         release-1.10.0
)

set(BUILD_MOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(teststrings test_strings.cpp)
target_link_libraries(teststrings PRIVATE NGU_TeamBook::Strings gtest)

add_test(NAME teststrings COMMAND teststrings)