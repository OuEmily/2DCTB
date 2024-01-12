add_library(cement cement.cpp include/cement/cement.hpp)
set_property(TARGET cement PROPERTY CXX_STANDARD 20) 
target_include_directories(cement PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS cement
        DESTINATION lib)
#target_link_libraries(cement  PRIVATE OpenGL::GL)
target_link_libraries( cement ${OpenCV_LIBS})
target_link_libraries(cement ${Boost_LIBRARIES})
