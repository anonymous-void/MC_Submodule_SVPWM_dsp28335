#include "SYM_app.h"
#include "SM_app.h"

void sym_Ecat_DATA_Get(void)
{/*
Description: This subroutine
*/

	unsigned int i,temp=0;//,N=0;

	   EcatRead(ECat_Download_Buf);

	   for(i=0;i<13;i++)
	   {
		   temp+=ECat_Download_Buf[i];
	   }

	if(temp == ECat_Download_Buf[13])//(N<200)
	{
		go_SYM_ECAT_DOWN_DATA.SM_CMD.all =       ECat_Download_Buf[0];
		go_SYM_ECAT_DOWN_DATA.DUTY1 =            ECat_Download_Buf[1];
		go_SYM_ECAT_DOWN_DATA.DUTY2 =            ECat_Download_Buf[2];
		go_SYM_ECAT_DOWN_DATA.DUTY3 =            ECat_Download_Buf[3];
		go_SYM_ECAT_DOWN_DATA.DUTY4 =            ECat_Download_Buf[4];
		go_SYM_ECAT_DOWN_DATA.TREE_SEC_1.all =   ECat_Download_Buf[5];
		go_SYM_ECAT_DOWN_DATA.TREE_SEC_2.all =   ECat_Download_Buf[6];
		go_SYM_ECAT_DOWN_DATA.TREE_SEC_3.all =   ECat_Download_Buf[7];
		go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_1.all = ECat_Download_Buf[8];
		go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_2.all = ECat_Download_Buf[9];
		go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_3.all = ECat_Download_Buf[10];
		go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_4.all = ECat_Download_Buf[11];
		go_SYM_ECAT_DOWN_DATA.UdcOverVol =       ECat_Download_Buf[12];
		go_SYM_ECAT_DOWN_DATA.OverCur =          ECat_Download_Buf[13];
    }

}

void sym_Ecat_DATA_Decode_vector(void)
{
    int i = 0;
    uint16_t mask_type = 0x0018, mask_num = 0x0007;
    for (i = 0; i < 5; ++i) {
        go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vtype = (mask_type & go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vraw)>>3;
        go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vnum = mask_num & go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[i].vraw;

        go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vtype = (mask_type & go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vraw)>>3;
        go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vnum = mask_num & go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[i].vraw;
    }
}

void sym_Ecat_DATA_Decode(void)
{
	SM_CMD.bit.Reset = ECAT_DOWNLOAD.SM_CMD.bit.Reset; // Original Command code copyed.
	SM_CMD.bit.Deblock = ECAT_DOWNLOAD.SM_CMD.bit.deblock;

    halfp2singles(&go_SYM_ECAT_DOWN_DATA_DECODED.duty[0], &go_SYM_ECAT_DOWN_DATA.DUTY1, 1);
    halfp2singles(&go_SYM_ECAT_DOWN_DATA_DECODED.duty[1], &go_SYM_ECAT_DOWN_DATA.DUTY2, 1);
    halfp2singles(&go_SYM_ECAT_DOWN_DATA_DECODED.duty[2], &go_SYM_ECAT_DOWN_DATA.DUTY3, 1);
    halfp2singles(&go_SYM_ECAT_DOWN_DATA_DECODED.duty[3], &go_SYM_ECAT_DOWN_DATA.DUTY4, 1);

    // Input side vector copy;
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[0].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_1.bit.vector_l;
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[1].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_1.bit.vector_m;
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[2].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_1.bit.vector_h;

    go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[3].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_2.bit.vector_l;
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_input[4].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_2.bit.vector_m;

    // Output side vector copy
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[0].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_3.bit.vector_l;
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[1].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_3.bit.vector_m;
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[2].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_3.bit.vector_h;

    go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[3].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_4.bit.vector_l;
    go_SYM_ECAT_DOWN_DATA_DECODED.vector_output[4].vraw = go_SYM_ECAT_DOWN_DATA.VECTOR_SEC_4.bit.vector_m;

    sym_Ecat_DATA_Decode_vector(); // Both side vector decode

    // Tree decode
    go_SYM_ECAT_DOWN_DATA_DECODED.tree[0] = go_SYM_ECAT_DOWN_DATA.TREE_SEC_1.bit.tree_l;
    go_SYM_ECAT_DOWN_DATA_DECODED.tree[1] = go_SYM_ECAT_DOWN_DATA.TREE_SEC_1.bit.tree_h;

    go_SYM_ECAT_DOWN_DATA_DECODED.tree[2] = go_SYM_ECAT_DOWN_DATA.TREE_SEC_2.bit.tree_l;
    go_SYM_ECAT_DOWN_DATA_DECODED.tree[3] = go_SYM_ECAT_DOWN_DATA.TREE_SEC_2.bit.tree_h;

    go_SYM_ECAT_DOWN_DATA_DECODED.tree[4] = go_SYM_ECAT_DOWN_DATA.TREE_SEC_3.bit.tree_l;
}



int singles2halfp(void *target, void *source, int numel)
{
    UINT16_TYPE *hp = (UINT16_TYPE *) target; // Type pun output as an unsigned 16-bit int
    UINT32_TYPE *xp = (UINT32_TYPE *) source; // Type pun input as an unsigned 32-bit int
    UINT16_TYPE    hs, he, hm;
    UINT32_TYPE x, xs, xe, xm;
    int hes;
    static int next;  // Little Endian adjustment
    static int checkieee = 1;  // Flag to check for IEEE754, Endian, and word size
    double one = 1.0; // Used for checking IEEE754 floating point format
    UINT32_TYPE *ip; // Used for checking IEEE754 floating point format

    if( checkieee ) { // 1st call, so check for IEEE754, Endian, and word size
        ip = (UINT32_TYPE *) &one;
        if( *ip ) { // If Big Endian, then no adjustment
            next = 0;
        } else { // If Little Endian, then adjustment will be necessary
            next = 1;
            ip++;
        }
        if( *ip != 0x3FF00000u ) { // Check for exact IEEE 754 bit pattern of 1.0
            return 1;  // Floating point bit pattern is not IEEE 754
        }
        if( sizeof(INT16_TYPE) != 2 || sizeof(INT32_TYPE) != 4 ) {
            return 1;  // short is not 16-bits, or long is not 32-bits.
        }
        checkieee = 0; // Everything checks out OK
    }

    if( source == NULL || target == NULL ) { // Nothing to convert (e.g., imag part of pure real)
        return 0;
    }

    while( numel-- ) {
        x = *xp++;
        if( (x & 0x7FFFFFFFu) == 0 ) {  // Signed zero
            *hp++ = (UINT16_TYPE) (x >> 16);  // Return the signed zero
        } else { // Not zero
            xs = x & 0x80000000u;  // Pick off sign bit
            xe = x & 0x7F800000u;  // Pick off exponent bits
            xm = x & 0x007FFFFFu;  // Pick off mantissa bits
            if( xe == 0 ) {  // Denormal will underflow, return a signed zero
                *hp++ = (UINT16_TYPE) (xs >> 16);
            } else if( xe == 0x7F800000u ) {  // Inf or NaN (all the exponent bits are set)
                if( xm == 0 ) { // If mantissa is zero ...
                    *hp++ = (UINT16_TYPE) ((xs >> 16) | 0x7C00u); // Signed Inf
                } else {
                    *hp++ = (UINT16_TYPE) 0xFE00u; // NaN, only 1st mantissa bit set
                }
            } else { // Normalized number
                hs = (UINT16_TYPE) (xs >> 16); // Sign bit
                hes = ((int)(xe >> 23)) - 127 + 15; // Exponent unbias the single, then bias the halfp
                if( hes >= 0x1F ) {  // Overflow
                    *hp++ = (UINT16_TYPE) ((xs >> 16) | 0x7C00u); // Signed Inf
                } else if( hes <= 0 ) {  // Underflow
                    if( (14 - hes) > 24 ) {  // Mantissa shifted all the way off & no rounding possibility
                        hm = (UINT16_TYPE) 0u;  // Set mantissa to zero
                    } else {
                        xm |= 0x00800000u;  // Add the hidden leading bit
                        hm = (UINT16_TYPE) (xm >> (14 - hes)); // Mantissa
                        if( (xm >> (13 - hes)) & 0x00000001u ) // Check for rounding
                            hm += (UINT16_TYPE) 1u; // Round, might overflow into exp bit, but this is OK
                    }
                    *hp++ = (hs | hm); // Combine sign bit and mantissa bits, biased exponent is zero
                } else {
                    he = (UINT16_TYPE) (hes << 10); // Exponent
                    hm = (UINT16_TYPE) (xm >> 13); // Mantissa
                    if( xm & 0x00001000u ) // Check for rounding
                        *hp++ = (hs | he | hm) + (UINT16_TYPE) 1u; // Round, might overflow to inf, this is OK
                    else
                        *hp++ = (hs | he | hm);  // No rounding
                }
            }
        }
    }
    return 0;
}

int halfp2singles(void *target, void *source, int numel)
{
    UINT16_TYPE *hp = (UINT16_TYPE *) source; // Type pun input as an unsigned 16-bit int
    UINT32_TYPE *xp = (UINT32_TYPE *) target; // Type pun output as an unsigned 32-bit int
    UINT16_TYPE h, hs, he, hm;
    UINT32_TYPE xs, xe, xm;
    INT32_TYPE xes;
    int e;
    static int next;  // Little Endian adjustment
    static int checkieee = 1;  // Flag to check for IEEE754, Endian, and word size
    double one = 1.0; // Used for checking IEEE754 floating point format
    UINT32_TYPE *ip; // Used for checking IEEE754 floating point format

    if( checkieee ) { // 1st call, so check for IEEE754, Endian, and word size
        ip = (UINT32_TYPE *) &one;
        if( *ip ) { // If Big Endian, then no adjustment
            next = 0;
        } else { // If Little Endian, then adjustment will be necessary
            next = 1;
            ip++;
        }
        if( *ip != 0x3FF00000u ) { // Check for exact IEEE 754 bit pattern of 1.0
            return 1;  // Floating point bit pattern is not IEEE 754
        }
        if( sizeof(INT16_TYPE) != 2 || sizeof(INT32_TYPE) != 4 ) {
            return 1;  // short is not 16-bits, or long is not 32-bits.
        }
        checkieee = 0; // Everything checks out OK
    }

    if( source == NULL || target == NULL ) // Nothing to convert (e.g., imag part of pure real)
        return 0;

    while( numel-- ) {
        h = *hp++;
        if( (h & 0x7FFFu) == 0 ) {  // Signed zero
            *xp++ = ((UINT32_TYPE) h) << 16;  // Return the signed zero
        } else { // Not zero
            hs = h & 0x8000u;  // Pick off sign bit
            he = h & 0x7C00u;  // Pick off exponent bits
            hm = h & 0x03FFu;  // Pick off mantissa bits
            if( he == 0 ) {  // Denormal will convert to normalized
                e = -1; // The following loop figures out how much extra to adjust the exponent
                do {
                    e++;
                    hm <<= 1;
                } while( (hm & 0x0400u) == 0 ); // Shift until leading bit overflows into exponent bit
                xs = ((UINT32_TYPE) hs) << 16; // Sign bit
                xes = ((INT32_TYPE) (he >> 10)) - 15 + 127 - e; // Exponent unbias the halfp, then bias the single
                xe = (UINT32_TYPE) (xes << 23); // Exponent
                xm = ((UINT32_TYPE) (hm & 0x03FFu)) << 13; // Mantissa
                *xp++ = (xs | xe | xm); // Combine sign bit, exponent bits, and mantissa bits
            } else if( he == 0x7C00u ) {  // Inf or NaN (all the exponent bits are set)
                if( hm == 0 ) { // If mantissa is zero ...
                    *xp++ = (((UINT32_TYPE) hs) << 16) | ((UINT32_TYPE) 0x7F800000u); // Signed Inf
                } else {
                    *xp++ = (UINT32_TYPE) 0xFFC00000u; // NaN, only 1st mantissa bit set
                }
            } else { // Normalized number
                xs = ((UINT32_TYPE) hs) << 16; // Sign bit
                xes = ((INT32_TYPE) (he >> 10)) - 15 + 127; // Exponent unbias the halfp, then bias the single
                xe = (UINT32_TYPE) (xes << 23); // Exponent
                xm = ((UINT32_TYPE) hm) << 13; // Mantissa
                *xp++ = (xs | xe | xm); // Combine sign bit, exponent bits, and mantissa bits
            }
        }
    }
    return 0;
}

