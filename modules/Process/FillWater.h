#include <Task.h>
extern TaskManager taskManager;

class FillWater : public WaterProcess
{
public:
  FillWater(callback ns) : WaterProcess(1000, ns)
  {
    pinMode(FT_SENSOR, INPUT);
  };

  String GetStatus()
  {
    /*
      {
        type: water-fill,
        data: {
          crt: currentTime,
          max: 0
        }
      }
    */
    return "{ \"type\": \"waterprocess-fill\", \"data\":{ \"crt\": " + String(currentTime) + ", \"max\": 0 }}";
  }

private:
  float flotingTime = 0;
  virtual bool OnStart()
  {

    boolean ft_state = digitalRead(FT_SENSOR);
    currentTime = 0;
    flotingTime = 0;
    if (ft_state)
    {
      nextState("fill water");
      return false;
    }

    //testCom.println("isFill:" + String(waterProcess.isFill));
    if (!waterProcess.isFill)
    {
      nextState("fill water");
      return false;
    }

    DigitalWrite(5, CH_ON);
    return true;
  }
  virtual void OnUpdate(uint32_t delta_time)
  {

    currentTime += (delta_time / 1000.0);
    //testCom.println(currentTime);

    if (!waterProcess.isFill)
    {
      DigitalWrite(5, CH_OFF);
      flotingTime = 0;
      nextState("fill water");
      taskManager.StopTask(this);
    }
    else if (digitalRead(FT_SENSOR))
    {
      flotingTime += (delta_time / 1000.0);
      if (flotingTime >= 3.0)
      {
        DigitalWrite(5, CH_OFF);
        flotingTime = 0;
        nextState("fill water");
        taskManager.StopTask(this);
      }
    }
    else
    {
      flotingTime = 0;
    }
  }
};