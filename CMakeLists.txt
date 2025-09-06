cmake_minimum_required(VERSION 3.30)
project(DogShelter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64")


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(DogShelter main.cpp
        validator/validator.h
        validator/validator.cpp
        undoRedo/AddDogCommand.cpp
        undoRedo/AddDogCommand.h
        undoRedo/AdoptDogCommand.cpp
        undoRedo/AdoptDogCommand.h
        undoRedo/ICommand.cpp
        undoRedo/ICommand.h
        undoRedo/RemoveDogCommand.cpp
        undoRedo/RemoveDogCommand.h
        undoRedo/UndoRedoManager.cpp
        undoRedo/UndoRedoManager.h
        undoRedo/UpdateDogCommand.cpp
        undoRedo/UpdateDogCommand.h
        service/service.cpp
        service/service.h
        repository/Repo.cpp
        repository/Repo.h
        gui/AddDogDialog.cpp
        gui/AddDogDialog.h
        gui/AdoptedDogsTableModel.cpp
        gui/AdoptedDogsTableModel.h
        gui/ChartDialog.cpp
        gui/ChartDialog.h
        gui/MainWindow.cpp
        gui/MainWindow.h
        gui/RemoveDogDialog.cpp
        gui/RemoveDogDialog.h
        gui/ShowAllAdoptedDialog.cpp
        gui/ShowAllAdoptedDialog.h
        gui/ShowByBreedDialog.cpp
        gui/ShowByBreedDialog.h
        gui/ShowListDogsDialog.cpp
        gui/ShowListDogsDialog.h
        gui/ShowOneByOneDialog.cpp
        gui/ShowOneByOneDialog.h
        gui/UndoRedoDialog.cpp
        gui/UndoRedoDialog.h
        gui/UpdateDogDialog.cpp
        gui/UpdateDogDialog.h
        domain/Dog.cpp
        domain/Dog.h
        adoption/AdoptionList.cpp
        adoption/AdoptionList.h
        adoption/AdoptionListFactory.cpp
        adoption/AdoptionListFactory.h
        adoption/CSVAdoptionList.cpp
        adoption/CSVAdoptionList.h
        adoption/HTMLAdoptionList.cpp
        adoption/HTMLAdoptionList.h)
target_link_libraries(DogShelter
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
