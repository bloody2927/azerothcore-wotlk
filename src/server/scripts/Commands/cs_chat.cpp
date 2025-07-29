/*
 * Placeholder command handlers for chat-related commands
 */

#include "Chat.h"
#include "CommandScript.h"

using namespace Acore::ChatCommands;

class chat_commandscript : public CommandScript
{
public:
    chat_commandscript() : CommandScript("chat_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable commandTable =
        {
            { "chat",  HandleChatCommand,  SEC_ADMINISTRATOR, Console::Yes },
            { "chata", HandleChatACommand, SEC_ADMINISTRATOR, Console::Yes },
            { "chath", HandleChatHCommand, SEC_ADMINISTRATOR, Console::Yes }
        };
        return commandTable;
    }

    static bool HandleChatCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("Chat command executed.");
        return true;
    }

    static bool HandleChatACommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("Chata command executed.");
        return true;
    }

    static bool HandleChatHCommand(ChatHandler* handler)
    {
        handler->PSendSysMessage("Chath command executed.");
        return true;
    }
};

void AddSC_chat_commandscript()
{
    new chat_commandscript();
}

