file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "*.h" "*.hpp")
file(GLOB_RECURSE inline_files "*.inl")

set(all_sources ${source_files}
        ${header_files}
        ${inline_files})

add_executable(${PROJECT_NAME} ${all_sources})
target_link_libraries(${PROJECT_NAME}
        Rumble3D
        EyeCandy3D
        glfw
        GLEW
        GL
        GLU
        X11
        Xrandr
        Xinerama
        Xi
        Xxf86vm
        Xcursor
        pthread
        dl
        freetype
        )