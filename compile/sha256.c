#include"sha256.h"

void	sha256(const void *data, size_t len, uint8_t *hash)
{
	t_sha	ctx;

	if (!data || !hash)
		return ;
	sha256_init(&ctx);
	sha256_hash(&ctx, data, len);
	sha256_done(&ctx, hash);
	return ;
}


//void showhash(uint8_t *hash);
//#include <stdio.h>
//
//int main(void)
//{
//    char *data = "";
//    uint8_t hash[32];
//    bzero(hash, sizeof(hash));
//    sha256(data, strlen(data), hash);
//    showhash(hash);
//    return (0);
//}
//
//void showhash(uint8_t *hash)
//{
//    for (size_t i = 0; i < 32; i++){
//        printf("%02hhx",hash[i]);
//    }
//    printf("\n");
//    return ;
//}
