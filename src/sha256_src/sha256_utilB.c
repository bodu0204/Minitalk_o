#include"sha256.h"

uint32_t	G1(uint32_t x)
{
	return (rbit(x, 17) ^ rbit(x, 19) ^ (x >> 10));
}
