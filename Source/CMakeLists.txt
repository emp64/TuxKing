# Set project name
project (TuxKing)

# Set minimum version
cmake_minimum_required (VERSION 2.8.6)

if (COMMAND cmake_policy)
  cmake_policy (SET CMP0003 NEW)
  if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
    # INTERFACE_LINK_LIBRARIES defines the link interface
    cmake_policy (SET CMP0022 NEW)
  endif ()
  if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
  # Disallow use of the LOCATION target property - therefore we set to OLD as we still need it
    cmake_policy (SET CMP0026 OLD)
    # MACOSX_RPATH is enabled by default
    cmake_policy (SET CMP0042 NEW)
  endif ()
endif ()

# Set CMake modules search path
set (CMAKE_MODULE_PATH "/home/projekty/Hry/TuxKing/CMake/Modules")

# Include Urho3D Cmake common module
include (Urho3D-CMake-common)

# Find Urho3D library
find_package (Urho3D REQUIRED)
include_directories (/home/projekty/Hry/Urho3D/Urho3D/include/Urho3D /home/projekty/Hry/Urho3D/Urho3D/include/Urho3D/ThirdParty)


# Define target name
set (TARGET_NAME TuxKing)


# Define source files
#define_source_files ()
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)

file (GLOB CPP_FILESE Events/*.cpp)
file (GLOB H_FILESE Events/*.h)

file (GLOB CPP_FILESG Game/*.cpp)
file (GLOB H_FILESG Game/*.h)

file (GLOB CPP_FILESH HUD/*.cpp)
file (GLOB H_FILESH HUD/*.h)

file (GLOB CPP_FILESM Map/*.cpp)
file (GLOB H_FILESM Map/*.h)

file (GLOB CPP_FILESS States/*.cpp)
file (GLOB H_FILESS States/*.h)

file (GLOB CPP_FILESU GUI/*.cpp)
file (GLOB H_FILESU GUI/*.h)


set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${CPP_FILESE} ${H_FILESE} ${CPP_FILESG} ${H_FILESG} ${CPP_FILESH} ${H_FILESH} ${CPP_FILESM} ${H_FILESM} ${CPP_FILESS} ${H_FILESS} ${CPP_FILESU} ${H_FILESU})

# Setup target with resource copying
setup_main_executable ()

# Setup test cases
#add_test (NAME ExternalLibAS COMMAND ${TARGET_NAME}/Data/Scripts/12_PhysicsStressTest.as -w -timeout ${URHO3D_TEST_TIME_OUT})
#add_test (NAME ExternalLibLua COMMAND ${TARGET_NAME}Data/LuaScripts/12_PhysicsStressTest.lua -w -timeout ${URHO3D_TEST_TIME_OUT})
