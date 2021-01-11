# sct_neopixel
SCT based NeoPixel driver

This library uses the State Configurable Timer (SCTimer or SCT) found in several NXP microcontrollers including the LPC55 to drive multiple strings of NeoPixels.

## Theory of operation

This driver utilizes the unique features of the State Configurable Timer to generate the pulse train needed to load NeoPixel LEDs.  The configurability of the SCT allows a single instance to drive as many as 10 strings of NeoPixels with minimal processor overhead (a single interrupt per pixel in the largest chain).

5 match regsiters are used to trigger events:

 * `NEO_MATCH_RISE` triggers `NEO_EVENT_RISE` in all states to start the pulse
 * `NEO_MATCH_0` conditionally triggers `NEO_EVENT_CHx` based on the data being transmitted in each channel
 * `NEO_MATCH_1` triggers `NEO_EVENT_FALL_1` in all states to finish the pulse
 * `NEO_MATCH_PERIOD` triggers `NEO_EVENT_NEXT` in all but STATE 0 to reset the counter and advance to the next STATE(bit)
 * `NEO_MATCH_PERIOD` triggers `NEO_EVENT_LAST` in STATE 0 which fires an interrupt and halts the timer at the end of a pixel
 * `NEO_MATCH_RESET` triggers `NEO_EVENT_RESET` to fire an interrupt and halt the timer at the end of the transaction

The interrupt handler is triggered at the end of each pixel.  If there are still pixels remaining on any of the configured channels, it updates the STATES that will trigger an early fall on each of the channel events to indicate a 0, then resets the counter and advances back to the top state.  If there are no pixels remaining, it lets the counter continue until the reset timeout is reached.  Another interrupt is triggered by hitting the reset count to clear the busy signal so that another transaction can be started.

## Configuration

`sctpix_init(neoPixelType)` is used to configure the SCTimer for operation.  This does not initialize any channels.  The nepPixelType indicates the number of bytes per pixel and color order (neoPixelType is a future feature, only 3byte pixels are currently implemented and none of the functions manipulate the data yet in a way that needs to be aware of the color order)

`sctpix_addCh(ch, *data, size)` configures a channel.  This driver does not allocate any buffers so that the application can control the location of the buffers to allow for optimization of the buffer organization for logical or performance concerns.  Pass a pointer to a buffer of 32bit unsigned integers with as many elements as there are pixels connected to that channel.  The data in the buffer is the raw data that will be sent to the pixel, in the order that the pixel expects.

`sctpix_rmCh(ch)` allows a channel to be removed if you need to change the configuration dynamically, such as if some channels have RGBW pixels while others have GRB pixels.  The color order can be mixed, but the nubmer of bytes per pixel should match to simplify logical mapping.  (4 byte pixel support is a future feature)

`sctpix_show()` initiates a transfer to update the pixels.

`sctpix_canShow()` returns a boolean indicating if it is safe to change pixel data if you want to avoid changing the values mid update.

`sctpix_setPixel(ch, pixel, color)` sets the value of a pixel on a specific channel.  The color is the raw value.

`sctpix_updateType(neoPixelType)` allows changing the neoPixelType if you need to reconfigure when changing channels (this is future feature that has not been implemented yet)