# FindLibevent.cmake
# Locate Libevent library

# Try to find Libevent library
find_path(Libevent_INCLUDE_DIR NAMES event2/event.h PATH_SUFFIXES libevent)
find_library(Libevent_LIBRARY NAMES event)

# Check if Libevent was found
if (Libevent_INCLUDE_DIR AND Libevent_LIBRARY)
    set(Libevent_FOUND TRUE)
else()
    set(Libevent_FOUND FALSE)
endif()

# Provide information to CMake
if (Libevent_FOUND)
    if (NOT Libevent_FIND_QUIETLY)
        message(STATUS "Found Libevent: ${Libevent_LIBRARY}")
    endif()
else()
    if (NOT Libevent_FIND_QUIETLY)
        message(STATUS "Libevent not found.")
    endif()
endif()

# Set the include directories and libraries for Libevent
if (Libevent_FOUND)
    set(Libevent_INCLUDE_DIRS ${Libevent_INCLUDE_DIR})
    set(Libevent_LIBRARIES ${Libevent_LIBRARY})
else()
    set(Libevent_INCLUDE_DIRS)
    set(Libevent_LIBRARIES)
endif()

# Report the results to the user
mark_as_advanced(Libevent_INCLUDE_DIR Libevent_LIBRARY)
