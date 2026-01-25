### Description

LED blinky

### Structure

- `bsp/config` - contains platform-specific make file
- `bsp/stm32f4xx` - contains board-specific files
- `scripts` - contains bash script to create build
- `src` - applcation code
- `uSDK` - link to shared SDK

### Set up

Target: NUCLEO-F411RE

### Connection 

| Nucleo pin   | GPIO   | LED    |
|--------------|--------|--------|
| CN7 (37)     | PC3    | Yellow |
| CN10 (34)    | PC4    | White  |
| Build-in     | PA5    | Green  |

![LEDs blink](led-animation.gif)
