#ifndef MODULE_SERVERPROGRESSIONMGR_H
#define MODULE_SERVERPROGRESSIONMGR_H

#include "DatabaseEnvFwd.h"
#include <cstdint>
#include <unordered_map>

class ServerProgressionMgr
{
public:
    static ServerProgressionMgr* instance();

    void Load();
    uint8 GetPhase() const { return _phase; }
    void SetPhase(uint8 phase) { _phase = phase; }
    void SavePhase();
    uint8 GetQuestRequiredPhase(uint32 questId) const;

private:
    ServerProgressionMgr() = default;
    uint8 _phase = 0;
    std::unordered_map<uint32, uint8> _questPhases;
};

#define sServerProgressionMgr ServerProgressionMgr::instance()

#endif
