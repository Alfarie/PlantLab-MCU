#include <Task.h>

extern TaskManager taskManager;
class Timer : public Control
{
  public:
    Timer(int ch) : Control(1000,ch){
      UpdateFromRom();
    };

    void SaveValue(timer_s *t, int s,int m )
    {
      ArrayTimerCopy(timer_list, t,s);
      size = s;
      mode = m;
      SaveToRom();
    }
  private:
    timer_s timer_list[8];
    byte size;
    byte mode;
    virtual bool OnStart()
    {
      DigitalWrite(channel - 1, CH_OFF);
      return true;
    }
    // datetime,22,2,2018,14,21}
    virtual void OnUpdate(uint32_t delta_time)
    {
      int currentMin = RTC::instance()->GetCurrentMin();
       debugCom.print("Timer    is running " + String(channel) + " " + String(mode) + " " + String(size)) + " " + String(currentMin);;
       debugCom.print(" [");
       for(int i = 0 ; i < size; i++)
       {
         debugCom.print( String(timer_list[i].st) + "-" + String(timer_list[i].en) + ",");
       }
       debugCom.println("] ");
     
      bool flag = false;
      for(int i = 0 ; i < size; i++){
        if(currentMin >= timer_list[i].st && currentMin <= timer_list[i].en){
          flag = true;
          break;
        }
      }
      if(flag){
        // ChannelHanler::SetChannelStatus( channel - 1, HIGH);
        DigitalWrite(channel - 1, CH_ON);
        // debugCom.println(" CH_ON ");
      }
      else {
        // ChannelHanler::SetChannelStatus( channel - 1, LOW);
        DigitalWrite(channel - 1, CH_OFF);
        // debugCom.println(" CH_OFF ");
      }
    }

    void ArrayTimerCopy(timer_s *from, timer_s *to, int size)
    {
      int i = 0 ;
      for( i = 0 ; i < size ; i++){
        to[i] = from[i];
      }
    }

    void UpdateFromRom()
    {
      ArrayTimerCopy(rom_channel[channel-1].timer.timer_list, timer_list, rom_channel[channel-1].timer.size);
      mode = rom_channel[channel-1].timer.mode;
      size = rom_channel[channel-1].timer.size;
    }

    void SaveToRom()
    {
      ArrayTimerCopy(timer_list, rom_channel[channel-1].timer.timer_list, rom_channel[channel-1].timer.size);
      rom_channel[channel-1].timer.mode = mode;
      rom_channel[channel-1].timer.size = size;
    }

};