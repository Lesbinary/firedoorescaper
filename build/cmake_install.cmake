<<<<<<< HEAD
# Install script for directory: /home/antonio/git/firedoorescaper/src
=======
# Install script for directory: /home/leopoldo/workspaceC/fretsonfire/src
>>>>>>> branch 'master' of https://github.com/Lesbinary/firedoorescaper.git

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

<<<<<<< HEAD
FILE(WRITE "/home/antonio/git/firedoorescaper/build/${CMAKE_INSTALL_MANIFEST}" "")
=======
FILE(WRITE "/home/leopoldo/workspaceC/fretsonfire/build/${CMAKE_INSTALL_MANIFEST}" "")
>>>>>>> branch 'master' of https://github.com/Lesbinary/firedoorescaper.git
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
<<<<<<< HEAD
  FILE(APPEND "/home/antonio/git/firedoorescaper/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
=======
  FILE(APPEND "/home/leopoldo/workspaceC/fretsonfire/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
>>>>>>> branch 'master' of https://github.com/Lesbinary/firedoorescaper.git
ENDFOREACH(file)
