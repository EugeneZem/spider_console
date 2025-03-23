cmake_minimum_required (VERSION 3.20)

project (Spider)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON)

set(Boost_USE_MULTITHREADED ON)

#set(BOOST_ROOT D:\development\boost-build)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} D:\\Developments\\boost_1_87_0)
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} D:\\Developments\\boost_1_87_0\\stage\\lib)

#FIND_PACKAGE(Boost)
#IF (Boost_FOUND)
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#    ADD_DEFINITIONS( "-DHAS_BOOST" )
#ENDIF()

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(PostgreSQL_ADDITIONAL_VERSION "17")

add_subdirectory(D:\\Projects\\libpqxx-7.9.2 pqxx-build)

add_executable (Spider 
        Spider.cpp 
        Model/DataBase.h 
        Model/DataBase.cpp 
        Model/Indexer.h
        Model/Indexer.cpp
        Model/NetClient.h
        Model/NetClient.cpp
    )

target_compile_features(Spider PRIVATE cxx_std_17)

target_include_directories(Spider PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(Spider 
        pqxx
        ${Boost_LIBRARIES}
    )
