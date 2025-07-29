/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Chat.h"
#include "CommandScript.h"
#include "Language.h"
#include "Player.h"

using namespace Acore::ChatCommands;

class phase_commandscript : public CommandScript
{
public:
    phase_commandscript() : CommandScript("phase_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable phaseCommandTable =
        {
            { "set", HandlePhaseSetCommand, SEC_GAMEMASTER, Console::No }
        };

        static ChatCommandTable commandTable =
        {
            { "phase", phaseCommandTable }
        };

        return commandTable;
    }

    static bool HandlePhaseSetCommand(ChatHandler* handler, uint32 phaseMask)
    {
        if (!phaseMask)
        {
            handler->SendErrorMessage(LANG_BAD_VALUE);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
            target = handler->GetSession()->GetPlayer();

        if (!target || handler->HasLowerSecurity(target))
            return false;

        target->SetPhaseMask(phaseMask, true);
        return true;
    }
};

void AddSC_phase_commandscript()
{
    new phase_commandscript();
}
