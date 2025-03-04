# SPDX-License-Identifier: GPL-2.0-only
# Copyright © Interactive Echoes. All rights reserved.
# Author: mozahzah

cmake_minimum_required(VERSION 3.20)
project(IEActions VERSION 1.0.0 LANGUAGES CXX)

set(IEACTIONS_INCLUDE_EXAMPLES FALSE)

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

message("Gathering ${CMAKE_SYSTEM_NAME} specific files")
if (WIN32)
  set(IMPL_FILE 
    "Implementation/IEAction_Impl_Win.cpp"
    "Implementation/IEAction_Impl_Win.h"
  )
elseif(APPLE)
  set(IMPL_FILE 
  "Implementation/IEAction_Impl_Apple.cpp"
  "Implementation/IEAction_Impl_Apple.h"
  )
elseif(LINUX)
  set(IMPL_FILE 
  "Implementation/IEAction_Impl_Linux.cpp"
  "Implementation/IEAction_Impl_Linux.h"
  )
endif()

message("Gathering source files")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(IEActions_SOURCE_FILES "Source/IEActions.cpp")
list(APPEND IEActions_SOURCE_FILES ${IMPL_FILE})

message("Creating Library")
add_library(${PROJECT_NAME} SHARED ${IEActions_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ".")
set(IEActions_HEADER_FILES "IEActions.h")
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
if(IEACTIONS_INCLUDE_EXAMPLES)
  add_subdirectory(Examples)
endif()

message("------------------------------------------------------------\n")