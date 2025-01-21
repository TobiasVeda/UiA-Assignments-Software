cmake_minimum_required(VERSION 3.26)
project(assignment_3_1)

set(CMAKE_CXX_STANDARD 17)

# SQLite3 library
add_library(SQLite3 SQLite3/sqlite3.c)
target_include_directories(SQLite3 PUBLIC SQLite3)
# library name, allows to use include correct in when in wrapper,folder name

if (UNIX)
    target_link_libraries(SQLite3 pthread dl)
endif (UNIX)


# SQLiteCpp library
add_library(SQLiteCpp
        SQLiteCpp/src/Backup.cpp
        SQLiteCpp/src/Column.cpp
        SQLiteCpp/src/Database.cpp
        SQLiteCpp/src/Exception.cpp
        SQLiteCpp/src/Savepoint.cpp
        SQLiteCpp/src/Statement.cpp
        SQLiteCpp/src/Transaction.cpp
)
target_include_directories(SQLiteCpp PUBLIC SQLiteCpp/include)
target_link_libraries(SQLiteCpp SQLite3)


add_executable(assignment_3_1 main.cpp)
target_link_libraries(assignment_3_1 SQLiteCpp SQLite3)