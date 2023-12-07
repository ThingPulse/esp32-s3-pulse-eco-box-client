#include <Wire.h>
#include <sps30.h>
#include "settings.h"

void pmInit() {
  int16_t ret;
  uint8_t auto_clean_days = 4;
  uint32_t auto_clean;


  //sensirion_i2c_init();


  /*while (sps30_probe() != 0) {
    SER.print("SPS sensor probing failed\n");
    delay(500);
  }*/

#ifndef PLOTTER_FORMAT
  SER.print("SPS sensor probing successful\n");
#endif /* PLOTTER_FORMAT */

  ret = sps30_set_fan_auto_cleaning_interval_days(auto_clean_days);
  if (ret) {
    SER.print("error setting the auto-clean interval: ");
    SER.println(ret);
  }

  ret = sps30_start_measurement();
  if (ret < 0) {
    SER.print("error starting measurement\n");
  }

#ifndef PLOTTER_FORMAT
  SER.print("measurements started\n");
#endif /* PLOTTER_FORMAT */

#ifdef SPS30_LIMITED_I2C_BUFFER_SIZE
  SER.print("Your Arduino hardware has a limitation that only\n");
  SER.print("  allows reading the mass concentrations. For more\n");
  SER.print("  information, please check\n");
  SER.print("  https://github.com/Sensirion/arduino-sps#esp8266-partial-legacy-support\n");
  SER.print("\n");
  delay(2000);
#endif

  delay(1000);
}

void getPmMeasurement(sps30_measurement *spsdata) {
  char serial[SPS30_MAX_SERIAL_LEN];
  uint16_t data_ready;
  int16_t ret;

  do {
    ret = sps30_read_data_ready(&data_ready);
    if (ret < 0) {
      SER.print("error reading data-ready flag: ");
      SER.println(ret);
    } else if (!data_ready)
      SER.print("data not ready, no new measurement available\n");
    else
      break;
    delay(100); /* retry in 100ms */
  } while (1);

  ret = sps30_read_measurement(spsdata);
  if (ret < 0) {
    SER.print("error reading measurement\n");
  } else {
  
    return;
  }

}