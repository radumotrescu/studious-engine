cmake_minimum_required(VERSION 3.8)
include_directories("C:/ez-gen-test/src/studious-engine/PublicFiles")
include_directories("C:/ez-gen-test/src/glew/PublicFiles")
include_directories("C:/ez-gen-test/src/glfw/PublicFiles")
include_directories("C:/ez-gen-test/src/opengl32/PublicFiles")
file(GLOB PublicFiles_H "C:/ez-gen-test/src/studious-engine/PublicFiles/*.h")
file(GLOB PublicFiles_HH "C:/ez-gen-test/src/studious-engine/PublicFiles/*.hh")
file(GLOB PublicFiles_HPP "C:/ez-gen-test/src/studious-engine/PublicFiles/*.hpp")
file(GLOB PublicFiles_HXX "C:/ez-gen-test/src/studious-engine/PublicFiles/*.hxx")
file(GLOB PublicFiles_C "C:/ez-gen-test/src/studious-engine/PublicFiles/*.c")
file(GLOB PublicFiles_CC "C:/ez-gen-test/src/studious-engine/PublicFiles/*.cc")
file(GLOB PublicFiles_CPP "C:/ez-gen-test/src/studious-engine/PublicFiles/*.cpp")
file(GLOB PublicFiles_CXX "C:/ez-gen-test/src/studious-engine/PublicFiles/*.cxx")
source_group("PublicFiles" FILES ${PublicFiles_H} ${PublicFiles_HH} ${PublicFiles_HPP} ${PublicFiles_HXX} ${PublicFiles_C} ${PublicFiles_CC} ${PublicFiles_CPP} ${PublicFiles_CXX})
add_executable(studious-engine
    ${PublicFiles_H}
    ${PublicFiles_HH}
    ${PublicFiles_HPP}
    ${PublicFiles_HXX}
    ${PublicFiles_C}
    ${PublicFiles_CC}
    ${PublicFiles_CPP}
    ${PublicFiles_CXX}
)
target_link_libraries(studious-engine glew32s glfw3 opengl32)
if(WIN32)
add_definitions(-DGLEW_STATIC)
endif(WIN32)
install(TARGETS studious-engine RUNTIME DESTINATION "C:/ez-gen-test/build_view")
