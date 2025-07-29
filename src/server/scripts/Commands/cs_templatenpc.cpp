/*
 * Placeholder command handlers for templatenpc commands
 */

#include "Chat.h"
#include "CommandScript.h"

using namespace Acore::ChatCommands;

class templatenpc_commandscript : public CommandScript
{
public:
    templatenpc_commandscript() : CommandScript("templatenpc_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable templatenpcCommandTable =
        {
            { "create", HandleTemplateNPCCreateCommand, SEC_ADMINISTRATOR, Console::Yes },
            { "reload", HandleTemplateNPCReloadCommand, SEC_ADMINISTRATOR, Console::Yes }
        };

        static ChatCommandTable commandTable =
        {
            { "templatenpc", templatenpcCommandTable }
        };
        return commandTable;
    }

    static bool HandleTemplateNPCCreateCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("Template NPC create command executed.");
        return true;
    }

    static bool HandleTemplateNPCReloadCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("Template NPC reload command executed.");
        return true;
    }
};

void AddSC_templatenpc_commandscript()
{
    new templatenpc_commandscript();
}

