#pragma once
#include "pokemon.hpp"
#include "pokemonGuessingGame.hpp"
#include "regionalTypeAbundance.hpp"

class hintGenerator
{
    public:
    hintGenerator(const pokemon& randomPokemon, const std::vector<std::string>& includedRegions, const std::vector<std::string>& regionReference, const eDifficulty& difficultySetting);
    void generateHint(const float& ratio);

    private:
    const pokemon* randomPokemonPtr;
    const std::vector<std::string>* includedRegionsPtr;
    const std::vector<std::string>* regionReferencePtr;
    const eDifficulty* difficultySettingPtr;

    unsigned short typeAbundance;
    unsigned short initializeAbundanceOfRandomPokemonType(const pokemonTypes& ePokemonType) const;

    /*HINT GENERATOR TOOLS*/
    void initializeHints();
    std::string getTypeString(const pokemonTypes& ePokemonType) const;
    void initializeTyping();
    void initializeSubTyping();
    std::string getEvolutionStageString(const evolutionStages& eEvolutionStage) const;
    std::string getEvolutionTypeString(const evolutionTypes& eEvolutionType) const;
    std::string getSpecialEvolutionTypeString(const evolutionTypes& eEvolutionType) const;
    std::string getRegionOriginString(const regions& eRegionOrigin) const;
    std::string getMonoGenderString(const gender& eGender) const;
    std::string getBodyColorString(const colors& eBodyColor) const;

    std::string hintBuffer;
    std::string variableStringBuffer;

    std::vector<std::string> smallerHints;
    std::vector<std::string> biggerHints;

    /*DEBUG TOOLS*/
    void debugTest();
    void printAllHints();
};