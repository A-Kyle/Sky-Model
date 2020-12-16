cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(TITLE SkyModel)
project(devModel)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../inc)
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2.lib)
set(SDL2_MAIN ${PROJECT_SOURCE_DIR}/../lib/SDL2main.lib)
set(SDLIMG_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_image.lib)
set(SDLMIX_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_mixer.lib)

include_directories(${SDL2_INCLUDE_DIR})

set(SRCDIR ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
${SRCDIR}/CApp.cpp
${SRCDIR}/CApp_Event.cpp
${SRCDIR}/CApp_Ext.cpp
${SRCDIR}/CApp_Init.cpp
${SRCDIR}/CApp_Loop.cpp
${SRCDIR}/CApp_Render.cpp
${SRCDIR}/CApp_Terminate.cpp
${SRCDIR}/CAsset.cpp
${SRCDIR}/CAsset_Ext.cpp
${SRCDIR}/CButton.cpp
${SRCDIR}/CColor.cpp
${SRCDIR}/CColor_Ext.cpp
${SRCDIR}/CCore.cpp
${SRCDIR}/CCore_Ext.cpp
${SRCDIR}/CEvent.cpp
${SRCDIR}/CFont.cpp
${SRCDIR}/CFont_Def.cpp
${SRCDIR}/CFPS.cpp
${SRCDIR}/CInform.cpp
${SRCDIR}/CInterrupt.cpp
${SRCDIR}/CMeter.cpp
${SRCDIR}/CProfile.cpp
${SRCDIR}/CProfile_Ext.cpp
${SRCDIR}/CSurface.cpp
)

set(HEADER_FILES
${SRCDIR}/CApp.h
${SRCDIR}/CAsset.h
${SRCDIR}/CButton.h
${SRCDIR}/CColor.h
${SRCDIR}/CCore.h
${SRCDIR}/CEvent.h
${SRCDIR}/CFont.h
${SRCDIR}/CFPS.h
${SRCDIR}/CInform.h
${SRCDIR}/CInterrupt.h
${SRCDIR}/CMeter.h
${SRCDIR}/CProfile.h
${SRCDIR}/CSurface.h
${SRCDIR}/Define.h
)

set(GCC_COVERAGE_LINK_FLAGS	"-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(${TITLE} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${TITLE} ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDLIMG_LIBRARY} ${SDLMIX_LIBRARY})
