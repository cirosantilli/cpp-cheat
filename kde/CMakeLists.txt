project (kdecheat)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES})
set(kdecheat_SRCS main.cpp)
kde4_add_executable(kdecheat ${kdecheat_SRCS})
target_link_libraries(kdecheat ${KDE4_KDEUI_LIBS})

install(TARGETS kdecheat DESTINATION ${BIN_INSTALL_DIR})
install(FILES kdecheatui.rc
        DESTINATION  ${DATA_INSTALL_DIR}/kdecheat)
