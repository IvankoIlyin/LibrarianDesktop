cmake_minimum_required(VERSION 3.16)

project(LibrarianDesktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core  Sql Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core  Sql Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        resources/resources.qrc
)

set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LibrarianDesktop
        MANUAL_FINALIZATION
              ${PROJECT_SOURCES}
              db_manager/database_manager.h
              db_manager/database_manager.cpp

              entity/user.h
              entity/user.cpp
              entity/document.h
              entity/document.cpp
              entity/transaction.h
              entity/transaction.cpp
              table_widget/tablewidget.h
              table_widget/tablewidget.cpp
              user_widget/userwidget.h
              user_widget/userwidget.cpp
              document_widget/documentwidget.h document_widget/documentwidget.cpp
              transaction_widget/transactionwidget.h transaction_widget/transactionwidget.cpp
              report_snapshots/reportsnapshots.h report_snapshots/reportsnapshots.cpp
              about_author/aboutauthor.h about_author/aboutauthor.cpp
              snapshots_diagram/snapshotsdiagram.h snapshots_diagram/snapshotsdiagram.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LibrarianDesktop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(LibrarianDesktop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(LibrarianDesktop
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(LibrarianDesktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql  Qt${QT_VERSION_MAJOR}::Charts)
target_include_directories(LibrarianDesktop PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/db_manager
    ${CMAKE_CURRENT_SOURCE_DIR}/entity
)
file(GLOB DB_FILES "${CMAKE_SOURCE_DIR}/db/*.db")
file(COPY ${DB_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/db)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/db)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LibrarianDesktop)
endif()
set_target_properties(LibrarianDesktop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LibrarianDesktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LibrarianDesktop)
endif()
