#pragma once
#include <iostream>
#include <vector>

void printStringVector(std::vector<std::string>& vector)
{
    for (uint64_t i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i];

        if (i != vector.size() - 1)
        {
            std::cout << " || ";
        }
        else
        {
            std::cout << "\n";
        }
    }
}

void stringToAllCaps(std::string& str)
{
    for (uint64_t i = 0; i < str.length(); i++)
    {
        str[i] = toupper(str[i]);
    }
}

void formatPokemonNameString(std::string& str)
{
    str[0] = toupper(str[0]);
    
    for (uint64_t i = 1; i < str.length(); i++)
    {
        if (isalpha(str[i]))
        {
            str[i] = tolower(str[i]);
        }
        else if (' ' == str[i])
        {
            i++;
            str[i] = toupper(str[i]);
        }
    }
}

bool isValidStringInput(const std::string& stringInput, const std::vector<std::string>& validInputs)
{
    for (uint64_t i = 0; i < validInputs.size(); i++)
    {
        if (stringInput == validInputs[i])
        {
            return true;
        }
    }

    return false;
}

std::string getShorterString(const std::string& str1, const std::string& str2)
{
    if (str1.length() > str2.length())
    {
        return str1;
    }

    return str2;
}

void popStringFromVector(std::vector<std::string>& vec, std::string& stringToPop)
{
    for (uint64_t i = 0; i < vec.size(); i++)
    {
        if (stringToPop == vec[i])
        {
            vec.erase(vec.begin() + i);
        }
    }
}

void sortStringVector(std::vector<std::string>& vecToSort, const std::vector<std::string>& vecReference)
{
    std::vector<std::string> sortedVec;

    for (uint64_t i = 0; i < vecReference.size(); i++)
    {
        for (uint64_t k = 0; k < vecToSort.size(); k++)
        {
            if (vecReference[i] == vecToSort[k])
            {
                sortedVec.push_back(vecReference[i]);
            }
        }
    }

    vecToSort = sortedVec;
}

uint64_t generateRandomNumber(const uint64_t& min, const uint64_t& max)
{
    return (rand() % max) + min;
}