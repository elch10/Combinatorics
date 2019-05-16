#ifndef COMBINATORICS_H
#define COMBINATORICS_H

#include "UINT32.h"

UINT32 Binomial(byte N, byte R);
UINT32 Stirling(byte N, byte R);
UINT32 Bell(byte N);
UINT32 Permutations(byte N);
UINT32 Placements(byte N, byte R);
UINT32 PlacementsWithoutRepetition(byte N, byte R);

#endif //COMBINATORICS_H