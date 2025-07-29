#include "Chat.h"
#include "CommandScript.h"
#include "Player.h"

using namespace Acore::ChatCommands;

class phase_commandscript : public CommandScript
{
public:
    phase_commandscript() : CommandScript("phase_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable setCommandTable =
        {
            { "set", HandlePhaseSetCommand, SEC_GAMEMASTER, Console::No }
        };
        static ChatCommandTable commandTable =
        {
            { "phase", setCommandTable }
        };
        return commandTable;
    }

    static bool HandlePhaseSetCommand(ChatHandler* handler, uint32 phaseMask)
    {
        Player* target = handler->getSelectedPlayer();
        if (!target)
            target = handler->GetSession()->GetPlayer();

        target->SetPhaseMask(phaseMask, true);
        handler->PSendSysMessage("Phase set to %u", phaseMask);
        return true;
    }
};

void AddSC_phase_commandscript()
{
    new phase_commandscript();
}
