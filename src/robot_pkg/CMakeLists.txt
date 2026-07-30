cmake_minimum_required(VERSION 3.8)
project(robot_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(base_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

# add_executable(robot_server src/robot_server.cpp)
# ament_target_dependencies(robot_server rclcpp base_interfaces)

add_executable(robot_brain src/robot_brain.cpp)
ament_target_dependencies(robot_brain rclcpp base_interfaces sensor_msgs)
# --- Install Section ---
install(TARGETS
  # robot_server
  robot_brain
  DESTINATION lib/${PROJECT_NAME}
)
install(
  DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
