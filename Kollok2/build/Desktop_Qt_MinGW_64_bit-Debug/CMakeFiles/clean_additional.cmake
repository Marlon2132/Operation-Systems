# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Kollok2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Kollok2_autogen.dir\\ParseCache.txt"
  "Kollok2_autogen"
  )
endif()
