cmake_minimum_required(VERSION 2.6)
project (RemoteTcpLogger)

#define Sources
set (LOGGER_SRC   TcpClientLogger.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -Wall -Werror")

#compiling step
add_executable(RemoteTcpLogger ${LOGGER_SRC})
