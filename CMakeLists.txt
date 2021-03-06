cmake_minimum_required(VERSION 3.1.0)

project(Fespp)

set (FESPP_ROOT_DIR ${CMAKE_SOURCE_DIR})
set (FESPP_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# -----------------------------------------------------------------------------
# Disable deprecation warnings for standard C and STL functions in VS2005 and
# later (no, we don't need IF(CMAKE_COMPILER_2005) ... )
# -----------------------------------------------------------------------------
add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
add_definitions(-D_SCL_SECURE_NO_DEPRECATE)

IF (UNIX)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.6 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.6)
		add_compile_options(-std=c++11)
	else ()
		add_compile_options(-std=gnu++0x)
	endif()
	add_compile_options(-fPIC)
ENDIF (UNIX)

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET (CMAKE_INSTALL_PREFIX ${FESPP_BINARY_DIR}/install CACHE PATH "Fespp install prefix" FORCE)
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# ============================================================================
# checking for required dependencies
# ============================================================================

# -- FESAPI --
SET(FESAPI_INCLUDE FESAPI_INCLUDE-NOTFOUND CACHE PATH "Path to the directory which contains the FESAPI header files")
IF (NOT IS_DIRECTORY ${FESAPI_INCLUDE})
	MESSAGE(WARNING "The Fesapi include dir does not look to be a valid directory. Please modify it.")
ENDIF ()
SET(FESAPI_LIBRARY FESAPI_LIBRARY-NOTFOUND CACHE FILEPATH "Path to the file which contains the FESAPI library release")
IF (NOT EXISTS ${FESAPI_LIBRARY})
	MESSAGE(WARNING "The Fesapi library does not look to be a valid file. Please modify it.")
ENDIF ()

# path to custom find_package modules
SET (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(Fesapi REQUIRED)

# -- ParaView --
IF (ParaView_SOURCE_DIR)
  # we are building from within ParaView Source. The environment is already set.
  # Nothing more to do.
ELSE (ParaView_SOURCE_DIR)
  find_package(ParaView REQUIRED)
  include ("${PARAVIEW_USE_FILE}")
  include (ParaViewPlugins)

  # Load information about VTK/ParaView modules loaded/available.
  pv_setup_module_environment("Fespp")
ENDIF (ParaView_SOURCE_DIR)


# -----------------------------------------------------------------------------
# Process all vtk-modules defined in this plugin. This generates the necessary
# wrappings for all these modules as well.
# -----------------------------------------------------------------------------
pv_process_modules()


SET (WITH_ETP OFF CACHE BOOL "Only if Fesapi build with ETP support... for build Fespp with ETP support.")

IF (WITH_ETP)

	message ("WARNING: ETP support only if FESAPI build with ETP support")
	add_compile_definitions (WITH_ETP)

	# -- Boost DEPENDENCY --
	SET (BOOST_INCLUDE_DIR BOOST_INCLUDE_DIR-NOTFOUND CACHE PATH "Path to the directory which contains the BOOST header files")
	IF (NOT IS_DIRECTORY ${BOOST_INCLUDE_DIR})
		MESSAGE(WARNING "The BOOST include dir (BOOST_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
	ENDIF ()
	SET (BOOST_SYSTEM_LIBRARY BOOST_SYSTEM_LIBRARY-NOTFOUND CACHE FILEPATH "Path to the file which contains the Boost system static library release")
	IF (NOT EXISTS ${BOOST_SYSTEM_LIBRARY})
		MESSAGE(WARNING "The BOOST library (BOOST_SYSTEM_LIBRARY variable) does not look to be a valid file. Please modify it.")
	ENDIF ()	
	
	# -- avro DEPENDENCY --
	SET (AVRO_INCLUDE_DIR AVRO_INCLUDE_DIR-NOTFOUND CACHE PATH "Path to the directory which contains the avro header files")
	IF (NOT IS_DIRECTORY ${AVRO_INCLUDE_DIR})
		MESSAGE(WARNING "The Avro include dir (AVRO_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
	ENDIF ()
	SET (AVRO_LIBRARY_RELEASE AVRO_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the avro library release")
	IF (NOT EXISTS ${AVRO_LIBRARY_RELEASE})
		MESSAGE(WARNING "The avro library (AVRO_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
	ENDIF ()
ENDIF (WITH_ETP)

# ============================================================================
# compilation options
# ============================================================================

# Build with Multiple Processes on windows
IF (WIN32)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
ENDIF (WIN32)

# -----------------------------------------------------------------------------
# Build the Paraview plugins
# -----------------------------------------------------------------------------
add_subdirectory(src)
#
