// Define Device Specific Function
#include "Device.h"
#include "esp_adc/adc_oneshot.h"

// Device Configs
#include "V100/Config.h"
#include "V110/Config.h"
#include "RevC/Config.h"

void BurnEFuse();  // This is in device folder, a custom BurnEFuse will be provided

namespace Device
{
  void LoadVariantInfo() 
  {
    // Load Factory Config
    #ifdef FACTORY_CONFIG
        #pragma message "FACTORY_CONFIG IS USED"
        DeviceInfo factoryDeviceInfo{FACTORY_DEVICE_MODEL, FACTORY_DEVICE_REVISION, FACTORY_MFG_YEAR, FACTORY_MFG_MONTH};
        memcpy (&deviceInfo, &factoryDeviceInfo, sizeof(DeviceInfo));
        ESP_LOGI("Device Init", "Factory config - Mystrix %.4s %.4s", deviceInfo.Model, deviceInfo.Revision);
    #endif

    // Load Velocity Sensitive Config
    if(deviceInfo.Model[3] == 'P')
    {
      name += " Pro";
      product_name += " Pro";
      model = "MX1P";
      KeyPad::velocity_sensitivity = true;
    }
    else if(deviceInfo.Model[3] == 'S')
    {
      KeyPad::velocity_sensitivity = false;
      // Remove "Underglow" from led_partitions
      led_partitions.pop_back();
    }
    else
    { 
      // Default to Mystrix Pro because RC units has no config baked in
      name += " Pro";
      product_name += " Pro";
      model = "MX1P";
      KeyPad::velocity_sensitivity = true;
      ESP_LOGE("Device Init", "Failed to find config for %.4s %.4s", deviceInfo.Model, deviceInfo.Revision);
    }

    ESP_LOGI("Device Init", "Loading config for %s (%.4s %.4s) (MFG: %02d-%02d) (Serial: %s)", Device::name.c_str(), deviceInfo.Model, deviceInfo.Revision,
             deviceInfo.ProductionYear, deviceInfo.ProductionMonth, GetSerial().c_str());  // It seems excessive but
                                                                                           // deviceInfo.Revision does
                                                                                           // not have null terminator
    if (string(deviceInfo.Revision).compare(0, 4, "V100") == 0)
    { LoadV100(); }
    else if (string(deviceInfo.Revision).compare(0, 4, "V110") == 0)
    { LoadV110(); }
    else if (string(deviceInfo.Revision).compare(0, 4, "REVC") == 0)
    { LoadRevC(); }
    else
    {
    ESP_LOGE("Device Init", "Failed to find config for %s %.4s", Device::name.c_str(), deviceInfo.Revision);
      LoadV110();
    }
  }
}
