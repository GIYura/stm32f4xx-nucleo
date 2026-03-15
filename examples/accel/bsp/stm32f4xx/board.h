#ifndef BOARD_H
#define BOARD_H

#include "adxl345.h"

/*Brief: Board initialization
* [in] - none
* [out] - none
* */
void BoardInit(void);

/*Brief: Get board ADXL345
* [in] - none
* [out] - pointer to ADXL object
* */
AdxlHandle_t* BoardGetAdxl(void);

#endif /* BOARD_H */
