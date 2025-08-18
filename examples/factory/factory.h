#ifndef __TEST_FACTORY_H__
#define __TEST_FACTORY_H__

/*********************************************************************************
 *                                  INCLUDES
 * *******************************************************************************/
#define XPOWERS_CHIP_BQ25896
#include <XPowersLib.h>
#include "bq27220.h"
#include "FS.h"
#include "SPI.h"
#include "SPIFFS.h"

/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/

#define DISP_REFR_MODE_FULL 0
#define DISP_REFR_MODE_PART 1

#define DISP_REFR_MODE_FULL 0
#define DISP_REFR_MODE_PART 1

extern XPowersPPM PPM;
extern BQ27220 bq27220;

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/
union flush_buf_pixel
{
    struct _byte {
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
        uint8_t b8 : 1;
    }bit;
    uint8_t full;
};

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void disp_full_refr(void); // Next global refresh

#endif