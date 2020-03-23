cmake_minimum_required(VERSION 3.10)

project(mavlinkbridge)

include_directories(src mavlink mavlink/common gcomm)
add_executable(mavlinkbridge src/CommLink.cc  src/main.cc  src/MAVLinkBridge.cc  src/SerialComm.cc  src/UDPComm.cc)
target_link_libraries(mavlinkbridge pthread)
