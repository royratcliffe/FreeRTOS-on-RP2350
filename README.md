# FreeRTOS on RP2350

A starter project for running FreeRTOS on the Raspberry Pi Pico 2 (RP2350) using the Pico SDK and the VS Code Raspberry Pi Pico extension.

## Overview

This project provides a minimal FreeRTOS template targeting the RP2350 (ARM Cortex-M33, no TrustZone). It initialises the FreeRTOS scheduler and is ready for tasks to be added. The FreeRTOS kernel is included as a submodule and linked via the `pico_async_context_freertos` integration layer.

## Requirements

- [Raspberry Pi Pico VS Code Extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)
- Pico SDK **2.2.0**
- ARM GCC Toolchain **14.2 Rel1**
- picotool **2.2.0-a4**
- CMake **3.13+**
- Ninja build system

The extension manages SDK and toolchain installation automatically.

## Building

Initialise the FreeRTOS-Kernel submodule, if you haven't already:

```sh
git submodule update --init --recursive
```

### Using VS Code

Open the project in VS Code with the Raspberry Pi Pico extension installed. Use the **Compile Project** build task (`Ctrl+Shift+B`) to build.

### Using the command line

```sh
mkdir build && cd build
cmake ..
ninja
```

The build outputs (`FreeRTOS-on-RP2350.uf2`, `.dis`, etc.) are placed in the `build/` directory.

## Flashing

### UF2 (drag-and-drop)

Hold the **BOOTSEL** button on the Pico 2 while plugging it in via USB, then copy `build/FreeRTOS-on-RP2350.uf2` onto the mounted drive.

### picotool

Use the **Run Project** VS Code task, or run:

```sh
picotool load build/FreeRTOS-on-RP2350.uf2 -fx
```

### OpenOCD (SWD)

Use the **Flash** VS Code task, which connects via a CMSIS-DAP probe:

```sh
openocd -f interface/cmsis-dap.cfg -f target/rp2350.cfg \
  -c "adapter speed 5000; program build/FreeRTOS-on-RP2350.elf verify reset exit"
```

## Project Structure

| File | Description |
|---|---|
| `main.c` | Entry point — initialises stdio and starts the FreeRTOS scheduler |
| `FreeRTOSConfig.h` | Board-specific FreeRTOS config (includes common config) |
| `FreeRTOSConfig_common.h` | Shared FreeRTOS configuration parameters |
| `CMakeLists.txt` | CMake build definition |
| `FreeRTOS-Kernel/` | FreeRTOS kernel source (submodule) |

## FreeRTOS Configuration Highlights

| Parameter | Value |
|---|---|
| Tick rate | 1000 Hz |
| Max priorities | 32 |
| Total heap size | 128 KB (heap_4) |
| Preemption | Enabled |
| Software timers | Enabled |
| Mutexes / semaphores | Enabled |
| Port | GCC/RP2350_ARM_NTZ |

## Adding Tasks

Add tasks in `main.c` before calling `vTaskStartScheduler()`:

```c
#include "FreeRTOS.h"
#include "task.h"

void myTask(void *pvParameters) {
    for (;;) {
        // task body
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main() {
    stdio_init_all();

    xTaskCreate(myTask, "MyTask", 256, NULL, 1, NULL);

    vTaskStartScheduler();
}
```

## License

FreeRTOS kernel files are licensed under the [MIT License](FreeRTOS-Kernel/LICENSE.md).
