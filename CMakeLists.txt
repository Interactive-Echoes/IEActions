# SPDX-License-Identifier: GPL-2.0-only
# Copyright © Interactive Echoes. All rights reserved.
# Author: mozahzah

cmake_minimum_required(VERSION 3.20)
project(IEActions VERSION 1.0.0 LANGUAGES CXX)

message("\n------------------------------------------------------------")
message("IEActions\n")

message("Compiler Setup")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
message("Using Compiler: ${CMAKE_CXX_COMPILER_ID}")
message("version: ${CMAKE_CXX_COMPILER_VERSION}")
message("CXX standard: ${CMAKE_CXX_STANDARD}")
message("Working environment")
message("System name: ${CMAKE_SYSTEM_NAME}")
message("System version: ${CMAKE_SYSTEM_VERSION}")
message("System processor: ${CMAKE_SYSTEM_PROCESSOR}")

message("\nGathering ${CMAKE_SYSTEM_NAME} specific files")
file(GLOB IEActions_IMPL_CPP_FILES "Implementation/*.cpp")

message("\nGathering source files")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
file(GLOB IEActions_SOURCE_FILES "Source/*.cpp")
list(APPEND IEActions_SOURCE_FILES ${IEActions_IMPL_CPP_FILES})

message("Creating Library and setting compile time definitions")
add_library(${PROJECT_NAME} SHARED ${IEActions_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ".")
file(GLOB IEActions_HEADER_FILES "IEActions.h")
set_property(TARGET ${PROJECT_NAME} PROPERTY PUBLIC_HEADER ${IEActions_HEADER_FILES})

message("Linking ${CMAKE_SYSTEM_NAME} specific libraries")
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PUBLIC ole32 uuid)
elseif(APPLE)
  set(CMAKE_OSX_SYSROOT /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk)
  find_library(COREAUDIO_LIBRARY CoreAudio)
  target_link_libraries(${PROJECT_NAME} PUBLIC ${COREAUDIO_LIBRARY})
elseif(LINUX)
  message("Including Third Party Libraries")
  add_subdirectory(ThirdParty/IEAudio4Linux)
  target_link_libraries(${PROJECT_NAME} PUBLIC IEAudio4Linux)
endif()

message("Setting up install")
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
include(InstallRequiredSystemLibraries)

message("Adding extra directories")
add_subdirectory(Examples)

message("------------------------------------------------------------\n")