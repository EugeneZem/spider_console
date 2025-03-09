cmake_minimum_required (VERSION 3.20)

set(PostgreSQL_ADDITIONAL_VERSION "17")

project (Spider)

add_subdirectory(D:\\Projects\\libpqxx-7.9.2 pqxx-build)

add_executable (Spider Spider.cpp Spider.h Model/DataBase.h Model/DataBase.cpp)

target_compile_features(Spider PRIVATE cxx_std_17)

target_link_libraries(Spider pqxx)