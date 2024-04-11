add_executable(demo_univers demo_univers.cxx)
target_link_libraries(demo_univers particules)

file(GLOB VTU_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.vtu")
foreach(VTU_FILE ${VTU_FILES})
    file(COPY ${VTU_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
