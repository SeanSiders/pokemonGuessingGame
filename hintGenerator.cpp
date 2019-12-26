#include "hintGenerator.hpp"
#include "specialEvolutionDescriptions.hpp"

hintGenerator::hintGenerator(const pokemon& randomPokemon, const std::vector<std::string>& includedRegions, const std::vector<std::string>& regionReference, const eDifficulty& difficultySetting)
{
    levelOneHints.clear();
    levelTwoHints.clear();
    levelThreeHints.clear();
    typeAbundance = 0;
    hintBuffer = "";

    randomPokemonPtr = &randomPokemon;
    includedRegionsPtr = &includedRegions;
    regionReferencePtr = &regionReference;
    difficultySettingPtr = &difficultySetting;

    typeAbundance = initializeAbundanceOfRandomPokemonType(randomPokemonPtr->typing->type);

    initializeHints();
    debugTest();
}

unsigned short hintGenerator::initializeAbundanceOfRandomPokemonType(const pokemonTypes& ePokemonType) const
{
    unsigned short i;
    unsigned short abundance = 0;

    for (const auto referenceRegion : *regionReferencePtr)
    {
        i = 0;

        for (const auto includedRegion : *includedRegionsPtr)
        {
            if (referenceRegion == includedRegion)
            {
                switch(i)
                {
                    case KANTO:
                        abundance += regionalTypeAbundanceVec[KANTO][ePokemonType];
                        break;
                    case JOHTO:
                        abundance += regionalTypeAbundanceVec[JOHTO][ePokemonType];
                        break;
                    case HOENN:
                        abundance += regionalTypeAbundanceVec[HOENN][ePokemonType];
                        break;
                    case SINNOH:
                        abundance += regionalTypeAbundanceVec[SINNOH][ePokemonType];
                        break;
                    case UNOVA:
                        abundance += regionalTypeAbundanceVec[UNOVA][ePokemonType];
                        break;
                    case KALOS:
                        abundance += regionalTypeAbundanceVec[KALOS][ePokemonType];
                        break;
                    case ALOLA:
                        abundance += regionalTypeAbundanceVec[ALOLA][ePokemonType];
                        break;
                    default:
                        std::cout << "ERROR: hintGenerator::initializeAbundanceOfRandomPokemonType";
                        return 0;
                }
            }
            i++;
        }
    }

    return abundance;
}

void hintGenerator::initializeHints()
{
    /*POKEMON TYPING HINTS*/
    if (VARIABLE_FORM == randomPokemonPtr->typing->type)
    {
        hintBuffer = "This Pokemon's primary type varies, depending on it's form";
        levelOneHints.push_back(hintBuffer);

        variableStringBuffer = getTypeString(randomPokemonPtr->typing->subType);
        hintBuffer = "This Pokemon's sub type is " + variableStringBuffer;
        levelOneHints.push_back(hintBuffer);
    }
    else if (VARIABLE_FORM == randomPokemonPtr->typing->subType)
    {
        hintBuffer = "This Pokemon's sub type varies, depending on it's form";
        levelOneHints.push_back(hintBuffer);

        variableStringBuffer = getTypeString(randomPokemonPtr->typing->type);
        hintBuffer = "This Pokemon's primary type is " + variableStringBuffer;

        if (typeAbundance > 20)
        {
            levelThreeHints.push_back(hintBuffer);
        }
        else if (typeAbundance > 5)
        {
            levelTwoHints.push_back(hintBuffer);
        }
        else
        {
            levelOneHints.push_back(hintBuffer);
        }
    }
    else
    {
        if (randomPokemonPtr->isMonoType)
        {
            if (EASY == *difficultySettingPtr)
            {
                variableStringBuffer = "mono " + getTypeString(randomPokemonPtr->typing->type);
            }
            else
            {
                hintBuffer = "This Pokemon is mono type";
                levelTwoHints.push_back(hintBuffer);

                variableStringBuffer = getTypeString(randomPokemonPtr->typing->type);
            }
            
            hintBuffer = "This Pokemon is a " + variableStringBuffer + " type";
        }
        else
        {
            if (EASY == *difficultySettingPtr)
            {
                variableStringBuffer = getTypeString(randomPokemonPtr->typing->type) + " & " + getTypeString(randomPokemonPtr->typing->subType);
                hintBuffer = "This Pokemon is a " + variableStringBuffer + " type";
            }
            else
            {
                variableStringBuffer = getTypeString(randomPokemonPtr->typing->subType);
                hintBuffer = "This Pokemon's sub type is " + variableStringBuffer;
                levelOneHints.push_back(hintBuffer);

                variableStringBuffer = getTypeString(randomPokemonPtr->typing->type);
                hintBuffer = "This Pokemon's primary type is " + variableStringBuffer;
            }
        }

        if (typeAbundance > 20)
        {
            levelThreeHints.push_back(hintBuffer);
        }
        else if (typeAbundance > 5)
        {
            levelTwoHints.push_back(hintBuffer);
        }
        else
        {
            levelOneHints.push_back(hintBuffer);
        }
    }

    /*LEGENDARY MYTHICAL HINTS*/
    if (randomPokemonPtr->isLegendary)
    {
        if (randomPokemonPtr->isMythical)
        {
            hintBuffer = "This Pokemon is a mythical Pokemon";
        }
        else
        {
            hintBuffer = "This Pokemon is a legendary Pokemon";
        }
        
        if (EASY == *difficultySettingPtr)
        {
            levelTwoHints.push_back(hintBuffer);
        }
        else
        {
            levelOneHints.push_back(hintBuffer);
        } 
    }
    else
    {
        hintBuffer = "This Pokemon is not a Legendary Pokemon";
        levelThreeHints.push_back(hintBuffer);
    }

    /*EVOLUTION HINTS*/
    if (randomPokemonPtr->isStarter)
    {
        hintBuffer = "This Pokemon is a starter Pokemon";
        levelOneHints.push_back(hintBuffer);
    }
    else
    {
        hintBuffer = "This Pokemon is not a starter Pokemon";
        levelThreeHints.push_back(hintBuffer);

        if (UNEVOLVED == randomPokemonPtr->evolutionStage)
        {
            hintBuffer = "This pokemon is an unevolved form";
        }
        else
        {
            variableStringBuffer = getEvolutionStageString(randomPokemonPtr->evolutionStage);
            hintBuffer = "This Pokemon is a " + variableStringBuffer + " stage evolution";
        }

        if (SECOND == randomPokemonPtr->evolutionStage)
        {
            levelTwoHints.push_back(hintBuffer);
        }
        else
        {
            levelThreeHints.push_back(hintBuffer);

            if (randomPokemonPtr->canEvolve)
            {
                hintBuffer = "This Pokemon can evolve";
                variableStringBuffer = getEvolutionTypeString(randomPokemonPtr->evolutionType);

                if (EASY == *difficultySettingPtr)
                {
                    hintBuffer += " " + variableStringBuffer;
                    if (LEVEL == randomPokemonPtr->evolutionType)
                    {
                        levelThreeHints.push_back(hintBuffer);
                    }
                    else
                    {
                        levelTwoHints.push_back(hintBuffer);
                    }
                }
                else
                {
                    levelThreeHints.push_back(hintBuffer);

                    hintBuffer += " " + variableStringBuffer;
                    levelOneHints.push_back(hintBuffer);
                }     
            }
            else
            {
                hintBuffer = "This Pokemon cannot evolve";
                if (EASY == *difficultySettingPtr)
                {
                    levelTwoHints.push_back(hintBuffer);
                }
                else
                {
                    levelOneHints.push_back(hintBuffer);
                }
            }    
        }
    }

    /*REGION ORIGIN HINTS*/
    if (includedRegionsPtr->size() > 1)
    {
        variableStringBuffer = getRegionOriginString(randomPokemonPtr->regionOrigin);
        hintBuffer = "This Pokemon originated from " + variableStringBuffer;

        if (EASY == *difficultySettingPtr)
        {
            levelTwoHints.push_back(hintBuffer);
        }
        else
        {
            levelOneHints.push_back(hintBuffer);
        }
    }

    /*GENDER HINTS*/
    if (randomPokemonPtr->isGenderless)
    {
        hintBuffer = "This Pokemon is genderless";
        levelOneHints.push_back(hintBuffer);
    }
    else if (randomPokemonPtr->isMonoGender)
    {
        if (EASY == *difficultySettingPtr || MODERATE == *difficultySettingPtr)
        {
            variableStringBuffer = getMonoGenderString(randomPokemonPtr->possibleGender);
            hintBuffer = "This Pokemon can only be " + variableStringBuffer;
            levelOneHints.push_back(hintBuffer);
        }
        else
        {
            hintBuffer = "This Pokemon can only be one gender";
            levelTwoHints.push_back(hintBuffer);
        }
    }
}

std::string hintGenerator::getTypeString(const pokemonTypes& ePokemonType) const
{
    switch(ePokemonType)
    {
        case NORMAL:
            return "normal";
        case FIRE:
            return "fire";
        case WATER:
            return "water";
        case ELECTRIC:
            return "electric";
        case GRASS:
            return "grass";
        case ICE:
            return "ice";
        case FIGHTING:
            return "fighting";
        case POISON:
            return "poison";
        case GROUND:
            return "ground";
        case FLYING:
            return "flying";
        case PSYCHIC:
            return "psychic";
        case BUG:
            return "bug";
        case ROCK:
            return "rock";
        case GHOST:
            return "ghost";
        case DRAGON:
            return "dragon";
        case DARK:
            return "dark";
        case STEEL:
            return "steel";
        case FAIRY:
            return "fairy";
        default:
            std::cout << "ERROR: hintGenerator::getTypeString";
            return "";
    }
}

std::string hintGenerator::getEvolutionStageString(const evolutionStages& eEvolutionStage) const
{
    switch (eEvolutionStage)
    {
        case FIRST:
            return "first";
        case SECOND:
            return "second";
        default:
            std::cout << "ERROR: hintGenerator::getEvolutionStageString";
            return "";
    }
}

std::string hintGenerator::getEvolutionTypeString(const evolutionTypes& eEvolutionType) const
{
    switch (eEvolutionType)
    {
        case LEVEL:
            return "by leveling up";
        case LEVEL_MOVE:
            return "by leveling up while knowing a particular move";
        case ITEM:
            return "by item";
        case TRADE:
            return "by trade";
        case TRADE_ITEM:
            return "by trade, while holding a particular item";
        case FRIENDSHIP:
            return "by friendship level";
        case SPECIAL:
            return getSpecialEvolutionTypeString(eEvolutionType);
        default:
            std::cout << "ERROR: hingGenerator::getEvolutionTypeString";
            return "";
    }
}

std::string hintGenerator::getSpecialEvolutionTypeString(const evolutionTypes& eEvolutionType) const
{
    std::map<unsigned short, std::string>::iterator specialEvolutionIterator = specialEvolutionMap.find(randomPokemonPtr->pokemonIndex);
    
    if (specialEvolutionIterator != specialEvolutionMap.end())
    {
        return specialEvolutionIterator->second;
    }
    else
    {
        std::cout << "ERROR: hintGenerator::getSpecialEvolutionTypeString";
        return "";
    }
}

std::string hintGenerator::getRegionOriginString(const regions& eRegionOrigin) const
{
    switch (eRegionOrigin)
    {
        case KANTO:
            return "Kanto";
        case JOHTO:
            return "Johto";
        case HOENN:
            return "Hoenn";
        case SINNOH:
            return "Sinnoh";
        case UNOVA:
            return "Unova";
        case KALOS:
            return "Kalos";
        case ALOLA:
            return "Alola";
        default:
            std::cout << "ERROR: hintGenerator::getRegionOriginString";
            return "";
    }
}

std::string hintGenerator::getMonoGenderString(const gender& eGender) const
{
    switch (eGender)
    {
        case MALE:
            return "male";
        case FEMALE:
            return "female";
        default:
            std::cout << "ERROR: hintGenerator::getMonoGenderString";
            return "";
    }
}

void hintGenerator::debugTest()
{
    std::cout << randomPokemonPtr->nationalPokedexNumber << ". " << randomPokemonPtr->name << " | " << getTypeString(randomPokemonPtr->typing->type) << " / " << getTypeString(randomPokemonPtr->typing->subType) << "\n";

    //printAllHints();
}

void hintGenerator::printAllHints()
{
    std::cout << "LEVEL 3\n";
    for (const auto str : levelThreeHints)
    {
        std::cout << str << "\n";
    }

    std::cout << "LEVEL 2\n";
    for (const auto str : levelTwoHints)
    {
        std::cout << str << "\n";
    }

    std::cout << "LEVEL 1\n";
    for (const auto str : levelOneHints)
    {
        std::cout << str << "\n";
    }
}