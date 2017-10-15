#ifndef HomeLib_h
#define HomeLib_h

unsigned long int CURRENT_TIME;

#include <EEPROM.h>
#include <MsTimer2.h>
#include <DHT.h>
#include "lib/init.h"
#include "lib/Server.cpp"
#include "lib/functions.cpp"
#include "lib/std/Timeout.cpp"
#include "lib/std/Enums.cpp"
#include "lib/std/PinA.cpp"
#include "lib/std/PinD.cpp"
#include "lib/std/Module.cpp"
#include "lib/std/ModuleA.cpp"
#include "lib/std/ModuleD.cpp"
#include "lib/std/Memory.cpp"
#include "lib/module/Button.cpp"
#include "lib/module/Relay.cpp"
#include "lib/module/Gercon.cpp"
#include "lib/module/Motion.cpp"
#include "lib/module/PWM.cpp"
#include "lib/module/Dimmer.cpp"
#include "lib/module/IR.cpp"
#include "lib/module/ACDimmer.cpp"
#include "lib/module/PT100.cpp"
#include "lib/module/Gidrolock.cpp"
#include "lib/module/Leak.cpp"

#endif