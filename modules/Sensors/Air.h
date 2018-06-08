#include <Task.h>
extern TaskManager taskManager;
class Air : public Task
{
  public:
    static Air *s_instance;
    Air() : Task(MsToTaskTime(1000)) {}
    static Air *instance()
    {
        if (!s_instance)
            s_instance = new Air;
        return s_instance;
    }

  private:
    virtual bool OnStart()
    {
        return true;
    }
    virtual void OnUpdate(uint32_t delta_time) {}
};
Air *Air::s_instance = 0;