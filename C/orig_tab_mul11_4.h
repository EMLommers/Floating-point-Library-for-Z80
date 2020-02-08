#define MAX_NUMBER 1023
#define TOP_BIT 0x40000
#define PRICTI 0x7F
#define POSUN_VPRAVO 8
#define POCET_BITU 10

; // 0000 0100  0000 0000  .... ....  
; //                        111 1111  
; //        98  7654 3210  .... ....  

; //       neni presne: 518333 (49.432087%), preteceni: 518333, podteceni: 0
; // neni zaokrouhleno: 840 (0.080109%), preteceni: 348, podteceni: 492
; // sum(tab_dif[]): -4897, sum(abs(tab_dif[])): 5131
; // (( 1024 + a ) * ( 1024 + b )) >> 7 = (tab_plus[a+b] - tab_minus[a-b]) >> 7 = (1 xxxx xxxx) OR (0 1xxx xxxx)
; // 0 <= a < 1023, 0 <= b < 1023

; // tab_minus[i] = (i*i)/4 +- 0x5
int tab_minus[MAX_NUMBER+1] = {  // [0..1023]
0x0000,0x0000,0x0001,0x0000,0x0002,0x0001,0x0003,0x0002,0x0004,0x0003,0x0005,0x0004,0x0006,0x0005,0x0007,0x0008,
0x0009,0x000A,0x000D,0x000C,0x0010,0x000E,0x0012,0x0011,0x0015,0x0014,0x0019,0x0017,0x001C,0x001B,0x001E,0x001E,
0x0020,0x0022,0x0027,0x0025,0x002B,0x002B,0x0030,0x002F,0x0034,0x0035,0x003A,0x003A,0x003F,0x0041,0x0044,0x0046,
0x0049,0x004C,0x0051,0x0052,0x0058,0x0057,0x005E,0x005F,0x0065,0x0065,0x006D,0x006B,0x0072,0x0075,0x007A,0x007D,
0x0080,0x0084,0x008B,0x008E,0x0093,0x0096,0x009D,0x009D,0x00A5,0x00A6,0x00AD,0x00AF,0x00B8,0x00BA,0x00BF,0x00C4,
0x00C9,0x00CE,0x00D6,0x00D7,0x00DF,0x00E1,0x00EA,0x00EC,0x00F4,0x00FA,0x00FE,0x0103,0x010C,0x010F,0x0116,0x011B,
0x0120,0x0125,0x012D,0x0133,0x013B,0x0140,0x0147,0x014D,0x0156,0x0158,0x0161,0x0165,0x016F,0x0174,0x017C,0x0181,
0x018A,0x0190,0x0199,0x019D,0x01A8,0x01AC,0x01B6,0x01BB,0x01C3,0x01CB,0x01D4,0x01D9,0x01E3,0x01E8,0x01F1,0x01FA,
0x0200,0x0209,0x0213,0x021A,0x0223,0x0228,0x0232,0x023A,0x0243,0x024C,0x0257,0x025C,0x0268,0x026C,0x0279,0x027F,
0x028A,0x0291,0x029E,0x02A3,0x02AE,0x02B7,0x02C0,0x02C9,0x02D6,0x02DB,0x02E9,0x02EE,0x02FA,0x0303,0x030F,0x0316,
0x0321,0x032A,0x0337,0x033F,0x034B,0x0353,0x0360,0x0368,0x0374,0x037D,0x0388,0x0393,0x039F,0x03A7,0x03B4,0x03BD,
0x03C9,0x03D3,0x03E0,0x03E9,0x03F7,0x0400,0x040E,0x0417,0x0425,0x042D,0x043C,0x0445,0x0453,0x045C,0x046B,0x0475,
0x0480,0x048E,0x049B,0x04A4,0x04B2,0x04BD,0x04CC,0x04D6,0x04E5,0x04EE,0x04FC,0x0509,0x0517,0x0521,0x0530,0x053B,
0x0549,0x0556,0x0566,0x056F,0x057D,0x058B,0x059A,0x05A4,0x05B3,0x05C1,0x05D0,0x05DB,0x05EC,0x05F8,0x0605,0x0613,
0x0621,0x062E,0x063E,0x064B,0x065C,0x0666,0x0678,0x0684,0x0695,0x06A1,0x06B1,0x06BF,0x06D0,0x06DC,0x06EE,0x06FB,
0x070A,0x0718,0x0729,0x0736,0x0746,0x0755,0x0767,0x0773,0x0783,0x0792,0x07A3,0x07B1,0x07C2,0x07D1,0x07E2,0x07F0,
0x0800,0x0811,0x0822,0x0830,0x0842,0x0851,0x0864,0x0872,0x0883,0x0894,0x08A6,0x08B5,0x08C6,0x08D6,0x08E9,0x08F9,
0x090A,0x091A,0x092C,0x093B,0x094F,0x095E,0x0971,0x0982,0x0995,0x09A3,0x09B8,0x09C8,0x09DC,0x09EA,0x09FC,0x0A0F,
0x0A20,0x0A33,0x0A45,0x0A56,0x0A6C,0x0A7C,0x0A91,0x0A9F,0x0AB3,0x0AC6,0x0AD9,0x0AEA,0x0AFD,0x0B10,0x0B25,0x0B36,
0x0B49,0x0B5B,0x0B71,0x0B82,0x0B97,0x0BA8,0x0BBD,0x0BD0,0x0BE6,0x0BF7,0x0C0C,0x0C1C,0x0C31,0x0C45,0x0C5A,0x0C6B,
0x0C80,0x0C95,0x0CAA,0x0CBC,0x0CD3,0x0CE3,0x0CFB,0x0D0F,0x0D24,0x0D38,0x0D4D,0x0D60,0x0D77,0x0D8A,0x0DA1,0x0DB4,
0x0DCA,0x0DDD,0x0DF4,0x0E08,0x0E1F,0x0E32,0x0E48,0x0E5C,0x0E73,0x0E89,0x0EA0,0x0EB3,0x0ECB,0x0EDF,0x0EF6,0x0F0B,
0x0F21,0x0F37,0x0F4E,0x0F62,0x0F7A,0x0F90,0x0FA9,0x0FBC,0x0FD6,0x0FE8,0x0FFF,0x1016,0x102F,0x1044,0x105D,0x1071,
0x108A,0x109E,0x10B9,0x10CF,0x10E8,0x10FD,0x1116,0x112B,0x1143,0x115A,0x1172,0x1189,0x11A3,0x11B9,0x11D2,0x11E8,
0x1200,0x1219,0x1230,0x1249,0x1263,0x127A,0x1294,0x12AA,0x12C3,0x12DA,0x12F5,0x130D,0x1328,0x133E,0x1359,0x136F,
0x138A,0x13A2,0x13BC,0x13D4,0x13F0,0x1406,0x1421,0x143A,0x1455,0x146B,0x1486,0x149E,0x14BB,0x14D2,0x14EE,0x1507,
0x1521,0x153B,0x1557,0x156E,0x158C,0x15A3,0x15BF,0x15D8,0x15F4,0x160D,0x1629,0x1642,0x165F,0x1679,0x1696,0x16AD,
0x16CA,0x16E2,0x16FE,0x171A,0x1737,0x1750,0x176E,0x1788,0x17A4,0x17BE,0x17DC,0x17F6,0x1814,0x182C,0x184A,0x1863,
0x1880,0x189B,0x18BA,0x18D5,0x18F2,0x190E,0x192B,0x1947,0x1966,0x197E,0x199E,0x19B8,0x19D8,0x19F1,0x1A11,0x1A2B,
0x1A49,0x1A64,0x1A83,0x1A9E,0x1ABD,0x1ADA,0x1AF8,0x1B15,0x1B34,0x1B50,0x1B70,0x1B8C,0x1BAB,0x1BC8,0x1BE7,0x1C02,
0x1C21,0x1C3E,0x1C5E,0x1C7B,0x1C9C,0x1CB7,0x1CD8,0x1CF5,0x1D15,0x1D30,0x1D52,0x1D6C,0x1D90,0x1DAB,0x1DCC,0x1DE9,
0x1E0A,0x1E26,0x1E48,0x1E65,0x1E86,0x1EA4,0x1EC4,0x1EE2,0x1F03,0x1F22,0x1F42,0x1F61,0x1F82,0x1FA0,0x1FC1,0x1FE0,
0x2000,0x201F,0x2041,0x2060,0x2082,0x20A1,0x20C2,0x20E1,0x2103,0x2122,0x2144,0x2163,0x2186,0x21A5,0x21C7,0x21E7,
0x2209,0x2229,0x224C,0x226B,0x2290,0x22AD,0x22D1,0x22F0,0x2315,0x2334,0x2358,0x2378,0x239C,0x23BB,0x23DE,0x23FE,
0x2421,0x2442,0x2467,0x2487,0x24AB,0x24CC,0x24EF,0x2510,0x2534,0x2555,0x2579,0x259A,0x25BE,0x25DF,0x2604,0x2624,
0x2649,0x266B,0x2691,0x26B1,0x26D8,0x26F9,0x271D,0x2740,0x2765,0x2785,0x27AB,0x27CE,0x27F2,0x2815,0x283A,0x285C,
0x2880,0x28A3,0x28CA,0x28EC,0x2914,0x2935,0x295B,0x297E,0x29A4,0x29C7,0x29ED,0x2A11,0x2A38,0x2A5A,0x2A7E,0x2AA2,
0x2ACA,0x2AEC,0x2B15,0x2B38,0x2B5F,0x2B82,0x2BA9,0x2BCE,0x2BF4,0x2C18,0x2C3F,0x2C62,0x2C8C,0x2CAE,0x2CD7,0x2CFD,
0x2D21,0x2D47,0x2D6D,0x2D93,0x2DBB,0x2DDE,0x2E06,0x2E2B,0x2E55,0x2E79,0x2EA1,0x2EC7,0x2EEF,0x2F14,0x2F3C,0x2F60,
0x2F8A,0x2FAF,0x2FD8,0x2FFE,0x3028,0x304D,0x3075,0x309A,0x30C4,0x30E9,0x3114,0x3139,0x3163,0x3189,0x31B1,0x31D8,
0x3200,0x3227,0x3252,0x327A,0x32A3,0x32CA,0x32F2,0x331A,0x3343,0x336B,0x3397,0x33BC,0x33E8,0x340E,0x3439,0x345F,
0x348A,0x34B1,0x34DE,0x3504,0x352E,0x3557,0x357F,0x35A7,0x35D5,0x35FE,0x3629,0x3650,0x367B,0x36A2,0x36CF,0x36F7,
0x3721,0x374B,0x3776,0x379D,0x37CB,0x37F3,0x3820,0x3849,0x3874,0x389B,0x38C8,0x38F2,0x391F,0x3948,0x3975,0x399C,
0x39CA,0x39F3,0x3A20,0x3A49,0x3A77,0x3A9F,0x3ACE,0x3AF8,0x3B24,0x3B4E,0x3B7B,0x3BA5,0x3BD3,0x3BFD,0x3C2A,0x3C55,
0x3C80,0x3CAC,0x3CDB,0x3D04,0x3D32,0x3D5D,0x3D8D,0x3DB7,0x3DE6,0x3E10,0x3E3D,0x3E68,0x3E98,0x3EC3,0x3EF0,0x3F1B,
0x3F49,0x3F76,0x3FA5,0x3FD1,0x3FFD,0x4029,0x405A,0x4084,0x40B3,0x40DF,0x4110,0x413B,0x416B,0x4196,0x41C5,0x41F2,
0x4221,0x424F,0x427E,0x42AA,0x42DC,0x4307,0x4339,0x4363,0x4395,0x43C2,0x43F0,0x441E,0x4450,0x447D,0x44AB,0x44DA,
0x4509,0x4538,0x456A,0x4596,0x45C7,0x45F4,0x4626,0x4652,0x4684,0x46B1,0x46E4,0x4712,0x4742,0x4770,0x47A2,0x47D1,
0x4800,0x482F,0x4862,0x4891,0x48C2,0x48F1,0x4923,0x4951,0x4984,0x49B3,0x49E6,0x4A15,0x4A45,0x4A76,0x4AA9,0x4AD7,
0x4B09,0x4B39,0x4B6C,0x4B9B,0x4BCF,0x4BFE,0x4C30,0x4C60,0x4C95,0x4CC4,0x4CF8,0x4D26,0x4D5B,0x4D8B,0x4DBD,0x4DED,
0x4E22,0x4E52,0x4E84,0x4EB7,0x4EEB,0x4F1B,0x4F4F,0x4F80,0x4FB4,0x4FE4,0x501A,0x504B,0x507D,0x50AF,0x50E6,0x5116,
0x5149,0x517D,0x51AF,0x51DF,0x5217,0x5248,0x527D,0x52AD,0x52E6,0x5316,0x534C,0x537D,0x53B2,0x53E4,0x541A,0x544D,
0x5481,0x54B5,0x54EB,0x551C,0x5554,0x5585,0x55BA,0x55EE,0x5624,0x5655,0x568D,0x56C0,0x56F8,0x5729,0x5760,0x5795,
0x57C9,0x57FE,0x5834,0x5867,0x589F,0x58D3,0x5907,0x593E,0x5974,0x59A7,0x59DF,0x5A14,0x5A4C,0x5A7E,0x5AB7,0x5AEA,
0x5B22,0x5B55,0x5B8D,0x5BC3,0x5BFC,0x5C2E,0x5C69,0x5C9C,0x5CD5,0x5D09,0x5D3F,0x5D76,0x5DAF,0x5DE4,0x5E1A,0x5E51,
0x5E89,0x5EC0,0x5EF8,0x5F2E,0x5F69,0x5F9C,0x5FD7,0x600B,0x6043,0x607A,0x60B2,0x60EA,0x6123,0x6159,0x6192,0x61CA,
0x6200,0x6239,0x626F,0x62A8,0x62E2,0x6316,0x6354,0x6387,0x63C2,0x63FC,0x6434,0x646B,0x64A6,0x64DC,0x651A,0x6550,
0x6589,0x65C3,0x65FB,0x6633,0x666E,0x66A5,0x66DE,0x6716,0x6754,0x678D,0x67C5,0x67FF,0x683C,0x6872,0x68AF,0x68E5,
0x6920,0x695A,0x6997,0x69D0,0x6A0A,0x6A43,0x6A7E,0x6AB8,0x6AF4,0x6B2B,0x6B68,0x6BA1,0x6BDF,0x6C19,0x6C54,0x6C8F,
0x6CC9,0x6D00,0x6D3E,0x6D79,0x6DB5,0x6DF1,0x6E2D,0x6E68,0x6EA6,0x6EDA,0x6F1A,0x6F55,0x6F92,0x6FCE,0x700A,0x7045,
0x7081,0x70BD,0x70FB,0x7133,0x7171,0x71AD,0x71ED,0x7224,0x7263,0x72A0,0x72DC,0x7319,0x7356,0x7392,0x73CF,0x740C,
0x744B,0x7485,0x74C2,0x74FF,0x753C,0x7579,0x75B7,0x75F4,0x7632,0x766F,0x76AD,0x76EA,0x7728,0x7766,0x77A4,0x77E2,
0x7820,0x785E,0x789D,0x78DA,0x791A,0x7956,0x7996,0x79D3,0x7A13,0x7A50,0x7A8F,0x7ACE,0x7B0F,0x7B4C,0x7B8B,0x7BCA,
0x7C09,0x7C48,0x7C87,0x7CC7,0x7D07,0x7D45,0x7D85,0x7DC6,0x7E05,0x7E44,0x7E84,0x7EC4,0x7F03,0x7F44,0x7F82,0x7FC0};

; // tab_plus[i] = ((1024 + 1024 + i) * (1024 + 1024 + i))/4 +- 0x5
int tab_plus[MAX_NUMBER+MAX_NUMBER+1] = {  // [0..2046]
0x20000,0x20080,0x20100,0x20180,0x20200,0x20280,0x20301,0x20381,0x20402,0x20482,0x20503,0x20583,0x20604,0x20685,0x20706,0x20787,
0x20808,0x20889,0x2090A,0x2098B,0x20A0C,0x20A8D,0x20B0F,0x20B90,0x20C12,0x20C93,0x20D15,0x20D96,0x20E18,0x20E9A,0x20F1C,0x20F9E,
0x21020,0x210A2,0x21124,0x211A6,0x21228,0x212AA,0x2132D,0x213AF,0x21432,0x214B4,0x21537,0x215B9,0x2163C,0x216BF,0x21745,0x217C5,
0x21849,0x218CC,0x21951,0x219D3,0x21A57,0x21AD9,0x21B5E,0x21BE0,0x21C62,0x21CE5,0x21D6E,0x21DED,0x21E72,0x21EF2,0x21F7D,0x21FFD,
0x22081,0x22104,0x2218C,0x2220E,0x22294,0x22314,0x2239A,0x2241B,0x224A1,0x22529,0x225AF,0x22630,0x226B5,0x22739,0x227BE,0x22844,
0x228C9,0x2294F,0x229D7,0x22A59,0x22AE0,0x22B60,0x22BE9,0x22C6D,0x22CF2,0x22D78,0x22DFF,0x22E84,0x22F0C,0x22F90,0x23017,0x2309B,
0x23121,0x231A9,0x2322F,0x232B2,0x2333C,0x233C0,0x23447,0x234CD,0x23555,0x235D9,0x23660,0x236E5,0x2376F,0x237F4,0x2387D,0x23904,
0x23989,0x23A10,0x23A9A,0x23B1B,0x23BA7,0x23C29,0x23CB6,0x23D3C,0x23DC4,0x23E4C,0x23ED5,0x23F59,0x23FE2,0x24069,0x240F2,0x24178,
0x24202,0x24289,0x24313,0x24398,0x24423,0x244AB,0x24534,0x245BC,0x24644,0x246CC,0x24756,0x247DD,0x24868,0x248ED,0x24979,0x24A01,
0x24A89,0x24B10,0x24B9A,0x24C24,0x24CAE,0x24D37,0x24DC0,0x24E4A,0x24ED5,0x24F5C,0x24FE9,0x2506D,0x250FB,0x25184,0x2520C,0x25294,
0x25323,0x253AB,0x25436,0x254BF,0x2554C,0x255D3,0x25660,0x256E8,0x25774,0x257FE,0x25889,0x25913,0x2599F,0x25A26,0x25AB6,0x25B3F,
0x25BC9,0x25C54,0x25CE0,0x25D6A,0x25DF8,0x25E84,0x25F0E,0x25F96,0x26025,0x260AE,0x2613B,0x261C5,0x26253,0x262DC,0x26369,0x263F4,
0x26482,0x2650E,0x2659A,0x26624,0x266B2,0x2673F,0x267CD,0x26856,0x268E4,0x2696E,0x269FD,0x26A89,0x26B18,0x26BA1,0x26C30,0x26CBC,
0x26D49,0x26DD6,0x26E66,0x26EEE,0x26F7D,0x2700C,0x2709A,0x27124,0x271B4,0x27240,0x272D1,0x2735C,0x273E9,0x27479,0x27506,0x27593,
0x27623,0x276AD,0x2773D,0x277CC,0x2785C,0x278E7,0x27979,0x27A05,0x27A96,0x27B21,0x27BB0,0x27C3F,0x27CD0,0x27D5C,0x27DEC,0x27E79,
0x27F09,0x27F97,0x2802A,0x280B6,0x28146,0x281D5,0x28266,0x282F4,0x28382,0x28413,0x284A5,0x28531,0x285C2,0x28651,0x286E2,0x28771,
0x28802,0x28890,0x28922,0x289B2,0x28A42,0x28AD3,0x28B63,0x28BF2,0x28C83,0x28D13,0x28DA7,0x28E35,0x28EC6,0x28F56,0x28FE9,0x29079,
0x29109,0x2919B,0x2922D,0x292BC,0x29350,0x293DE,0x29471,0x29504,0x29596,0x29624,0x296B8,0x29747,0x297DC,0x2986A,0x298FD,0x29990,
0x29A22,0x29AB3,0x29B45,0x29BD7,0x29C6A,0x29CFB,0x29D90,0x29E21,0x29EB4,0x29F45,0x29FDA,0x2A069,0x2A0FF,0x2A190,0x2A226,0x2A2B6,
0x2A349,0x2A3DC,0x2A470,0x2A504,0x2A598,0x2A628,0x2A6BC,0x2A750,0x2A7E5,0x2A877,0x2A90C,0x2A99E,0x2AA32,0x2AAC5,0x2AB5B,0x2ABED,
0x2AC82,0x2AD15,0x2ADAB,0x2AE3D,0x2AED3,0x2AF65,0x2AFFC,0x2B08F,0x2B125,0x2B1B9,0x2B24E,0x2B2E0,0x2B378,0x2B40A,0x2B4A1,0x2B534,
0x2B5C9,0x2B65D,0x2B6F5,0x2B789,0x2B81F,0x2B8B3,0x2B948,0x2B9DC,0x2BA73,0x2BB09,0x2BBA0,0x2BC34,0x2BCCC,0x2BD5F,0x2BDF7,0x2BE8B,
0x2BF22,0x2BFB8,0x2C04F,0x2C0E3,0x2C17B,0x2C211,0x2C2A9,0x2C33D,0x2C3D5,0x2C468,0x2C500,0x2C597,0x2C62F,0x2C6C4,0x2C75E,0x2C7F2,
0x2C889,0x2C920,0x2C9B9,0x2CA4F,0x2CAE8,0x2CB7D,0x2CC17,0x2CCAB,0x2CD43,0x2CDDB,0x2CE73,0x2CF0A,0x2CFA3,0x2D03B,0x2D0D2,0x2D168,
0x2D202,0x2D298,0x2D332,0x2D3CA,0x2D463,0x2D4FA,0x2D594,0x2D62A,0x2D6C4,0x2D75C,0x2D7F6,0x2D88E,0x2D928,0x2D9BF,0x2DA59,0x2DAEF,
0x2DB89,0x2DC21,0x2DCBC,0x2DD55,0x2DDEE,0x2DE88,0x2DF22,0x2DFBA,0x2E055,0x2E0EC,0x2E187,0x2E220,0x2E2BA,0x2E354,0x2E3ED,0x2E488,
0x2E522,0x2E5BC,0x2E656,0x2E6EF,0x2E78B,0x2E823,0x2E8BE,0x2E959,0x2E9F3,0x2EA8E,0x2EB2B,0x2EBC3,0x2EC5F,0x2ECF9,0x2ED97,0x2EE2C,
0x2EEC9,0x2EF63,0x2EFFF,0x2F099,0x2F137,0x2F1D1,0x2F26D,0x2F308,0x2F3A5,0x2F43F,0x2F4DC,0x2F576,0x2F613,0x2F6AC,0x2F74B,0x2F7E4,
0x2F882,0x2F91C,0x2F9BA,0x2FA55,0x2FAF2,0x2FB8E,0x2FC2D,0x2FCC6,0x2FD64,0x2FE00,0x2FE9E,0x2FF3A,0x2FFD7,0x30072,0x30111,0x301AB,
0x30249,0x302E5,0x30384,0x30420,0x304BD,0x3055B,0x305FA,0x30696,0x30733,0x307D1,0x30870,0x3090D,0x309AC,0x30A48,0x30AE7,0x30B83,
0x30C22,0x30CBE,0x30D5F,0x30DFB,0x30E9C,0x30F39,0x30FD9,0x31075,0x31115,0x311B1,0x31252,0x312EE,0x3138F,0x3142B,0x314CE,0x31569,
0x31609,0x316A7,0x31748,0x317E5,0x31886,0x31923,0x319C5,0x31A62,0x31B03,0x31BA1,0x31C43,0x31CE2,0x31D82,0x31E21,0x31EC1,0x31F60,
0x32001,0x320A0,0x32141,0x321E0,0x32282,0x32321,0x323C3,0x32462,0x32503,0x325A2,0x32645,0x326E4,0x32786,0x32825,0x328C7,0x32966,
0x32A09,0x32AA9,0x32B4D,0x32BEB,0x32C8F,0x32D2D,0x32DD2,0x32E70,0x32F15,0x32FB5,0x33059,0x330F8,0x3319C,0x3323B,0x332DF,0x3337F,
0x33422,0x334C3,0x33567,0x33608,0x336AC,0x3374C,0x337F0,0x33890,0x33933,0x339D5,0x33A7A,0x33B1A,0x33BBD,0x33C5F,0x33D04,0x33DA4,
0x33E49,0x33EEB,0x33F91,0x34031,0x340D7,0x34179,0x3421E,0x342BF,0x34364,0x34407,0x344AD,0x3454E,0x345F2,0x34695,0x3473A,0x347DB,
0x34881,0x34924,0x349CB,0x34A6D,0x34B13,0x34BB6,0x34C5D,0x34CFE,0x34DA5,0x34E48,0x34EEC,0x34F91,0x35037,0x350DA,0x3517F,0x35222,
0x352C9,0x3536D,0x35417,0x354B9,0x3555F,0x35602,0x356AA,0x3574F,0x357F3,0x35898,0x3593E,0x359E2,0x35A8B,0x35B2D,0x35BD7,0x35C7B,
0x35D22,0x35DC7,0x35E6D,0x35F12,0x35FBA,0x3605E,0x36107,0x361AC,0x36255,0x362FA,0x363A1,0x36446,0x364EE,0x36594,0x3663C,0x366E2,
0x36789,0x3682F,0x368D9,0x3697E,0x36A28,0x36ACD,0x36B76,0x36C1B,0x36CC3,0x36D6A,0x36E14,0x36EBB,0x36F63,0x37009,0x370B2,0x37159,
0x37201,0x372A8,0x37352,0x373F9,0x374A3,0x3754A,0x375F2,0x3769A,0x37743,0x377EB,0x37897,0x3793D,0x379E8,0x37A8F,0x37B38,0x37BDF,
0x37C89,0x37D31,0x37DDD,0x37E84,0x37F2F,0x37FD6,0x38081,0x38129,0x381D5,0x3827C,0x38329,0x383CF,0x3847B,0x38522,0x385CF,0x38677,
0x38722,0x387CB,0x38877,0x3891F,0x389CC,0x38A74,0x38B20,0x38BC9,0x38C73,0x38D1D,0x38DC8,0x38E72,0x38F1F,0x38FC9,0x39075,0x3911D,
0x391C9,0x39274,0x39320,0x393CA,0x39478,0x39520,0x395CE,0x39678,0x39725,0x397CF,0x3987C,0x39924,0x399D3,0x39A7D,0x39B2B,0x39BD5,
0x39C81,0x39D2C,0x39DDB,0x39E85,0x39F32,0x39FDC,0x3A08C,0x3A137,0x3A1E4,0x3A290,0x3A33C,0x3A3E7,0x3A498,0x3A542,0x3A5F0,0x3A69C,
0x3A749,0x3A7F6,0x3A8A7,0x3A951,0x3A9FE,0x3AAAA,0x3AB5A,0x3AC05,0x3ACB4,0x3AD5F,0x3AE10,0x3AEBC,0x3AF6B,0x3B016,0x3B0C5,0x3B173,
0x3B222,0x3B2D0,0x3B37E,0x3B42B,0x3B4DC,0x3B588,0x3B638,0x3B6E3,0x3B795,0x3B841,0x3B8F0,0x3B99E,0x3BA50,0x3BAFC,0x3BBAD,0x3BC5A,
0x3BD09,0x3BDB9,0x3BE69,0x3BF17,0x3BFC6,0x3C075,0x3C127,0x3C1D4,0x3C283,0x3C332,0x3C3E4,0x3C492,0x3C542,0x3C5F0,0x3C6A2,0x3C752,
0x3C801,0x3C8B0,0x3C962,0x3CA12,0x3CAC2,0x3CB71,0x3CC24,0x3CCD3,0x3CD83,0x3CE33,0x3CEE6,0x3CF95,0x3D046,0x3D0F7,0x3D1AA,0x3D258,
0x3D309,0x3D3BB,0x3D46B,0x3D51C,0x3D5D0,0x3D67F,0x3D731,0x3D7E1,0x3D895,0x3D944,0x3D9F9,0x3DAA6,0x3DB5C,0x3DC0C,0x3DCBC,0x3DD6E,
0x3DE22,0x3DED3,0x3DF85,0x3E038,0x3E0EB,0x3E19B,0x3E250,0x3E301,0x3E3B3,0x3E464,0x3E51A,0x3E5CB,0x3E67E,0x3E730,0x3E7E5,0x3E896,
0x3E949,0x3E9FC,0x3EAB0,0x3EB62,0x3EC18,0x3ECC9,0x3ED7D,0x3EE2F,0x3EEE4,0x3EF97,0x3F04D,0x3F0FD,0x3F1B2,0x3F264,0x3F31B,0x3F3CE,
0x3F481,0x3F536,0x3F5EA,0x3F69D,0x3F753,0x3F806,0x3F8BB,0x3F96D,0x3FA25,0x3FAD7,0x3FB8D,0x3FC40,0x3FCF7,0x3FDA9,0x3FE60,0x3FF13,
0x3FFC9,0x4007E,0x40135,0x401E7,0x4029F,0x40353,0x40408,0x404BE,0x40573,0x40628,0x406E0,0x40794,0x4084B,0x408FF,0x409B6,0x40A6A,
0x40B21,0x40BD7,0x40C8F,0x40D43,0x40DFA,0x40EAF,0x40F69,0x4101C,0x410D5,0x41189,0x4123F,0x412F7,0x413AF,0x41463,0x4151E,0x415D3,
0x41689,0x41740,0x417FA,0x418AD,0x41967,0x41A1B,0x41AD7,0x41B8C,0x41C43,0x41CFB,0x41DB2,0x41E69,0x41F23,0x41FD9,0x42092,0x42149,
0x42200,0x422B9,0x42371,0x42429,0x424E3,0x4259A,0x42654,0x4270B,0x427C3,0x4287B,0x42936,0x429EC,0x42AA8,0x42B5D,0x42C18,0x42CD0,
0x42D89,0x42E43,0x42EFB,0x42FB4,0x4306E,0x43126,0x431E1,0x4329A,0x43355,0x4340D,0x434C7,0x43580,0x4363B,0x436F3,0x437AD,0x43866,
0x43922,0x439DB,0x43A98,0x43B50,0x43C0C,0x43CC3,0x43D7E,0x43E39,0x43EF3,0x43FAD,0x4406A,0x44122,0x441DF,0x44298,0x44357,0x4440F,
0x444C9,0x44584,0x44640,0x446FB,0x447B7,0x44870,0x4492D,0x449E6,0x44AA4,0x44B5E,0x44C1D,0x44CD6,0x44D94,0x44E4E,0x44F0B,0x44FC5,
0x45080,0x4513E,0x451FA,0x452B5,0x45372,0x4542D,0x454EC,0x455A5,0x45665,0x4571E,0x457DE,0x45899,0x45958,0x45A12,0x45AD1,0x45B8C,
0x45C49,0x45D06,0x45DC4,0x45E81,0x45F3E,0x45FFB,0x460BA,0x46176,0x46233,0x462F0,0x463B0,0x4646B,0x4652B,0x465E6,0x466A7,0x46762,
0x46822,0x468DF,0x4699E,0x46A5B,0x46B1C,0x46BD8,0x46C99,0x46D55,0x46E15,0x46ED1,0x46F92,0x47050,0x4710E,0x471CD,0x4728D,0x4734B,
0x47409,0x474C8,0x47587,0x47647,0x47705,0x477C5,0x47885,0x47944,0x47A03,0x47AC2,0x47B83,0x47C43,0x47D02,0x47DC2,0x47E81,0x47F42,
0x48000,0x480C2,0x48181,0x48242,0x48302,0x483C2,0x48483,0x48544,0x48603,0x486C3,0x48785,0x48845,0x48905,0x489C7,0x48A87,0x48B49,
0x48C09,0x48CC9,0x48D8D,0x48E4D,0x48F0E,0x48FCF,0x49092,0x49152,0x49215,0x492D4,0x49398,0x49457,0x4951C,0x495DB,0x4969E,0x4975E,
0x49822,0x498E2,0x499A7,0x49A66,0x49B2B,0x49BEB,0x49CB0,0x49D70,0x49E33,0x49EF6,0x49FBA,0x4A07B,0x4A13E,0x4A200,0x4A2C4,0x4A385,
0x4A449,0x4A50D,0x4A5D1,0x4A693,0x4A758,0x4A819,0x4A8DE,0x4A99F,0x4AA65,0x4AB25,0x4ABEC,0x4ACAD,0x4AD72,0x4AE37,0x4AEFA,0x4AFBD,
0x4B080,0x4B145,0x4B20B,0x4B2CE,0x4B394,0x4B456,0x4B51D,0x4B5DE,0x4B6A4,0x4B767,0x4B82C,0x4B8F0,0x4B9B7,0x4BA7C,0x4BB40,0x4BC04,
0x4BCC9,0x4BD8E,0x4BE57,0x4BF19,0x4BFDF,0x4C0A2,0x4C16A,0x4C22D,0x4C2F3,0x4C3B9,0x4C47E,0x4C544,0x4C60C,0x4C6D0,0x4C797,0x4C85B,
0x4C922,0x4C9E6,0x4CAAD,0x4CB73,0x4CC3A,0x4CCFF,0x4CDC7,0x4CE8D,0x4CF55,0x4D019,0x4D0E1,0x4D1A5,0x4D26F,0x4D335,0x4D3FC,0x4D4C2,
0x4D589,0x4D651,0x4D719,0x4D7DE,0x4D8A8,0x4D96C,0x4DA35,0x4DAFC,0x4DBC3,0x4DC8B,0x4DD54,0x4DE19,0x4DEE3,0x4DFA8,0x4E071,0x4E139,
0x4E200,0x4E2C9,0x4E393,0x4E459,0x4E523,0x4E5E9,0x4E6B3,0x4E77D,0x4E843,0x4E90C,0x4E9D7,0x4EA9C,0x4EB68,0x4EC2D,0x4ECF9,0x4EDC1,
0x4EE89,0x4EF52,0x4F01E,0x4F0E3,0x4F1AE,0x4F277,0x4F340,0x4F40A,0x4F4D5,0x4F59C,0x4F669,0x4F72F,0x4F7FA,0x4F8C3,0x4F98F,0x4FA57,
0x4FB22,0x4FBE9,0x4FCB5,0x4FD80,0x4FE4B,0x4FF15,0x4FFE0,0x500A7,0x50174,0x5023D,0x50308,0x503D2,0x5049F,0x50568,0x50635,0x506FE,
0x507C9,0x50894,0x50960,0x50A29,0x50AF7,0x50BC2,0x50C8E,0x50D57,0x50E24,0x50EEC,0x50FBC,0x51085,0x51153,0x5121C,0x512EB,0x513B5,
0x51480,0x5154D,0x5161B,0x516E4,0x517B1,0x5187E,0x5194C,0x51A16,0x51AE5,0x51BAF,0x51C7C,0x51D49,0x51E18,0x51EE2,0x51FB0,0x5207D,
0x52149,0x52216,0x522E7,0x523AF,0x5247D,0x5254C,0x5261A,0x526E4,0x527B4,0x52880,0x52950,0x52A1B,0x52AEB,0x52BB8,0x52C85,0x52D52,
0x52E22,0x52EEE,0x52FBE,0x5308C,0x5315C,0x53227,0x532F8,0x533C5,0x53495,0x53561,0x53630,0x536FF,0x537CF,0x5389C,0x5396D,0x53A3A,
0x53B09,0x53BD8,0x53CAA,0x53D77,0x53E46,0x53F15,0x53FE7,0x540B4,0x54183,0x54252,0x54324,0x543F1,0x544C2,0x54592,0x54662,0x54730,
0x54800,0x548D1,0x549A2,0x54A70,0x54B42,0x54C11,0x54CE4,0x54DB1,0x54E83,0x54F53,0x55026,0x550F5,0x551C6,0x55296,0x55369,0x55438,
0x55509,0x555DA,0x556AC,0x5577D,0x55850,0x5591D,0x559F2,0x55AC2,0x55B95,0x55C63,0x55D38,0x55E09,0x55EDB,0x55FAB,0x5607C,0x56150,
0x56222,0x562F3,0x563C5,0x56497,0x5656C,0x5663C,0x56711,0x567E0,0x568B4,0x56985,0x56A59,0x56B2B,0x56BFD,0x56CD1,0x56DA5,0x56E77,
0x56F49,0x5701B,0x570F1,0x571C2,0x57297,0x57368,0x5743D,0x5750F,0x575E5,0x576B7,0x5778C,0x5785D,0x57932,0x57A05,0x57ADA,0x57BAC,
0x57C80,0x57D55,0x57E2A,0x57EFD,0x57FD3,0x580A4,0x5817B,0x58250,0x58324,0x583F6,0x584CD,0x5859F,0x58677,0x5874B,0x58821,0x588F4,
0x589C9,0x58A9E,0x58B75,0x58C49,0x58D1F,0x58DF3,0x58EC8,0x58F9C,0x59074,0x59149,0x59220,0x592F4,0x593CB,0x5949F,0x59576,0x5964C,
0x59722,0x597F6,0x598CE,0x599A2,0x59A7A,0x59B51,0x59C29,0x59CFD,0x59DD4,0x59EA8,0x59F7F,0x5A057,0x5A12E,0x5A204,0x5A2DD,0x5A3B1,
0x5A489,0x5A55F,0x5A639,0x5A70F,0x5A7E8,0x5A8BD,0x5A996,0x5AA6C,0x5AB43,0x5AC18,0x5ACF2,0x5ADCB,0x5AEA3,0x5AF7B,0x5B052,0x5B129,
0x5B200,0x5B2D8,0x5B3B0,0x5B48A,0x5B563,0x5B63A,0x5B714,0x5B7E9,0x5B8C3,0x5B99C,0x5BA75,0x5BB4D,0x5BC27,0x5BCFE,0x5BDD9,0x5BEAF,
0x5BF89,0x5C061,0x5C13C,0x5C215,0x5C2EF,0x5C3C7,0x5C4A0,0x5C57B,0x5C655,0x5C72C,0x5C807,0x5C8E0,0x5C9BB,0x5CA94,0x5CB6E,0x5CC47,
0x5CD22,0x5CDFB,0x5CED7,0x5CFAF,0x5D08B,0x5D163,0x5D23F,0x5D318,0x5D3F3,0x5D4CF,0x5D5A9,0x5D682,0x5D75F,0x5D838,0x5D916,0x5D9EC,
0x5DAC9,0x5DBA4,0x5DC7E,0x5DD5A,0x5DE37,0x5DF11,0x5DFEE,0x5E0C9,0x5E1A4,0x5E27E,0x5E35C,0x5E436,0x5E512,0x5E5EC,0x5E6CA,0x5E7A4,
0x5E880,0x5E95D,0x5EA3A,0x5EB16,0x5EBF2,0x5ECCF,0x5EDAB,0x5EE86,0x5EF65,0x5F040,0x5F11E,0x5F1FA,0x5F2D8,0x5F3B1,0x5F491,0x5F56C,
0x5F649,0x5F725,0x5F803,0x5F8E0,0x5F9BF,0x5FA9B,0x5FB78,0x5FC56,0x5FD33,0x5FE11,0x5FEF0,0x5FFCD,0x600AA,0x60188,0x60267,0x60343,
0x60422,0x604FE,0x605DE,0x606BC,0x6079B,0x60879,0x60958,0x60A35,0x60B15,0x60BF1,0x60CD2,0x60DAE,0x60E90,0x60F6C,0x6104C,0x61129,
0x61209,0x612E8,0x613C8,0x614A5,0x61586,0x61663,0x61744,0x61822,0x61903,0x619E2,0x61AC2,0x61BA0,0x61C82,0x61D61,0x61E41,0x61F20,
0x62000,0x620E1,0x621C0,0x622A0,0x62382,0x62461,0x62543,0x62623,0x62702,0x627E3,0x628C5,0x629A5,0x62A86,0x62B66,0x62C49,0x62D27,
0x62E0A,0x62EE9,0x62FCD,0x630AC,0x63190,0x6326E,0x63352,0x63430,0x63515,0x635F5,0x636D9,0x637B9,0x6389B,0x6397C,0x63A5E,0x63B40,
0x63C22,0x63D04,0x63DE8,0x63EC9,0x63FAB,0x6408C,0x64171,0x64251,0x64333,0x64416,0x644FA,0x645DB,0x646BF,0x647A0,0x64885,0x64966,
0x64A49,0x64B2B,0x64C12,0x64CF2,0x64DD8,0x64EB9,0x64F9E,0x6507F,0x65165,0x65248,0x6532C,0x6540F,0x654F2,0x655D6,0x656BB,0x6579C,
0x65880,0x65963,0x65A4B,0x65B2D,0x65C12,0x65CF7,0x65DDD,0x65EBF,0x65FA4,0x66088,0x6616E,0x66251,0x66337,0x66419,0x66500,0x665E4,
0x666C9,0x667AC,0x66896,0x6697A,0x66A5E,0x66B43,0x66C2A,0x66D0F,0x66DF3,0x66ED7,0x66FC0,0x670A5,0x6718B,0x6726E,0x67358,0x6743B,
0x67522,0x67607,0x676EE,0x677D3,0x678BB,0x679A0,0x67A87,0x67B6C,0x67C55,0x67D3A,0x67E22,0x67F07,0x67FEE,0x680D4,0x681BD,0x682A0,
0x68389,0x68470,0x68558,0x6863F,0x68727,0x6880D,0x688F6,0x689DB,0x68AC3,0x68BAA,0x68C94,0x68D7B,0x68E63,0x68F49,0x69032,0x69119,
0x69200,0x692EA,0x693D3,0x694B9,0x695A3,0x6968A,0x69773,0x6985B,0x69943,0x69A2A,0x69B17,0x69BFD,0x69CE8,0x69DCF,0x69EB8,0x69FA0,
0x6A089,0x6A173,0x6A25D,0x6A345,0x6A42E,0x6A519,0x6A600,0x6A6EA,0x6A7D4,0x6A8BF,0x6A9A8,0x6AA90,0x6AB79,0x6AC63,0x6AD4E,0x6AE39,
0x6AF22,0x6B00D,0x6B0F6,0x6B1DF,0x6B2CB,0x6B3B4,0x6B4A0,0x6B589,0x6B673,0x6B75D,0x6B849,0x6B932,0x6BA1F,0x6BB07,0x6BBF6,0x6BCDE,
0x6BDC9,0x6BEB4,0x6BFA0,0x6C08C,0x6C176,0x6C25F,0x6C34E,0x6C439,0x6C525,0x6C60F,0x6C6FB,0x6C7E2,0x6C8D3,0x6C9BF,0x6CAAA,0x6CB96,
0x6CC80,0x6CD6C,0x6CE5B,0x6CF45,0x6D032,0x6D119,0x6D20D,0x6D2F8,0x6D3E5,0x6D4CF,0x6D5BD,0x6D6A8,0x6D797,0x6D882,0x6D970,0x6DA5C,
0x6DB49,0x6DC36,0x6DD26,0x6DE11,0x6DEFD,0x6DFEA,0x6E0DA,0x6E1C4,0x6E2B4,0x6E3A0,0x6E491,0x6E57E,0x6E66C,0x6E757,0x6E845,0x6E933,
0x6EA21,0x6EB0F,0x6EBFD,0x6ECEA,0x6EDDA,0x6EEC9,0x6EFB8,0x6F0A5,0x6F194,0x6F281,0x6F370,0x6F45F,0x6F54E,0x6F63D,0x6F72A,0x6F819,
0x6F90A,0x6F9F8,0x6FAEA,0x6FBD7,0x6FCC6,0x6FDB4,0x6FEA6,0x6FF94,0x70084,0x70173,0x70265,0x70353,0x70442,0x70530,0x70621,0x70711,
0x70800,0x708F1,0x709E3,0x70ACF,0x70BC1,0x70CB1,0x70DA4,0x70E93,0x70F84,0x71072,0x71167,0x71255,0x71346,0x71433,0x7152A,0x71619,
0x7170A,0x717F9,0x718EE,0x719DB,0x71ACE,0x71BBE,0x71CB2,0x71DA0,0x71E94,0x71F84,0x72079,0x72164,0x72258,0x7234D,0x7243C,0x7252E,
0x72621,0x72715,0x72804,0x728F8,0x729EC,0x72ADB,0x72BCE,0x72CC4,0x72DB4,0x72EA5,0x72F9B,0x7308C,0x7317D,0x73272,0x73367,0x73455,
0x73547,0x7363D,0x73731,0x7381F,0x73915,0x73A07,0x73AFF,0x73BF1,0x73CE3,0x73DD5,0x73ECE,0x73FBD,0x740B2,0x741A5,0x7429B,0x7438E,
0x74480,0x74574,0x7466C,0x7475E,0x74850,0x74946,0x74A3A,0x74B2E,0x74C21,0x74D19,0x74E0D,0x74F01,0x74FF6,0x750EA,0x751E1,0x752D5,
0x753C9,0x754BD,0x755B5,0x756A8,0x757A0,0x75893,0x75989,0x75A7C,0x75B73,0x75C64,0x75D61,0x75E52,0x75F4C,0x7603E,0x76137,0x76229,
0x76320,0x76419,0x7650D,0x76604,0x766FB,0x767F1,0x768EA,0x769DB,0x76AD4,0x76BC9,0x76CC1,0x76DB8,0x76EAF,0x76FA5,0x7709E,0x77193,
0x77289,0x7737F,0x77476,0x77570,0x77665,0x7775C,0x77858,0x7794D,0x77A42,0x77B3B,0x77C31,0x77D29,0x77E20,0x77F19,0x7800F,0x78108,
0x781FF,0x782F8,0x783F0,0x784E9,0x785E3,0x786DB,0x787D4,0x788C9,0x789C2,0x78ABD,0x78BB7,0x78CAD,0x78DA9,0x78E9D,0x78F9B,0x79091,
0x79189,0x79282,0x7937A,0x79473,0x7956C,0x79665,0x79761,0x7985A,0x79952,0x79A49,0x79B45,0x79C3E,0x79D3A,0x79E32,0x79F30,0x7A023,
0x7A120,0x7A219,0x7A315,0x7A410,0x7A50D,0x7A601,0x7A6FD,0x7A7F8,0x7A8F5,0x7A9E9,0x7AAE7,0x7ABE2,0x7ACE0,0x7ADD4,0x7AED4,0x7AFCE,
0x7B0C7,0x7B1C4,0x7B2C1,0x7B3B8,0x7B4B6,0x7B5B2,0x7B6AE,0x7B7A9,0x7B8A2,0x7B99C,0x7BA9E,0x7BB96,0x7BC94,0x7BD8E,0x7BE8C,0x7BF85,
0x7C080,0x7C17C,0x7C278,0x7C374,0x7C470,0x7C56C,0x7C669,0x7C765,0x7C862,0x7C95E,0x7CA5B,0x7CB57,0x7CC54,0x7CD51,0x7CE4E,0x7CF4B,
0x7D048,0x7D145,0x7D242,0x7D33F,0x7D43C,0x7D539,0x7D637,0x7D734,0x7D832,0x7D92F,0x7DA2D,0x7DB2A,0x7DC28,0x7DD26,0x7DE24,0x7DF22,
0x7E020,0x7E11E,0x7E21C,0x7E31A,0x7E418,0x7E516,0x7E615,0x7E713,0x7E812,0x7E910,0x7EA0F,0x7EB0D,0x7EC0C,0x7ED0B,0x7EE0A,0x7EF09,
0x7F008,0x7F107,0x7F206,0x7F305,0x7F404,0x7F503,0x7F603,0x7F702,0x7F802,0x7F901,0x7FA01,0x7FB00,0x7FC00,0x7FD00,0x7FE00};

