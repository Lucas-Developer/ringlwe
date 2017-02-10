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
#include "rlwe_params_631_44171.h"

const RINGELT m = 631, muwords = 10; /* key (mu) is m-1 bits */

const RINGELT q = 44171, qmod4 = 3;

const RINGELT B = 5, BB = 11, LOG2B = 4, BMASK = 0xf;

const RINGELT small_coeff_table[11] = {44166, 44167, 44168, 44169, 44170, 0, 1, 2, 3, 4, 5};

const RINGELT q_1_4 = 11042, q_2_4 = 22085, q_3_4 = 33129;
const RINGELT r0_l = 16563, r0_u = 38650, r1_l = 5520, r1_u = 27608;	


/* Public Parameter a. Each a parameter rejection sampled from non-overlapping
 * segments of the digits of e.
 * Note that this is held in the FFT / CRT basis.*/
const RINGELT a[631] = {
        0X1294, 0X97CE, 0X25AA, 0X2990, 0X3C00, 0X8E43, 0X35B7, 0X3E40, 
        0X896F, 0X43E1, 0X03FB, 0X14DF, 0X0EA5, 0X34B8, 0X073C, 0X7B6E, 
        0X1091, 0X732D, 0X3803, 0X8A8A, 0X4F0C, 0X1D8B, 0X1463, 0X99AF, 
        0X19A5, 0X22E4, 0X8C49, 0X4A55, 0X5977, 0X2BF8, 0X9A00, 0X7F53, 
        0XA062, 0X494D, 0X57B1, 0X07AF, 0X6B16, 0X3241, 0X997D, 0X0848, 
        0X69B5, 0X9263, 0X1F19, 0X1A2B, 0X35D4, 0X7A63, 0X9CE4, 0X8F00, 
        0X7840, 0X6D2C, 0X17F4, 0X0E63, 0X18BA, 0X1458, 0X6C68, 0X50C4, 
        0X0186, 0X256B, 0X5AFD, 0X0C13, 0X0673, 0X2BE9, 0XABA0, 0X951A, 
        0X8CE5, 0X53C1, 0X2805, 0X4B60, 0X2CF8, 0XAB76, 0X0623, 0X619D, 
        0X03B1, 0X7C13, 0X88CC, 0X3DA7, 0X3EE1, 0X47E6, 0X91E0, 0X5504, 
        0X694A, 0X0ED8, 0XAC6B, 0X9872, 0X565B, 0X1F2E, 0X5115, 0X2B3E, 
        0XA7BA, 0X6239, 0X1993, 0X38D2, 0X9639, 0X2023, 0X9CD7, 0X5CAF, 
        0X0625, 0X78CF, 0X4AD4, 0X8ADE, 0X8432, 0X7FD2, 0X244F, 0X6535, 
        0X90D3, 0X569B, 0X7507, 0X6FEA, 0X5794, 0X1736, 0X596E, 0X99A5, 
        0X33D4, 0X8AC8, 0XAA2F, 0X81DC, 0X056B, 0X75AD, 0X67C8, 0X4198, 
        0X0DE3, 0X68D1, 0X8854, 0X687D, 0X71AF, 0X3494, 0X1B98, 0XA11B, 
        0X7732, 0X9D39, 0X232A, 0X67D0, 0X7832, 0X0BCA, 0X37DA, 0X7C83, 
        0X7534, 0X807D, 0X7106, 0XA128, 0X1AE7, 0X8000, 0XA10B, 0X922D, 
        0X8613, 0X16EF, 0X135F, 0X113D, 0XAC87, 0X73E9, 0X02CA, 0X458F, 
        0X7F9E, 0X6D9F, 0X963A, 0X5CFD, 0X556E, 0X22E8, 0X3949, 0X4D43, 
        0XAA48, 0X6CFD, 0X235F, 0X9151, 0X9970, 0X6B34, 0X0492, 0XA043, 
        0X64C8, 0X73CA, 0X4DA9, 0X8F42, 0X0462, 0X0931, 0X228A, 0X2C39, 
        0X2E6D, 0X77E3, 0X30B4, 0X6CF2, 0X46AE, 0X76EC, 0X491B, 0X296E, 
        0X67D5, 0X7591, 0X4CD5, 0X8022, 0X11DF, 0X4261, 0X002C, 0X74CF, 
        0X69E0, 0X0B8D, 0X8AE8, 0X02DC, 0X1553, 0X204C, 0X5D2C, 0X1262, 
        0X8C0B, 0X0B62, 0X0538, 0X01EB, 0X8211, 0X654B, 0X01E1, 0X57BD, 
        0X4705, 0X2791, 0X7F0F, 0X8197, 0X51FF, 0X63B8, 0X11EB, 0X570F, 
        0X18C2, 0X6751, 0X9B36, 0X7A92, 0X4217, 0X03DD, 0X9B89, 0X86F4, 
        0X5450, 0X6DE9, 0X5DBD, 0X3228, 0X642A, 0X873D, 0X36E5, 0X993C, 
        0X6C89, 0X9761, 0X9049, 0X6456, 0X6EE6, 0X674F, 0X62B7, 0X8AB5, 
        0X9D4F, 0X8C9A, 0X19CE, 0X4AB2, 0X152D, 0X024E, 0X8055, 0X40CD, 
        0XA840, 0X8819, 0X1287, 0X35D4, 0X4C0F, 0X43BF, 0X64FF, 0X01C9, 
        0X6683, 0X5AFE, 0X4B32, 0X91B8, 0X2926, 0X6483, 0X1BE5, 0X99AB, 
        0X4476, 0X9711, 0X9701, 0XA507, 0X3588, 0X8DBE, 0X22F0, 0X32EF, 
        0X7BF0, 0X2A54, 0X595A, 0X8833, 0X19B2, 0X47C5, 0X9C4B, 0X5548, 
        0X3C5C, 0X6183, 0X01A8, 0X0516, 0X87C3, 0X99CF, 0X4EE8, 0X9074, 
        0X5E6C, 0X8567, 0XA7F2, 0X4977, 0X81F9, 0X3C9E, 0X27E7, 0X675B, 
        0X4F92, 0X9E94, 0XA525, 0X916A, 0X696A, 0X8C54, 0X6EF2, 0X4102, 
        0X35E2, 0X072E, 0X2256, 0X3C79, 0X675F, 0X9761, 0X0B64, 0X6FC8, 
        0X70C4, 0X8F37, 0X4FD1, 0XA8B5, 0X0851, 0X571E, 0X84FC, 0X9B07, 
        0X9A46, 0X7B43, 0X3A0B, 0X28A9, 0X2B68, 0X75EE, 0X18D8, 0X40F8, 
        0X4F2C, 0X336E, 0X635B, 0X28EE, 0X24EA, 0X97F4, 0X91B7, 0XA8DD, 
        0X0EB7, 0X6B61, 0X3F5E, 0X1B1B, 0X1820, 0X81F5, 0X9CAF, 0X2EEF, 
        0XA639, 0X8A3E, 0X2C9B, 0X46B1, 0X23CA, 0X1545, 0X030F, 0X11AE, 
        0X3C72, 0X4186, 0X9D34, 0X6E59, 0X86F7, 0X94B4, 0X8A21, 0XA900, 
        0X3BDC, 0X2F33, 0X2AE3, 0X6926, 0X48E5, 0X8739, 0X0D7B, 0X9B7D, 
        0X49D8, 0X3915, 0X88ED, 0X88C2, 0X02B5, 0X01E6, 0X9ECC, 0XAAAC, 
        0XA321, 0X015E, 0X56B9, 0X6473, 0X739A, 0X2362, 0X6361, 0X2C1A, 
        0X84E1, 0X4F78, 0X9DF5, 0X9855, 0X74BB, 0X0A20, 0X2A7A, 0X7072, 
        0X5CC0, 0X7B07, 0X16DF, 0X7C83, 0X426D, 0XABDE, 0XA3AD, 0X88DD, 
        0X6FA1, 0X25D2, 0X816B, 0X407E, 0X9FDA, 0X215E, 0X2EFF, 0X1003, 
        0X681F, 0X8D5F, 0X108C, 0X750C, 0X0D27, 0X2B27, 0X432E, 0X8317, 
        0X4B26, 0X77B9, 0XA9EE, 0X7ED0, 0X64AA, 0X3D82, 0X5772, 0X27E6, 
        0X042A, 0XA095, 0X0091, 0X6919, 0X281F, 0X4684, 0X9205, 0X5FF0, 
        0X9159, 0X4E5D, 0X799B, 0X889F, 0X9D22, 0X3E7B, 0X13DB, 0X8AA0, 
        0X8C7F, 0X742B, 0X7220, 0X1BF7, 0X78A8, 0X0A3B, 0X12D7, 0X63B0, 
        0X4B3D, 0X1271, 0X871F, 0X683C, 0X05EB, 0X6E73, 0X5DC2, 0X1D76, 
        0X1767, 0X86BC, 0X33A5, 0X8D6C, 0X0C36, 0X6C75, 0XA02F, 0X73D8, 
        0X3A1D, 0X8E80, 0X8A46, 0XA9C4, 0X9E29, 0X042D, 0XA523, 0XA612, 
        0X9B0C, 0X89A1, 0X1B6A, 0X25CC, 0X39A4, 0X5D96, 0X3B2F, 0X774F, 
        0X0539, 0X5CB4, 0X9EE0, 0X9CE2, 0X59B7, 0X7A36, 0X7616, 0X08E3, 
        0X74C3, 0X31AD, 0X3EFA, 0X1162, 0X4008, 0X4CD7, 0X0DF7, 0X0AE6, 
        0X17A9, 0X3042, 0X6EC0, 0X80B3, 0X3E9C, 0X9526, 0X2EC1, 0X70EE, 
        0X959B, 0X944B, 0X8980, 0X5BF8, 0X38D7, 0X3A71, 0X9D24, 0X5CC3, 
        0X9006, 0X656C, 0X7EBF, 0X049A, 0X88FF, 0X1C3F, 0X00A3, 0XA79E, 
        0X76B1, 0X54B0, 0X00D6, 0X6F58, 0X45EF, 0X5A62, 0X06BF, 0XA68F, 
        0X2374, 0X9E3B, 0X01E8, 0X3475, 0X1E01, 0X34D7, 0X5ACD, 0XAB32, 
        0X8C76, 0X22BC, 0X9975, 0X936B, 0X213E, 0X4585, 0X0079, 0X64A8, 
        0X2D71, 0X9B00, 0X1DFE, 0X83CE, 0X7850, 0X2570, 0X5A9A, 0X0FDB, 
        0X50A9, 0X136F, 0X7172, 0X5020, 0X8CA3, 0X8DEE, 0X5548, 0X1744, 
        0X76B3, 0X8583, 0X8384, 0X2E01, 0X7870, 0X5525, 0X3CBB, 0X10C0, 
        0X5212, 0X427D, 0X4C66, 0X1C91, 0X0F46, 0X6D53, 0X54C3, 0X2397, 
        0X4115, 0X068A, 0X18EA, 0X28B7, 0X9FE0, 0X63E0, 0X3C03, 0XA5BC, 
        0X5EE6, 0X50E9, 0X28F6, 0X380A, 0X6C45, 0X5D43, 0X099B, 0X12AD, 
        0X27BA, 0X3B23, 0X8A3A, 0X3FEF, 0X0695, 0X31BB, 0X8CB6, 0X9155, 
        0X32CA, 0X9818, 0X5E87, 0X37EB, 0X597D, 0X3DD9, 0X30E6, 0X5CD6, 
        0X890E, 0X618C, 0X797A, 0X5413, 0X6292, 0X59D9, 0X9908, 0X3397, 
        0X9E98, 0X8442, 0X4B41, 0X4C43, 0X3DF0, 0X3590, 0XA020, 0X79A1, 
        0X1240, 0X8907, 0XA743, 0X55AB, 0X91D4, 0X2249, 0X9C15
        };
