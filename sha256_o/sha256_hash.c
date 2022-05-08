#include"sha256.h"
#include"debug.h"

void	sha256_hash(t_sha *ctx, const void *data, size_t len)
{
	const uint8_t	*bytes;
	size_t			i;

	ctx->bits[0] = (len * 8) / 0x100000000;
	ctx->bits[1] = (len * 8) % 0x100000000;
	bytes = (const uint8_t *)data;
	i = 0;
	while (i < len)
	{
		ctx->buf[ctx->len] = bytes[i];
		ctx->len++;
		i++;
		if (ctx->len == sizeof(ctx->buf)) {
//TEST
			hash(ctx);
			ctx->len = 0;
		}
	}
}

void	hash(t_sha *ctx)
{
	uint32_t hs[8];
	uint32_t t[2];
	size_t	i;

	//a = ctx->hash[0];
	//b = ctx->hash[1];
	//c = ctx->hash[2];
	//d = ctx->hash[3];
	//e = ctx->hash[4];
	//f = ctx->hash[5];
	//g = ctx->hash[6];
	//h = ctx->hash[7];
	memcpy(hs, ctx->hash, sizeof(uint32_t) * 8);

	i = 0;
	while (i < 64)
	{
		memmove(ctx->W, ctx->W + 1, sizeof(uint32_t) * 16);
		if (i < 16) {
			/* ctx->W[16] = _word(&ctx->buf[_shw(i, 2)]); */ b8tob32(ctx->buf + (i * 4), ctx->W + 16);
		} else {
			ctx->W[16] = G1(ctx->W[14]) + ctx->W[9] + G0(ctx->W[1]) + ctx->W[0];
		}
/* char c;
TESTsx("a", hs[0])
TESTsx("b", hs[1])
TESTsx("c", hs[2])
TESTsx("d", hs[3])
TESTsx("e", hs[4])
TESTsx("f", hs[5])
TESTsx("g", hs[6])
TESTsx("h", hs[7])

TESTnx(i, ctx->W[0])
TESTnx(i + 1, ctx->W[1])
TESTnx(i + 2, ctx->W[2])
TESTnx(i + 3, ctx->W[3])
TESTnx(i + 4, ctx->W[4])
TESTnx(i + 5, ctx->W[5])
TESTnx(i + 6, ctx->W[6])
TESTnx(i + 7, ctx->W[7])
TESTnx(i + 8, ctx->W[8])
TESTnx(i + 9, ctx->W[9])
TESTnx(i + 10, ctx->W[10])
TESTnx(i + 11, ctx->W[11])
TESTnx(i + 12, ctx->W[12])
TESTnx(i + 13, ctx->W[13])
TESTnx(i + 14, ctx->W[14])
TESTnx(i + 15, ctx->W[15])
TESTnx(i + 16, ctx->W[16])
read(0, &c, 1);
 */
		t[0] = hs[7] + S1(hs[4]) + Ch(hs[4], hs[5], hs[6]) + ctx->K[i] + ctx->W[16];
		t[1] = S0(hs[0]) + Ma(hs[0], hs[1], hs[2]);
		memmove(hs + 1, hs, sizeof(uint32_t) * 7);
		hs[4] += t[0];
		hs[0] = t[0] + t[1];
		//h = g;
		//g = f;
		//f = e;
		//e = d + t[0];
		//d = c;
		//c = b;
		//b = a;
		//a = t[0] + t[1];
		i++;
	}

	//ctx->hash[0] += a;
	//ctx->hash[1] += b;
	//ctx->hash[2] += c;
	//ctx->hash[3] += d;
	//ctx->hash[4] += e;
	//ctx->hash[5] += f;
	//ctx->hash[6] += g;
	//ctx->hash[7] += h;
	i = 0;
	while (i < 8)
	{
		ctx->hash[i] += hs[i];
		i++;
	}
}
