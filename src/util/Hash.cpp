#include "Hash.h"

/*一些基本转换函数*/
#define ROTL32(x,r) (x << r) | ((x & 0xFFFFFFFF) >> (32 - r))
#define F1(y,z,l) ( (y)^ ((z)& ((l)^(y))))
#define F2(y,z,l) ((y) ^ ((l) | (~z)))
#define P1(a,b,c,d,k,s,t)   \
{						   \
    (a) += ((F1(b,c,d))+(w[k]) +(t));\
    (a) = ((ROTL32(a,s)) + (b));          \
}

#define P2(a,b,c,d,k,s,t)   \
{						   \
    (a) += ((F2(b,c,d))+(w[k]) +(t));\
    (a) = ((ROTL32(a,s)) + (b));          \
}

const char Hash::HEX[16]={
    '0', '1', '2', '3',
     '4', '5', '6', '7',
     '8', '9', 'a', 'b',
     'c', 'd', 'e', 'f'
};

const byte Hash::PADDING[64] = { 0x80 };

const uint32 K[64]={
    0xc4343361,0xe8929933,0xf468ebb7,0x32da638a,
    0x86ee3abc,0x5accfd6e,0x836c6cab,0xf25f1553,
    0x662b56b2,0x1143aabb,0xd87638d2,0x2f773b58,
    0xff5a6aa7,0xee4e3eea,0x32faeaa3,0x19fb9b84,
    0xa9bdb6e7,0xcc6525a8,0x4c2f6b14,0xb28b6fb1,
    0x1237de8e,0xf5e8e273,0x78d51bd2,0x8ae39eb5,
    0x5c6da38a,0xb4a4deb3,0x225b811b,0x50e62412,
    0x818740a5,0x8b7eff2b,0xb78f6a2f,0x82cf8997,
    0xd5f91f82,0x0723be5c,0x616f9748,0x43f64717,
    0x8b76ea5e,0x35948bae,0x0023e714,0x54573c13,
    0x3784d133,0x051cd836,0x5227c588,0xed73b5d8,
    0xe2571b48,0x0231fb8f,0xc68c895b,0xfc61e74f,
    0x4334e2c9,0x36887d97,0x199ea71d,0x0245e5d9,
    0x346c8894,0x765e9ce3,0x12f99f33,0x139e2e57,
    0xae61fc8d,0xc1e8d8a4,0xff51afd7,0xed558ccd,
    0xc4ceb9fe,0x1a85ec53,0xcc9e2d51,0x1b873593
};

Hash::Hash()
{
    set();
}

Hash::Hash(const string& mes){
    set();
    init((byte*)mes.c_str(),mes.length());
}

void Hash::update(const string &mes){
    set();
    init((byte*)mes.c_str(),mes.length());
}

//找8个初始值
void Hash::set(){
    finished = false;
    /*用于存储数据的长度*/
    count[1] = count[0]=0;
    /*初始化*/
    state[0] = 0x71b2b78a;
    state[1] = 0xec9ef898;
    state[2] = 0x3145caee;
    state[3] = 0xed119de9;
    state[4] = 0xd83a713b;
    state[5] = 0x4996668b;
    state[6] = 0x4434d6b9;
    state[7] = 0xa8dca679;
}

/*
 * 判断数据是否处理完成
 * @return 原来的hash值
 */

const byte* Hash::getDigest(){
    if (!finished) {
        finished = true;

        byte bits[8]={0};
        uint32 oldState[8]={0};
        uint32 oldCount[2]={0};
        uint32 index, padLen;

        /*存储当前的状态和数据长度 */
        memcpy(oldState, state, 32);
        memcpy(oldCount, count, 8);

        /*存储当前的数据长度 */
        encode(count, bits, 8);

        /*填补数据长度 mod512 == 448*/
        index = (uint32)((count[0] >> 3) & 0x3f);
        padLen = (index < 56) ? (56 - index) : (120 - index);
        init(PADDING, padLen);

        /* Append length (before padding) */
        init(bits, 8);

        /*将当前计算出的状态存放在 digest中*/
        encode(state, digest, 32);

        /* 重新存储当前的状态 */
        memcpy(state, oldState, 32);
        memcpy(count, oldCount, 8);
    }

//    state[0] += state[1]; state[1] += state[2]; state[3] += state[4]; state[4] += state[5];
//    state[5] += state[6]; state[6] += state[7]; state[7] += state[0];

//    state[0] = fmix(state[0]);
//    state[1] = fmix(state[1]);
//    state[2] = fmix(state[2]);
//    state[3] = fmix(state[3]);
//    state[4] = fmix(state[4]);
//    state[5] = fmix(state[5]);
//    state[6] = fmix(state[6]);
//    state[7] = fmix(state[7]);

//    state[0] += state[1]; state[1] += state[2]; state[3] += state[4]; state[4] += state[5];
//    state[5] += state[6]; state[6] += state[7]; state[7] += state[0];

//    encode(state, digest, 32);

    return digest;
}

/*
 * 对数据进行处理
 * @param 数据以及数据的长度
 */

void Hash::init(const byte *input, size_t len){
    uint32 i, index, partLen;
    finished = false;

    /* 数据长度mod 64 */
    index = (uint32)((count[0] >> 3) & 0x3f);

    /*更新数据长度*/
    if ((count[0] += ((uint32)len << 3)) < ((uint32)len << 3)) {
        ++count[1];
    }
    count[1] += ((uint32)len >> 29);

    partLen = 64 - index;

    /*转换*/
    if (len >= partLen) {

        memcpy(&buffer[index], input, partLen);
        transform(buffer);

        for (i = partLen; i + 63 < len; i += 64) {
            transform(&input[i]);
        }
        index = 0;

    }
    else {
        i = 0;
    }

    memcpy(&buffer[index], &input[i], len - i);
}


void Hash::transform(const byte block[64]){
    uint32 w[16]{0};
    decode(block,w,16);

    uint32 A,B,C,D,E,F,G,H;

    A = state[0];
    B = state[1];
    C = state[2];
    D = state[3];
    E = state[4];
    F = state[5];
    G = state[6];
    H = state[7];

    //R1 处理A,B,C,D
    P2(A, B, C, D, 0, 6, K[0]);
    P2(D, A, B, C, 7, 10, K[1]);
    P2(C, D, A, B, 14, 15, K[2]);
    P2(B, C, D, A, 5, 21, K[3]);
    P2(A, B, C, D, 12, 6, K[4]);
    P2(D, A, B, C, 3, 10, K[5]);
    P2(C, D, A, B, 10, 15, K[6]);
    P2(B, C, D, A, 1, 21, K[7]);
    P2(A, B, C, D, 8, 6, K[8]);
    P2(D, A, B, C, 15, 10, K[9]);
    P2(C, D, A, B, 6, 15, K[10]);
    P2(B, C, D, A, 13, 21, K[11]);
    P2(A, B, C, D, 4, 6, K[12]);
    P2(D, A, B, C, 11, 10, K[13]);
    P2(C, D, A, B, 2, 15, K[14]);
    P2(B, C, D, A, 9, 21, K[15]);

    //R[2] 处理E,F,G,H
    P1(E, F, G, H, 1, 5, K[16]);
    P1(H, E, F, G, 6, 9, K[17]);
    P1(G, H, E, F, 11, 14,K[18]);
    P1(F, G, H, E, 0, 20, K[19]);
    P1(E, F, G, H, 5, 5, K[20]);
    P1(H, E, F, G, 10, 9, K[21]);
    P1(G, H, E, F, 15, 14, K[22]);
    P1(F, G, H, E, 4, 20, K[23]);
    P1(E, F, G, H, 9, 5, K[24]);
    P1(H, E, F, G, 14, 9, K[25]);
    P1(G, H, E, F, 3, 14, K[26]);
    P1(F, G, H, E, 8, 20, K[27]);
    P1(E, F, G, H, 13, 5, K[28]);
    P1(H, E, F, G, 2, 9, K[29]);
    P1(G, H, E, F, 7, 14, K[30]);
    P1(F, G, H, E, 12, 20, K[31]);

    //R3 处理A,B,C,D,E,F,G,H
    w[0] *= A; w[0] = ROTL32(w[0], 15); w[0] *= K[32]; A ^= w[0];
    A = ROTL32(A, 19); A += B; A = A * 5 + K[32];
    w[2] *= B; w[2] = ROTL32(w[2], 16); w[2] *= K[33]; B ^= w[2];
    B = ROTL32(B, 17); B += C; B = B * 5 + K[33];
    w[4] *= C; w[4] = ROTL32(w[4], 17); w[4] *= K[34]; C ^= w[4];
    C = ROTL32(C, 15); C += D; C = C * 5 + K[34];
    w[6] *= D; w[6] = ROTL32(w[6], 18);  w[6] *= K[35]; D ^= w[6];
    D = ROTL32(D, 13); D += E; D = D * 5 + K[35];
    w[8] *= E; w[8] = ROTL32(w[8], 15); w[8] *= K[36]; E ^= w[8];
    E = ROTL32(E, 19); E += F; E = E * 5 + K[36];
    w[10] *= F; w[10] = ROTL32(w[10], 16); w[10] *= K[37]; F ^= w[10];
    F = ROTL32(F, 17); F += G; F = F * 5 + K[37];
    w[12] *= G; w[12] = ROTL32(w[12], 17); w[12] *= K[38]; G ^= w[12];
    G = ROTL32(C, 15); G += H; G = G * 5 + K[38];
    w[14] *= H; w[14] = ROTL32(w[14], 18);  w[14] *= K[39]; H ^= w[14];
    H = ROTL32(D, 13); H += A; H = H * 5 + K[39];
    w[1] *= A; w[1] = ROTL32(w[1], 11); w[1] *= K[40]; A ^= w[1];
    A = ROTL32(A, 19); A += B; A = A * 5 + K[40];
    w[3] *= B; w[3] = ROTL32(w[3], 13); w[3] *= K[41]; B ^= w[3];
    B = ROTL32(B, 17); B += C; B = B * 5 + K[41];
    w[5] *= C; w[5] = ROTL32(w[5], 17); w[5] *= K[42]; C ^= w[5];
    C = ROTL32(C, 15); C += D; C = C * 5 + K[42];
    w[7] *= D; w[7] = ROTL32(w[7], 19);  w[7] *= K[43]; D ^= w[7];
    D = ROTL32(D, 13); D += E; D = D * 5 + K[43];
    w[9] *= E; w[9] = ROTL32(w[9], 11); w[9] *= K[44]; E ^= w[9];
    E = ROTL32(E, 19); E += F; E = E * 5 + K[44];
    w[11] *= F; w[11] = ROTL32(w[11], 13); w[11] *= K[45]; F ^= w[11];
    F = ROTL32(F, 17); F += G; F = F * 5 + K[45];
    w[13] *= G; w[13] = ROTL32(w[13], 17); w[13] *= K[46]; G ^= w[13];
    G = ROTL32(C, 15); G += H; G = G * 5 + K[46];
    w[15] *= H; w[15] = ROTL32(w[15], 19);  w[15] *= K[47]; H ^= w[15];
    H = ROTL32(D, 13); H += A; H = H * 5 + K[47];

    //R4
    w[4] *= A; w[4] = ROTL32(w[4], 10); w[4] *= K[48]; A ^= w[4];
    A = ROTL32(A, 19); A += B; A = A * 5 + K[48];
    w[8] *= B; w[8] = ROTL32(w[8], 15); w[8] *= K[49]; B ^= w[8];
    B = ROTL32(B, 17); B += C; B = B * 5 + K[49];
    w[7] *= C; w[7] = ROTL32(w[7], 20); w[7] *= K[50]; C ^= w[7];
    C = ROTL32(C, 15); C += D; C = C * 5 + K[50];
    w[5] *= D; w[5] = ROTL32(w[5], 25);  w[5] *= K[51]; D ^= w[5];
    D = ROTL32(D, 13); D += E; D = D * 5 + K[51];
    w[1] *= E; w[1] = ROTL32(w[1], 10); w[1] *= K[52]; E ^= w[1];
    E = ROTL32(E, 19); E += F; E = E * 5 + K[52];
    w[3] *= F; w[3] = ROTL32(w[3], 15); w[3] *= K[53]; F ^= w[3];
    F = ROTL32(F, 17); F += G; F = F * 5 + K[53];
    w[2] *= G; w[2] = ROTL32(w[2], 20); w[2] *= K[54]; G ^= w[2];
    G = ROTL32(C, 15); G += H; G = G * 5 + K[54];
    w[13] *= H; w[14] = ROTL32(w[13], 25);  w[13] *= K[55]; H ^= w[13];
    H = ROTL32(D, 13); H += A; H = H * 5 + K[55];
    w[6] *= A; w[6] = ROTL32(w[6], 11); w[6] *= K[56]; A ^= w[6];
    A = ROTL32(A, 19); A += B; A = A * 5 + K[56];
    w[9] *= B; w[9] = ROTL32(w[9], 13); w[9] *= K[57]; B ^= w[9];
    B = ROTL32(B, 17); B += C; B = B * 5 + K[57];
    w[11] *= C; w[11] = ROTL32(w[11], 17); w[11] *= K[58]; C ^= w[11];
    C = ROTL32(C, 15); C += D; C = C * 5 + K[58];
    w[14] *= D; w[14] = ROTL32(w[14], 19);  w[14] *= K[59]; D ^= w[14];
    D = ROTL32(D, 13); D += E; D = D * 5 + K[59];
    w[12] *= E; w[12] = ROTL32(w[12], 11); w[12] *= K[60]; E ^= w[12];
    E = ROTL32(E, 19); E += F; E = E * 5 + K[60];
    w[15] *= F; w[15] = ROTL32(w[15], 13); w[15] *= K[61]; F ^= w[15];
    F = ROTL32(F, 17); F += G; F = F * 5 + K[61];
    w[0] *= G; w[0] = ROTL32(w[0], 17); w[0] *= K[62]; G ^= w[0];
    G = ROTL32(C, 15); G += H; G = G * 5 + K[62];
    w[10] *= H; w[10] = ROTL32(w[10], 19);  w[10] *= K[63]; H ^= w[10];
    H = ROTL32(D, 13); H += A; H = H * 5 + K[63];

    A ^= fmix(A);
    B ^= fmix(B);
    C ^= fmix(C);
    D ^= fmix(D);
    E ^= fmix(E);
    F ^= fmix(F);
    G ^= fmix(G);
    H ^= fmix(H);

    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
    state[4] += E;
    state[5] += F;
    state[6] += G;
    state[7] += H;
}


/*使所有位都有翻转的可能*/
uint32 Hash::fmix(uint32 h){
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

/*
 * 将32bit转换成8bit
 */

void Hash::encode(const uint32* input,byte* output,size_t length){
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
       output[j]= (byte)(input[i] & 0xff);
       output[j + 1] = (byte)((input[i] >> 8) & 0xff);
       output[j + 2] = (byte)((input[i] >> 16) & 0xff);
       output[j + 3] = (byte)((input[i] >> 24) & 0xff);
    }
}

/*
 * 将8bit转换成32bit
 */
void Hash::decode(const byte* input,uint32* output, size_t length){
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
      output[i] = ((uint32)input[j]) | (((uint32)input[j + 1]) << 8) |
              (((uint32)input[j + 2]) << 16) | (((uint32)input[j + 3]) << 24);
    }
}

/*
 * 将哈希值转换成16进制
 * @return 转换后的hash值
 */
string Hash::toString(){
    const byte* digest_ = getDigest();
    string str;
    str.reserve(32 << 1);
    for (size_t i = 0; i < 32; ++i) {
        int t = digest_[i];
        int a= t / 16;
        int b = t % 16;
        str.append(1, HEX[a]);
        str.append(1, HEX[b]);
    }
    return str;
}
