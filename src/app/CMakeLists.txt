add_executable(app
    main.cpp
)

target_link_libraries(app
    PRIVATE
        comprotocol
)

target_include_directories(app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../comprotocol/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../comprotocol/include/comprotocol)
