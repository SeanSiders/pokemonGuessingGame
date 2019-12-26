#pragma once
#include <vector>

std::vector<unsigned short> kantoTypeAbundance
{
    22, 12, 32, 9, 14, 5, 8, 33, 14, 19, 14, 12, 11, 3, 3, 0, 2, 5 
};

std::vector<unsigned short> johtoTypeAbundance
{
    15, 10, 18, 8, 10, 5, 3, 4, 10, 19, 10, 10, 7, 1, 1, 6, 4, 8
};

std::vector<unsigned short> hoennTypeAbundance
{
    18, 7, 29, 4, 17, 7, 7, 5, 13, 12, 20, 14, 12, 6, 9, 10, 9, 5
};

std::vector<unsigned short> sinnohTypeAbundance
{
    17, 6, 15, 7, 15, 7, 7, 8, 11, 16, 9, 9, 7, 8, 6, 7, 11, 2
};

std::vector<unsigned short> unovaTypeAbundance
{
    17, 15, 17, 11, 20, 7, 16, 7, 11, 18, 16, 18, 10, 9, 10, 16, 12, 2
};

std::vector<unsigned short> kalosTypeAbundance
{
    12, 9, 13, 10, 13, 5, 10, 7, 4, 8, 10, 11, 5, 11, 9, 8, 13, 13
};

std::vector<unsigned short> alolaTypeAbundance
{
    6, 7, 10, 8, 8, 9, 6, 3, 4, 4, 9, 7, 5, 8, 10, 9, 9, 9
};

std::vector< std::vector<unsigned short> > regionalTypeAbundanceVec
{
    kantoTypeAbundance,
    johtoTypeAbundance,
    hoennTypeAbundance,
    sinnohTypeAbundance,
    unovaTypeAbundance,
    kalosTypeAbundance,
    alolaTypeAbundance
};