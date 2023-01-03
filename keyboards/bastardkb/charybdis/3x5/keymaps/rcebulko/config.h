/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Disable unused features. */
#define NO_ACTION_ONESHOT

/* Use I2C or Serial, not both */
// #define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
// #define MASTER_LEFT
// #undef MASTER_RIGHT
// #define EE_HANDS

#define IGNORE_MOD_TAP_INTERRUPT
// #define HOLD_ON_OTHER_KEY_PRESS if PERMISSIVE_HOLD isn't enough
// PERMISSIVE_HOLD: MOD(down), K(down), K(up), MOD(up), TT => hold
// HOLD_ON_OTHER_KEY_PRESS: MOD(down), K(down), MOD(up), K(up) TT => hold
#define PERMISSIVE_HOLD
// #define TAPPING_TERM 100

// #define TAPPING_TOGGLE 2

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#endif // POINTING_DEVICE_ENABLE
