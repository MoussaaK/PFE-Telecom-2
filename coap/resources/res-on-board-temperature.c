#include "contiki.h"

//#if PLATFORM_HAS_TEMPERATURE

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "coap-engine.h"
#include "dev/adc-sensors.h"
#include "dev/adc-zoul.h"
#include "dev/zoul-sensors.h"
//#include "dev/temperature-sensor.h"

static void res_get_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_periodic_handler(void);

#define MAX_AGE      60
#define INTERVAL_MIN 5
#define INTERVAL_MAX (MAX_AGE - 1)
#define CHANGE       1

static int32_t interval_counter = INTERVAL_MIN;
static int temperature_old = INT_MIN;
PERIODIC_RESOURCE(res_on_board,
         "title=\"Temperature interne\";rt=\"Temperature\";obs",
         res_get_handler,
         NULL,
         NULL,
         NULL,
         CLOCK_SECOND,
         res_periodic_handler);
static void
res_get_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  /*
   * For minimal complexity, request query and options should be ignored for GET on observable resources.
   * Otherwise the requests must be stored with the observer list and passed by coap_notify_observers().
   * This would be a TODO in the corresponding files in contiki/apps/erbium/!
   */

  //int temperature = adc_zoul.value(ZOUL_SENSORS_ADC1);
  //int temperature = vdd3_sensor.value(CC2538_SENSORS_VALUE_TYPE_CONVERTED);
  int temperature = cc2538_temp_sensor.value(CC2538_SENSORS_VALUE_TYPE_CONVERTED);

  unsigned int accept = -1;
  coap_get_header_accept(request, &accept);

  if(accept == -1 || accept == TEXT_PLAIN) {
    coap_set_header_content_format(response, TEXT_PLAIN);
    snprintf((char *)buffer, COAP_MAX_CHUNK_SIZE, "%d.%u", temperature/1000, temperature%1000);

    coap_set_payload(response, (uint8_t *)buffer, strlen((char *)buffer));
  } else if(accept == APPLICATION_JSON) {
    coap_set_header_content_format(response, APPLICATION_JSON);
    snprintf((char *)buffer, COAP_MAX_CHUNK_SIZE, "{'temperature':%d}", temperature);

    coap_set_payload(response, buffer, strlen((char *)buffer));
  } else {
    coap_set_status_code(response, NOT_ACCEPTABLE_4_06);
    const char *msg = "Supporting content-types text/plain and application/json";
    coap_set_payload(response, msg, strlen(msg));
  }

  coap_set_header_max_age(response, MAX_AGE);

  /* The coap_subscription_handler() will be called for observable resources by the coap_framework. */
}

/*
 * Additionally, a handler function named [resource name]_handler must be implemented for each PERIODIC_RESOURCE.
 * It will be called by the coap_manager process with the defined period.
 */
static void
res_periodic_handler()
{
  //int temperature = adc_zoul.value(ZOUL_SENSORS_ADC1);
  //int temperature = vdd3_sensor.value(CC2538_SENSORS_VALUE_TYPE_CONVERTED);
  // cc2538_temp_sensor donne la valeur de la temperature interne
  // vdd3_sensor donne la valeur du voltage
  /*
  adc_zoul.value(ZOUL_SENSORS_ADC1);
  adc_zoul.value(ZOUL_SENSORS_ADC2);
  adc_zoul.value(ZOUL_SENSORS_ADC3);

  Permettent de sniffer les trois ports du capteur
  */
  int temperature = cc2538_temp_sensor.value(CC2538_SENSORS_VALUE_TYPE_CONVERTED);

  ++interval_counter;

  if((abs(temperature - temperature_old) >= CHANGE && interval_counter >= INTERVAL_MIN) ||
     interval_counter >= INTERVAL_MAX) {
     interval_counter = 0;
     temperature_old = temperature;
    /* Notify the registered observers which will trigger the res_get_handler to create the response. */
    coap_notify_observers(&res_on_board);
  }
}
//#endif /* PLATFORM_HAS_TEMPERATURE */
