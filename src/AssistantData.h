#ifndef ASSISTANTDATA_H
#define ASSISTANTDATA_H

struct SpawnPoints
{
    uint32 MapId;
    float X;
    float Y;
    float Z;
    float O;
};

struct Mounts
{
    int32 RaceId;
    int32 ClassId;
    int32 TeamId;
    uint32 SpellId;
    uint32 RequiredLevel;
    uint32 RequiredSpellId;
};

class AssistantData
{
    public:
        std::vector<SpawnPoints> GetSpawnPoints();
        std::vector<Mounts> GetMounts();
        int GetMountsCount();
};

#endif