#
# Copyright (c) 2017 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#

# set include directories for nanoFramework Debugger
list(APPEND NF_Debugger_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/CLR/Debugger)
list(APPEND NF_Debugger_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/CLR/Include)

# source files for nanoFramework Debugger
set(NF_Debugger_SRCS

    Debugger.cpp
    Debugger_full.cpp

)

foreach(SRC_FILE ${NF_Debugger_SRCS})
    set(NF_Debugger_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(NF_Debugger_SRC_FILE ${SRC_FILE}
        PATHS 
            ${PROJECT_SOURCE_DIR}/src/CLR/Debugger

        CMAKE_FIND_ROOT_PATH_BOTH
    )
    # message("${SRC_FILE} >> ${NF_Debugger_SRC_FILE}") # debug helper
    list(APPEND NF_Debugger_SOURCES ${NF_Debugger_SRC_FILE})
endforeach()


include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(NF_Debugger DEFAULT_MSG NF_Debugger_INCLUDE_DIRS NF_Debugger_SOURCES)
