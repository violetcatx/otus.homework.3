cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(custom_allocator VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(custom_allocator main.cxx)

set_target_properties(custom_allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(custom_allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(custom_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-parameter")
endif()

install(TARGETS custom_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT smallvioletcat@gmail.com)
include(CPack)