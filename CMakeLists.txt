cmake_minimum_required(VERSION 3.14)
project(HotelMgrSystem)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Fetch xlnt
FetchContent_Declare(
  xlnt
  GIT_REPOSITORY https://github.com/tfussell/xlnt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(xlnt)

# Fetch tabulate
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG master
)
FetchContent_MakeAvailable(tabulate)

# Add your main.cpp or other source files
add_executable(HotelMgrSystem main.cpp src/Customer.cpp src/Room.cpp src/User.cpp src/ExcelUtils.cpp src/MenuUtils.cpp src/Input.cpp
)
# Tell the compiler where to find all the headers 
target_include_directories(HotelMgrSystem PRIVATE include )
# Link libraries
target_link_libraries(HotelMgrSystem PRIVATE xlnt tabulate)

add_custom_command(TARGET HotelMgrSystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/build/_deps/xlnt-build/source/Release/xlnt.dll"
        $<TARGET_FILE_DIR:HotelMgrSystem>)