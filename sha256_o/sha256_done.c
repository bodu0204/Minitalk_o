#include"sha256.h"
#include"debug.h"

void	sha256_done(t_sha *ctx, uint8_t *hdst)
{
	size_t i;

	//j = ctx->len % sizeof(ctx->buf);
	ctx->buf[ctx->len] = 0x80;
	i = ctx->len + 1;
	while (i < 64)
	{
		ctx->buf[i] = 0x00;
		i++;
	}
	if (ctx->len > 55)
	{
//TEST
		hash(ctx);
		i = 0;
		while (i < 64)
		{
			ctx->buf[i] = 0x00;
			i++;
		}
	}
	//ctx->buf[63] = _shb(ctx->bits[0],  0);
	//ctx->buf[62] = _shb(ctx->bits[0],  8);
	//ctx->buf[61] = _shb(ctx->bits[0], 16);
	//ctx->buf[60] = _shb(ctx->bits[0], 24);
	//ctx->buf[59] = _shb(ctx->bits[1],  0);
	//ctx->buf[58] = _shb(ctx->bits[1],  8);
	//ctx->buf[57] = _shb(ctx->bits[1], 16);
	//ctx->buf[56] = _shb(ctx->bits[1], 24);
	b32tob8(ctx->bits + 1, ctx->buf + 60);
	b32tob8(ctx->bits, ctx->buf + 56);
//TEST
	hash(ctx);
	//if (hash != NULL) {
	//	for (i = 0, j = 24; i < 4; i++, j -= 8) {
	//		hash[i +  0] = _shb(ctx->hash[0], j);
	//		hash[i +  4] = _shb(ctx->hash[1], j);
	//		hash[i +  8] = _shb(ctx->hash[2], j);
	//		hash[i + 12] = _shb(ctx->hash[3], j);
	//		hash[i + 16] = _shb(ctx->hash[4], j);
	//		hash[i + 20] = _shb(ctx->hash[5], j);
	//		hash[i + 24] = _shb(ctx->hash[6], j);
	//		hash[i + 28] = _shb(ctx->hash[7], j);
	//	}
	//}
	i = 0;
	while (i < 8)
	{
		b32tob8(ctx->hash + i, hdst + (i * 4));
		i++;
	}
}
