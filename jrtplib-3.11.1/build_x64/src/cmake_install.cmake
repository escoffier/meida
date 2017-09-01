# Install script for directory: E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Program Files/jrtplib")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jrtplib3" TYPE FILE FILES
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpapppacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpbyepacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpcompoundpacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpcompoundpacketbuilder.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcppacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcppacketbuilder.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcprrpacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpscheduler.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpsdesinfo.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpsdespacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpsrpacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtcpunknownpacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpaddress.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpcollisionlist.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/build_x64/src/rtpconfig.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpdebug.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpdefines.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtperrors.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtphashtable.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpinternalsourcedata.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpipv4address.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpipv4destination.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpipv6address.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpipv6destination.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpkeyhashtable.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtplibraryversion.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpmemorymanager.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpmemoryobject.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtppacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtppacketbuilder.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtppollthread.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtprandom.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtprandomrand48.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtprandomrands.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtprandomurandom.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtprawpacket.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpsession.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpsessionparams.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpsessionsources.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpsourcedata.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpsources.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpstructs.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtptimeutilities.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtptransmitter.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtptypes_win.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/build_x64/src/rtptypes.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpudpv4transmitter.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpudpv6transmitter.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpbyteaddress.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpexternaltransmitter.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpsecuresession.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpsocketutil.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpabortdescriptors.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtpselect.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtptcpaddress.h"
    "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/src/rtptcptransmitter.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/Program Files/jrtplib/lib/jrtplib_d.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/Program Files/jrtplib/lib" TYPE STATIC_LIBRARY FILES "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/build_x64/src/Debug/jrtplib_d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/Program Files/jrtplib/lib/jrtplib.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/Program Files/jrtplib/lib" TYPE STATIC_LIBRARY FILES "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/build_x64/src/Release/jrtplib.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/Program Files/jrtplib/lib/jrtplib.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/Program Files/jrtplib/lib" TYPE STATIC_LIBRARY FILES "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/build_x64/src/MinSizeRel/jrtplib.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/Program Files/jrtplib/lib/jrtplib.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/Program Files/jrtplib/lib" TYPE STATIC_LIBRARY FILES "E:/workspace/DTNVS3000/nvs3000/jrtplib-3.11.1/build_x64/src/RelWithDebInfo/jrtplib.lib")
  endif()
endif()

