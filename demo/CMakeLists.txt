add_executable(demo_univers demo_univers.cxx)
target_link_libraries(demo_univers particules)

# Copier des fichiers .vtu
file(GLOB VTU_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.vtu")
foreach(VTU_FILE ${VTU_FILES})
    file(COPY ${VTU_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

# Copier le fichier configuration.conf
configure_file(configuration.conf ${CMAKE_CURRENT_BINARY_DIR}/configuration.conf COPYONLY)
