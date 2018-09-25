cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 14)

project(meida)
find_package(Ice REQUIRED Ice)
message(${Ice_LIBRARIES})
message("@@@@@@@@@" ${Ice_SLICE_DIRS})
add_definitions(-DICE_CPP11_MAPPING)
get_filename_component(hw_proto "ices/stream.ice" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

set(hw_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/stream.cpp")
set(hw_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/stream.h")

add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${Ice_SLICE2CPP_EXECUTABLE}
      ARGS --output-dir ${CMAKE_CURRENT_SOURCE_DIR}
      #--impl-c++98
      -I${Ice_SLICE_DIRS}
        #--cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        #-I "${hw_proto_path}"
        #--plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")



include_directories(./hksdk/include)
#include_directories(./ffmpeg-3.4.2-win64-dev/include)
include_directories(.)
#aux_source_directory(. SRCS )

#link_directories(  ${CMAKE_CURRENT_BINARY_DIR}/libs ${CMAKE_CURRENT_BINARY_DIR}/hksdk/libs ${CMAKE_CURRENT_BINARY_DIR}/ffmpeg-3.4.2-win64-dev/lib)
link_directories(/opt/CH_HCNetSDK_V5.3.5.2_build20171124_Linux64/lib /opt/CH_HCNetSDK_V5.3.5.2_build20171124_Linux64/lib/HCNetSDKCom)
add_definitions(-DHKDEVICE_EXPORTS -DGLOG_NO_ABBREVIATED_SEVERITIES -DGOOGLE_GLOG_DLL_DECL= -D__x86_64__)

link_libraries(pthread glog)

#add_executable(client Client.cpp Pricing.cpp)
add_executable(${PROJECT_NAME}  main.cpp streamI.cpp stream.cpp buffer.cpp mediastream.cpp RTPSender.cpp zmd5.c)
target_link_libraries( ${PROJECT_NAME} libhcnetsdk.so Ice++11 IceGrid++11 Glacier2++11 pthread dl jrtp)
#target_link_libraries(${PROJECT_NAME} pthread glog swresample avformat avcodec avutil z)
