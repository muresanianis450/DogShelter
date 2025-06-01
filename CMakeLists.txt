cmake_minimum_required(VERSION 3.30)
project(a10_muresanianis450_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64")

include_directories(src)
include_directories(src/domain)
include_directories(src/repository)
include_directories(src/service)
include_directories(src/validator)
include_directories(src/gui)

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(a10_muresanianis450_1 main.cpp
        src/adoption/AdoptionList.cpp
        src/adoption/AdoptionList.h
        src/adoption/AdoptionListFactory.cpp
        src/adoption/AdoptionListFactory.h
        src/adoption/CSVAdoptionList.h
        src/adoption/HTMLAdoptionList.h
        src/domain/Dog.cpp
        src/exceptions/CustomExceptions.h
        src/repository/Repo.cpp
        src/repository/Repo.h
        src/service/service.cpp
        src/validator/validator.cpp
        src/gui/MainWindow.h
        src/gui/MainWindow.cpp
        src/gui/AddDogDialog.h
        src/gui/AddDogDialog.cpp
        src/gui/RemoveDogDialog.cpp
        src/gui/UpdateDogDialog.h
        src/gui/UpdateDogDialog.cpp
        src/gui/ShowListDogsDialog.cpp
        src/gui/ShowListDogsDialog.h
        src/gui/ShowOneByOneDialog.cpp
        src/gui/ShowOneByOneDialog.h
        src/gui/ShowOneByOneDialog.cpp
        src/gui/ShowByBreedDialog.cpp
        src/gui/ShowByBreedDialog.h
        src/gui/ShowAllAdoptedDialog.cpp
        src/gui/ShowAllAdoptedDialog.h
        src/gui/ChartDialog.cpp
        src/undoRedo/ICommand.cpp
        src/undoRedo/ICommand.h
        src/undoRedo/AddDogCommand.cpp
        src/undoRedo/AddDogCommand.h
        src/undoRedo/RemoveDogCommand.cpp
        src/undoRedo/RemoveDogCommand.h
        src/undoRedo/UpdateDogCommand.cpp
        src/undoRedo/UpdateDogCommand.h
        src/undoRedo/UndoRedoManager.cpp
        src/undoRedo/UndoRedoManager.h
        src/gui/AdoptedDogsTableModel.cpp
        src/gui/AdoptedDogsTableModel.h
        src/gui/UndoRedoDialog.cpp
        src/gui/UndoRedoDialog.h
        src/undoRedo/AdoptDogCommand.cpp
        src/undoRedo/AdoptDogCommand.h
        src/gui/AdoptedDogsTableModel.h
        src/gui/ADoptedDogsTableModel.cpp)
target_link_libraries(a10_muresanianis450_1
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()
    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()
    foreach(QT_LIB Core Gui Widgets )
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach(QT_LIB)
endif()
