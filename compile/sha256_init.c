#include"sha256.h"
void	sha256_init1(t_sha *ctx);
void	sha256_init2(t_sha *ctx);
void	sha256_init3(t_sha *ctx);

void	sha256_init(t_sha *ctx)
{
	ctx->bits[0] = 0;
	ctx->bits[1] = 0;
	ctx->len = 0;
	ctx->hash[0] = 0x6a09e667;
	ctx->hash[1] = 0xbb67ae85;
	ctx->hash[2] = 0x3c6ef372;
	ctx->hash[3] = 0xa54ff53a;
	ctx->hash[4] = 0x510e527f;
	ctx->hash[5] = 0x9b05688c;
	ctx->hash[6] = 0x1f83d9ab;
	ctx->hash[7] = 0x5be0cd19;
	sha256_init1(ctx);
	return ;
}

void	sha256_init1(t_sha *ctx)
{
	ctx->K[0] = 0x428a2f98;
	ctx->K[1] = 0x71374491;
	ctx->K[2] = 0xb5c0fbcf;
	ctx->K[3] = 0xe9b5dba5;
	ctx->K[4] = 0x3956c25b;
	ctx->K[5] = 0x59f111f1;
	ctx->K[6] = 0x923f82a4;
	ctx->K[7] = 0xab1c5ed5;
	ctx->K[8] = 0xd807aa98;
	ctx->K[9] = 0x12835b01;
	ctx->K[10] = 0x243185be;
	ctx->K[11] = 0x550c7dc3;
	ctx->K[12] = 0x72be5d74;
	ctx->K[13] = 0x80deb1fe;
	ctx->K[14] = 0x9bdc06a7;
	ctx->K[15] = 0xc19bf174;
	ctx->K[16] = 0xe49b69c1;
	ctx->K[17] = 0xefbe4786;
	ctx->K[18] = 0x0fc19dc6;
	ctx->K[19] = 0x240ca1cc;
	ctx->K[20] = 0x2de92c6f;
	sha256_init2(ctx);
	return ;
}

void	sha256_init2(t_sha *ctx)
{
	ctx->K[21] = 0x4a7484aa;
	ctx->K[22] = 0x5cb0a9dc;
	ctx->K[23] = 0x76f988da;
	ctx->K[24] = 0x983e5152;
	ctx->K[25] = 0xa831c66d;
	ctx->K[26] = 0xb00327c8;
	ctx->K[27] = 0xbf597fc7;
	ctx->K[28] = 0xc6e00bf3;
	ctx->K[29] = 0xd5a79147;
	ctx->K[30] = 0x06ca6351;
	ctx->K[31] = 0x14292967;
	ctx->K[32] = 0x27b70a85;
	ctx->K[33] = 0x2e1b2138;
	ctx->K[34] = 0x4d2c6dfc;
	ctx->K[35] = 0x53380d13;
	ctx->K[36] = 0x650a7354;
	ctx->K[37] = 0x766a0abb;
	ctx->K[38] = 0x81c2c92e;
	ctx->K[39] = 0x92722c85;
	ctx->K[40] = 0xa2bfe8a1;
	sha256_init3(ctx);
	return ;
}

void	sha256_init3(t_sha *ctx)
{
	ctx->K[41] = 0xa81a664b;
	ctx->K[42] = 0xc24b8b70;
	ctx->K[43] = 0xc76c51a3;
	ctx->K[44] = 0xd192e819;
	ctx->K[45] = 0xd6990624;
	ctx->K[46] = 0xf40e3585;
	ctx->K[47] = 0x106aa070;
	ctx->K[48] = 0x19a4c116;
	ctx->K[49] = 0x1e376c08;
	ctx->K[50] = 0x2748774c;
	ctx->K[51] = 0x34b0bcb5;
	ctx->K[52] = 0x391c0cb3;
	ctx->K[53] = 0x4ed8aa4a;
	ctx->K[54] = 0x5b9cca4f;
	ctx->K[55] = 0x682e6ff3;
	ctx->K[56] = 0x748f82ee;
	ctx->K[57] = 0x78a5636f;
	ctx->K[58] = 0x84c87814;
	ctx->K[59] = 0x8cc70208;
	ctx->K[60] = 0x90befffa;
	ctx->K[61] = 0xa4506ceb;
	ctx->K[62] = 0xbef9a3f7;
	ctx->K[63] = 0xc67178f2;
	return ;
}
