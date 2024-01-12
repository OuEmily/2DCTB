add_executable(cement_test "cement_test.cpp")
target_link_libraries( cement_test PRIVATE ${OpenCV_LIBS} cement ${Boost_LIBRARIES})
install(TARGETS cement_test DESTINATION bin)
include_directories(${CMAKE_SOURCE_DIR}/include)


