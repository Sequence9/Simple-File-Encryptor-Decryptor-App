# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FileEncryption_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FileEncryption_autogen.dir\\ParseCache.txt"
  "FileEncryption_autogen"
  )
endif()
