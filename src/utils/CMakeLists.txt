# ----------------------------------------------------------------------------
# Target: wflinfo (executable)
# ----------------------------------------------------------------------------

if(waffle_has_nacl)
    return()
endif()

add_executable(wflinfo wflinfo.c)
target_link_libraries(wflinfo ${waffle_libname} ${GETOPT_LIBRARIES})

if(waffle_on_switch)
    # Use the C++ linker to link the libraries, as mesa depends on libstdc++
    set_target_properties(wflinfo PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(wflinfo
            EGL
            glapi
            GLESv2
            drm_nouveau
            nx
    )
endif()

if(waffle_on_mac)
    set_target_properties(wflinfo
        PROPERTIES
        COMPILE_FLAGS "-ObjC"
        )
endif()

install(
    TARGETS wflinfo
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT utils
    )
