
#requirement for the cmake version
cmake_minimum_required(VERSION 3.10)

#creates a variable CMAKE_PROJECT_NAME, the name of our project
project(${PROJ_NAME})

#set(PROJ_NAME_DYNAMIC_SUFF shared)

#compiler flags
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -g -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++17 -O2 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -g -Wall -Wextra -Werror -pedantic")

# directory with header files
# our_math.h, logic.h, graphics.h teslib.h
include_directories(src/include)
# gtest.h
include_directories(src/google_test/include/gtest)

# directories with executable files
# logic.cpp, graphics.cpp, our_math.cpp teslib.cpp
add_subdirectory(src/source)
# google tests
add_subdirectory(src/google_test)

#adding target 'run' to the generated Makefile, which compiles and runs the calculator linked with static libraries
add_custom_target( run
    COMMAND ${CMAKE_PROJECT_NAME}
    DEPENDS ${CMAKE_PROJECT_NAME}
    WORKING_DIRECTORY ./bin
)

#adding target 'test' to the generated Makefile, which compiles and runs the google tests
add_custom_target( test_
    COMMAND ${CMAKE_PROJECT_NAME}_test
    DEPENDS ${CMAKE_PROJECT_NAME}_test
    WORKING_DIRECTORY ./bin
)
#adding target 'run_${PROJ_NAME_DYNAMIC_SUFF}' to the generated Makefile, which compiles and runs the calculator linked with shared libraries
add_custom_target( run_${PROJ_NAME_DYNAMIC_SUFF}
    COMMAND ${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF}
    DEPENDS ${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF}
    WORKING_DIRECTORY ./bin
)

#+++++++++++++++++++++++++++++++++++ INSTALATION ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

option(INSTALLATION "The project instalation" OFF)
option(STATIC_INSTALLATION "The project static installation" OFF)

if(INSTALLATION)

# uncomment lines 50-133 to enable and then uncomment one more time either lines 56-79 for the static installation
# or lines 81-107 for the ${PROJ_NAME_DYNAMIC_SUFF} installation and make the program again (i.e. 'make clean && make' in the src directory )

#============ either .a installation or .so installation can be performed, not both at once =====================

#creating variables for installation
    set(INSTALL_DIR "/usr/local/bin/")
    set(GRAPHICS_SOURCE_DIR src/source)
    set(SOURCE_DIR src/installation)
    set(INSTALL_DESKTOP_DIR "/usr/share/applications/")
    set(INSTALL_LIB_DIR "/usr/lib/")

#==============for static installation (with .a libraries) ===========

    if(STATIC_INSTALLATION)

# installation of the calculator application
        install(TARGETS ${CMAKE_PROJECT_NAME}
            COMPONENT linapp
            DESTINATION ${INSTALL_DIR})
        
# installation of the uninstaller script
        install(PROGRAMS ${SOURCE_DIR}/${CMAKE_PROJECT_NAME}_uninstaller
            COMPONENT linapp 
            DESTINATION ${INSTALL_DIR})

# setting the package variables
        set(DEB_PACKAGE_NAME pp_calc)
        set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CMAKE_PROJECT_NAME}")

# instalation of the .desktop file which connects the executable with icon and other data
        install(FILES ${SOURCE_DIR}/PP_calc.desktop DESTINATION ${INSTALL_DESKTOP_DIR})

# setting conflict with the other instalation (pp_calc_${PROJ_NAME_DYNAMIC_SUFF} debian package), they cannot be installed together
        set(CPACK_DEBIAN_PACKAGE_CONFLICTS "pp_calc_dynamic")
        set(CPACK_DEBIAN_PACKAGE_CONFLICTS "pp_calc")

#=============================================== end of static installation

#=================for ${PROJ_NAME_DYNAMIC_SUFF} installation (with .so libraires) ===========

    else(STATIC_INSTALLATION)

# installation of the calculator application
        install(TARGETS ${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF}
            COMPONENT linapp
            DESTINATION ${INSTALL_DIR})

# installation of the shared library    
        install(FILES ./build/lib/libgraphics-s.so DESTINATION ${INSTALL_LIB_DIR})

# installation of the uninstaller script
        install(PROGRAMS ${SOURCE_DIR}/${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF}_uninstaller
            COMPONENT linapp 
            DESTINATION ${INSTALL_DIR})

# setting the package variables
        set(DEB_PACKAGE_NAME pp_calc_dynamic)
        set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF}")
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CMAKE_PROJECT_NAME}_${PROJ_NAME_DYNAMIC_SUFF}")

# instalation of the .desktop file which connects the executable with icon and other data
        install(FILES ${SOURCE_DIR}/PP_calc.desktop DESTINATION ${INSTALL_DESKTOP_DIR})

# setting conflict with the other instalation (pp_calc debian package), they cannot be installed together
        set(CPACK_DEBIAN_PACKAGE_CONFLICTS "pp_calc")
        set(CPACK_DEBIAN_PACKAGE_CONFLICTS "pp_calc_dynamic")
    
    endif(STATIC_INSTALLATION)

#=============================================== end of ${PROJ_NAME_DYNAMIC_SUFF} installation 

#=============== reguired by both installations ==============================================================

# instalation of the graphics design file
    install(FILES ${GRAPHICS_SOURCE_DIR}/grap.glade DESTINATION ${INSTALL_DIR})
# instalation of the program icon
    install(FILES ${SOURCE_DIR}/calc_icon.ico DESTINATION ${INSTALL_DIR})

# setting the another important package variables
    set(DEB_PACKAGE_DESRCIPTION "Pied Piper calculator that can operate in two modes: Basic or Pro mode")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Pied Piper calculator that can operate in two modes: Basic or Pro mode")
    set(DEB_PACKAGE_MAINTAINER "David Mihola <xmihol00@stud.fit.vutbr.cz>")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtk-3-0 (>= 3.22)")
    set(CPACK_PACKAGE_DESCRIPTION_FILE "../README.md")
    set(CPACK_RESOURCE_FILE_LICENSE "../LICENSE.txt")
    set(CPACK_PACKAGE_ICON "${SOURCE_DIR}/calc_icon_doc.ico")
    set(CPACK_PACKAGE_VERSION_MAJOR 1)
    set(CPACK_PACKAGE_VERSION_MINOR 0)
    set(CPACK_PACKAGE_VERSION_PATCH 0)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

# including Cpack to generate the debian package
    include(CPack)

endif(INSTALLATION)
