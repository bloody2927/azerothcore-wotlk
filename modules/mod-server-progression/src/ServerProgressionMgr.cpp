#include "ServerProgressionMgr.h"
#include "DatabaseEnv.h"
#include "World.h"
#include "ScriptMgr.h"

ServerProgressionMgr* ServerProgressionMgr::instance()
{
    static ServerProgressionMgr instance;
    return &instance;
}

void ServerProgressionMgr::Load()
{
    QueryResult result = WorldDatabase.Query("SELECT phase FROM server_progression LIMIT 1");
    if (result)
        _phase = (*result)[0].Get<uint8>();
    else
    {
        WorldDatabase.Execute("INSERT INTO server_progression (phase) VALUES (0)");
        _phase = 0;
    }

    _questPhases.clear();
    if (QueryResult qRes = WorldDatabase.Query("SELECT quest, required_phase FROM server_progression_quest"))
    {
        do
        {
            Field* fields = qRes->Fetch();
            _questPhases.emplace(fields[0].Get<uint32>(), fields[1].Get<uint8>());
        }
        while (qRes->NextRow());
    }
}

void ServerProgressionMgr::SavePhase()
{
    WorldDatabase.Execute("UPDATE server_progression SET phase = {}", _phase);
}

uint8 ServerProgressionMgr::GetQuestRequiredPhase(uint32 questId) const
{
    auto itr = _questPhases.find(questId);
    return itr != _questPhases.end() ? itr->second : 0;
}

class ServerProgressionWorldScript : public WorldScript
{
public:
    ServerProgressionWorldScript() : WorldScript("ServerProgressionWorldScript") { }

    void OnLoadCustomDatabaseTable() override
    {
        sServerProgressionMgr->Load();
    }
};

void AddSC_mod_server_progression()
{
    new ServerProgressionWorldScript();
}

void Addmod_server_progressionScripts()
{
    AddSC_mod_server_progression();
    AddSC_phase_commands();
}
