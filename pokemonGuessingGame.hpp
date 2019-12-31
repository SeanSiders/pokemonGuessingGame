#pragma once
#include <iostream>
#include <vector>

struct indexRange
{
    uint64_t firstIndex;
    uint64_t lastIndex;
};

enum eDifficulty
{
    EASY,
    MODERATE,
    HARD,
    EXPERT
};

class pokemon;
class hintGenerator;

class pokemonGuessingGame
{
    public:
    pokemonGuessingGame();
    void reset();

    void getDesiredRegionsFromUser();
    void getDesiredDifficultyFromUser();

    bool verifyUserInput();

    void initializeIncludedPokemonIndices();

    pokemon getRandomPokemon() const;
    hintGenerator getHintGenerator(pokemon& randomPokemonRef) const;
    uint64_t getMaxHints();

    std::string getValidPokemonGuess();
    bool playAgain(bool& hasDesiredSettings);
    void removePokemon(const uint64_t& pokemonIndex);
    
    void debugTest(const uint64_t& index);

    private:
    /*REFERENCE VARIABLES*/
    const std::vector<std::string> regionReference = {"KANTO", "JOHTO", "HOENN", "SINNOH", "UNOVA", "KALOS", "ALOLA"};
    const std::vector<indexRange> indexRangeReference =
    {
        {0, 150},
        {151, 250},
        {251, 385},
        {386, 492},
        {493, 648},
        {649, 720},
        {721, 806}
    };

    /*VARIABLES*/
    std::vector<std::string> availableRegions;
    std::vector<std::string> includedRegions;
    std::vector<uint64_t> includedPokemonIndices;
    std::vector<indexRange> pokemonIndexRanges;
    uint64_t totalIncludedPokemon;

    void pushBackIndexRangesByRegion(const std::string& regionName);

    void getValidRegionInput(bool& breakInputLoop);
    std::string getValidStringInput(const std::vector<std::string>& validInputs) const;

    eDifficulty eDesiredDifficulty;
    std::vector<std::string> validDifficultyLevels = {"EASY", "MODERATE", "HARD", "EXPERT"};
    void setDifficultyParameters(const std::string& desiredDifficulty);
    
    uint64_t maxHints;
    uint64_t getMaxHints() const;
};