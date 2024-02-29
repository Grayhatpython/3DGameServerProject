
include(ExternalProject)

# PROJECT_BINARY_DIR - > build Folder
# DEP_INCLUDE_DIR -> build/include
# DEP_LIB_DIR -> build/lib
set(DEP_EXTERNAL_DIR ${PROJECT_BINARY_DIR}/external)
set(DEP_INCLUDE_DIR ${DEP_EXTERNAL_DIR}/include)
set(DEP_LIB_DIR ${DEP_EXTERNAL_DIR}/lib)

# spdlog: fast logger library
ExternalProject_Add(
    dep-spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_EXTERNAL_DIR}
)

# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep-spdlog)
# Config Debug -> spdlogd.lib ( build Time )
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)

# glfw
ExternalProject_Add(
    dep-glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.4"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND "" 
    TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_EXTERNAL_DIR}
        #   GLFW CMakeLists.txt -> option
        -DGLFW_BUILD_EXAMPLES=OFF   # 예제 x
        -DGLFW_BUILD_TESTS=OFF      # 테스트 x
        -DGLFW_BUILD_DOCS=OFF       # 문서 x
    )

set(DEP_LIST ${DEP_LIST} dep-glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)

# DEP_LIST -> dep-spdlog dep-glfw
# DEP_LIBS -> spdlogd(Debug) glfw3