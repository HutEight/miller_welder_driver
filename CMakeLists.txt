cmake_minimum_required(VERSION 2.8.3)
project(miller_welder_driver)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS odva_ethernetip roscpp sensor_msgs)

find_package(Boost 1.47 REQUIRED COMPONENTS system)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS odva_ethernetip roscpp sensor_msgs
  LIBRARIES MillerWelder
  DEPENDS Boost
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_library(MillerWelder src/MillerWelder.cpp)
target_link_libraries(MillerWelder
  ${catkin_LIBRARIES}
)

add_executable(miller_welder_node src/miller_welder_node.cpp)
target_link_libraries(miller_welder_node
  MillerWelder
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

## Mark executables and libraries for installation
install(TARGETS MillerWelder
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
