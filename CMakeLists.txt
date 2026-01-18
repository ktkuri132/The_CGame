cmake_minimum_required(VERSION 3.16)
project(The_Control_System_Box LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ============================================
# SDL3 配置
# ============================================
# 你的SDL3安装路径
set(SDL3_PATH "C:/Users/ktkuri/Desktop/SDL3-devel-3.4.0-mingw/SDL3-3.4.0/x86_64-w64-mingw32")
set(SDL3_TTF_PATH "C:/Users/ktkuri/Desktop/SDL3-devel-3.4.0-mingw/SDL3_ttf-3.2.2/x86_64-w64-mingw32")

# 设置SDL3的头文件路径
set(SDL3_INCLUDE_DIR "${SDL3_PATH}/include")
set(SDL3_TTF_INCLUDE_DIR "${SDL3_TTF_PATH}/include")

# 设置SDL3的库文件路径
set(SDL3_LIB_DIR "${SDL3_PATH}/lib")
set(SDL3_TTF_LIB_DIR "${SDL3_TTF_PATH}/lib")

# 设置SDL3的DLL路径（运行时需要）
set(SDL3_BIN_DIR "${SDL3_PATH}/bin")
set(SDL3_TTF_BIN_DIR "${SDL3_TTF_PATH}/bin")

set(control_system_src
    control_system/control_panel.c
)

set(SOURCE_FILE 
    src/button.c
    src/test.c
    src/menu.c
    src/text.c
)

# ============================================
# 创建可执行文件
# ============================================
add_executable(${PROJECT_NAME} 
    src/main.c
    ${SOURCE_FILE}
    ${control_system_src}
)

# 添加头文件搜索路径
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL3_INCLUDE_DIR}
    ${SDL3_TTF_INCLUDE_DIR}
    inc
    control_system
    )

# 链接库文件路径
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_LIB_DIR} ${SDL3_TTF_LIB_DIR})

# 链接SDL3库
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3 SDL3_ttf)

# ============================================
# 复制DLL到输出目录（Windows需要）
# ============================================
# 构建后自动复制SDL3.dll到exe所在目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_BIN_DIR}/SDL3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_TTF_BIN_DIR}/SDL3_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    # 复制assets文件夹到exe所在目录
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying SDL3.dll and assets to output directory"
)

message(STATUS "SDL3 Include: ${SDL3_INCLUDE_DIR} ${SDL3_TTF_INCLUDE_DIR}")
message(STATUS "SDL3 Lib: ${SDL3_LIB_DIR} ${SDL3_TTF_LIB_DIR}")
message(STATUS "SDL3 Bin: ${SDL3_BIN_DIR} ${SDL3_TTF_BIN_DIR}")