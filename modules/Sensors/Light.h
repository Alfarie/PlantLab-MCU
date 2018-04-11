#include <Task.h>
extern TaskManager taskManager;
class Light : public Task
{
  public:
    static Light *s_instance;
    Light() : Task(MsToTaskTime(100)){};
    static Light *instance()
    {
      if (!s_instance)
      s_instance = new Light;
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
Light *Light::s_instance = 0;