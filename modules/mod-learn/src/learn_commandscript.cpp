#include "Chat.h"
#include "CommandScript.h"
#include "Player.h"

using namespace Acore::ChatCommands;

class learn_commandscript_custom : public CommandScript
{
public:
    learn_commandscript_custom() : CommandScript("learn_commandscript_custom") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable learnCommandTable =
        {
            { "ingi", HandleLearnIngiCommand, SEC_GAMEMASTER, Console::No }
        };
        static ChatCommandTable commandTable =
        {
            { "learn", learnCommandTable }
        };
        return commandTable;
    }

    static bool HandleLearnIngiCommand(ChatHandler* handler)
    {
        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        // Engineering profession spell id (learn ability)
        uint32 const ENGINEERING_SPELL = 4036;
        player->learnSpell(ENGINEERING_SPELL);
        handler->PSendSysMessage("Learned Engineering (spell %u)", ENGINEERING_SPELL);
        return true;
    }
};

void AddSC_learn_commandscript_custom()
{
    new learn_commandscript_custom();
}
