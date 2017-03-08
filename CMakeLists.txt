cmake_minimum_required(VERSION 3.6)
project(dns)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    answer.cpp
    answer.h
    dns.cpp
    dns.h
    dnsd.cpp
    dnsDb.cpp
    dnsDb.h
    header.cpp
    header.h
    log.cpp
    log.h
    message.cpp
    message.h
    question.cpp
    question.h
    rr.cpp
    rr.h)

add_executable(dns ${SOURCE_FILES})