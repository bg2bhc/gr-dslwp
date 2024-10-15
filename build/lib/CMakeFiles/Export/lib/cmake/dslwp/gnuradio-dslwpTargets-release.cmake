#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "gnuradio::gnuradio-dslwp" for configuration "Release"
set_property(TARGET gnuradio::gnuradio-dslwp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(gnuradio::gnuradio-dslwp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libgnuradio-dslwp.so.4dd49f90"
  IMPORTED_SONAME_RELEASE "libgnuradio-dslwp.so.1.0.0git"
  )

list(APPEND _IMPORT_CHECK_TARGETS gnuradio::gnuradio-dslwp )
list(APPEND _IMPORT_CHECK_FILES_FOR_gnuradio::gnuradio-dslwp "${_IMPORT_PREFIX}/lib/libgnuradio-dslwp.so.4dd49f90" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
