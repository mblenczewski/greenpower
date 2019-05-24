/*
 Name:		CarOS.ino
 Created:	17.05.2019 15:29:47
 Author:	Mikołaj Lenczewski
*/

#include <Adafruit_GFX.h>
#include <eRCaGuy_Timer2_Counter.h>
#include <FreeDefaultFonts.h>
#include <MCUFRIEND_kbv.h>
#include <PID_v1.h>
#include <Streaming.h>
#include <TFT_HX8357GLUE.h>
#include <UTFTGLUE.h>

#include "builtin_button_callbacks.h"
#include "CarOS.h"
#include "inputs.h"
#include "miscellaneous.h"
#include "models.h"
#include "outputs.h"