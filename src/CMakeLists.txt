add_subdirectory(blogger)
add_subdirectory(calendar)
add_subdirectory(contacts)
add_subdirectory(core)
add_subdirectory(drive)
add_subdirectory(latitude)
add_subdirectory(staticmaps)
add_subdirectory(tasks)

add_subdirectory(saslplugin)

add_subdirectory(onedrive)

install( FILES libkgapi.categories DESTINATION ${KDE_INSTALL_CONFDIR} )

