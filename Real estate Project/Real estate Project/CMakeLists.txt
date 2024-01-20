cmake_minimum_required(VERSION 3.25)
project(Project_fund2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_fund2 main.cpp Apartment.cpp Apartment.h User.cpp User.h
        BankAccount.cpp
        BankAccount.h
        Account.cpp
        Account.h)
