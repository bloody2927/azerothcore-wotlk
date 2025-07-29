/*
 * Placeholder command handlers for XP related commands
 */

#include "Chat.h"
#include "CommandScript.h"

using namespace Acore::ChatCommands;

class xp_commandscript : public CommandScript
{
public:
    xp_commandscript() : CommandScript("xp_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable xpCommandTable =
        {
            { "default", HandleXpDefaultCommand, SEC_ADMINISTRATOR, Console::Yes },
            { "disable", HandleXpDisableCommand, SEC_ADMINISTRATOR, Console::Yes },
            { "enable",  HandleXpEnableCommand,  SEC_ADMINISTRATOR, Console::Yes },
            { "set",     HandleXpSetCommand,     SEC_ADMINISTRATOR, Console::Yes },
            { "view",    HandleXpViewCommand,    SEC_ADMINISTRATOR, Console::Yes }
        };

        static ChatCommandTable commandTable =
        {
            { "xp", xpCommandTable }
        };
        return commandTable;
    }

    static bool HandleXpDefaultCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("XP default command executed.");
        return true;
    }

    static bool HandleXpDisableCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("XP disable command executed.");
        return true;
    }

    static bool HandleXpEnableCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("XP enable command executed.");
        return true;
    }

    static bool HandleXpSetCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("XP set command executed.");
        return true;
    }

    static bool HandleXpViewCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("XP view command executed.");
        return true;
    }
};

void AddSC_xp_commandscript()
{
    new xp_commandscript();
}

