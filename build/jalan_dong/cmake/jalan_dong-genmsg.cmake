# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "jalan_dong: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ijalan_dong:/home/mfikih15/Documents/mekatron/src/jalan_dong/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(jalan_dong_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg" NAME_WE)
add_custom_target(_jalan_dong_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "jalan_dong" "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(jalan_dong
  "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jalan_dong
)

### Generating Services

### Generating Module File
_generate_module_cpp(jalan_dong
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jalan_dong
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(jalan_dong_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(jalan_dong_generate_messages jalan_dong_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg" NAME_WE)
add_dependencies(jalan_dong_generate_messages_cpp _jalan_dong_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jalan_dong_gencpp)
add_dependencies(jalan_dong_gencpp jalan_dong_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jalan_dong_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(jalan_dong
  "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jalan_dong
)

### Generating Services

### Generating Module File
_generate_module_eus(jalan_dong
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jalan_dong
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(jalan_dong_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(jalan_dong_generate_messages jalan_dong_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg" NAME_WE)
add_dependencies(jalan_dong_generate_messages_eus _jalan_dong_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jalan_dong_geneus)
add_dependencies(jalan_dong_geneus jalan_dong_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jalan_dong_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(jalan_dong
  "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jalan_dong
)

### Generating Services

### Generating Module File
_generate_module_lisp(jalan_dong
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jalan_dong
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(jalan_dong_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(jalan_dong_generate_messages jalan_dong_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg" NAME_WE)
add_dependencies(jalan_dong_generate_messages_lisp _jalan_dong_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jalan_dong_genlisp)
add_dependencies(jalan_dong_genlisp jalan_dong_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jalan_dong_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(jalan_dong
  "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jalan_dong
)

### Generating Services

### Generating Module File
_generate_module_nodejs(jalan_dong
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jalan_dong
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(jalan_dong_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(jalan_dong_generate_messages jalan_dong_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg" NAME_WE)
add_dependencies(jalan_dong_generate_messages_nodejs _jalan_dong_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jalan_dong_gennodejs)
add_dependencies(jalan_dong_gennodejs jalan_dong_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jalan_dong_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(jalan_dong
  "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jalan_dong
)

### Generating Services

### Generating Module File
_generate_module_py(jalan_dong
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jalan_dong
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(jalan_dong_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(jalan_dong_generate_messages jalan_dong_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mfikih15/Documents/mekatron/src/jalan_dong/msg/image_msgs.msg" NAME_WE)
add_dependencies(jalan_dong_generate_messages_py _jalan_dong_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jalan_dong_genpy)
add_dependencies(jalan_dong_genpy jalan_dong_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jalan_dong_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jalan_dong)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jalan_dong
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(jalan_dong_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(jalan_dong_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jalan_dong)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jalan_dong
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(jalan_dong_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(jalan_dong_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jalan_dong)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jalan_dong
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(jalan_dong_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(jalan_dong_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jalan_dong)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jalan_dong
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(jalan_dong_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(jalan_dong_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jalan_dong)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jalan_dong\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jalan_dong
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(jalan_dong_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(jalan_dong_generate_messages_py sensor_msgs_generate_messages_py)
endif()
