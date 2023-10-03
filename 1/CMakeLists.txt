cmake_minimum_required(VERSION 3.20)


#set(PostgreSQL_ADDITOINAL_VERSIONS "15")

project(p1)



add_executable(p1 1.cpp table.h table.cpp)

add_subdirectory(C:\\libpqxx-7.8.1 libpqxx-build) # Укажите путь к libpq++

target_compile_features(p1 PRIVATE cxx_std_17) # Включите C++17

target_link_libraries(p1 pqxx)  # Слинкуйте libpq++ к проекту