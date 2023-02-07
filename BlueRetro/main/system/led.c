/*
 * Copyright (c) 2019-2022, Jacques Gagnon
 * SPDX-License-Identifier: Apache-2.0
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "soc/efuse_reg.h"
#include "esp_efuse.h"
#include "zephyr/atomic.h"
#include "system/gpio.h"
#include "driver/ledc.h"
#include "led.h"

#ifdef CONFIG_BLUERETRO_SYSTEM_SEA_BOARD
#define ERR_LED_PIN 32
#else
#define ERR_LED_PIN 17
#endif
#define PICO_ERR_LED_PIN 20
#define ERR_LED_DUTY_MIN 50
#define ERR_LED_DUTY_MAX 2000
#define ERR_LED_FADE_TIME 500


#define DEV_LED_0 14
#define DEV_LED_1 32
#define DEV_LED_2 33
#define DEV_LED_3 25

/* LED flags */
enum {
    ERR_LED_SET = 0,
};

static atomic_t led_flags = 0;
static TaskHandle_t err_led_task_hdl;
static uint8_t err_led_pin = ERR_LED_PIN;

static void err_led_task(void *param) {
    while (1) {
        if (!atomic_test_bit(&led_flags, ERR_LED_SET)) {
            ledc_set_fade_time_and_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, ERR_LED_DUTY_MAX,
                ERR_LED_FADE_TIME, LEDC_FADE_NO_WAIT);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            ledc_set_fade_time_and_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, ERR_LED_DUTY_MIN,
                ERR_LED_FADE_TIME, LEDC_FADE_NO_WAIT);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else {
            vTaskSuspend(err_led_task_hdl);
        }
    }
}

void err_led_init(void) {
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = 5000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .gpio_num   = ERR_LED_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0,
    };

    uint32_t package = esp_efuse_get_pkg_ver();
    if (package == EFUSE_RD_CHIP_VER_PKG_ESP32PICOV302) {
        ledc_channel.gpio_num = PICO_ERR_LED_PIN;
        err_led_pin = PICO_ERR_LED_PIN;
    }

    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);
    ledc_set_duty_and_update(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0, 0);

    xTaskCreatePinnedToCore(&err_led_task, "err_led_task", 768, NULL, 5, &err_led_task_hdl, 0);
    err_led_clear();
}

void err_led_set(void) {
    vTaskSuspend(err_led_task_hdl);
    ledc_set_duty_and_update(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 8191, 0);
    atomic_set_bit(&led_flags, ERR_LED_SET);
}

void err_led_clear(void) {
    /* When error is set it stay on until power cycle */
    if (!atomic_test_bit(&led_flags, ERR_LED_SET)) {
        vTaskSuspend(err_led_task_hdl);
        ledc_set_duty_and_update(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0, 0);
    }
}

void err_led_pulse(void) {
    vTaskResume(err_led_task_hdl);
}

uint32_t err_led_get_pin(void) {
    return err_led_pin;
}


void dev_led_init()
{
    //
    gpio_pad_select_gpio(DEV_LED_0);
    gpio_pad_select_gpio(DEV_LED_1);
    gpio_pad_select_gpio(DEV_LED_2);
    gpio_pad_select_gpio(DEV_LED_3);

    gpio_set_pull_mode(DEV_LED_0, GPIO_PULLUP_ENABLE);
    gpio_set_pull_mode(DEV_LED_1, GPIO_PULLUP_ENABLE);
    gpio_set_pull_mode(DEV_LED_2, GPIO_PULLUP_ENABLE);
    gpio_set_pull_mode(DEV_LED_3, GPIO_PULLUP_ENABLE);
    
    gpio_set_direction(DEV_LED_0, GPIO_MODE_OUTPUT);
    gpio_set_direction(DEV_LED_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(DEV_LED_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(DEV_LED_3, GPIO_MODE_OUTPUT);

}

void dev_led_set(uint8_t num, uint8_t value)
{
    if(num == 0)
        gpio_set_level(DEV_LED_0, value);
    else if(num ==1)
        gpio_set_level(DEV_LED_1, value);
    else if(num ==2)
        gpio_set_level(DEV_LED_2, value);
    else if(num ==3)
        gpio_set_level(DEV_LED_3, value);
}

