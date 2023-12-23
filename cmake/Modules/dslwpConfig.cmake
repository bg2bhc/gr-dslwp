INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DSLWP dslwp)

FIND_PATH(
    DSLWP_INCLUDE_DIRS
    NAMES dslwp/api.h
    HINTS $ENV{DSLWP_DIR}/include
        ${PC_DSLWP_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DSLWP_LIBRARIES
    NAMES gnuradio-dslwp
    HINTS $ENV{DSLWP_DIR}/lib
        ${PC_DSLWP_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/dslwpTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DSLWP DEFAULT_MSG DSLWP_LIBRARIES DSLWP_INCLUDE_DIRS)
MARK_AS_ADVANCED(DSLWP_LIBRARIES DSLWP_INCLUDE_DIRS)
