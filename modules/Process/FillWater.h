#include <Task.h>
extern TaskManager taskManager;
#define FT_SENSOR A3
class FillWater : public WaterProcess
{
public:
  FillWater(callback ns) : WaterProcess(1000, ns)
  {
    pinMode(FT_SENSOR, INPUT);
  };

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
    return "{ \"type\": \"water-fill\", \"data\":{ \"crt\": " + String(currentTime) + ", \"max\": 0 }}" ;
  }

private:
  virtual bool OnStart()
  {

    boolean ft_state = digitalRead(FT_SENSOR);
    currentTime = 0;
    if(ft_state){
      nextState();
      return false;
    }

    testCom.println("isFill:" + String(waterProcess.isFill));
    if(!waterProcess.isFill){
      nextState();
      return false;
    }

    testCom.println("fill water: start");
    DigitalWrite(5, HIGH);
    return true;
  }
  virtual void OnUpdate(uint32_t delta_time)
  {
    if(digitalRead(FT_SENSOR)){
      currentTime += (delta_time/1000.0);
      if(currentTime >= 3.0){
        DigitalWrite(5, LOW);
        currentTime=0;

        nextState();
        taskManager.StopTask(this);
        
      }
    }
    else{
      currentTime = 0;
    }
  }

};