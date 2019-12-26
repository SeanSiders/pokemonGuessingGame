#include <iostream>

#include "pokemonGuessingGame.cpp"
#include "pokemon.hpp"

int main()
{
    srand(time(NULL));
    bool programRunning = true;

    while(programRunning)
    {
        pokemonGuessingGame game;
    
        do { game.getDesiredRegionsFromUser(); }
            while (!game.verifyUserInput());

        game.initializeIncludedPokemonIndices();

        uint64_t i = 251;
        std::string in;
        while (i < 386)
        {       
            game.debugTest(i);
            i++;
        }
    
        /*
        do { game.getDesiredDifficultyFromUser(); }
            while ( !game.verifyUserInput() );
        */
        /*
        std::string in;
        while (in.empty())
        {
            pokemon randomPokemon = game.getRandomPokemon();
            hintGenerator hintGeneratorInstance = game.getHintGenerator(randomPokemon);
            getline(std::cin, in);
        }
        */
        /*
        bool gameInstanceRunning = true;

        while (gameInstanceRunning)
        {
            auto randomPokemonIndex = generateRandomNumber(0, totalIncludedPokemon - 1);
            auto randomPokemon = includedPokemonVector[randomPokemonIndex];

            uint64_t hintsGiven = 0;
            while (hintsGiven < game.getMaxHints())
            {
                auto randomHintIndex = generateRandomNumber(0, 2);
                game.generateHint(randomHintIndex);
            }
        }*/
    }

    return 0;
}