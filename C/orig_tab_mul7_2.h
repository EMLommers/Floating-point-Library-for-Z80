#define MAX_NUMBER 127
#define TOP_BIT 0x800
#define PRICTI 0x7
#define POSUN_VPRAVO 4
#define POCET_BITU 7

; // 0000 1000  0000 ....  
; //                  111  
; //       654  3210 ....  

; //       neni presne: 7055 (43.060303%), preteceni: 7055, podteceni: 0
; // neni zaokrouhleno: 584 (3.564453%), preteceni: 0, podteceni: 584
; // sum(tab_dif[]): 0, sum(abs(tab_dif[])): 0
; // (( 128 + a ) * ( 128 + b )) >> 3 = (tab_plus[a+b] - tab_minus[a-b]) >> 3 = (1 mmmm mmm.) OR (0 1mmm mmmm)
; // 0 <= a <= 127, 0 <= b <= 127

; // tab_minus[i] = (i*i)/4 +- 0x0
int tab_minus[MAX_NUMBER+1] = {  // [0..127]
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0001,0x0001,0x0001,0x0002,0x0002,0x0003,0x0003,
0x0004,0x0004,0x0005,0x0005,0x0006,0x0006,0x0007,0x0008,0x0009,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,
0x0010,0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,0x0017,0x0019,0x001A,0x001B,0x001C,0x001E,0x001F,0x0021,0x0022,
0x0024,0x0025,0x0027,0x0028,0x002A,0x002B,0x002D,0x002F,0x0031,0x0032,0x0034,0x0036,0x0038,0x003A,0x003C,0x003E,
0x0040,0x0042,0x0044,0x0046,0x0048,0x004A,0x004C,0x004E,0x0051,0x0053,0x0055,0x0057,0x005A,0x005C,0x005F,0x0061,
0x0064,0x0066,0x0069,0x006B,0x006E,0x0070,0x0073,0x0076,0x0079,0x007B,0x007E,0x0081,0x0084,0x0087,0x008A,0x008D,
0x0090,0x0093,0x0096,0x0099,0x009C,0x009F,0x00A2,0x00A5,0x00A9,0x00AC,0x00AF,0x00B2,0x00B6,0x00B9,0x00BD,0x00C0,
0x00C4,0x00C7,0x00CB,0x00CE,0x00D2,0x00D5,0x00D9,0x00DD,0x00E1,0x00E4,0x00E8,0x00EC,0x00F0,0x00F4,0x00F8,0x00FC};

; // tab_plus[i] = ((128 + 128 + i) * (128 + 128 + i))/4 +- 0x0
int tab_plus[MAX_NUMBER+MAX_NUMBER+1] = {  // [0..254]
0x0400,0x0408,0x0410,0x0418,0x0420,0x0428,0x0430,0x0438,0x0441,0x0449,0x0451,0x0459,0x0462,0x046A,0x0473,0x047B,
0x0484,0x048C,0x0495,0x049D,0x04A6,0x04AE,0x04B7,0x04C0,0x04C9,0x04D1,0x04DA,0x04E3,0x04EC,0x04F5,0x04FE,0x0507,
0x0510,0x0519,0x0522,0x052B,0x0534,0x053D,0x0546,0x054F,0x0559,0x0562,0x056B,0x0574,0x057E,0x0587,0x0591,0x059A,
0x05A4,0x05AD,0x05B7,0x05C0,0x05CA,0x05D3,0x05DD,0x05E7,0x05F1,0x05FA,0x0604,0x060E,0x0618,0x0622,0x062C,0x0636,
0x0640,0x064A,0x0654,0x065E,0x0668,0x0672,0x067C,0x0686,0x0691,0x069B,0x06A5,0x06AF,0x06BA,0x06C4,0x06CF,0x06D9,
0x06E4,0x06EE,0x06F9,0x0703,0x070E,0x0718,0x0723,0x072E,0x0739,0x0743,0x074E,0x0759,0x0764,0x076F,0x077A,0x0785,
0x0790,0x079B,0x07A6,0x07B1,0x07BC,0x07C7,0x07D2,0x07DD,0x07E9,0x07F4,0x07FF,0x080A,0x0816,0x0821,0x082D,0x0838,
0x0844,0x084F,0x085B,0x0866,0x0872,0x087D,0x0889,0x0895,0x08A1,0x08AC,0x08B8,0x08C4,0x08D0,0x08DC,0x08E8,0x08F4,
0x0900,0x090C,0x0918,0x0924,0x0930,0x093C,0x0948,0x0954,0x0961,0x096D,0x0979,0x0985,0x0992,0x099E,0x09AB,0x09B7,
0x09C4,0x09D0,0x09DD,0x09E9,0x09F6,0x0A02,0x0A0F,0x0A1C,0x0A29,0x0A35,0x0A42,0x0A4F,0x0A5C,0x0A69,0x0A76,0x0A83,
0x0A90,0x0A9D,0x0AAA,0x0AB7,0x0AC4,0x0AD1,0x0ADE,0x0AEB,0x0AF9,0x0B06,0x0B13,0x0B20,0x0B2E,0x0B3B,0x0B49,0x0B56,
0x0B64,0x0B71,0x0B7F,0x0B8C,0x0B9A,0x0BA7,0x0BB5,0x0BC3,0x0BD1,0x0BDE,0x0BEC,0x0BFA,0x0C08,0x0C16,0x0C24,0x0C32,
0x0C40,0x0C4E,0x0C5C,0x0C6A,0x0C78,0x0C86,0x0C94,0x0CA2,0x0CB1,0x0CBF,0x0CCD,0x0CDB,0x0CEA,0x0CF8,0x0D07,0x0D15,
0x0D24,0x0D32,0x0D41,0x0D4F,0x0D5E,0x0D6C,0x0D7B,0x0D8A,0x0D99,0x0DA7,0x0DB6,0x0DC5,0x0DD4,0x0DE3,0x0DF2,0x0E01,
0x0E10,0x0E1F,0x0E2E,0x0E3D,0x0E4C,0x0E5B,0x0E6A,0x0E79,0x0E89,0x0E98,0x0EA7,0x0EB6,0x0EC6,0x0ED5,0x0EE5,0x0EF4,
0x0F04,0x0F13,0x0F23,0x0F32,0x0F42,0x0F51,0x0F61,0x0F71,0x0F81,0x0F90,0x0FA0,0x0FB0,0x0FC0,0x0FD0,0x0FE0};

