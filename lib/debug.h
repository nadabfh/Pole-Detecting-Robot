
#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG // à mettre en commentaire ou non au besoin
#ifdef DEBUG

#include "USART.h"
# define DEBUG_PRINT(x) transmissionUart(x) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort

#endif

#endif