#include "pokemonGuessingGame.hpp"

#include <iostream>
#include <vector>

#include "tools.hpp"
#include "pokemon.cpp"
#include "hintGenerator.cpp"

pokemonGuessingGame::pokemonGuessingGame()
{
    reset();
}

void pokemonGuessingGame::reset()
{
    includedRegions.clear();
    availableRegions = regionReference;
    includedPokemonIndices.clear();
    pokemonIndexRanges.clear();
    totalIncludedPokemon = 0;
    eDesiredDifficulty = EASY;
}

bool pokemonGuessingGame::verifyUserInput()
{
    std::cout << "Is this correct? (Y / N)" << "\n>>> ";
    std::string stringInput;

    getline(std::cin, stringInput);
    stringInput = toupper(stringInput[0]);
    
    if ("Y" == stringInput)
    {
        std::cout << "\n";
        return true;
    }
    else if ("N" == stringInput)
    {
        std::cout << "\n";
        return false;
    }
    else
    {
        std::cout << "ERROR: pokemonGuessingGame::verifyUserInput()";
    }
}

void pokemonGuessingGame::getDesiredRegionsFromUser()
{   
    availableRegions = regionReference;
    includedRegions.clear();

    std::cout
    << "Type a Pokemon region you would like to include in the game, then push enter\n"
    << "When you are done including regions, simply press enter again without typing any characters\n"
    << "VALID REGION INPUTS (caps not necessary)\n";
    
    printStringVector(availableRegions);

    bool breakInputLoop = false;
    while (!breakInputLoop)
    {
        getValidRegionInput(breakInputLoop);
    }

    sortStringVector(includedRegions, regionReference);

    std::cout << "\nYOUR INCLUDED REGIONS\n";
    printStringVector(includedRegions);
}

void pokemonGuessingGame::getValidRegionInput(bool& breakInputLoop)
{
    std::string stringInput = getValidStringInput(availableRegions);

    if (stringInput.empty())
    {
        if (!includedRegions.empty())
        {
            breakInputLoop = true;
        }

        return;
    }

    includedRegions.push_back(stringInput);
    popStringFromVector(availableRegions, stringInput);

    if (availableRegions.empty())
    {
        breakInputLoop = true;
    }

    return;
}

std::string pokemonGuessingGame::getValidStringInput(const std::vector<std::string>& validInputs) const
{
    std::string stringInput;

    std::cout << ">>> ";
    getline(std::cin, stringInput);
    stringToAllCaps(stringInput);

    while (!isValidStringInput(stringInput, validInputs))
    {
        if (stringInput.empty())
        {
            return stringInput;
        }
        else if (isValidStringInput(stringInput, regionReference))
        {
            std::cout << stringInput << " Has already been included";
        }
        else
        {
            std::cout << "INVALID INPUT: choose from the regions provided";
        }

        std::cout << "\n>>> ";
        getline(std::cin, stringInput);
        stringToAllCaps(stringInput);
    }

    return stringInput;
    
}

void pokemonGuessingGame::initializeIncludedPokemonIndices()
{
    for (const std::string regionName : includedRegions)
    {
        pushBackIndexRangesByRegion(regionName);
    }
    
    for (const auto& regionIndexRange : pokemonIndexRanges)
    {
        for (uint64_t i = regionIndexRange.firstIndex; i <= regionIndexRange.lastIndex; i++)
        {
            includedPokemonIndices.push_back(i);
        }
    }

    totalIncludedPokemon = includedPokemonIndices.size();
}

void pokemonGuessingGame::pushBackIndexRangesByRegion(const std::string& regionName)
{
    uint64_t i = 0;
    for (const auto regionRef : regionReference)
    {
        if (regionRef == regionName)
        {
            pokemonIndexRanges.push_back(indexRangeReference[i]);
            return;
        }
        i++;
    }
}

void pokemonGuessingGame::getDesiredDifficultyFromUser()
{
    std::cout
    << "Type in a difficulty level, then push enter\n"
    << "VALID DIFFICULTY INPUTS\n"
    << "EASY || MODERATE || HARD || EXPERT";
    
    auto desiredDifficulty = getValidStringInput(validDifficultyLevels);
    setDifficultyParameters(desiredDifficulty);

    std::cout << "\nYOUR DESIRED DIFFICULTY LEVEL\n" << desiredDifficulty << "\n";
}

void pokemonGuessingGame::setDifficultyParameters(const std::string& desiredDifficulty)
{
    for (uint64_t i = 0; i < validDifficultyLevels.size(); i++)
    {
        if (desiredDifficulty == validDifficultyLevels[i])
        {
            switch (i)
            {
                case 0:
                    eDesiredDifficulty = EASY;
                    maxHints = 20;
                    return;
                case 1:
                    eDesiredDifficulty = MODERATE;
                    maxHints = 12;
                    return;
                case 2:
                    eDesiredDifficulty = HARD;
                    maxHints = 8;
                    return;
                case 3:
                    eDesiredDifficulty = EXPERT;
                    maxHints = 3;
                    return;
                default:
                    std::cout << "ERROR: pokemonGuessingGame::setDifficulty";
                    return;
            }
        }
    }
}

pokemon pokemonGuessingGame::getRandomPokemon() const
{
    const uint64_t randomNumber = generateRandomNumber(0, totalIncludedPokemon - 1);
    const uint64_t randomPokemonIndex = includedPokemonIndices[randomNumber];
    class pokemon randomPokemon(randomPokemonIndex, includedRegions, indexRangeReference);
    return randomPokemon;
}

hintGenerator pokemonGuessingGame::getHintGenerator(pokemon& randomPokemonRef) const
{
    hintGenerator hintGeneratorInstance(randomPokemonRef, includedRegions, regionReference, eDesiredDifficulty);
    return hintGeneratorInstance;
}

uint64_t pokemonGuessingGame::getMaxHints()
{
    return maxHints;
}

void pokemonGuessingGame::generateHint(const uint64_t& randomIndex)
{
}

void pokemonGuessingGame::debugTest(const uint64_t& index)
{
        pokemon debugPokemon(index, includedRegions, indexRangeReference);
        getHintGenerator(debugPokemon);
}