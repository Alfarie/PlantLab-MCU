#include <Task.h>
extern TaskManager taskManager;
#include "./Solution.h"
#include "./Gy21.h"
#include "./CO2.h"
#include "./Light.h"
class Sensor : public Task
{
public:
  static Sensor *s_instance;
  Sensor() : Task(MsToTaskTime(5))
  {
    sensor.temp = 0;
    sensor.humi = 0;
    sensor.soil = 0;
    sensor.ec = 0;
    sensor.ph = 0;
    sensor.vpd = 0;
    sensor.co2 = 0;

    // taskManager.StartTask(Solution::instance());
    // taskManager.StartTask(GY21::instance());
    // taskManager.StartTask(Co2Sensor::instance());
  };
  static Sensor *instance()
  {
    if (!s_instance)
      s_instance = new Sensor;
    return s_instance;
  }
  sensor_s GetSensors()
  {
    return sensor;
  }

  String GetSensorsString()
  {
    String sensorDataJsonStr = "{ \"ec\":" + String(sensor.ec) +
                               ",\"ph\":" + String(sensor.ph) +
                               ",\"water\":" + String(sensor.water) +
                               ",\"light\":" + String(sensor.light) +
                               ",\"temperature\":" + String(sensor.temp) +
                               ",\"humidity\":" + String(sensor.humi) +
                               ",\"co2\":" + String(sensor.co2) +
                               ", \"date\":" + "\"" + RTC::instance()->GetDateString() + "\"" +
                               ", \"time\":" + "\"" + RTC::instance()->GetTimeString() + "\"" + "}";
    String data = "{\"type\": \"sensors\",\"data\": " + sensorDataJsonStr + "}";
    return data;
  }
  
  float GetSensor(int num)
  {
    float value = 0.0f;
    switch (num)
    {
    case 0: // 0:vpd, 1:soil, 2:par, 3:temp, 4:humi, 5:co2
      value = sensor.vpd;
      break;
    case 1:
      value = sensor.soil;
      break;
    case 2:
      value = sensor.temp;
      break;
    case 3:
      value = sensor.humi;
      break;
    case 4:
      value = sensor.co2;
      break;
    case 5:
      value = sensor.ec;
      break;
    case 6:
      value = sensor.ph;
      break;
    case 7:
      value = sensor.light;
      break;
    default:
      value = -1;
    }
    return value;
  }

private:
  sensor_s sensor;

  virtual bool OnStart()
  {

    return true;
  }
  virtual void OnUpdate(uint32_t delta_time)
  {
    // sensor.temp = GY21::instance()->GetTemperature();
    // sensor.humi = GY21::instance()->GetHumidity();
    // sensor.vpd = GY21::instance()->GetVpd();
    // sensor.ec = Solution::instance()->GetEC();
    // sensor.ph = Solution::instance()->GetpH();
    // sensor.co2 = Co2Sensor::instance()->GetCO2();
    // sensor.light = Light::instance()->GetLight();

    // #if defined(ARDUINO_ARCH_AVR)
    //   int increase = digitalRead(6);
    //   int decrease = digitalRead(7);

    //   float ival = 0.01;
    //   if(increase == HIGH){
    //     sensor.temp += ival;
    //     sensor.humi += ival;
    //     sensor.soil += ival;
    //     sensor.par += ival;
    //     sensor.vpd += ival;
    //   }
    //   if(decrease == HIGH){
    //     sensor.temp -= ival;
    //     sensor.humi -= ival;
    //     sensor.soil -= ival;
    //     sensor.par -= ival;
    //     sensor.vpd -= ival;
    //   }
    // #endif
  }
};
Sensor *Sensor::s_instance = 0;