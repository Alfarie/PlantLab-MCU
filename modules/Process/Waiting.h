#include <Task.h>
extern TaskManager taskManager;
class Waiting : public WaterProcess
{
public:
  Waiting(callback ns) : WaterProcess(1000, ns){};
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
    return "{ \"type\": \"water-waiting\", \"data\":{ \"crt\": " + String(currentTime) + ", \"max\": "+ String(waterProcess.waitingTime) +" }}" ;
  }
private:
  virtual bool OnStart()
  {
    testCom.println("waiting water: start");
    currentTime = 0;
    DigitalWrite(5, OFF);
    DigitalWrite(6, OFF);
    return true;
  }
  virtual void OnUpdate(uint32_t delta_time)
  {
    currentTime += (delta_time / 1000.0);
    if (currentTime > waterProcess.waitingTime)
    {
      currentTime = 0;
      
      if (waterProcess.isFill || waterProcess.isCir)
      {
        nextState();
        taskManager.StopTask(this);
      }
    }
  }
};