#include <iostream>

#include "pokemonGuessingGame.cpp"
#include "pokemon.hpp"

int main()
{
    srand(time(NULL));
    bool programRunning = true;

    do
    {
        pokemonGuessingGame game;
        
        do { game.getDesiredRegionsFromUser(); }
            while (!game.verifyUserInput());

        game.initializeIncludedPokemonIndices();
    
        do { game.getDesiredDifficultyFromUser(); }
            while ( !game.verifyUserInput() );
        /*
        std::string str;

        for (uint64_t i = 0; i < 807; i++)
        {
            game.debugTest(i);
            getline(std::cin, str);
        }

        return 0;
        */
        bool userHasDesiredSettings = true;

        do
        {
            pokemon randomPokemon = game.getRandomPokemon();
            hintGenerator hintGeneratorInstance = game.getHintGenerator(randomPokemon);

            const uint64_t maxHints = game.getMaxHints();
            uint64_t currentHint = 1;
            std::string userGuess;
            bool gameIsLooping = true;
            bool gameIsWon = false;

            do
            {
                std::cout << currentHint << "/" << maxHints << " ";
                _Float64 hintRatio = (_Float64)currentHint / (_Float64)maxHints;
                hintGeneratorInstance.generateHint(hintRatio);
                std::cout << "\n";

                userGuess = game.getValidPokemonGuess();

                if (userGuess == randomPokemon.name)
                {
                    gameIsWon = true;
                    gameIsLooping = false;
                }
                else if (currentHint == maxHints)
                {
                    gameIsLooping = false;
                }
                else
                {
                    currentHint++;
                }
            }
                while (gameIsLooping);

            if (gameIsWon)
            {
                std::cout << "YOU GOT IT!!!\n" << userGuess << " IS CORRECT!\n";
            }
            else
            {
                std::cout << "Sorry... you're all out of guesses.\n The pokemon you were looking for was " << randomPokemon.name << "\n";
            }

            programRunning = game.playAgain(userHasDesiredSettings);

            if (userHasDesiredSettings)
            {
                game.removePokemon(randomPokemon.pokemonIndex);
            }
        }
            while (userHasDesiredSettings && programRunning);
    }
        while(programRunning);

    return 0;
}