#include <Task.h>
extern TaskManager taskManager;
class Solution : public Task
{
  public:
    static Solution *s_instance;
    Solution() : Task(MsToTaskTime(100)){};
    static Solution *instance()
    {
      if (!s_instance)
      s_instance = new Solution;
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
Solution *Solution::s_instance = 0;