cmake_minimum_required(VERSION 3.28)

project(id3tags LANGUAGES CXX)

add_executable(id3tags id3tags.cpp)

find_package(cxxopts REQUIRED)
find_package(taglib REQUIRED)
find_package(ZLIB REQUIRED)

target_link_libraries(id3tags
	PRIVATE cxxopts::cxxopts
	PRIVATE TagLib::TagLib
)

install(TARGETS id3tags)
