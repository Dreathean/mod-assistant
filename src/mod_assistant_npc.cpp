#include "mod_assistant.h"

bool Assistant::OnGossipHello(Player* player, Creature* creature)
{
    ClearGossipMenuFor(player);

    if (HeirloomsEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want heirlooms", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM);

    if (GlyphsEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want glyphs", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GLYPH);

    if (GemsEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM);

    if (FlasksEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want flasks", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLASK);

    if (UtilitiesEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want utilities", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES);

    if (CanUnlockFlightPaths(player))
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want to unlock flight paths", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS);

    if (HasValidProfession(player))
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want help with my professions", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_PROFESSIONS);
    
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANTS);
    
    SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    return true;
}

bool Assistant::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
        return false;

    if (action == 1)
  //       if (player->GetLevel() >= 40)
  //          AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Vanilla Enchantment Scrolls", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANTS + 1);
    {
        OnGossipHello(player, creature);
    }
    else if (action == ASSISTANT_GOSSIP_HEIRLOOM)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want weapons", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want armor", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM + 2);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want something else", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM + 3);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_HEIRLOOM + 1 && action <= ASSISTANT_GOSSIP_HEIRLOOM + 3)
    {
        uint32 id = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_HEIRLOOM + 1:
            id = ASSISTANT_VENDOR_HEIRLOOM_WEAPON;
            break;
        case ASSISTANT_GOSSIP_HEIRLOOM + 2:
            id = ASSISTANT_VENDOR_HEIRLOOM_ARMOR;
            break;
        case ASSISTANT_GOSSIP_HEIRLOOM + 3:
            id = ASSISTANT_VENDOR_HEIRLOOM_OTHER;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), id);
    }
    else if (action == ASSISTANT_GOSSIP_GLYPH)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some major glyphs", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GLYPH + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some minor glyphs", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GLYPH + 2);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_GLYPH + 1 && action <= ASSISTANT_GOSSIP_GLYPH + 2)
    {
        bool major = true;

        if (action == ASSISTANT_GOSSIP_GLYPH + 2)
            major = false;

        uint32 id = 0;

        switch (player->getClass())
        {
        case CLASS_WARRIOR:
            id = GLYPH_WARRIOR;
            break;
        case CLASS_PALADIN:
            id = GLYPH_PALADIN;
            break;
        case CLASS_HUNTER:
            id = GLYPH_HUNTER;
            break;
        case CLASS_ROGUE:
            id = GLYPH_ROGUE;
            break;
        case CLASS_PRIEST:
            id = GLYPH_PRIEST;
            break;
        case CLASS_DEATH_KNIGHT:
            id = GLYPH_DEATH_KNIGHT;
            break;
        case CLASS_SHAMAN:
            id = GLYPH_SHAMAN;
            break;
        case CLASS_MAGE:
            id = GLYPH_MAGE;
            break;
        case CLASS_WARLOCK:
            id = GLYPH_WARLOCK;
            break;
        case CLASS_DRUID:
            id = GLYPH_DRUID;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), GetGlyphId(id, major));
    }
    else if (action == ASSISTANT_GOSSIP_GEM)
     {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some Burning Crusade gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some Wrath of the Lich King gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    
    else if (action == ASSISTANT_GOSSIP_GEM_WOTLK)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some meta gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some red gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK + 2);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some blue gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK + 3);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some yellow gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK + 4);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some purple gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK + 5);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some green gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK + 6);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some orange gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_WOTLK + 7);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_GEM_WOTLK + 1 && action <= ASSISTANT_GOSSIP_GEM_WOTLK + 7)
    {
        uint32 id = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_GEM_WOTLK + 1:
            id = ASSISTANT_VENDOR_GEM;
            break;
        case ASSISTANT_GOSSIP_GEM_WOTLK + 2:
            id = ASSISTANT_VENDOR_GEM + 1;
            break;
        case ASSISTANT_GOSSIP_GEM_WOTLK + 3:
            id = ASSISTANT_VENDOR_GEM + 2;
            break;
        case ASSISTANT_GOSSIP_GEM_WOTLK + 4:
            id = ASSISTANT_VENDOR_GEM + 3;
            break;
        case ASSISTANT_GOSSIP_GEM_WOTLK + 5:
            id = ASSISTANT_VENDOR_GEM + 4;
            break;
        case ASSISTANT_GOSSIP_GEM_WOTLK + 6:
            id = ASSISTANT_VENDOR_GEM + 5;
            break;
        case ASSISTANT_GOSSIP_GEM_WOTLK + 7:
            id = ASSISTANT_VENDOR_GEM + 6;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), id);
    }

else if (action == ASSISTANT_GOSSIP_GEM_BC)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some meta gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some red gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC + 2);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some blue gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC + 3);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some yellow gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC + 4);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some purple gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC + 5);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some green gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC + 6);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some orange gems", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM_BC + 7);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_GEM_BC + 1 && action <= ASSISTANT_GOSSIP_GEM_BC + 7)
    {
        uint32 id = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_GEM_BC + 1:
            id = ASSISTANT_VENDOR_GEM + 8;
            break;
        case ASSISTANT_GOSSIP_GEM_BC + 2:
            id = ASSISTANT_VENDOR_GEM + 9;
            break;
        case ASSISTANT_GOSSIP_GEM_BC + 3:
            id = ASSISTANT_VENDOR_GEM + 10;
            break;
        case ASSISTANT_GOSSIP_GEM_BC + 4:
            id = ASSISTANT_VENDOR_GEM + 11;
            break;
        case ASSISTANT_GOSSIP_GEM_BC + 5:
            id = ASSISTANT_VENDOR_GEM + 12;
            break;
        case ASSISTANT_GOSSIP_GEM_BC + 6:
            id = ASSISTANT_VENDOR_GEM + 13;
            break;
        case ASSISTANT_GOSSIP_GEM_BC + 7:
            id = ASSISTANT_VENDOR_GEM + 14;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), id);
    }
        
    else if (action == ASSISTANT_GOSSIP_FLASK)
    {
        player->GetSession()->SendListInventory(creature->GetGUID(), ASSISTANT_VENDOR_FLASK);
    }
    else if (action == ASSISTANT_GOSSIP_UTILITIES)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want to change my name", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 1, "Do you wish to continue the transaction?", NameChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want to change my appearance", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 2, "Do you wish to continue the transaction?", CustomizeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want to change my race", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 3, "Do you wish to continue the transaction?", RaceChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want to change my faction", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 4, "Do you wish to continue the transaction?", FactionChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_UTILITIES + 1 && action <= ASSISTANT_GOSSIP_UTILITIES + 4)
    {
        ClearGossipMenuFor(player);

        AtLoginFlags flag = AT_LOGIN_NONE;
        uint32 cost = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_UTILITIES + 1:
            flag = AT_LOGIN_RENAME;
            cost = NameChangeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 2:
            flag = AT_LOGIN_CUSTOMIZE;
            cost = CustomizeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 3:
            flag = AT_LOGIN_CHANGE_RACE;
            cost = RaceChangeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 4:
            flag = AT_LOGIN_CHANGE_FACTION;
            cost = FactionChangeCost;
            break;
        }

        SetLoginFlag(player, flag, cost);
        CloseGossipMenuFor(player);
    }
    else if (action == ASSISTANT_GOSSIP_FLIGHT_PATHS)
    {
        ClearGossipMenuFor(player);

        if (FlightPathsEnabled[EXPANSION_CLASSIC] && player->GetLevel() >= FlightPathsRequiredLevel[EXPANSION_CLASSIC] && HasAvailableFlightPaths(player, EXPANSION_CLASSIC))
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Kalimdor & Eastern Kingdoms", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS + 1, "Do you wish to continue the transaction?", FlightPathsCost[EXPANSION_CLASSIC], false);

        if (FlightPathsEnabled[EXPANSION_THE_BURNING_CRUSADE] && player->GetLevel() >= FlightPathsRequiredLevel[EXPANSION_THE_BURNING_CRUSADE]  && HasAvailableFlightPaths(player, EXPANSION_THE_BURNING_CRUSADE))
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Outland", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS + 2, "Do you wish to continue the transaction?", FlightPathsCost[EXPANSION_THE_BURNING_CRUSADE], false);

        if (FlightPathsEnabled[EXPANSION_WRATH_OF_THE_LICH_KING] && player->GetLevel() >= FlightPathsRequiredLevel[EXPANSION_WRATH_OF_THE_LICH_KING] && HasAvailableFlightPaths(player, EXPANSION_WRATH_OF_THE_LICH_KING))
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Northrend", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS + 3, "Do you wish to continue the transaction?", FlightPathsCost[EXPANSION_WRATH_OF_THE_LICH_KING], false);

        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_FLIGHT_PATHS + 1 && action <= ASSISTANT_GOSSIP_FLIGHT_PATHS + 3)
    {
        ClearGossipMenuFor(player);

        uint8 expansion = EXPANSION_CLASSIC;

        if (action == ASSISTANT_GOSSIP_FLIGHT_PATHS + 2)
            expansion = EXPANSION_THE_BURNING_CRUSADE;
        else if (action == ASSISTANT_GOSSIP_FLIGHT_PATHS + 3)
            expansion = EXPANSION_WRATH_OF_THE_LICH_KING;

        UnlockFlightPaths(player, expansion);
        OnGossipSelect(player, creature, GOSSIP_SENDER_MAIN, 1);
    }
    else if (action == ASSISTANT_GOSSIP_PROFESSIONS)
    {
        ClearGossipMenuFor(player);
        ListProfession(player, SKILL_FIRST_AID);
        ListProfession(player, SKILL_BLACKSMITHING);
        ListProfession(player, SKILL_LEATHERWORKING);
        ListProfession(player, SKILL_ALCHEMY);
        ListProfession(player, SKILL_HERBALISM);
        ListProfession(player, SKILL_COOKING);
        ListProfession(player, SKILL_MINING);
        ListProfession(player, SKILL_TAILORING);
        ListProfession(player, SKILL_ENGINEERING);
        ListProfession(player, SKILL_ENCHANTING);
        ListProfession(player, SKILL_FISHING);
        ListProfession(player, SKILL_SKINNING);
        ListProfession(player, SKILL_INSCRIPTION);
        ListProfession(player, SKILL_JEWELCRAFTING);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_PROFESSIONS + 1 && action <= ASSISTANT_GOSSIP_PROFESSIONS + 14)
    {
        ClearGossipMenuFor(player);

        uint32 skill = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_PROFESSIONS + 1:
            skill = SKILL_FIRST_AID;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 2:
            skill = SKILL_BLACKSMITHING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 3:
            skill = SKILL_LEATHERWORKING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 4:
            skill = SKILL_ALCHEMY;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 5:
            skill = SKILL_HERBALISM;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 6:
            skill = SKILL_COOKING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 7:
            skill = SKILL_MINING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 8:
            skill = SKILL_TAILORING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 9:
            skill = SKILL_ENGINEERING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 10:
            skill = SKILL_ENCHANTING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 11:
            skill = SKILL_FISHING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 12:
            skill = SKILL_SKINNING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 13:
            skill = SKILL_INSCRIPTION;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 14:
            skill = SKILL_JEWELCRAFTING;
            break;
        }

        SetProfession(player, skill);
        OnGossipSelect(player, creature, GOSSIP_SENDER_MAIN, 1);
    }
    else if (action == ASSISTANT_GOSSIP_ENCHANT)
     {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some leveling vanilla enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some good vanilla enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 2);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some rare vanilla enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 3);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some good Burning Crusade enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 4);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some rare Burning Crusade enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 5);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some good WotLK enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 6);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some rare WotLK enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 7);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I want some epic WotLK enchants", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_ENCHANT + 8);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Previous Page", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_ENCHANT + 1 && action <= ASSISTANT_GOSSIP_ENCHANT + 8)
    {
        uint32 id = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_ENCHANT + 1:
            id = ASSISTANT_VENDOR_ENCHANT;
            break;
        case ASSISTANT_GOSSIP_ENCHANT + 2:
            id = ASSISTANT_VENDOR_ENCHANT + 1;
            break;
        case ASSISTANT_GOSSIP_ENCHANT + 3:
            id = ASSISTANT_VENDOR_ENCHANT + 2;
            break;
        case ASSISTANT_GOSSIP_ENCHANT + 4:
            id = ASSISTANT_VENDOR_ENCHANT + 3;
            break;
        case ASSISTANT_GOSSIP_ENCHANT + 5:
            id = ASSISTANT_VENDOR_ENCHANT + 4;
            break;
        case ASSISTANT_GOSSIP_ENCHANT + 6:
            id = ASSISTANT_VENDOR_ENCHANT + 5;
            break;
        case ASSISTANT_GOSSIP_ENCHANT + 7:
            id = ASSISTANT_VENDOR_ENCHANT + 6;
        case ASSISTANT_GOSSIP_ENCHANT + 8:
            id = ASSISTANT_VENDOR_ENCHANT + 7;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), id);
    }
    return true;
}
