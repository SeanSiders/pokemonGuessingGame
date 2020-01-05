#include "hintGenerator.hpp"
#include "specialEvolutionDescriptions.hpp"
#include "tools.hpp"

hintGenerator::hintGenerator(const pokemon& randomPokemon, const std::vector<std::string>& includedRegions, const std::vector<std::string>& regionReference, const eDifficulty& difficultySetting)
{
    biggerHints.clear();
    smallerHints.clear();
    typeAbundance = 0;
    hintBuffer.clear();

    randomPokemonPtr = &randomPokemon;
    includedRegionsPtr = &includedRegions;
    regionReferencePtr = &regionReference;
    difficultySettingPtr = &difficultySetting;

    typeAbundance = initializeAbundanceOfRandomPokemonType(randomPokemonPtr->typing->type);

    initializeHints();
    //debugTest();
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
        biggerHints.push_back(hintBuffer);

        variableStringBuffer = getTypeString(randomPokemonPtr->typing->subType);
        hintBuffer = "This Pokemon's sub type is " + variableStringBuffer;
        biggerHints.push_back(hintBuffer);
    }
    else if (VARIABLE_FORM == randomPokemonPtr->typing->subType)
    {
        hintBuffer = "This Pokemon's sub type varies, depending on it's form";
        biggerHints.push_back(hintBuffer);

        variableStringBuffer = getTypeString(randomPokemonPtr->typing->type);
        hintBuffer = "This Pokemon's primary type is " + variableStringBuffer;

        if (typeAbundance > 20)
        {
            smallerHints.push_back(hintBuffer);
        }
        else
        {
            biggerHints.push_back(hintBuffer);
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
                smallerHints.push_back(hintBuffer);

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
                biggerHints.push_back(hintBuffer);

                variableStringBuffer = getTypeString(randomPokemonPtr->typing->type);
                hintBuffer = "This Pokemon's primary type is " + variableStringBuffer;
            }
        }

        if (typeAbundance > 20)
        {
            smallerHints.push_back(hintBuffer);
        }
        else
        {
            biggerHints.push_back(hintBuffer);
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
            smallerHints.push_back(hintBuffer);
        }
        else
        {
            biggerHints.push_back(hintBuffer);
        } 
    }

    /*EVOLUTION HINTS*/
    if (randomPokemonPtr->isStarter)
    {
        hintBuffer = "This Pokemon is a starter Pokemon";
        biggerHints.push_back(hintBuffer);
    }
 
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
        smallerHints.push_back(hintBuffer);
    }
    else
    {
        smallerHints.push_back(hintBuffer);

        if (randomPokemonPtr->canEvolve)
        {
            hintBuffer = "This Pokemon can evolve";
            variableStringBuffer = getEvolutionTypeString(randomPokemonPtr->evolutionType);

            if (EASY == *difficultySettingPtr)
            {
                hintBuffer += " " + variableStringBuffer;
                if (LEVEL == randomPokemonPtr->evolutionType)
                {
                    smallerHints.push_back(hintBuffer);
                }
                else
                {
                    biggerHints.push_back(hintBuffer);
                }
            }
            else
            {
                smallerHints.push_back(hintBuffer);

                hintBuffer += " " + variableStringBuffer;
                biggerHints.push_back(hintBuffer);
            }     
        }
        else
        {
            hintBuffer = "This Pokemon cannot evolve";
            if (EASY == *difficultySettingPtr)
            {
                smallerHints.push_back(hintBuffer);
            }
            else
            {
                biggerHints.push_back(hintBuffer);
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
            smallerHints.push_back(hintBuffer);
        }
        else
        {
            biggerHints.push_back(hintBuffer);
        }
    }

    /*GENDER HINTS*/
    if (randomPokemonPtr->isGenderless)
    {
        hintBuffer = "This Pokemon is genderless";
        biggerHints.push_back(hintBuffer);
    }
    else if (randomPokemonPtr->isMonoGender)
    {
        if (EASY == *difficultySettingPtr || MODERATE == *difficultySettingPtr)
        {
            variableStringBuffer = getMonoGenderString(randomPokemonPtr->possibleGender);
            hintBuffer = "This Pokemon can only be " + variableStringBuffer;
            biggerHints.push_back(hintBuffer);
        }
        else
        {
            hintBuffer = "This Pokemon can only be one gender";
            smallerHints.push_back(hintBuffer);
        }
    }

    /*CHAR HINTS*/
    const auto firstChar = randomPokemonPtr->name[0];
    hintBuffer = "The first letter of this Pokemon's name is: ";
    hintBuffer += firstChar;

    biggerHints.push_back(hintBuffer);

    const auto lastChar = randomPokemonPtr->name[randomPokemonPtr->name.length() - 1];
    hintBuffer = "The last letter of this Pokemon's name is: ";
    hintBuffer += lastChar;
    biggerHints.push_back(hintBuffer);
    
    /*POKEDEX HINTS*/
    variableStringBuffer = randomPokemonPtr->pokedexCategory;
    hintBuffer = "The Pokedex refers to this Pokemon as the " + variableStringBuffer + " Pokemon";
    biggerHints.push_back(hintBuffer);

    hintBuffer = "This Pokemon's national pokedex number is #";
    hintBuffer += std::to_string(randomPokemonPtr->nationalPokedexNumber);
    biggerHints.push_back(hintBuffer);

    hintBuffer = randomPokemonPtr->pokedexEntry.first;
    biggerHints.push_back(hintBuffer);

    hintBuffer = randomPokemonPtr->pokedexEntry.second;
    biggerHints.push_back(hintBuffer);

    /*COLOR HINTS*/
    variableStringBuffer = getBodyColorString(randomPokemonPtr->bodyColor);
    hintBuffer = "This Pokemon's primary body color is " + variableStringBuffer;
    biggerHints.push_back(hintBuffer);

    /*HEIGHT WEIGHT HINTS*/
    variableStringBuffer = std::to_string(randomPokemonPtr->heightWeight.feet) + "'" + std::to_string(randomPokemonPtr->heightWeight.inches) + "\"";
    hintBuffer = "This Pokemon is " + variableStringBuffer + " in height";
    if (randomPokemonPtr->heightWeight.feet > 10 || randomPokemonPtr->heightWeight.feet < 1)
    {
        smallerHints.push_back(hintBuffer);
    }
    else
    {
        biggerHints.push_back(hintBuffer);
    }

    variableStringBuffer = std::to_string(randomPokemonPtr->heightWeight.weight);
    hintBuffer = "This Pokemon weighs on average " + variableStringBuffer + " lbs";
    if (randomPokemonPtr->heightWeight.weight > 100.0 || randomPokemonPtr->heightWeight.weight < 5.0)
    {
        smallerHints.push_back(hintBuffer);
    }
    else
    {
        biggerHints.push_back(hintBuffer);
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

std::string hintGenerator::getBodyColorString(const colors& eBodyColor) const
{
    switch (eBodyColor)
    {
        case RED: return "red";
        case ORANGE: return "orange";
        case BLUE: return "blue";
        case YELLOW: return "yellow";
        case GREEN: return "green";
        case BLACK: return "black";
        case BROWN: return "brown";
        case TAN: return "tan";
        case PURPLE: return "purple";
        case GRAY: return "gray";
        case SILVER: return "silver";
        case WHITE: return "white";
        case PINK: return "pink";
        default:
            std::cout << "ERROR: hintGenerator::getBodyColorString";
            return "";
    }
}

void hintGenerator::generateHint(const _Float64& ratio)
{
    uint64_t randomIndex;
    uint64_t hintVecSize;

    if (ratio <= .5 && !smallerHints.empty())
    {
        hintVecSize = smallerHints.size();

        if (hintVecSize == 1)
        {
            std::cout << smallerHints[0];
            smallerHints.erase(smallerHints.begin());
        }
        else
        {
            randomIndex = generateRandomNumber(0, hintVecSize - 1);
            std::cout << smallerHints[randomIndex];
            smallerHints.erase(smallerHints.begin() + randomIndex);
        }
    }
    else
    {
        hintVecSize = biggerHints.size();

        if (hintVecSize == 1)
        {
            std::cout << biggerHints[0];
            biggerHints.erase(smallerHints.begin());
        }
        else
        {
            randomIndex = generateRandomNumber(0, hintVecSize - 1);
            std::cout << biggerHints[randomIndex];
            biggerHints.erase(biggerHints.begin() + randomIndex);
        }
    }

    std::cout << "\n";
}

void hintGenerator::debugTest()
{
    std::cout << randomPokemonPtr->nationalPokedexNumber << ". " << randomPokemonPtr->name << "\n";
    printAllHints();
}

void hintGenerator::printAllHints()
{
    std::cout << "LEVEL 2\n";
    for (const auto str : smallerHints)
    {
        std::cout << str << "\n";
    }

    std::cout << "LEVEL 1\n";
    for (const auto str : biggerHints)
    {
        std::cout << str << "\n";
    }
}