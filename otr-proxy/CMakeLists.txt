include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(KTpProxy)
add_subdirectory(data)
if (KDE4_BUILD_TESTS)
add_subdirectory(test)
endif ()
