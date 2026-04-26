#include "pico/stdlib.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

int main() {
  stdio_init_all();

  /*
   * Start the FreeRTOS scheduler. The main function will not continue
   * past this point, as the scheduler will take over and run the tasks.
   * Add tasks and pre-start functionality before launching the
   * scheduler.
   */
  vTaskStartScheduler();
}
