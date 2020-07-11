file(GLOB STRINGS_HEADER_LIST "${NGU_TeamBook_SOURCE_DIR}/include/ngu_teambook/strings/*.hpp")
file(GLOB STRINGS_SOURCE_LIST strings/*)

add_library(strings ${STRINGS_SOURCE_LIST} ${STRINGS_HEADER_LISTS})
target_include_directories(strings PUBLIC ../include)
target_compile_features(strings PUBLIC cxx_std_17)

add_library(NGU_TeamBook::Strings ALIAS strings)