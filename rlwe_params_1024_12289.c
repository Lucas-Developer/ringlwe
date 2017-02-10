/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * See LICENSE for complete information.
 */
#include <inttypes.h>
#include "rlwe_params_1024_12289.h"

const RINGELT m = 1024;

const RINGELT q = 12289;

const RINGELT muwords = 4; /* key (mu) is 256 bits */
const RINGELT recwords = 32; /* reconciliation vector is 2*m bits */

#ifdef BINOMIAL
const RINGELT BINOMK = 16; // Binomial sampling parameter
#endif

#ifdef NHRECONCILE
const RINGELT rdim = 4; // rdim is number of coeffs per keybit
const RINGELT rsize = 2; // rsize is number of encoding bits per coeff per keybit
#else
const RINGELT qmod4 = 1;
const RINGELT q_1_4 = 3072, q_2_4 = 6144, q_3_4 = 9217;
const RINGELT r0_l = 4608, r0_u = 10753, r1_l = 1535, r1_u = 7681;
#endif


/* Public Parameter a. Each a parameter rejection sampled from non-overlapping
 * segments of the digits of e.
 * Note that this is held in the FFT / CRT basis.*/
const RINGELT a[1024] = {
	0x0CFF, 0x258B, 0x0646, 0x18E1, 0x0FB2, 0x24C6, 0x2DA9, 0x2AB2, 
	0x2064, 0x0F9E, 0x14B3, 0x1320, 0x12D8, 0x24F6, 0x0A21, 0x12F6, 
	0x1D3A, 0x28E8, 0x2DD1, 0x0058, 0x0344, 0x038A, 0x0A50, 0x18A7, 
	0x2FDC, 0x21E1, 0x09E2, 0x2F9A, 0x2102, 0x278C, 0x1BD1, 0x2F69, 
	0x261A, 0x102F, 0x2ED0, 0x2563, 0x278B, 0x0031, 0x2F9D, 0x26CC, 
	0x1CC7, 0x2CC2, 0x2C07, 0x1098, 0x0A40, 0x211B, 0x03D9, 0x12DA, 
	0x2D21, 0x076D, 0x2937, 0x2FFD, 0x0712, 0x28E1, 0x03D2, 0x0FB0, 
	0x06B0, 0x1566, 0x0CED, 0x2334, 0x1F8F, 0x2D42, 0x046A, 0x1B4B, 
	0x0BFE, 0x15B0, 0x1FAC, 0x260B, 0x06EE, 0x17DE, 0x2E69, 0x2F4D, 
	0x0E56, 0x2CA0, 0x1B0E, 0x1E01, 0x239C, 0x25BB, 0x2DE5, 0x07B6, 
	0x1AC3, 0x10EB, 0x13E3, 0x267F, 0x103C, 0x1951, 0x288C, 0x0FDA, 
	0x1BA6, 0x16A0, 0x2E9E, 0x0647, 0x10F1, 0x1AD2, 0x2907, 0x2E39, 
	0x2BBF, 0x0103, 0x21CD, 0x2CD8, 0x1983, 0x12B6, 0x048F, 0x2900, 
	0x2102, 0x2CFD, 0x1E6F, 0x00E8, 0x0729, 0x08BC, 0x1963, 0x2D78, 
	0x184A, 0x143D, 0x0DB8, 0x1808, 0x0428, 0x03EC, 0x2C5D, 0x1C15, 
	0x243C, 0x0345, 0x14EA, 0x1417, 0x2A2F, 0x06D3, 0x2C68, 0x2C33, 
	0x2BAF, 0x2615, 0x05F3, 0x09B9, 0x27DE, 0x2E09, 0x1D57, 0x29E0, 
	0x1AC0, 0x150B, 0x0725, 0x0B60, 0x2A03, 0x1E02, 0x1C5A, 0x14F0, 
	0x1967, 0x1D39, 0x0DA9, 0x2A0D, 0x1A1F, 0x068C, 0x087B, 0x02F8, 
	0x2A5C, 0x185C, 0x0865, 0x2970, 0x172D, 0x0836, 0x0ABD, 0x0C95, 
	0x2A05, 0x26CC, 0x2134, 0x107D, 0x1C51, 0x0327, 0x1620, 0x16AB, 
	0x2488, 0x2B83, 0x18AA, 0x1097, 0x14CE, 0x1A7B, 0x0043, 0x0D49, 
	0x07F6, 0x0C77, 0x08F2, 0x0983, 0x1970, 0x0670, 0x250A, 0x0F7A, 
	0x24DA, 0x11FB, 0x0E74, 0x25EA, 0x00A7, 0x117D, 0x0124, 0x10A2, 
	0x0532, 0x10C1, 0x08C4, 0x0AC4, 0x2719, 0x2870, 0x0E6A, 0x1D30, 
	0x1147, 0x2218, 0x080E, 0x12B5, 0x0B5A, 0x0DC2, 0x26B0, 0x1F71, 
	0x232C, 0x2483, 0x17A4, 0x2786, 0x00E7, 0x1172, 0x0442, 0x1C13, 
	0x1921, 0x1718, 0x1F3D, 0x2A00, 0x2AFA, 0x0330, 0x244A, 0x161A, 
	0x2565, 0x26D1, 0x087D, 0x11BF, 0x219C, 0x1510, 0x0731, 0x1AD2, 
	0x1DDA, 0x022E, 0x0EBF, 0x23FE, 0x1AE5, 0x08DF, 0x1408, 0x19BB, 
	0x2C91, 0x0914, 0x22E9, 0x1D2E, 0x24B4, 0x2AB2, 0x1346, 0x198A, 
	0x226E, 0x07D8, 0x2A3E, 0x1A7C, 0x25BB, 0x0DB0, 0x1D18, 0x0DC9, 
	0x2780, 0x2465, 0x0A9F, 0x11CF, 0x184F, 0x040E, 0x20B3, 0x1C5C, 
	0x1B52, 0x1580, 0x2D75, 0x0DFC, 0x08E5, 0x24B2, 0x1B91, 0x1B02, 
	0x0D3D, 0x0D71, 0x1CDE, 0x0E3F, 0x02B7, 0x2433, 0x2B67, 0x03F4, 
	0x22DE, 0x171D, 0x2DE3, 0x1FC5, 0x2A04, 0x0534, 0x159A, 0x1BED, 
	0x21BF, 0x0EB9, 0x076C, 0x09AC, 0x0A7E, 0x2161, 0x1880, 0x20DB, 
	0x2F76, 0x16F4, 0x0C75, 0x217B, 0x0C65, 0x0E81, 0x23BF, 0x025E, 
	0x2D55, 0x2F38, 0x0ADB, 0x29B0, 0x21B1, 0x2C6E, 0x16F7, 0x0093, 
	0x2361, 0x272D, 0x21B2, 0x2CE5, 0x2B53, 0x0880, 0x0716, 0x0AC8, 
	0x2458, 0x2AD0, 0x2162, 0x2A45, 0x27D5, 0x2C71, 0x1CC7, 0x02ED, 
	0x1B80, 0x1D30, 0x006E, 0x22CE, 0x0682, 0x0242, 0x2AA0, 0x0ED2, 
	0x13AD, 0x0804, 0x1529, 0x1291, 0x229B, 0x019E, 0x0AA1, 0x206A, 
	0x1B52, 0x280F, 0x2A6B, 0x1C96, 0x1F79, 0x2D98, 0x1EF6, 0x2AD8, 
	0x112E, 0x16C2, 0x0C91, 0x2439, 0x1144, 0x2ED5, 0x157F, 0x1CA2, 
	0x1A15, 0x2422, 0x12C5, 0x0DC9, 0x09F7, 0x23F6, 0x089E, 0x0FDB, 
	0x0A0A, 0x2A49, 0x1EC1, 0x1088, 0x0411, 0x1A9D, 0x1FF5, 0x2FA7, 
	0x2CC8, 0x1282, 0x1E89, 0x049F, 0x009C, 0x03FA, 0x1A9E, 0x29A5, 
	0x2CE3, 0x13BE, 0x1687, 0x0254, 0x2657, 0x0927, 0x1351, 0x0915, 
	0x053D, 0x061D, 0x1A34, 0x0CC5, 0x0206, 0x2279, 0x092E, 0x00D1, 
	0x2180, 0x2F25, 0x13FD, 0x2261, 0x137A, 0x04B6, 0x10AD, 0x01CC, 
	0x1608, 0x1D27, 0x16E6, 0x0FAC, 0x0186, 0x28B7, 0x1B67, 0x2F47, 
	0x0E28, 0x14AD, 0x2C98, 0x25B7, 0x236C, 0x2C66, 0x1FBF, 0x0630, 
	0x071D, 0x00DD, 0x1C98, 0x1535, 0x2F8F, 0x0C43, 0x056E, 0x0536, 
	0x07F9, 0x285C, 0x0CA8, 0x2D91, 0x1A1F, 0x20C7, 0x1E75, 0x1E63, 
	0x1437, 0x1586, 0x171F, 0x2B85, 0x2ABD, 0x281C, 0x2B1C, 0x101E, 
	0x0C87, 0x0EE5, 0x219C, 0x16E4, 0x28D3, 0x1E14, 0x24C0, 0x00D0, 
	0x0B92, 0x21E6, 0x10E8, 0x2C81, 0x238E, 0x0C7A, 0x29A8, 0x08E9, 
	0x1C84, 0x2D93, 0x063E, 0x05D6, 0x299F, 0x2D65, 0x20CA, 0x2E67, 
	0x2C06, 0x289C, 0x0FD6, 0x1616, 0x1A5B, 0x0040, 0x1D4B, 0x1223, 
	0x135C, 0x08E3, 0x26C4, 0x2D86, 0x2984, 0x004C, 0x252C, 0x2F41, 
	0x2FBD, 0x0822, 0x0335, 0x2771, 0x25D4, 0x0073, 0x060D, 0x1930, 
	0x1F58, 0x23A7, 0x163B, 0x2095, 0x2D49, 0x08F4, 0x1088, 0x2681, 
	0x0D1B, 0x128B, 0x14A4, 0x2011, 0x088B, 0x075D, 0x22A1, 0x25F2, 
	0x0852, 0x17BA, 0x1C45, 0x2335, 0x0B36, 0x1D2C, 0x218B, 0x1AF5, 
	0x1EA7, 0x2889, 0x0891, 0x0BC5, 0x161D, 0x0016, 0x1B16, 0x1E44, 
	0x1386, 0x14CD, 0x1871, 0x04D7, 0x1A9E, 0x2B90, 0x1EEB, 0x04B7, 
	0x2E4C, 0x09AD, 0x150A, 0x0454, 0x0E9A, 0x0F1B, 0x2597, 0x0743, 
	0x1734, 0x1BD6, 0x00C5, 0x2439, 0x2168, 0x03FD, 0x1543, 0x0184, 
	0x2569, 0x08B3, 0x28AC, 0x1122, 0x1CCD, 0x2642, 0x134C, 0x0CCE, 
	0x166B, 0x0866, 0x289C, 0x2A9E, 0x0AE7, 0x2279, 0x18C6, 0x1F1B, 
	0x1CD5, 0x224F, 0x1A6A, 0x005C, 0x1E71, 0x1D00, 0x1795, 0x1DB1, 
	0x1059, 0x0AEB, 0x2226, 0x2F2C, 0x1DDA, 0x132C, 0x2AD8, 0x25DC, 
	0x2525, 0x04C5, 0x1734, 0x2D51, 0x0710, 0x0BD3, 0x200A, 0x2473, 
	0x1C46, 0x15B0, 0x15EA, 0x14AF, 0x20F7, 0x1640, 0x07F8, 0x0753, 
	0x2D91, 0x278C, 0x1A7C, 0x2932, 0x121B, 0x0A04, 0x033F, 0x1AAB, 
	0x287A, 0x213D, 0x03ED, 0x014D, 0x15E9, 0x0D58, 0x2C39, 0x2EBD, 
	0x0EEC, 0x2FE6, 0x0E2C, 0x2ADC, 0x1E44, 0x1C74, 0x1CF8, 0x0E0A, 
	0x0251, 0x0B08, 0x0183, 0x26B3, 0x09D8, 0x1C87, 0x0B7B, 0x0F0F, 
	0x1956, 0x006F, 0x2490, 0x2394, 0x207C, 0x2B40, 0x12CF, 0x1256, 
	0x070A, 0x1B6C, 0x1A2F, 0x2F6E, 0x15C0, 0x04DE, 0x1284, 0x1E45, 
	0x207A, 0x15D9, 0x0343, 0x08B6, 0x2878, 0x13FF, 0x0259, 0x2A32, 
	0x21E2, 0x172B, 0x0DCC, 0x2021, 0x0E45, 0x1E2F, 0x0D02, 0x2153, 
	0x1E59, 0x28BA, 0x25FD, 0x0F46, 0x0278, 0x1052, 0x2D1E, 0x0333, 
	0x150B, 0x163B, 0x1312, 0x03C0, 0x191B, 0x2E72, 0x15CB, 0x1326, 
	0x1FBB, 0x1962, 0x01D7, 0x2BFD, 0x0FC7, 0x2F02, 0x26EC, 0x2ABE, 
	0x0162, 0x1985, 0x29F0, 0x0129, 0x2713, 0x1195, 0x0444, 0x14DB, 
	0x2508, 0x0B24, 0x0372, 0x154F, 0x0952, 0x06DA, 0x1118, 0x2455, 
	0x2F11, 0x293E, 0x0842, 0x2EE4, 0x06DF, 0x0BC0, 0x2DF2, 0x0E98, 
	0x01FF, 0x0EA2, 0x2C8D, 0x02E7, 0x2229, 0x28A8, 0x27C5, 0x0A80, 
	0x0C16, 0x081B, 0x0192, 0x0499, 0x1311, 0x05CB, 0x1AA4, 0x2050, 
	0x0F2C, 0x1B57, 0x1932, 0x2D66, 0x291B, 0x1B7D, 0x0877, 0x1AFC, 
	0x14B1, 0x1A54, 0x126B, 0x08C4, 0x2845, 0x1A9F, 0x1C55, 0x0B69, 
	0x0BA8, 0x2F16, 0x28EA, 0x0FDC, 0x07E3, 0x037F, 0x0626, 0x0DD1, 
	0x194E, 0x05DD, 0x0249, 0x1E7A, 0x0D53, 0x18EE, 0x2E90, 0x0AE3, 
	0x1752, 0x002B, 0x2D1E, 0x23B7, 0x0342, 0x24B7, 0x03B2, 0x1B0F, 
	0x266B, 0x0F25, 0x1358, 0x0833, 0x14CE, 0x2F03, 0x05EA, 0x2264, 
	0x2395, 0x064C, 0x22C5, 0x1900, 0x2C38, 0x055C, 0x1845, 0x271C, 
	0x008D, 0x0B24, 0x0102, 0x0355, 0x02EE, 0x1F82, 0x28FA, 0x1B9D, 
	0x0EEC, 0x1EB1, 0x0139, 0x2C44, 0x0297, 0x1AE3, 0x0080, 0x0074, 
	0x1D2B, 0x2A60, 0x1A96, 0x0BA7, 0x209A, 0x1C49, 0x1366, 0x00FD, 
	0x2C32, 0x06BE, 0x2860, 0x12A7, 0x2308, 0x0050, 0x249C, 0x1C58, 
	0x14C0, 0x0B15, 0x23D5, 0x0BA7, 0x08E2, 0x0BA6, 0x08E2, 0x052C, 
	0x2409, 0x011A, 0x0E8A, 0x2D0C, 0x1649, 0x2397, 0x1160, 0x13F5, 
	0x04A6, 0x1A7D, 0x10FA, 0x25AD, 0x0CA6, 0x0178, 0x0B56, 0x0A75, 
	0x07D2, 0x0D9B, 0x0EDB, 0x1769, 0x154B, 0x2069, 0x0D1E, 0x1A4E, 
	0x2A9E, 0x140A, 0x175B, 0x0089, 0x0FFB, 0x028A, 0x0FD4, 0x21B3, 
	0x2E9E, 0x25BA, 0x0881, 0x2FF3, 0x2180, 0x267F, 0x1424, 0x15F7, 
	0x1CBF, 0x16EF, 0x1116, 0x124B, 0x177D, 0x25EF, 0x2F48, 0x14B8, 
	0x09C0, 0x2F4D, 0x046E, 0x20C8, 0x1371, 0x2789, 0x20DB, 0x0EF3, 
	0x2ADE, 0x1C00, 0x1B00, 0x2D36, 0x215E, 0x04BA, 0x16D8, 0x2AE2, 
	0x2FDB, 0x2453, 0x19B0, 0x1B24, 0x2897, 0x0355, 0x0148, 0x1ED3, 
	0x2D79, 0x2475, 0x1D96, 0x1E96, 0x1C27, 0x2E64, 0x1F59, 0x1C3F, 
	0x1C64, 0x05C9, 0x09B7, 0x1232, 0x1CB8, 0x1E89, 0x28F2, 0x1CA5, 
	0x1817, 0x1430, 0x2241, 0x271A, 0x11FD, 0x221F, 0x1BCC, 0x2889, 
	0x0A8A, 0x157F, 0x221C, 0x0CBE, 0x0FA6, 0x2D81, 0x29AE, 0x21A4, 
	0x0630, 0x0456, 0x0728, 0x22CC, 0x0173, 0x2FB8, 0x269F, 0x2E85, 
	0x1246, 0x0063, 0x1FC9, 0x29B7, 0x1A3B, 0x15E4, 0x251F, 0x2B0E, 
	0x2308, 0x1765, 0x2F0F, 0x0EA6, 0x25FC, 0x1DB7, 0x0A7C, 0x01FE, 
	0x1E2E, 0x2624, 0x1457, 0x2DB4, 0x1F46, 0x10A9, 0x2C08, 0x060C, 
	0x1C8D, 0x0D9C, 0x28E9, 0x0F67, 0x288D, 0x2344, 0x1303, 0x2E1C, 
	0x1127, 0x1C1A, 0x2818, 0x0CF5, 0x237A, 0x265F, 0x2C75, 0x1722, 
	0x1045, 0x1B9D, 0x1681, 0x14CC, 0x0199, 0x1A72, 0x2A0C, 0x1B25, 
	0x1BF2, 0x0311, 0x04E3, 0x0FFA, 0x1989, 0x0371, 0x08C3, 0x17E5, 
	0x1876, 0x1844, 0x1C0B, 0x2894, 0x204B, 0x0DA4, 0x0CF9, 0x023E, 
	0x00F3, 0x2AFF, 0x0F82, 0x1629, 0x019A, 0x1AE4, 0x030F, 0x28F6, 
	0x1D29, 0x19F5, 0x17F3, 0x10FF, 0x0A68, 0x0A76, 0x22F2, 0x22AF, 
	0x07C0, 0x1CC2, 0x19F0, 0x05AF, 0x20DF, 0x07C0, 0x2AB5, 0x08B2
        };

