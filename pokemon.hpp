#pragma once
#include "pokemonParams.hpp"
#include "pokemonGuessingGame.hpp"

class pokemon
{
    public:
    pokemon(uint64_t index, const std::vector<std::string>& includedRegions, const std::vector<indexRange>& indexRangeReference);

    /*PARAMS*/
    uint64_t pokemonIndex;
    uint64_t nationalPokedexNumber;
    std::string name;
    regions regionOrigin;
    typings* typing;
    evolutionStages evolutionStage;
    gender possibleGender;
    evolutionTypes evolutionType;

    bool isMonoType;
    bool isLegendary;
    bool isMythical;
    bool isStarter;
    bool canEvolve;
    bool isGenderless;
    bool isMonoGender;

    private:
    regions getRegionOrigin(const std::vector<indexRange>& indexRangeReference);
    void initializeParams();

    bool getMonoTypeBool() const;
    void initializeBoolByVec(bool& boolToInitialize, const std::vector<unsigned short>& indicesVec);
    void initializeEvolutionParams();
    void initializeGenderParams();
};