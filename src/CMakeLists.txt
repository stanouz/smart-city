include(FetchContent)



# find sfml
find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)

if(SFML_FOUND)
    message(STATUS "SFML found")

    file(GLOB_RECURSE SRC_FILES *.cpp)
    add_executable(${PROJECT_NAME}_exec ${SRC_FILES})

    # ajout des a inclure -> include qui contient les .h et date qui contient les ressourses
    target_include_directories(${PROJECT_NAME}_exec PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/data)

    # on recupère imgui
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
    )
    FetchContent_MakeAvailable(imgui)

    # on recupère imgui-sfml
    FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
        GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35
    )
    set(IMGUI_DIR ${imgui_SOURCE_DIR})
    set(IMGUI_SFML_FIND_SFML OFF)
    set(IMGUI_SFML_IMGUI_DEMO ON)
    FetchContent_MakeAvailable(imgui-sfml)

    # on cherche le package contenant pthread
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)

    # Add ImGui-SFML and pthread
    target_link_libraries(${PROJECT_NAME}_exec PRIVATE  sfml-graphics sfml-window ImGui-SFML::ImGui-SFML ${CMAKE_THREAD_LIBS_INIT})
else()
    message(STATUS "|!| SFML not found, please download it")
endif()



