cmake_minimum_required(VERSION 3.8)
include_directories("D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles")
include_directories("D:/mechanics/studious-engine/ez-brick-breaker/src/glew/PublicFiles")
include_directories("D:/mechanics/studious-engine/ez-brick-breaker/src/glfw/PublicFiles")
include_directories("D:/mechanics/studious-engine/ez-brick-breaker/src/opengl32/PublicFiles")
include_directories("D:/mechanics/studious-engine/ez-brick-breaker/src/studious-engine/PublicFiles")
file(GLOB PublicFiles_H "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.h")
file(GLOB PublicFiles_HH "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.hh")
file(GLOB PublicFiles_HPP "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.hpp")
file(GLOB PublicFiles_HXX "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.hxx")
file(GLOB PublicFiles_C "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.c")
file(GLOB PublicFiles_CC "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.cc")
file(GLOB PublicFiles_CPP "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.cpp")
file(GLOB PublicFiles_CXX "D:/mechanics/studious-engine/ez-brick-breaker/src/brick-breaker/PublicFiles/*.cxx")
source_group("PublicFiles" FILES ${PublicFiles_H} ${PublicFiles_HH} ${PublicFiles_HPP} ${PublicFiles_HXX} ${PublicFiles_C} ${PublicFiles_CC} ${PublicFiles_CPP} ${PublicFiles_CXX})
add_executable(brick-breaker
    ${PublicFiles_H}
    ${PublicFiles_HH}
    ${PublicFiles_HPP}
    ${PublicFiles_HXX}
    ${PublicFiles_C}
    ${PublicFiles_CC}
    ${PublicFiles_CPP}
    ${PublicFiles_CXX}
)
target_link_libraries(brick-breaker glew32s glfw3 opengl32 studious-engine)
if(WIN32)
add_definitions(-DGLEW_STATIC)
endif(WIN32)
install(TARGETS brick-breaker RUNTIME DESTINATION "D:/mechanics/studious-engine/ez-brick-breaker/build_view")
