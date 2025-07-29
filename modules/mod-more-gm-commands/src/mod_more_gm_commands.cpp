#include "Chat.h"
#include "CommandScript.h"
#include "DBCStores.h"
#include "Language.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "SpellMgr.h"
#include "BattlegroundMgr.h"
#include "WorldPacket.h"
#include "ScriptMgr.h"

using namespace Acore::ChatCommands;

namespace
{
    constexpr uint32 HEARTHSTONE_ITEM_ID = 6948;
    constexpr uint32 ENGINEERING_SKILL_ID = SKILL_ENGINEERING;
}

class more_gm_commandscript : public CommandScript
{
public:
    more_gm_commandscript() : CommandScript("more_gm_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable learnTable =
        {
            { "ingi", HandleLearnEngineering, SEC_GAMEMASTER, Console::No }
        };

        static ChatCommandTable addItemTable =
        {
            { "hearthstone", HandleAddHearthstone, SEC_GAMEMASTER, Console::Yes }
        };

        static ChatCommandTable removeItemTable =
        {
            { "hearthstone", HandleRemoveHearthstone, SEC_GAMEMASTER, Console::Yes }
        };

        static ChatCommandTable avTable =
        {
            { "queue", HandleAVQueue, SEC_GAMEMASTER, Console::No }
        };

        static ChatCommandTable commandTable =
        {
            { "learn", learnTable },
            { "additem", addItemTable },
            { "removeitem", removeItemTable },
            { "av", avTable }
        };

        return commandTable;
    }

    static bool HandleLearnEngineering(ChatHandler* handler)
    {
        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        uint32 classmask = player->getClassMask();
        for (SkillLineAbilityEntry const* skillLine : GetSkillLineAbilitiesBySkillLine(ENGINEERING_SKILL_ID))
        {
            if (skillLine->SupercededBySpell)
                continue;
            if (skillLine->RaceMask != 0)
                continue;
            if (skillLine->ClassMask && (skillLine->ClassMask & classmask) == 0)
                continue;
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->Spell);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;
            player->learnSpell(skillLine->Spell);
        }

        handler->PSendSysMessage("Learned all engineering recipes for %s", handler->GetNameLink(player).c_str());
        return true;
    }

    static bool AddOrRemoveItem(ChatHandler* handler, uint32 itemId, int32 count)
    {
        Player* target = handler->getSelectedPlayer();
        if (!target)
            target = handler->GetSession()->GetPlayer();
        if (!target)
            return false;

        if (count > 0)
        {
            ItemPosCountVec dest;
            uint8 msg = target->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count);
            if (msg != EQUIP_ERR_OK)
            {
                handler->PSendSysMessage("Couldn't add item %u", itemId);
                return false;
            }
            if (Item* item = target->StoreNewItem(dest, itemId, true))
                target->SendNewItem(item, count, false, true);
            handler->PSendSysMessage("Added item %u to %s", itemId, handler->GetNameLink(target).c_str());
        }
        else if (count < 0)
        {
            if (!target->HasItemCount(itemId, -count))
            {
                handler->PSendSysMessage("%s does not have enough of item %u", handler->GetNameLink(target).c_str(), itemId);
                return false;
            }
            target->DestroyItemCount(itemId, -count, true);
            handler->PSendSysMessage("Removed item %u from %s", itemId, handler->GetNameLink(target).c_str());
        }
        return true;
    }

    static bool HandleAddHearthstone(ChatHandler* handler)
    {
        return AddOrRemoveItem(handler, HEARTHSTONE_ITEM_ID, 1);
    }

    static bool HandleRemoveHearthstone(ChatHandler* handler)
    {
        return AddOrRemoveItem(handler, HEARTHSTONE_ITEM_ID, -1);
    }

    static bool HandleAVQueue(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        BattlegroundTypeId bgTypeId = BATTLEGROUND_AV;
        BattlegroundQueueTypeId bgQueueTypeId = BattlegroundMgr::BGQueueTypeId(bgTypeId, 0);

        if (!player->HasFreeBattlegroundQueueId() || player->InBattleground())
        {
            handler->PSendSysMessage("Cannot queue player for battleground.");
            return false;
        }

        Battleground* bg = sBattlegroundMgr->GetBattlegroundTemplate(bgTypeId);
        if (!bg)
            return false;
        PvPDifficultyEntry const* bracketEntry = GetBattlegroundBracketByLevel(bg->GetMapId(), player->getLevel());
        if (!bracketEntry)
            return false;

        BattlegroundQueue& bgQueue = sBattlegroundMgr->GetBattlegroundQueue(bgQueueTypeId);
        GroupQueueInfo* ginfo = bgQueue.AddGroup(player, nullptr, bgTypeId, bracketEntry, 0, false, false, 0, 0);
        uint32 avgWaitTime = bgQueue.GetAverageQueueWaitTime(ginfo);
        uint32 queueSlot = player->AddBattlegroundQueueId(bgQueueTypeId);
        WorldPacket data;
        sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, bg, queueSlot, STATUS_WAIT_QUEUE, avgWaitTime, 0, 0, TEAM_NEUTRAL);
        player->GetSession()->SendPacket(&data);
        sScriptMgr->OnPlayerJoinBG(player);
        sBattlegroundMgr->ScheduleQueueUpdate(0, 0, bgQueueTypeId, bgTypeId, bracketEntry->GetBracketId());

        handler->PSendSysMessage("Added %s to Alterac Valley queue", handler->GetNameLink(player).c_str());
        return true;
    }
};

void Addmod_more_gm_commandsScripts()
{
    new more_gm_commandscript();
}

