/*
 * MIT License
 *
 * Copyright (c) 2023 Dennisman219
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MINIMAL_CLOCK_FACE_H_
#define MINIMAL_CLOCK_FACE_H_

#include "movement.h"

/*
 * MINIMAL CLOCK FACE
 *
 * A minimal clock face that just shows hours and minutes.
 * There is nothing to configure. The face follows the 12h/24h setting
 *
 */

typedef struct {
    // Anything you need to keep track of, put it here!
    uint8_t unused;
} minimal_clock_state_t;

void minimal_clock_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr);
void minimal_clock_face_activate(movement_settings_t *settings, void *context);
bool minimal_clock_face_loop(movement_event_t event, movement_settings_t *settings, void *context);
void minimal_clock_face_resign(movement_settings_t *settings, void *context);

#define minimal_clock_face ((const watch_face_t){ \
    minimal_clock_face_setup, \
    minimal_clock_face_activate, \
    minimal_clock_face_loop, \
    minimal_clock_face_resign, \
    NULL, \
})

#endif // MINIMAL_CLOCK_FACE_H_

