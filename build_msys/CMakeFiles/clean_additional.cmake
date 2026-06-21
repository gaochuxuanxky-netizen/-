# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\SmartPath_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SmartPath_autogen.dir\\ParseCache.txt"
  "SmartPath_autogen"
  )
endif()
