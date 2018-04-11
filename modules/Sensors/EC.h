#include <Task.h>
extern TaskManager taskManager;
class EC : public Task
{
  public:
    static EC *s_instance;
    EC() : Task(MsToTaskTime(100)){};
    static EC *instance()
    {
      if (!s_instance)
      s_instance = new EC;
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
EC *EC::s_instance = 0;