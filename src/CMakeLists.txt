file(GLOB_RECURSE SRC_FILES *.cpp)

add_executable(${PROJECT_NAME}_exec ${SRC_FILES})

# ajout des a inclure -> include qui contient les .h et date qui contient les ressourses
target_include_directories(${PROJECT_NAME}_exec PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/data)


# find pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# Add ImGui-SFML and pthread
target_link_libraries(${PROJECT_NAME}_exec PRIVATE ImGui-SFML::ImGui-SFML ${CMAKE_THREAD_LIBS_INIT})
