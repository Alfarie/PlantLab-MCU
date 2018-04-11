#include <Task.h>
extern TaskManager taskManager;
class CO2 : public Task
{
  public:
    static CO2 *s_instance;
    CO2() : Task(MsToTaskTime(100)){};
    static CO2 *instance()
    {
      if (!s_instance)
      s_instance = new CO2;
      return s_instance;
    }

  private:
    virtual bool OnStart()
    {
        return true;
    }
    virtual void OnUpdate(uint32_t delta_time)
    {
        
    }
};
CO2 *CO2::s_instance = 0;