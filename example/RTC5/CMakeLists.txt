cmake_minimum_required(VERSION 3.7)

project (RTC5Demos) 

include (RTC_Variables.cmake)

include_directories (
	.
	${RTC_FILES_DIR} )
	
# demo1 隐式连接
# set (INCS 
# 	${RTC_FILES_DIR}/RTC5impl.h ${RTC_FILES_DIR}/RTC5expl.h )
# set (SRCS
# 	Demo1.cpp )
	
# add_executable(RTCDemo ${SRCS} ${INCS})

# target_link_libraries(RTCDemo ${RTC_LIB})

# foreach (RTCFile ${RTC_FILES}) 
# 	add_custom_command(TARGET RTCDemo POST_BUILD COMMAND 
# 		${CMAKE_COMMAND} -E copy_if_different 
# 		${RTCFile} $<TARGET_FILE_DIR:RTCDemo> )
# endforeach (RTCFile) 
# set_vs_debugger_path(RTCDemo)


# demo2-7 显式链接
set (DEMOS 
# Demo1.cpp  Demo3.cpp Demo4.cpp Demo5.cpp Demo6.cpp Demo7.cpp 
Demo2.cpp)
set (RTC_EXPL_SRC
	${RTC_FILES_DIR}/RTC5expl.c )
foreach (RTC_Demo ${DEMOS})
# adding RTC5expl.c doesn't harm even when implicit linking is selected.
	add_executable (${RTC_Demo} ${RTC_Demo} ${RTC_EXPL_SRC})
	target_link_libraries (${RTC_Demo} ${RTC_LIB})
	foreach (RTC_File ${RTC_FILES})
		add_custom_command (
			TARGET ${RTC_Demo} POST_BUILD COMMAND 
			${CMAKE_COMMAND} -E copy_if_different 
			${RTC_File} $<TARGET_FILE_DIR:${RTC_Demo}> )
	endforeach (RTC_File)
	set_vs_debugger_path (${RTC_Demo})
endforeach (RTC_Demo)
