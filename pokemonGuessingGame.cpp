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
    std::cout << "(Y / N)" << "\n>>> ";
    std::string stringInput;

    getline(std::cin, stringInput);
    stringInput = toupper(stringInput[0]);
    
    std::cout << "\n";

    if ("Y" == stringInput)
    {
        return true;
    }
    
    return false;
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

    std::cout << "Is this correct? ";
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
    << "EASY || MODERATE || HARD || EXPERT\n";
    
    std::string desiredDifficulty;
    desiredDifficulty = getValidStringInput(validDifficultyLevels);

    while (desiredDifficulty.empty())
    {
        desiredDifficulty = getValidStringInput(validDifficultyLevels);
    }

    setDifficultyParameters(desiredDifficulty);

    std::cout << "\nYOUR DESIRED DIFFICULTY LEVEL\n" << desiredDifficulty << "\n";
    std::cout << "Is this correct? ";
}

void pokemonGuessingGame::setDifficultyParameters(const std::string& desiredDifficulty)
{
    for (uint64_t i = 0; i < validDifficultyLevels.size(); i++)
    {
        if (desiredDifficulty == validDifficultyLevels[i])
        {
            switch (i)
            {
                case EASY:
                    eDesiredDifficulty = EASY;
                    maxHints = 12;
                    return;
                case MODERATE:
                    eDesiredDifficulty = MODERATE;
                    maxHints = 10;
                    return;
                case HARD:
                    eDesiredDifficulty = HARD;
                    maxHints = 8;
                    return;
                case EXPERT:
                    eDesiredDifficulty = EXPERT;
                    maxHints = 5;
                    return;
                default:
                    std::cout << "ERROR: pokemonGuessingGame::setDifficulty";
                    return;
            }
        }
    }
}

uint64_t pokemonGuessingGame::getMaxHints() const
{
    return maxHints;
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

std::string pokemonGuessingGame::getValidPokemonGuess()
{
    uint64_t closestMatchIndex;
    bool isValidVerified = false;

    do
    {
        std::string pokemonGuess;

        std::cout << ">>> ";
        getline(std::cin, pokemonGuess);
        formatPokemonNameString(pokemonGuess);

        uint64_t mostMatchingChars = 0;

        for (const auto pokemonIndex : includedPokemonIndices)
        {
            if (pokemonGuess == pokemonNamesVec[pokemonIndex])
            {
                return pokemonGuess;
            }
            else
            {
                const auto shorterStrLength = getShorterString(pokemonGuess, pokemonNamesVec[pokemonIndex]).length();
                uint64_t i = 0;

                while (pokemonNamesVec[pokemonIndex][i] == pokemonGuess[i] && i < shorterStrLength)
                {
                    i++;
                }

                if (i > mostMatchingChars)
                {
                    mostMatchingChars = i;
                    closestMatchIndex = pokemonIndex;
                }
            }
        }

        if (closestMatchIndex == (28 || 31))
        {
            std::cout << "Did you mean Nidoran? ";
            
            if (verifyUserInput())
            {
                std::cout << "Please input F for " << pokemonNamesVec[28] << "or M for" << pokemonNamesVec[31];

                std::string userInStr;
                getline(std::cin, userInStr);
                toupper(userInStr[0]);

                if (userInStr[0] == 'F')
                {
                    return pokemonNamesVec[28];
                }
                else if (userInStr[0] == 'M')
                {
                    return pokemonNamesVec[31];
                }
            } 
        }
        else
        {
            std::cout << "Did you mean " << pokemonNamesVec[closestMatchIndex] << " ? ";
            isValidVerified = verifyUserInput();
        }
    }
        while (!isValidVerified);

    return pokemonNamesVec[closestMatchIndex];
}

bool pokemonGuessingGame::playAgain(bool& hasDesiredSettings)
{
    std::cout << "Would you like to play again?\n";
    if (verifyUserInput())
    {
        std::cout << "Would you like to apply new game settings?\n";
        hasDesiredSettings = !verifyUserInput();
        return true;
    }
    else
    {
        return false;
    }

    return false;
}

void pokemonGuessingGame::removePokemon(const uint64_t& pokemonIndex)
{
    for (const auto i : includedPokemonIndices)
    {
        if (pokemonIndex == i)
        {
            includedPokemonIndices.erase(includedPokemonIndices.begin() + i);
            totalIncludedPokemon--;
            return;
        }
    }  
}

void pokemonGuessingGame::debugTest(const uint64_t& index)
{
        pokemon debugPokemon(index, includedRegions, indexRangeReference);
        getHintGenerator(debugPokemon);
}