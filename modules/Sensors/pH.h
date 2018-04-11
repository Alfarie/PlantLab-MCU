#include <Task.h>
extern TaskManager taskManager;
class pH : public Task
{
  public:
    static pH *s_instance;
    pH() : Task(MsToTaskTime(100)){};
    static pH *instance()
    {
      if (!s_instance)
      s_instance = new pH;
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
pH *pH::s_instance = 0;