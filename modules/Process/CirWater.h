#include <Task.h>
extern TaskManager taskManager;
class CirWater : public WaterProcess
{
public:
  CirWater(callback ns) : WaterProcess(1000, ns){};

  String GetStatus(){
    /*
      {
        type: water-fill,
        data: {
          crt: currentTime,
          max: 0
        }
      }
    */
    return "{ \"type\": \"water-cir\", \"data\":{ \"crt\": " + String(currentTime) + ", \"max\": "+ String(waterProcess.cirTime) +" }}" ;
  }

private:
  virtual bool OnStart()
  {
    if (!waterProcess.isCir)
    {
      nextState();
      return false;
    }
    testCom.println("cir water: start");
    currentTime = 0;
    DigitalWrite(4, HIGH);
    return true;
  }
  virtual void OnUpdate(uint32_t delta_time)
  {
    currentTime += (delta_time / 1000.0);
    if (currentTime >= waterProcess.cirTime)
    {
      currentTime = 0;
      DigitalWrite(4, LOW);
      nextState();
      taskManager.StopTask(this);
    }
  }
};