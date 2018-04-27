#include <Task.h>
#include <Wire.h>
extern TaskManager taskManager;

#include "RTClib.h"
#define ADDRESS 0x68
RTC_Millis rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

class RTC : public Task
{
  public:
    static RTC *s_instance;
    RTC() : Task(MsToTaskTime(1000)){};
    
    static RTC *instance()
    {
        if (!s_instance)
            s_instance = new RTC;
        return s_instance;
    }

    int GetCurrentMin()
    {
        int min = (now.hour() * 60) + now.minute();
        return min;
    }

    String GetDateString()
    {

        String str = String(now.year()) + "-" +
                     AddZero(now.month()) + String(now.month()) + "-" +
                     AddZero(now.day()) + String(now.day());
        return str;
    }

    String GetTimeString()
    {
        String str = AddZero(now.hour()) + String(now.hour()) + ":" +
                     AddZero(now.minute()) + String(now.minute()) + ":" +
                     AddZero(now.second()) + String(now.second());
        return str;
    }

    void setDateDs1307(byte s, byte m, byte h, byte dow, byte dom, byte mo, byte y)
    {
        // Wire.beginTransmission(ADDRESS);
        // Wire.write(decToBcd(0));
        // Wire.write(decToBcd(s)); // 0 to bit 7 starts the clock
        // Wire.write(decToBcd(m));
        // Wire.write(decToBcd(h)); // If you want 12 hour am/pm you need to set
        // // bit 6 (also need to change readDateDs1307)
        // Wire.write(decToBcd(dow));
        // Wire.write(decToBcd(dom));
        // Wire.write(decToBcd(mo));
        // Wire.write(decToBcd(y));
        // Wire.endTransmission();
        
        rtc.adjust(DateTime(y, mo,dom, h, m, s));
    }

  private:
    DateTime now;
    virtual bool OnStart()
    {
        
        // Wire.beginTransmission(ADDRESS);
        // Wire.write(decToBcd(0));
        // Wire.endTransmission();
        // Wire.requestFrom(ADDRESS, 7);

        // byte second = bcdToDec(Wire.read() & 0x7f);
        // byte minute = bcdToDec(Wire.read());
        // byte hour = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
        // byte dayOfWeek = bcdToDec(Wire.read());
        // byte day = bcdToDec(Wire.read());
        // byte month = bcdToDec(Wire.read());
        // byte year = bcdToDec(Wire.read());

        rtc.begin( DateTime(__DATE__, __TIME__) );
        return true;
    }
    virtual void OnUpdate(uint32_t delta_time)
    {
        now = rtc.now();
        //debugCom.println(GetTimeString() + " " + GetDateString() + "-------------------------");
    }
    String AddZero(byte val)
    {
        if (val < 10)
        {
            return "0";
        }
        else
            return "";
    }
    byte decToBcd(byte val)
    {
        return ((val / 10 * 16) + (val % 10));
    }
    byte bcdToDec(byte val)
    {
        return ((val / 16 * 10) + (val % 16));
    }
};
RTC *RTC::s_instance = 0;