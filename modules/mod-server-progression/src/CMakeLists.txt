set(MODULE_SOURCES
    ServerProgressionMgr.cpp
    phase_commands.cpp
)

acore_add_module("mod-server-progression" STATIC
    SOURCES ${MODULE_SOURCES}
)
