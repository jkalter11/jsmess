#pragma once

#ifndef __COLECO_CONTROLLERS__
#define __COLECO_CONTROLLERS__

void coleco_scan_paddles(running_machine &machine, int *joy_status0, int *joy_status1);
UINT8 coleco_paddle_read(running_machine &machine, int port, int joy_mode, int joy_status);

INPUT_PORTS_EXTERN( coleco );

#endif
