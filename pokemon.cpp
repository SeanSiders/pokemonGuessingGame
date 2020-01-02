#include "pokemon.hpp"

pokemon::pokemon(uint64_t index, const std::vector<std::string>& includedRegions, const std::vector<indexRange>& indexRangeReference)
{
    pokemonIndex = index;
    nationalPokedexNumber = pokemonIndex + 1;
    
    name = pokemonNamesVec[pokemonIndex];
    typing = &pokemonTypingVec[pokemonIndex];
    regionOrigin = getRegionOrigin(indexRangeReference);
    evolutionStage = evolutionStageVec[pokemonIndex];
    pokedexCategory = pokedexCategoryVec[pokemonIndex];
    bodyColor = bodyColorVec[pokemonIndex];
    heightWeight = heightWeightVec[pokemonIndex];
    pokedexEntry = pokedexEntriesVec[pokemonIndex];

    initializeParams();
}

regions pokemon::getRegionOrigin(const std::vector<indexRange>& indexRangeReference)
{  
    uint64_t i = 0;
    for (const indexRange range : indexRangeReference)
    {
        if (pokemonIndex <= range.lastIndex)
        {
            switch (i)
            {
                case 0:
                    return KANTO;
                case 1:
                    return JOHTO;
                case 2:
                    return HOENN;
                case 3:
                    return SINNOH;
                case 4:
                    return UNOVA;
                case 5:
                    return KALOS;
                case 6:
                    return ALOLA;
                default:
                    std::cout << "ERROR: pokemon::initializeRegionOrigion";
                    return KANTO;
            }
        }
        i++;
    }
    
    return KANTO;
}

void pokemon::initializeParams()
{
    isMonoType = getMonoTypeBool();
    initializeBoolByVec(isLegendary, legendaryIndicesVec);

    if (isLegendary)
    {
        isStarter = false;
        initializeBoolByVec(isMythical, mythicalIndicesVec);
    }
    else
    {
        isMythical = false;
        initializeBoolByVec(isStarter, starterIndicesVec);
    }

    initializeEvolutionParams();
    initializeGenderParams();
}

bool pokemon::getMonoTypeBool() const
{
    return NONE == typing->subType;  
}

void pokemon::initializeBoolByVec(bool& boolToInitialize, const std::vector<unsigned short>& indicesVec)
{
    for (const auto index : indicesVec)
    {
        if (index > pokemonIndex)
        {
            boolToInitialize = false;
            return;
        }
        else if (index == pokemonIndex)
        {
            boolToInitialize = true;
            return;
        }
    }
}

void pokemon::initializeEvolutionParams()
{
    std::map<unsigned short, evolutionTypes>::iterator canEvolveByIterator = canEvolveByMap.find(pokemonIndex);

    if (canEvolveByIterator != canEvolveByMap.end())
    {
        canEvolve = true;
        evolutionType = canEvolveByIterator->second;
    }
    else
    {
        canEvolve = false;
    }
}

void pokemon::initializeGenderParams()
{
    initializeBoolByVec(isGenderless, genderlessIndicesVec);

    if (isGenderless)
    {
        isMonoGender = false;
    }
    else
    {
        std::map<unsigned short, gender>::iterator monoGenderIterator = monoGenderMap.find(pokemonIndex);

        if (monoGenderIterator != monoGenderMap.end())
        {
            isMonoGender = true;
            possibleGender = monoGenderIterator->second;
        }
        else
        {
            isMonoGender = false;
        }
    }
}