cmake_minimum_required(VERSION 3.0)
set(PIM_VERSION "5.8.41")

set(KGAPI_LIB_VERSION ${PIM_VERSION})

project(kgapi VERSION ${KGAPI_LIB_VERSION})

# ECM setup
set(KF5_VERSION "5.44.0")

find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(CMakePackageConfigHelpers)
include(ECMPoQmTools)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)



set(KCALENDARCORE_LIB_VERSION "5.7.80")
set(KCONTACTS_LIB_VERSION "5.7.80")

ecm_setup_version(PROJECT
    VARIABLE_PREFIX KGAPI
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kgapi_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPimGAPIConfigVersion.cmake"
    SOVERSION 5
)

############## Find Packages ##############
set(QT_REQUIRED_VERSION "5.9.0")
find_package(Qt5 ${QT_REQUIRED_VERSION} REQUIRED COMPONENTS
    Core
    Network
    Widgets
    WebEngineWidgets
    Xml
)

find_package(KF5 ${KF5_VERSION} REQUIRED COMPONENTS
    KIO
    WindowSystem
)

find_package(KF5CalendarCore ${KCALENDARCORE_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Contacts ${KCONTACTS_LIB_VERSION} CONFIG REQUIRED)

find_package(Sasl2)
set_package_properties(Sasl2 PROPERTIES TYPE REQUIRED)

add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050800)

############## Targets ##############
add_subdirectory(src)
add_subdirectory(examples)
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

############## CMake Config Files ##############
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPimGAPI")
set(KGAPI_KF5_COMPAT FALSE)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimGAPIConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPimGAPIConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPimGAPIConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPimGAPIConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KPimGAPITargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPimGAPITargets.cmake
    NAMESPACE KPim::
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/kgapi_version.h"
    DESTINATION "${KDE_INSTALL_INCLUDEDIR}/KPim"
    COMPONENT Devel
)


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
