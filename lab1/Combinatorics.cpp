#include "UINT32.h"
#include "Combinatorics.h"
#include "ArihmeticError.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

UINT32 Binomial(byte N, byte R)
{
  if (N < R) {
    return UINT32(0);
  }
  // (N >= R):
  R = (R <= N - R ? R : N - R); // R <= N/2:
  UINT32 C;
  int r;
  for (C = UINT32(1), r = 1; r <= R; r++) {
    C = C * (N-r+1) / r;
  }
  return C; // Binomial(N, R)
} // UINT32 Bin(byte n, byte r)

UINT32 Stirling(byte N, byte R)
{
  if (N < R) return UINT32(0);
  UINT32 S; 
  vector<UINT32> A(static_cast<size_t>(R+1)); // A[R] = S1(R+j, R)
  int rc, j;

  // r_current = rc; n_current = rc+j;
  // r < rc => A[r] == S1(r+j, r); => n == r+j - current diag
  // r = rc => A[r] == S1(r+j-1, r); before assignment:
  //           A[r] = A[r-1] + A[r]*(r+j-1);
  // S1(r+j-1, r-1) + S1(r+j-1, r)*(r+j-1);
  // A[r] == S1(r+j , r); after assignment.
  // r > rc => A[r] == S1(r+j-1, r); => n_ == r+j-1 - prev.diag

  for (rc = 0; rc <= R; rc++) {
    A[rc] = UINT32(1);
  }
  for (S = A[R], A[0] = UINT32(0), j = 1; j <= N - R; j++, S = A[R]) {
    for (rc = 1; rc <= R; rc++) {
      A[rc] = A[rc - 1] + A[rc] * (rc+j-1);
    }
  }
  return S;
} // UINT32 Stir1(byte N, byte R)

UINT32 Bell(byte N)
{
  UINT32 B;
  vector<UINT32> A(static_cast<size_t>(N+1));
  int rc, j;
  // r_current = rc; n_current = rc+j;
  // r < rc => A[r] == S2(r+j, r); => n == r+j - current diag
  // r = rc => A[r] == S2(r+j-1, r); before assignment:
  // A[r] = A[r-1] + A[r]*r;
  // S2(r+j-1, r-1) + S2(r+j-1, r)*r;
  // A[r] == S2(r+j , r); after assignment.
  //rc<r<N-j=> A[r] == S2(r+j-1, r); => n_ == r+j-1 - previous diag
  //N-j<=r<=N=>A[r] == S2(N, r); - final row tail

  for (rc = 0; rc <= N; rc++) {
    A[rc] = UINT32(1); // A[0] = 1 = A[N] first
  }
  for (B = A[N], A[0] = UINT32(0), j = 1; j <= N; B += A[N-j++]) {
    for (rc = 1; rc <= N-j; rc++) {
      A[rc] = A[rc - 1] + A[rc] * rc;
    }
  }
  return B; // = sum(S2(N, N-j), j = 0..N)
} // UINT32 Bell(byte N)

UINT32 Permutations(byte N)
{
  UINT32 ans(1);
  for (int i = 2; i <= N; ++i) {
    ans *= i;
  }
  return ans;
}

UINT32 Placements(byte N, byte R)
{
  UINT32 ans(1);
  for (int i = 1; i <= R; ++i) {
    ans *= N;
  }
  return ans;
}

UINT32 PlacementsWithoutRepetition(byte N, byte R)
{
  if (R > N) {
    return 0;
  }
  UINT32 ans(1);
  for (int i = N - R + 1; i <= N; ++i) {
    ans *= i;
  }
  return ans;
}


