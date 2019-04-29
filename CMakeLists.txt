CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

PROJECT(UnivLib)

# Set generic sources
FILE(GLOB GENERIC_SOURCES source/all/*.c)

# Scan for the required files dependent on architecture
IF (WIN32)
    FILE(GLOB PLATFORM_SOURCES source/windows/*.c)

    IF (MSVC)
        # Add multi-processor compilation.
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    ENDIF ()
ELSE()
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

    FILE(GLOB PLATFORM_SOURCES source/linux/*.c)
ENDIF()

# Set include directory
INCLUDE_DIRECTORIES ("${CMAKE_SOURCE_DIR}" "include")

# And finally the source files for the project
SET(PROJECT_SOURCES ${GENERIC_SOURCES} ${PLATFORM_SOURCES})
ADD_LIBRARY (UnivLib ${PROJECT_SOURCES})

# Add the tests
ADD_SUBDIRECTORY(tests)
