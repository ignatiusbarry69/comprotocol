add_library(comprotocol STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tlv.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tllv.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command_frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/response_frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/comprotocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/comprotocolC.cpp

)

target_include_directories(comprotocol
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)
