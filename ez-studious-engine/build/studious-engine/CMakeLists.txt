cmake_minimum_required(VERSION 3.8)
include_directories("D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles")
include_directories("D:/mechanics/studious-engine/ez-studious-engine/src/glew/PublicFiles")
include_directories("D:/mechanics/studious-engine/ez-studious-engine/src/glfw/PublicFiles")
include_directories("D:/mechanics/studious-engine/ez-studious-engine/src/opengl32/PublicFiles")
file(GLOB PublicFiles_H "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.h")
file(GLOB PublicFiles_HH "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.hh")
file(GLOB PublicFiles_HPP "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.hpp")
file(GLOB PublicFiles_HXX "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.hxx")
file(GLOB PublicFiles_C "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.c")
file(GLOB PublicFiles_CC "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.cc")
file(GLOB PublicFiles_CPP "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.cpp")
file(GLOB PublicFiles_CXX "D:/mechanics/studious-engine/ez-studious-engine/src/studious-engine/PublicFiles/*.cxx")
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
install(TARGETS studious-engine RUNTIME DESTINATION "D:/mechanics/studious-engine/ez-studious-engine/build_view")
