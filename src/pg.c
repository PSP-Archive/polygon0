// primitive graphics for PSP
// now not only graphics :)

#include "shered.h"
#include "_clib.h"
#include "pg.h"

#define HANKAKU10_OFFS 0x20

#define bc(aa,bb,cc,dd,ee,ff,gg,hh) (\
(aa?0x01:0x00)+\
(bb?0x02:0x00)+\
(cc?0x04:0x00)+\
(dd?0x08:0x00)+\
(ee?0x10:0x00)+\
(ff?0x20:0x00)+\
(gg?0x40:0x00)+\
(hh?0x80:0x00)\
)

const unsigned char hankaku_font5x10[]={ /* x:y == 5x10 */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x20 ' ' */
	0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x04,0x00,0x00,	/*0x21 '!' */
	0x00,0x0a,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x22 '"' */
	0x00,0x0a,0x0a,0x1f,0x0a,0x1f,0x0a,0x0a,0x00,0x00,	/*0x23 '#' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,1,1,1,0,0),
bc(0,1,0,1,0,0,0,0),
bc(0,0,1,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,1,0,0,0),
bc(0,0,0,1,0,1,0,0),
bc(0,0,0,1,0,1,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x04,0x1e,0x05,0x0e,0x14,0x0f,0x04,0x00,0x00,	/*0x24 '$' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,0,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x00,0x16,0x16,0x08,0x04,0x1a,0x1a,0x00,0x00,	/*0x25 '%' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,1,0,1,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,0,1,1,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x04,0x0a,0x02,0x14,0x12,0x0a,0x14,0x00,0x00,	/*0x26 '&' */
	0x00,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x27 ''' */

bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,1,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x10,0x08,0x08,0x04,0x04,0x04,0x08,0x08,0x10,0x00,	/*0x28 '(' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x02,0x04,0x04,0x08,0x08,0x08,0x04,0x04,0x02,0x00,	/*0x29 ')' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x00,0x0a,0x04,0x1f,0x04,0x0a,0x00,0x00,0x00,	/*0x2a '*' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x00,0x04,0x04,0x1f,0x04,0x04,0x00,0x00,0x00,	/*0x2b '+' */
	0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x02,0x00,	/*0x2c ',' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,	/*0x2d '-' */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,	/*0x2e '.' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,1,0,0),
bc(0,0,0,0,0,1,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x00,	/*0x2f '/' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,0,1,1,1,0,0,0),//00001100
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00011010
bc(0,1,0,0,0,1,0,0),//00010110
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00001100
bc(0,0,1,1,1,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x0c,0x12,0x1a,0x16,0x12,0x12,0x0c,0x00,0x00,	/*0x30 '0' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,0,0,1,0,0,0,0),//00000100
bc(0,0,1,1,0,0,0,0),//00000110
bc(0,0,0,1,0,0,0,0),//00000100
bc(0,0,0,1,0,0,0,0),//00000100
bc(0,0,0,1,0,0,0,0),//00000100
bc(0,0,0,1,0,0,0,0),//00000100
bc(0,0,0,1,0,0,0,0),//00001110
bc(0,0,0,1,0,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x04,0x06,0x04,0x04,0x04,0x04,0x0e,0x00,0x00,	/*0x31 '1' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,1,1,1,1,0,0,0),//00001100
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00011010
bc(0,0,0,0,1,0,0,0),//00010110
bc(0,0,0,1,0,0,0,0),//00010010
bc(0,0,1,0,0,0,0,0),//00010010
bc(0,1,0,0,0,0,0,0),//00001100
bc(0,1,1,1,1,1,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x0c,0x12,0x10,0x08,0x04,0x02,0x1e,0x00,0x00,	/*0x32 '2' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,1,1,1,1,0,0,0),//00001100
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00011010
bc(0,0,0,1,1,0,0,0),//00010110
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00001100
bc(0,1,1,1,1,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x0c,0x12,0x10,0x08,0x10,0x12,0x0c,0x00,0x00,	/*0x33 '3' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,0,0,0,1,0,0,0),//00001100
bc(0,0,0,1,1,0,0,0),//00010010
bc(0,0,1,0,1,0,0,0),//00011010
bc(0,0,1,0,1,0,0,0),//00010110
bc(0,1,0,0,1,0,0,0),//00010010
bc(0,1,1,1,1,1,0,0),//00010010
bc(0,0,0,0,1,0,0,0),//00001100
bc(0,0,0,0,1,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x08,0x0c,0x0a,0x0a,0x1e,0x08,0x08,0x00,0x00,	/*0x34 '4' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,1,1,1,1,1,0,0),//00001100
bc(0,1,0,0,0,0,0,0),//00010010
bc(0,1,0,0,0,0,0,0),//00011010
bc(0,1,1,1,1,0,0,0),//00010110
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00001100
bc(0,1,1,1,1,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x1e,0x02,0x0e,0x10,0x10,0x12,0x0c,0x00,0x00,	/*0x35 '5' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,0,1,1,1,1,0,0),//00001100
bc(0,1,0,0,0,0,0,0),//00010010
bc(0,1,0,0,0,0,0,0),//00011010
bc(0,1,1,1,1,0,0,0),//00010110
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00001100
bc(0,0,1,1,1,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x0c,0x12,0x02,0x0e,0x12,0x12,0x0c,0x00,0x00,	/*0x36 '6' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,1,1,1,1,1,0,0),//00001100
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,1,0,0,0),//00011010
bc(0,0,0,0,1,0,0,0),//00010110
bc(0,0,0,1,0,0,0,0),//00010010
bc(0,0,0,1,0,0,0,0),//00010010
bc(0,0,0,1,0,0,0,0),//00001100
bc(0,0,0,1,0,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x1e,0x12,0x08,0x08,0x04,0x04,0x04,0x00,0x00,	/*0x37 '7' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,0,1,1,1,0,0,0),//00001100
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00011010
bc(0,0,1,1,1,0,0,0),//00010110
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00001100
bc(0,0,1,1,1,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x0c,0x12,0x12,0x0c,0x12,0x12,0x0c,0x00,0x00,	/*0x38 '8' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,0,1,1,1,0,0,0),//00001100
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00011010
bc(0,0,1,1,1,1,0,0),//00010110
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00010010
bc(0,0,0,0,0,1,0,0),//00001100
bc(0,1,1,1,1,0,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x0c,0x12,0x12,0x1c,0x10,0x12,0x0c,0x00,0x00,	/*0x39 '9' */

	0x00,0x00,0x0c,0x0c,0x00,0x00,0x0c,0x0c,0x00,0x00,	/*0x3a ':' */
	0x00,0x00,0x0c,0x0c,0x00,0x00,0x0c,0x08,0x04,0x00,	/*0x3b ';' */
	0x00,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x00,0x00,	/*0x3c '<' */
	0x00,0x00,0x00,0x1e,0x00,0x1e,0x00,0x00,0x00,0x00,	/*0x3d '=' */
	0x00,0x02,0x04,0x08,0x10,0x08,0x04,0x02,0x00,0x00,	/*0x3e '>' */
	0x00,0x0c,0x12,0x10,0x08,0x08,0x00,0x08,0x00,0x00,	/*0x3f '?' */

	0x00,0x0c,0x12,0x1a,0x16,0x0a,0x02,0x0c,0x00,0x00,	/*0x40 '@' */

bc(0,0,0,0,0,0,0,0),//00000000
bc(0,0,0,1,0,0,0,0),//00001100
bc(0,0,0,1,0,0,0,0),//00010010
bc(0,0,1,0,1,0,0,0),//00010010
bc(0,0,1,0,1,0,0,0),//00011110
bc(0,0,1,1,1,0,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00010010
bc(0,1,0,0,0,1,0,0),//00000000
bc(0,0,0,0,0,0,0,0),//00000000
//	0x00,0x0c,0x12,0x12,0x1e,0x12,0x12,0x12,0x00,0x00,	/*0x41 'A' */

bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,0,0,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0e,0x12,0x12,0x0e,0x12,0x12,0x0e,0x00,0x00,	/*0x42 'B' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,1,1,1,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,1,1,1,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0c,0x12,0x02,0x02,0x02,0x12,0x0c,0x00,0x00,	/*0x43 'C' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0e,0x12,0x12,0x12,0x12,0x12,0x0e,0x00,0x00,	/*0x44 'D' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x1e,0x02,0x02,0x0e,0x02,0x02,0x1e,0x00,0x00,	/*0x45 'E' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x1e,0x02,0x02,0x0e,0x02,0x02,0x02,0x00,0x00,	/*0x46 'F' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,1,1,1,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,1,1,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,1,1,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0c,0x12,0x02,0x1a,0x12,0x12,0x1c,0x00,0x00,	/*0x47 'G' */

bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x12,0x12,0x1e,0x12,0x12,0x12,0x00,0x00,	/*0x48 'H' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,1,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,1,1,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0e,0x04,0x04,0x04,0x04,0x04,0x0e,0x00,0x00,	/*0x49 'I' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,1,1,1,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,1,1,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x18,0x10,0x10,0x10,0x12,0x12,0x0c,0x00,0x00,	/*0x4a 'J' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,1,0,1,0,0,0,0),
bc(0,1,1,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,1,0,0,0,0,0),
bc(0,1,0,1,0,0,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x12,0x0a,0x06,0x0a,0x12,0x12,0x00,0x00,	/*0x4b 'K' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x1e,0x00,0x00,	/*0x4c 'L' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,1,0,1,1,0,0),
bc(0,1,1,0,1,1,0,0),
bc(0,1,1,0,1,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x1e,0x1e,0x12,0x12,0x12,0x12,0x00,0x00,	/*0x4d 'M' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,1,0,0,1,0,0),
bc(0,1,1,0,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,0,1,1,0,0),
bc(0,1,0,0,1,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x12,0x16,0x1a,0x12,0x12,0x12,0x00,0x00,	/*0x4e 'N' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,1,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,1,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0c,0x12,0x12,0x12,0x12,0x12,0x0c,0x00,0x00,	/*0x4f 'O' */

bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0e,0x12,0x12,0x0e,0x02,0x02,0x02,0x00,0x00,	/*0x50 'P' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,1,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,0,1,1,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0c,0x12,0x12,0x12,0x16,0x1a,0x0c,0x10,0x00,	/*0x51 'Q' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,1,0,1,0,0,0,0),
bc(0,1,0,0,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0e,0x12,0x12,0x0e,0x06,0x0a,0x12,0x00,0x00,	/*0x52 'R' */
bc(0,0,0,0,0,0,0,0),
bc(0,0,1,1,1,1,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,0,0,1,0,0),
bc(0,0,0,0,0,1,0,0),
bc(0,1,1,1,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x0c,0x12,0x02,0x0c,0x10,0x12,0x0c,0x00,0x00,	/*0x53 'S' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x1f,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,	/*0x54 'T' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,1,1,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x12,0x12,0x12,0x12,0x12,0x0c,0x00,0x00,	/*0x55 'U' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x12,0x12,0x12,0x1e,0x0c,0x0c,0x00,0x00,	/*0x56 'V' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,0,1,0,1,0,0),
bc(0,1,1,0,1,1,0,0),
bc(0,1,1,0,1,1,0,0),
bc(0,1,1,0,1,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x12,0x12,0x12,0x1e,0x1e,0x12,0x00,0x00,	/*0x57 'W' */

bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x12,0x12,0x12,0x0c,0x12,0x12,0x12,0x00,0x00,	/*0x58 'X' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x11,0x11,0x0a,0x04,0x04,0x04,0x04,0x00,0x00,	/*0x59 'Y' */
bc(0,0,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,0,0,0,1,0,0),
bc(0,0,0,0,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,1,0,0,0,0,0,0),
bc(0,1,1,1,1,1,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x1e,0x10,0x08,0x04,0x04,0x02,0x1e,0x00,0x00,	/*0x5a 'Z' */
	0x1c,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x1c,0x00,	/*0x5b '[' */
	0x00,0x11,0x0a,0x04,0x1f,0x04,0x1f,0x04,0x00,0x00,	/*0x5c '/'(yen) */
	0x0e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0e,0x00,	/*0x5d ']' */
	0x04,0x0a,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x5e '^' */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,	/*0x5f '_' */

	0x00,0x04,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x60 '`' */
	0x00,0x00,0x00,0x16,0x19,0x11,0x11,0x19,0x16,0x00,	/*0x61 'a' */
	0x00,0x01,0x01,0x0f,0x11,0x11,0x11,0x11,0x0f,0x00,	/*0x62 'b' */
	0x00,0x00,0x00,0x1e,0x01,0x01,0x01,0x01,0x1e,0x00,	/*0x63 'c' */
	0x00,0x10,0x10,0x1e,0x11,0x11,0x11,0x11,0x1e,0x00,	/*0x64 'd' */
	0x00,0x00,0x00,0x0e,0x11,0x1f,0x01,0x01,0x1e,0x00,	/*0x65 'e' */
	0x00,0x18,0x04,0x1e,0x04,0x04,0x04,0x04,0x04,0x00,	/*0x66 'f' */
	0x00,0x00,0x00,0x1e,0x11,0x11,0x1e,0x10,0x08,0x06,	/*0x67 'g' */

	0x00,0x01,0x01,0x0f,0x11,0x11,0x11,0x11,0x11,0x00,	/*0x68 'h' */
	0x00,0x04,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x00,	/*0x69 'i' */
	0x00,0x10,0x00,0x10,0x10,0x10,0x10,0x10,0x08,0x04,	/*0x6a 'j' */
	0x00,0x01,0x01,0x11,0x09,0x05,0x07,0x09,0x11,0x00,	/*0x6b 'k' */
	0x00,0x06,0x04,0x04,0x04,0x04,0x04,0x04,0x0e,0x00,	/*0x6c 'l' */
	0x00,0x00,0x00,0x0b,0x15,0x15,0x15,0x15,0x15,0x00,	/*0x6d 'm' */
	0x00,0x00,0x00,0x0f,0x11,0x11,0x11,0x11,0x11,0x00,	/*0x6e 'n' */
	0x00,0x00,0x00,0x0e,0x11,0x11,0x11,0x11,0x0e,0x00,	/*0x6f 'o' */

	0x00,0x00,0x00,0x0f,0x11,0x11,0x0f,0x01,0x01,0x01,	/*0x70 'p' */
	0x00,0x00,0x00,0x1e,0x11,0x11,0x1e,0x10,0x10,0x10,	/*0x71 'q' */
	0x00,0x00,0x00,0x1a,0x06,0x02,0x02,0x02,0x02,0x00,	/*0x72 'r' */
	0x00,0x00,0x00,0x1c,0x02,0x0c,0x10,0x10,0x0e,0x00,	/*0x73 's' */
	0x00,0x04,0x04,0x1e,0x04,0x04,0x04,0x04,0x18,0x00,	/*0x74 't' */
	0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x1e,0x00,	/*0x75 'u' */
	0x00,0x00,0x00,0x11,0x11,0x11,0x0a,0x0a,0x04,0x00,	/*0x76 'v' */
	0x00,0x00,0x00,0x11,0x15,0x15,0x15,0x15,0x0a,0x00,	/*0x77 'w' */

	0x00,0x00,0x00,0x11,0x0a,0x04,0x0a,0x0a,0x11,0x00,	/*0x78 'x' */

bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
bc(0,1,0,0,0,1,0,0),
bc(0,0,1,0,1,0,0,0),
bc(0,0,0,1,1,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,0,1,0,0,0,0),
bc(0,0,1,0,0,0,0,0),
bc(0,0,0,0,0,0,0,0),
//	0x00,0x00,0x00,0x11,0x14,0x18,0x10,0x08,0x08,0x04,	/*0x79 'y' */
	0x00,0x00,0x00,0x1e,0x10,0x08,0x04,0x02,0x1e,0x00,	/*0x7a 'z' */
	0x18,0x04,0x04,0x04,0x02,0x04,0x04,0x04,0x04,0x18,	/*0x7b '{' */
	0x04,0x04,0x04,0x04,0x00,0x04,0x04,0x04,0x04,0x04,	/*0x7c '|' */
	0x06,0x08,0x08,0x08,0x10,0x08,0x08,0x08,0x08,0x06,	/*0x7d '}' */
	0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x7e '~' */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x7f ' ' */


#if 00
/* ���p�J�i�Ȃ��v��� */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*0x80*/
	0x00,0x00,0x00,0x00,0x00,0x0e,0x0a,0x0e,0x00,0x00,	/*�B*/
	0x00,0x1c,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x0e,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x02,0x04,0x04,0x00,0x00,
	0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
	0x00,0x1e,0x10,0x1e,0x10,0x10,0x08,0x04,0x00,0x00,
	0x00,0x00,0x00,0x1e,0x10,0x0c,0x04,0x02,0x00,0x00,

	0x00,0x00,0x00,0x10,0x08,0x0e,0x08,0x08,0x00,0x00,
	0x00,0x00,0x00,0x04,0x1e,0x12,0x10,0x08,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0e,0x04,0x04,0x0e,0x00,0x00,
	0x00,0x00,0x00,0x08,0x1e,0x08,0x0c,0x0a,0x00,0x00,
	0x00,0x00,0x00,0x04,0x1e,0x14,0x04,0x04,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0c,0x08,0x08,0x1e,0x00,0x00,
	0x00,0x00,0x00,0x1e,0x10,0x1c,0x10,0x1e,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0a,0x1a,0x10,0x0c,0x00,0x00,

	0x00,0x00,0x00,0x02,0x1c,0x00,0x00,0x00,0x00,0x00,	/*0x90*/
	0x00,0x1e,0x10,0x14,0x0c,0x04,0x04,0x02,0x00,0x00,
	0x00,0x10,0x10,0x08,0x0c,0x0a,0x08,0x08,0x00,0x00,
	0x00,0x04,0x1e,0x12,0x10,0x10,0x08,0x04,0x00,0x00,
	0x00,0x00,0x0e,0x04,0x04,0x04,0x04,0x1f,0x00,0x00,
	0x00,0x08,0x1e,0x08,0x0c,0x0c,0x0a,0x0a,0x00,0x00,
	0x00,0x04,0x1e,0x14,0x14,0x14,0x12,0x1a,0x00,0x00,
	0x00,0x04,0x1e,0x04,0x1e,0x08,0x08,0x08,0x00,0x00,

	0x00,0x1c,0x14,0x12,0x10,0x10,0x08,0x04,0x00,0x00,
	0x00,0x02,0x1e,0x0a,0x0a,0x08,0x08,0x04,0x00,0x00,
	0x00,0x00,0x1e,0x10,0x10,0x10,0x10,0x1e,0x00,0x00,
	0x00,0x0a,0x1f,0x0a,0x0a,0x08,0x08,0x04,0x00,0x00,
	0x00,0x06,0x10,0x16,0x10,0x10,0x08,0x06,0x00,0x00,
	0x00,0x1e,0x10,0x08,0x08,0x0c,0x14,0x12,0x00,0x00,
	0x00,0x04,0x04,0x1e,0x14,0x04,0x04,0x18,0x00,0x00,
	0x00,0x12,0x12,0x14,0x10,0x08,0x08,0x04,0x00,0x00,

	0x00,0x1c,0x14,0x14,0x1a,0x10,0x08,0x04,0x00,0x00,	/*0xa0*/
	0x00,0x10,0x0c,0x08,0x1e,0x08,0x08,0x04,0x00,0x00,
	0x00,0x0a,0x1a,0x1a,0x10,0x10,0x08,0x04,0x00,0x00,
	0x00,0x0e,0x00,0x1f,0x04,0x04,0x04,0x02,0x00,0x00,
	0x00,0x02,0x02,0x06,0x0a,0x02,0x02,0x02,0x00,0x00,
	0x00,0x08,0x08,0x1e,0x08,0x08,0x08,0x04,0x00,0x00,
	0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x1e,0x00,0x00,
	0x00,0x00,0x1e,0x10,0x0c,0x08,0x14,0x02,0x00,0x00,

	0x00,0x04,0x1f,0x08,0x04,0x0e,0x15,0x04,0x00,0x00,
	0x00,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00,0x00,
	0x00,0x04,0x08,0x10,0x12,0x12,0x12,0x12,0x00,0x00,
	0x00,0x02,0x02,0x1e,0x02,0x02,0x02,0x1c,0x00,0x00,
	0x00,0x1e,0x10,0x10,0x10,0x10,0x08,0x04,0x00,0x00,
	0x00,0x00,0x04,0x0a,0x0a,0x10,0x10,0x00,0x00,0x00,
	0x00,0x04,0x1f,0x04,0x04,0x15,0x15,0x04,0x00,0x00,
	0x00,0x00,0x1e,0x10,0x08,0x0a,0x04,0x08,0x00,0x00,

	0x00,0x00,0x0e,0x00,0x0e,0x00,0x0e,0x10,0x00,0x00,	/*0xb0*/
	0x00,0x08,0x04,0x04,0x02,0x12,0x1e,0x10,0x00,0x00,
	0x00,0x10,0x10,0x14,0x08,0x18,0x14,0x02,0x00,0x00,
	0x00,0x1e,0x04,0x1e,0x04,0x04,0x04,0x18,0x00,0x00,
	0x00,0x04,0x1e,0x14,0x04,0x04,0x04,0x04,0x00,0x00,
	0x00,0x00,0x0c,0x08,0x08,0x08,0x08,0x1e,0x00,0x00,
	0x00,0x1e,0x10,0x10,0x1c,0x10,0x10,0x1e,0x00,0x00,
	0x00,0x1e,0x00,0x1e,0x10,0x10,0x08,0x04,0x00,0x00,

	0x00,0x12,0x12,0x12,0x10,0x10,0x08,0x04,0x00,0x00,
	0x00,0x08,0x0a,0x0a,0x0a,0x0a,0x1a,0x0a,0x00,0x00,
	0x00,0x02,0x02,0x02,0x02,0x12,0x0a,0x06,0x00,0x00,
	0x00,0x1e,0x12,0x12,0x12,0x12,0x12,0x1e,0x00,0x00,
	0x00,0x1e,0x12,0x10,0x10,0x10,0x08,0x04,0x00,0x00,
	0x00,0x00,0x16,0x10,0x10,0x10,0x08,0x06,0x00,0x00,
	0x00,0x04,0x08,0x02,0x04,0x00,0x00,0x00,0x00,0x00,
	0x00,0x04,0x0a,0x0a,0x04,0x00,0x00,0x00,0x00,0x00,
#endif
};
#undef bc


//variables
static void* psp_screen_ptr= ((void*)0x04000000) ;

/* Gu�̃t���[���ɓ��������Ȃ��ƁA�r�v�`�o�o���Ȃ��B */
extern int gu_current_frame; // (show1,draw0 or show0,draw1)
unsigned *PSP_Screen_GetBackBuffer_offs(int xxx,int yyy)
{
	return(psp_screen_ptr+(gu_current_frame?0:FRAMESIZE)+yyy*(LINESIZE*2)+xxx+xxx );
}
/*+(gu_current_frame?0:FRAMESIZE)+0x40000000*/
unsigned *PSP_Screen_GetTempBuffer_offs(int xxx,int yyy)
{
	return(psp_screen_ptr+(gu_current_frame?FRAMESIZE:0)+yyy*(LINESIZE*2)+xxx+xxx );
}





void pgFillvram(unsigned long color)
{
	unsigned short *vptr0;		//pointer to vram
	unsigned long i;

	vptr0=(void *)PSP_Screen_GetBackBuffer_offs(0,0);
	for (i=0; i<FRAMESIZE/2; i++) {
		*vptr0=color;
		vptr0+=PIXELSIZE ;
	}
}

void pgFillrect(unsigned long x, unsigned long y, long w, long h, unsigned long color)
{
	unsigned short *vptr0;
	unsigned short *vptr;
	long xx,yy;

	if (w<0) w=-w;
	if (h<0) h=-h;
	vptr0=(void *)PSP_Screen_GetBackBuffer_offs(x,y);
	for (yy=0; yy<h; yy++) {
		vptr=vptr0;
		for (xx=0; xx<w; xx++) {
			*vptr=color;
			vptr+=PIXELSIZE ;
		}
		vptr0+=LINESIZE ;
	}
}



void pgPrint(unsigned int x,unsigned int y,unsigned int color,const char *str)
{
//	while (*str!=0 /*&& x<CMAX_X && y<CMAX_Y*/) {
//		pgPutChar(x, y, color,0,*str);
//		str++;
//		x+=(5+2);
//		//if (x>=CMAX_X) {
//		//	x=0;
//		//	y++;
//		//}
//	}
//}
//void pgPrint(
//unsigned int x,unsigned int y,
//unsigned long color,unsigned long bgcolor,
//)
//,char drawfg,char drawbg,char mag)
//{
	unsigned short*	vr;		//
	unsigned char	cy;
	unsigned char	len;	//�����񒷂�
	unsigned char	i;
	len=0; while(0!=str[len]) {len++;	}

//	vr=(void *)PSP_Screen_GetBackBuffer_offs(x,y);
	vr=(void *)PSP_Screen_GetTempBuffer_offs(x,y);//�킴�Ƌt�ɂ���B
	for (cy=0; cy<10; cy++) {
		for(i=0;i<len;i++){
		unsigned char pt;
			pt = hankaku_font5x10[(((str[i]-HANKAKU10_OFFS)&0x7f)*10)+cy];	/* ascii(0x00-0x7f) */
			vr++;
			if(pt & 0x02) {	*vr = 0xffff;	}/*	else {	*vr=0;	}*/	vr++;
			if(pt & 0x04) {	*vr = 0xffff;	}/*	else {	*vr=0;	}*/	vr++;
			if(pt & 0x08) {	*vr = 0xffff;	}/*	else {	*vr=0;	}*/	vr++;
			if(pt & 0x10) {	*vr = 0xffff;	}/*	else {	*vr=0;	}*/	vr++;
			if(pt & 0x20) {	*vr = 0xffff;	}/*	else {	*vr=0;	}*/	vr++;
			vr++;
		}
		vr += LINESIZE -((5+2)*len);
	}
}
//480*272 = 60*38
//#define CMAX_X 60
//#define CMAX_Y 34






void pgScreenFlip()
{
	sceDisplaySetFrameBuf(psp_screen_ptr+(gu_current_frame?FRAMESIZE:0),LINESIZE,PIXELSIZE,0);
}
/******************************************************************************/
/******************************************************************************/

//void pgiInit()
//{
//	sceCtrlSetSamplingCycle(0);
//	sceCtrlSetSamplingMode(1);
//}


unsigned long pgiGetpad()
{
	ctrl_data_t paddata;
	sceCtrlReadBufferPositive(&paddata,1);
	return paddata.buttons;
}


unsigned long pgiGetTick()
{
	ctrl_data_t paddata;
	sceCtrlReadBufferPositive(&paddata,1);
	return paddata.frame;
}



void pgiGetCtrl(pgi_ctrl_t *d)
{
	ctrl_data_t paddata;
	sceCtrlReadBufferPositive(&paddata,1);
	d->tick=paddata.frame;
	d->pad=paddata.buttons;
	d->analog=*(unsigned long *)paddata.analog;
}



/******************************************************************************/
/******************************************************************************/
//int xmain(void);
//void __exit();

//void pgMain(unsigned long args, void *argp)
//{
//	int ret;
//	pgiInit();
//	ret=xmain();
//	pgExit(ret);
//}
void pgInit()
{
	sceDisplaySetMode(1,SCREEN_WIDTH,SCREEN_HEIGHT);
	sceDisplaySetFrameBuf(0,0,0,1);

//	my_memset( psp_screen_ptr, 0, FRAMESIZE * 2 ) ;
	sceDisplaySetFrameBuf( psp_screen_ptr, LINESIZE,1,1 ) ;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(1);
}
