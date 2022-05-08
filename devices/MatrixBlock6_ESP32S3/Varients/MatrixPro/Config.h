//Define Device Specific Macro, Value and private function
#pragma once

#define GRID_8x8
#define MODEL MX1P

#define DEVICE_BATTERY
// #define DEVICE_MIDI

#define MULTIPRESS 10 //Key Press will be process at once
// #define LC8812

#include "Family.h"

struct DeviceInfo
{
    char DeviceCode[4];
    char Revision[4];
    uint8_t ProductionYear;
    uint8_t ProductionMonth;
};

namespace Device
{
    inline DeviceInfo deviceInfo;
    const string name = "Matrix Pro";
    const string model = "MX1P";

    const string manufaturer_name = "203 Electronics";
    const string product_name = "Matrix";
    const uint16_t usb_vid = 0x0203; 
    const uint16_t usb_pid = 0x1040; //(Device Class)0001 (Device Code)000001 (Reserved for Device ID (0~63))000000


    const uint16_t numsOfLED = 64 + 32;
    inline uint16_t keypad_scanrate = 120;
    const uint8_t x_size = 8;
    const uint8_t y_size = 8;
    const uint8_t touchbar_size = 16; //Not required by the API, private use.
    inline uint8_t touchbar_map[touchbar_size] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3}; //Touch number as index and touch location as value (Left touch down and then right touch down)

    namespace KeyPad
    {
        inline KeyInfo keypadState[x_size][y_size];
        inline KeyInfo touchbarState[touchbar_size];
        inline uint16_t changeList[MULTIPRESS + 1];
        
    }

    //LED
    #define MAX_LED_LAYERS 5
    inline uint16_t fps = 120; //Depends on the FreeRTOS tick speed
    inline uint8_t brightness_level[9] = {8, 12, 24, 40, 64, 90, 128, 168, 255};
    // const Dimension grid_size(8,8);
    // const Point grid_offset = Point(1,1);
}

#define FN_Pin GPIO_NUM_16
// #define FN_Pin GPIO_NUM_42 //FN got stuck on prototype so remapped

#define LED_Pin GPIO_NUM_38

#define Key1_Pin GPIO_NUM_21
#define Key2_Pin GPIO_NUM_17
#define Key3_Pin GPIO_NUM_1
#define Key4_Pin GPIO_NUM_6
#define Key5_Pin GPIO_NUM_12
#define Key6_Pin GPIO_NUM_13
#define Key7_Pin GPIO_NUM_14
#define Key8_Pin GPIO_NUM_15

#define KeyRead1_Pin GPIO_NUM_2
#define KeyRead2_Pin GPIO_NUM_3
#define KeyRead3_Pin GPIO_NUM_4
#define KeyRead4_Pin GPIO_NUM_5
#define KeyRead5_Pin GPIO_NUM_7
#define KeyRead6_Pin GPIO_NUM_8
#define KeyRead7_Pin GPIO_NUM_9
#define KeyRead8_Pin GPIO_NUM_10

#define FSR_KEYPAD
#define KeyRead1_ADC_CHANNEL ADC1_CHANNEL_1
#define KeyRead2_ADC_CHANNEL ADC1_CHANNEL_2
#define KeyRead3_ADC_CHANNEL ADC1_CHANNEL_3
#define KeyRead4_ADC_CHANNEL ADC1_CHANNEL_4
#define KeyRead5_ADC_CHANNEL ADC1_CHANNEL_6
#define KeyRead6_ADC_CHANNEL ADC1_CHANNEL_7
#define KeyRead7_ADC_CHANNEL ADC1_CHANNEL_8
#define KeyRead8_ADC_CHANNEL ADC1_CHANNEL_9

#define TouchData_Pin GPIO_NUM_33
#define TouchClock_Pin GPIO_NUM_34

#define PowerCord_Pin GPIO_NUM_18

#define PMIC_INT_Pin GPIO_NUM_11

#define Matrix_Mod_GPIO_Pin GPIO_NUM_37

#define I2C_SDA_Pin GPIO_NUM_46
#define I2C_SCL_Pin GPIO_NUM_45

inline gpio_num_t keypad_write_pins[] = {
    Key1_Pin,
    Key2_Pin,
    Key3_Pin,
    Key4_Pin,
    Key5_Pin,
    Key6_Pin,
    Key7_Pin,
    Key8_Pin,
};

inline gpio_num_t keypad_read_pins[] = {
    KeyRead1_Pin,
    KeyRead2_Pin,
    KeyRead3_Pin,
    KeyRead4_Pin,
    KeyRead5_Pin,
    KeyRead6_Pin,
    KeyRead7_Pin,
    KeyRead8_Pin,
};

inline adc1_channel_t keypad_read_adc_channel[] = {
    KeyRead1_ADC_CHANNEL,
    KeyRead2_ADC_CHANNEL,
    KeyRead3_ADC_CHANNEL,
    KeyRead4_ADC_CHANNEL,
    KeyRead5_ADC_CHANNEL,
    KeyRead6_ADC_CHANNEL,
    KeyRead7_ADC_CHANNEL,
    KeyRead8_ADC_CHANNEL,
};
