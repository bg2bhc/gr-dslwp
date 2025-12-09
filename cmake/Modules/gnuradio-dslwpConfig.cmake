find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_DSLWP gnuradio-dslwp)

FIND_PATH(
    GR_DSLWP_INCLUDE_DIRS
    NAMES gnuradio/dslwp/api.h
    HINTS $ENV{DSLWP_DIR}/include
        ${PC_DSLWP_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_DSLWP_LIBRARIES
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

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-dslwpTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_DSLWP DEFAULT_MSG GR_DSLWP_LIBRARIES GR_DSLWP_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_DSLWP_LIBRARIES GR_DSLWP_INCLUDE_DIRS)
