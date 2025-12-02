/*
 * MIT License
 *
 * Copyright (c) 2022 Joey Castillo
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

#ifndef MOVEMENT_CONFIG_H_
#define MOVEMENT_CONFIG_H_

#include "movement_faces.h"

const watch_face_t watch_faces[] = {

    // Complications
    //// Games
    higher_lower_game_face,
    invaders_face,
    endless_runner_face,
    butterfly_game_face,
    simon_face,
    wordle_face,

    //// Celestial
    solstice_face,
    astronomy_face,
    planetary_time_face,
    planetary_hours_face,
    moon_phase_face,
    sunrise_sunset_alt_face,

    //// Lifestyle
    wareki_face,
    breathing_face,
    beer_o_clock_face,
    tarot_face,
    menstrual_cycle_face,
    kitchen_conversions_face,
    habit_face,
    activity_face,
    pulsometer_face,

    //// Time based
    countdown_face,
    stock_stopwatch_face,
    alarm_face,
    wake_face,
    timer_face,
    time_left_face,
    deadline_face,
    day_one_face,

    //// Randomize
    probability_face,
    simple_coin_flip_face,
    geomancy_face,
    toss_up_face,
    tomato_face,

    //// Tracking
    ratemeter_face,
    blinky_face,
    tally_face,

    //// Tools
    simple_calculator_face,
    flashlight_face,
    metronome_face,
    tachymeter_face,
    counter_face,
    totp_face,
    totp_face_lfs,

    //// Reference
    periodic_face,
    databank_face,

    // Clocks
    //// Conventional
    simple_clock_face,
    minimal_clock_face,
    wyoscan_face,
    weeknumber_clock_face,
    ships_bell_face,
    minute_repeater_decimal_face,
    repetition_minute_face,
    world_clock2_face,

    //// Unconventional
    close_enough_clock_face,
    french_revolutionary_face,
    beats_face,
    day_night_percentage_face,
    decimal_time_face,
    mars_time_face,

    // Settings
    voltage_face,
    nanosec_face,
    finetune_face,
    set_time_hackwatch_face,
    preferences_face,

    // Sensor
    thermistor_readout_face,
};

#define MOVEMENT_NUM_FACES (sizeof(watch_faces) / sizeof(watch_face_t))

/* Determines what face to go to from the first face on long press of the Mode button.
 * Also excludes these faces from the normal rotation.
 * In the default firmware, this lets you access temperature and battery voltage with a long press of Mode.
 * Some folks also like to use this to hide the preferences and time set faces from the normal rotation.
 * If you don't want any faces to be excluded, set this to 0 and a long Mode press will have no effect.
 */
#define MOVEMENT_SECONDARY_FACE_INDEX (MOVEMENT_NUM_FACES - 16) // or (0)
#define MOVEMENT_TERTIARY_FACE_INDEX (MOVEMENT_NUM_FACES - 6) // or (0)

/* Custom hourly chime tune. Check movement_custom_signal_tunes.h for options. */
//#define SIGNAL_TUNE_DEFAULT
//#define SIGNAL_TUNE_MARIO_THEME
//#define SIGNAL_TUNE_ZELDA_SECRET
//#define SIGNAL_TUNE_HARRY_POTTER_SHORT
#define SIGNAL_TUNE_HARRY_POTTER_LONG

/* Determines the intensity of the led colors
 * Set a hex value 0-15 with 0x0 being off and 0xF being max intensity
 */
#define MOVEMENT_DEFAULT_GREEN_COLOR 0xF
#define MOVEMENT_DEFAULT_RED_COLOR 0x0

/* Set to true for 24h mode or false for 12h mode */
#define MOVEMENT_DEFAULT_24H_MODE false

/* Enable or disable the sound on mode button press */
#define MOVEMENT_DEFAULT_BUTTON_SOUND false

/* Set the timeout before switching back to the main watch face
 * Valid values are:
 * 0: 60 seconds
 * 1: 2 minutes
 * 2: 5 minutes
 * 3: 30 minutes
 */
#define MOVEMENT_DEFAULT_TIMEOUT_INTERVAL 0

/* Set the timeout before switching to low energy mode
 * Valid values are:
 * 0: Never
 * 1: 1 hour
 * 2: 2 hours
 * 3: 6 hours
 * 4: 12 hours
 * 5: 1 day
 * 6: 2 days
 * 7: 7 days
 */
#define MOVEMENT_DEFAULT_LOW_ENERGY_INTERVAL 1

/* Set the led duration
 * Valid values are:
 * 0: No LED
 * 1: 1 second
 * 2: 3 seconds
 * 3: 5 seconds
 */
#define MOVEMENT_DEFAULT_LED_DURATION 3

#endif // MOVEMENT_CONFIG_H_
