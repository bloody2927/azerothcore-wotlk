#include "Chat.h"
#include "CommandScript.h"
#include "Language.h"
#include "Player.h"
#include "ServerProgressionMgr.h"

using namespace Acore::ChatCommands;

class phase_commandscript : public CommandScript
{
public:
    phase_commandscript() : CommandScript("phase_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable phaseCommandTable =
        {
            { "get", HandlePhaseGetCommand, SEC_ADMINISTRATOR, Console::Yes },
            { "set", HandlePhaseSetCommand, SEC_ADMINISTRATOR, Console::Yes }
        };
        static ChatCommandTable commandTable =
        {
            { "phase", phaseCommandTable }
        };
        return commandTable;
    }

    static bool HandlePhaseGetCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("Current phase: %u", sServerProgressionMgr->GetPhase());
        return true;
    }

    static bool HandlePhaseSetCommand(ChatHandler* handler, uint8 phase)
    {
        sServerProgressionMgr->SetPhase(phase);
        sServerProgressionMgr->SavePhase();
        handler->PSendSysMessage("Phase set to: %u", phase);
        return true;
    }
};

void AddSC_phase_commands()
{
    new phase_commandscript();
}
