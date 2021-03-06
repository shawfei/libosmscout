if(NOT ${OSMSCOUT_BUILD_MAP_QT})
	message(SEND_ERROR "The Qt map drawing backend is required for StyleEditor application")
endif()
if(NOT ${OSMSCOUT_BUILD_CLIENT_QT})
	message(SEND_ERROR "The Qt client lib is required for StyleEditor application")
endif()
if(NOT Qt5Core_FOUND)
	message(SEND_ERROR "Qt5Core is required for StyleEditor application")
endif()
if(NOT Qt5Gui_FOUND)
	message(SEND_ERROR "Qt5Gui is required for StyleEditor application")
endif()
if(NOT Qt5Widgets_FOUND)
	message(SEND_ERROR "Qt5Widgets is required for StyleEditor application")
endif()
if(NOT Qt5Qml_FOUND)
	message(SEND_ERROR "Qt5Qml is required for StyleEditor application")
endif()
if(NOT Qt5Quick_FOUND)
	message(SEND_ERROR "Qt5Quick is required for StyleEditor application")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(HEADER_FILES
	src/FileIO.h
	src/Highlighter.h
	src/MainWindow.h
	src/SettingsDialog.h
	src/StyleAnalyser.h
	)

set(SOURCE_FILES
	src/FileIO.cpp
	src/Highlighter.cpp
	src/MainWindow.cpp
	src/SettingsDialog.cpp
	src/StyleEditor.cpp
	src/StyleAnalyser.cpp

	# qml files in CMake sources make it visible in QtCreator
	qml/AboutDialog.qml
	qml/main.qml
	qml/settings.qml
	qml/SearchGeocodeDialog.qml
	qml/TextEditor.qml
	qml/custom/LocationEdit.qml
	qml/custom/MapDialog.qml
	qml/custom/ScrollIndicator.qml
	qml/custom/LineEdit.qml
	qml/custom/DialogActionButton.qml
	qml/custom/MapButton.qml
	qml/SearchLocationDialog.qml
	qml/MapControl.qml
	)

set(RESOURCE_FILES
    StyleEditor.qrc
)

add_executable(StyleEditor ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES})

target_link_libraries(StyleEditor
	OSMScout
		OSMScoutMap
		Qt5::Core
		Qt5::Gui
		Qt5::Widgets
		Qt5::Qml
		Qt5::Quick
		OSMScoutMapQt
		OSMScoutClientQt
)

if (Qt5Svg_FOUND)
	target_link_libraries(StyleEditor Qt5::Svg)
endif()

# enable QML debuger
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DQT_QML_DEBUG ")
set_property(TARGET StyleEditor PROPERTY CXX_STANDARD 11)
