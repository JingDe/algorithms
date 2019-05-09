
#include<string.h>
#include<stdint.h>


int stringHashFunction(std::string s)
{
#if defined MURMUR
	return murmurHashFunction(s.c_str(), s.length());
#elif defined SIP_CASE
	return sipCaseHashFunction(s.c_str(), s.length()); // uint64_t to int ??
#elif defined SIP_NOCASE
	return sipHashFunction(s.c_str(), s.length());
#else
	return djbHashFunction(s.c_str(), s.length());
#endif
}


static uint8_t hash_function_seed[16];
void setHashFunctionSeed(uint8_t* seed)
{
	memcpy(hash_function_seed, seed, sizeof(hash_function_seed));
}


unsigned int djbHashFunction(const unsigned char* buf, int len)
{
	unsigned int hash=(unsigned int)hash_function_seed;
	while(len--)
		hash=((hash<<5)+hash) + (std::tolower(*buf++));
	return hash;
}

// ======================
#ifdefined SIPHASH
#define U8TO64_LE_NOCASE(p)                                                   \
    (((uint64_t)(siptlw((p)[0]))) |                                           \
     ((uint64_t)(siptlw((p)[1])) << 8) |                                      \
     ((uint64_t)(siptlw((p)[2])) << 16) |                                     \
     ((uint64_t)(siptlw((p)[3])) << 24) |                                     \
     ((uint64_t)(siptlw((p)[4])) << 32) |                                     \
     ((uint64_t)(siptlw((p)[5])) << 40) |                                     \
     ((uint64_t)(siptlw((p)[6])) << 48) |                                     \
     ((uint64_t)(siptlw((p)[7])) << 56))
	 
#define SIPROUND                                                               \
    do {                                                                       \
        v0 += v1;                                                              \
        v1 = ROTL(v1, 13);                                                     \
        v1 ^= v0;                                                              \
        v0 = ROTL(v0, 32);                                                     \
        v2 += v3;                                                              \
        v3 = ROTL(v3, 16);                                                     \
        v3 ^= v2;                                                              \
        v0 += v3;                                                              \
        v3 = ROTL(v3, 21);                                                     \
        v3 ^= v0;                                                              \
        v2 += v1;                                                              \
        v1 = ROTL(v1, 17);                                                     \
        v1 ^= v2;                                                              \
        v2 = ROTL(v2, 32);                                                     \
    } while (0)	

#ifdef UNALIGNED_LE_CPU
#define U8TO64_LE(p) (*((uint64_t*)(p)))
#else
#define U8TO64_LE(p)                                                           \
    (((uint64_t)((p)[0])) | ((uint64_t)((p)[1]) << 8) |                        \
     ((uint64_t)((p)[2]) << 16) | ((uint64_t)((p)[3]) << 24) |                 \
     ((uint64_t)((p)[4]) << 32) | ((uint64_t)((p)[5]) << 40) |                 \
     ((uint64_t)((p)[6]) << 48) | ((uint64_t)((p)[7]) << 56))
#endif		




uint64_t sipCaseHashFunction(const unsigned char *buf, int len) {
    return siphash(buf,len,hash_function_seed);
}

uint64_t sipHashFunction(const unsigned char *buf, int len) {
    return siphash_nocase(buf,len,hash_function_seed);
}

uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k)
{
#ifndef UNALIGNED_LE_CPU
    uint64_t hash;
    uint8_t *out = (uint8_t*) &hash;
#endif
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t k0 = U8TO64_LE(k);
    uint64_t k1 = U8TO64_LE(k + 8);
    uint64_t m;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    uint64_t b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

    for (; in != end; in += 8) {
        m = U8TO64_LE_NOCASE(in);
        v3 ^= m;

        SIPROUND;

        v0 ^= m;
    }

    switch (left) {
    case 7: b |= ((uint64_t)siptlw(in[6])) << 48; /* fall-thru */
    case 6: b |= ((uint64_t)siptlw(in[5])) << 40; /* fall-thru */
    case 5: b |= ((uint64_t)siptlw(in[4])) << 32; /* fall-thru */
    case 4: b |= ((uint64_t)siptlw(in[3])) << 24; /* fall-thru */
    case 3: b |= ((uint64_t)siptlw(in[2])) << 16; /* fall-thru */
    case 2: b |= ((uint64_t)siptlw(in[1])) << 8; /* fall-thru */
    case 1: b |= ((uint64_t)siptlw(in[0])); break;
    case 0: break;
    }

    v3 ^= b;

    SIPROUND;

    v0 ^= b;
    v2 ^= 0xff;

    SIPROUND;
    SIPROUND;

    b = v0 ^ v1 ^ v2 ^ v3;
#ifndef UNALIGNED_LE_CPU
    U64TO8_LE(out, b);
    return hash;
#else
    return b;
#endif
}

uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k) {
#ifndef UNALIGNED_LE_CPU
    uint64_t hash;
    uint8_t *out = (uint8_t*) &hash;
#endif
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t k0 = U8TO64_LE(k);
    uint64_t k1 = U8TO64_LE(k + 8);
    uint64_t m;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    uint64_t b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

    for (; in != end; in += 8) {
        m = U8TO64_LE(in);
        v3 ^= m;

        SIPROUND;

        v0 ^= m;
    }

    switch (left) {
    case 7: b |= ((uint64_t)in[6]) << 48; /* fall-thru */
    case 6: b |= ((uint64_t)in[5]) << 40; /* fall-thru */
    case 5: b |= ((uint64_t)in[4]) << 32; /* fall-thru */
    case 4: b |= ((uint64_t)in[3]) << 24; /* fall-thru */
    case 3: b |= ((uint64_t)in[2]) << 16; /* fall-thru */
    case 2: b |= ((uint64_t)in[1]) << 8; /* fall-thru */
    case 1: b |= ((uint64_t)in[0]); break;
    case 0: break;
    }

    v3 ^= b;

    SIPROUND;

    v0 ^= b;
    v2 ^= 0xff;

    SIPROUND;
    SIPROUND;

    b = v0 ^ v1 ^ v2 ^ v3;
#ifndef UNALIGNED_LE_CPU
    U64TO8_LE(out, b);
    return hash;
#else
    return b;
#endif
}

#endif

// ==========

unsigned int murmurHashFunction(const void *key, int len) 
{  
    /* 'm' and 'r' are mixing constants generated offline. 
    They're not really 'magic', they just happen to work well.  */  
    //seed种子，m，r的值都将会参与到计算中  
    uint32_t seed = hash_function_seed;  
    const uint32_t m = 0x5bd1e995;  
    const int r = 24;  
    /* Initialize the hash to a 'random' value */  
    uint32_t h = seed ^ len;  
    /* Mix 4 bytes at a time into the hash */  
    const unsigned char *data = (const unsigned char *)key;  
	while(len >= 4) {  
        uint32_t k = *(uint32_t*)data;  
        k *= m;  
        k ^= k >> r;  
        k *= m;  
        h *= m;  
        h ^= k;  
        data += 4;  
		len -= 4;  
    }  
    /* Handle the last few bytes of the input array  */  
    switch(len) {  
    case 3: h ^= data[2] << 16;  
    case 2: h ^= data[1] << 8;  
    case 1: h ^= data[0]; h *= m;  
    };  
     /* Do a few final mixes of the hash to ensure the last few 
      * bytes are well-incorporated. */  
    h ^= h >> 13;  
    h *= m;  
    h ^= h >> 15;  
	return (unsigned int)h;  
}  

