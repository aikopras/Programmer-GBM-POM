# Programmer GBM-POM, Qt version (version 2.3, November 2026)
# Runs on Windows and Linux (and should also run on macOS). Requires Qt 6 (Widgets, Network, SerialPort) and C++17.
# Build: see README.md in this directory
# The XpressNetQt library (in XpressNetQt) is a copy of the library in https://github.com/aikopras/XpressNet
# The help pages are the same files as those of the macOS version (../Xcode/Helpfiles/GBM-POMHelp).

cmake_minimum_required(VERSION 3.16)
project(ProgrammerGbmPoM VERSION 2.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Visual Studio: the source files are UTF-8
if(MSVC)
  add_compile_options(/utf-8)
endif()

add_subdirectory(XpressNetQt)

add_executable(ProgrammerGbmPoM WIN32 MACOSX_BUNDLE
  src/main.cpp
  src/CvNames.h
  src/DccDecoder.h
  src/DccDecoder.cpp
  src/PomConnection.h
  src/PomConnection.cpp
  src/MainWindow.h
  src/MainWindow.cpp
  src/PreferencesDialog.h
  src/PreferencesDialog.cpp
  src/HelpWindow.h
  src/HelpWindow.cpp
  src/CenteredComboBox.h
  src/CenteredComboBox.cpp
  src/tabs/DecoderTab.h
  src/tabs/DecoderTab.cpp
  src/tabs/ControlTab.h
  src/tabs/ControlTab.cpp
  src/tabs/DelayTab.h
  src/tabs/DelayTab.cpp
  src/tabs/SensitivityTab.h
  src/tabs/SensitivityTab.cpp
  src/tabs/ReverserTab.h
  src/tabs/ReverserTab.cpp
  src/tabs/RelaysTab.h
  src/tabs/RelaysTab.cpp
  src/tabs/SpeedTab.h
  src/tabs/SpeedTab.cpp
  src/tabs/InitialiseTab.h
  src/tabs/InitialiseTab.cpp
  src/tabs/CvTab.h
  src/tabs/CvTab.cpp
  ui/mainwindow.ui
  ui/preferencesdialog.ui
  ui/controltab.ui
  ui/delaytab.ui
  ui/sensitivitytab.ui
  ui/reversertab.ui
  ui/relaystab.ui
  ui/speedtab.ui
  ui/initialisetab.ui
  ui/cvtab.ui
  resources/resources.qrc
)

# Windows: the icon of the program
if(WIN32)
  target_sources(ProgrammerGbmPoM PRIVATE resources/Programmer-GBM-POM.rc)
endif()

# Visual Studio: this program is the startup project, and while debugging the Qt DLLs are found via PATH
if(MSVC)
  set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ProgrammerGbmPoM)
  set_target_properties(ProgrammerGbmPoM PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$<TARGET_FILE_DIR:Qt6::Core>;%PATH%")
endif()

# The help pages, as resources with prefix /help. After adding a help page, run cmake again
set(HELP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Xcode/Helpfiles/GBM-POMHelp)
file(GLOB HELP_FILES CONFIGURE_DEPENDS ${HELP_DIR}/*)
qt_add_resources(ProgrammerGbmPoM "help" PREFIX "/help" BASE ${HELP_DIR} FILES ${HELP_FILES})

target_include_directories(ProgrammerGbmPoM PRIVATE src src/tabs)
target_link_libraries(ProgrammerGbmPoM PRIVATE Qt6::Widgets XpressNetQt)
target_compile_definitions(ProgrammerGbmPoM PRIVATE APP_VERSION="${PROJECT_VERSION}")
# The name of the program, the same as in the macOS version
set_target_properties(ProgrammerGbmPoM PROPERTIES OUTPUT_NAME "Programmer GBM-POM")
