cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_FLAGS "-std=c++14" )



project("TestProject")
set(APP_NAME TestProject)
set(SOURCE_DIR ./src)

# Set Env----------------------------------------------------------------------



file(GLOB_RECURSE userdata_c_srcs ${SOURCE_DIR}/*.cpp)




# Application
set(ALL_COMPILE_SRC
    ${userdata_c_srcs}
     
)

# Build-------------------------------------------------------------------------


# Add lib-----------------------------------------------------------------------
add_executable(${APP_NAME} ${ALL_COMPILE_SRC})

