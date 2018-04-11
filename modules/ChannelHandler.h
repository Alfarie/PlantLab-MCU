#include <Task.h>
extern TaskManager taskManager;
class ChannelHanler : public Task
{
  public:
    static ChannelHanler *s_instance;

    ChannelHanler() : Task(MsToTaskTime(100))
    {
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {
            pinMode(ChannelGpio[i], OUTPUT);
        }
        Init();
    };
    static ChannelHanler *instance()
    {
        if (!s_instance)
            s_instance = new ChannelHanler;
        return s_instance;
    }

    void Update(int ch)
    {
        taskManager.StopTask(channel[ch - 1]);
        int mode = rom_channel[ch - 1].mode;
        switch (mode)
        {
        case 0:
            channel[ch - 1] = ControlFactory::instance("manual", ch);
            taskManager.StartTask(channel[ch - 1]);
            break;
        case 1:
            channel[ch - 1] = ControlFactory::instance("timer", ch);
            taskManager.StartTask(channel[ch - 1]);
            break;
        case 2:
            channel[ch - 1] = ControlFactory::instance("setpoint", ch);
            taskManager.StartTask(channel[ch - 1]);
            break;
        case 3:
            channel[ch - 1] = ControlFactory::instance("setbound", ch);
            taskManager.StartTask(channel[ch - 1]);
            break;
        case 4:
            channel[ch - 1] = ControlFactory::instance("irrigation", ch);
            taskManager.StartTask(channel[ch - 1]);
            break;
        default:
            DisplayLog::PrintError("ChannelHandler: Unknow channel mode " + String(mode));
        }
    }

    static String JsonChannelStatus()
    {
        /*
            [
                {
                    status: 0,1
                    mode: [0,5],
                    sensor: rom_channel[i].sensor
                }
            ]
        */
        String ch[CHANNEL_NUMBER];
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {
            ch[i] = "{ \"status\": " + String(ChannelStatus[i]) + "," +
                    "\"mode\": " + String(rom_channel[i].mode) + "," +
                    "\"sensor\": " + String(rom_channel[i].sensor) + "}";
        }
        String chstr = "";
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {
            chstr += ch[0];
            if(i != CHANNEL_NUMBER -1) chstr += ",";
        }
        return "{\"type\": \"channel-status\",\"data\": [" + chstr + "]}";
    }

    String JsonManual()
    {
        String ch[CHANNEL_NUMBER];
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {
            String data = "\"manual\":{ \"status\":" + String(rom_channel[i].manual.status) + "}";
            ch[i] = "{ \"ch\":" + String(i + 1) + ", \"mode\":" + String(rom_channel[i].mode) + ",\"sensor\":" + String(rom_channel[i].sensor) + "," + data + "}";
        }
        return "{\"type\": \"control-manual\",\"data\": [" + ch[0] + "," + ch[1] + "," + ch[2] + "," + ch[3] + "]}";
    }
    String JsonSetpoint()
    {
        String ch[CHANNEL_NUMBER];
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {

            String data = "\"setpoint\": { \"working\":" + String(rom_channel[i].setpoint.working) + ",\"setpoint\":" + String(rom_channel[i].setpoint.setpoint) + ",\"detecting\":" + String(rom_channel[i].setpoint.detecting) + "}";
            ch[i] = "{ \"ch\":" + String(i + 1) + ", \"mode\":" + String(rom_channel[i].mode) + ",\"sensor\":" + String(rom_channel[i].sensor) + "," + data + "}";
        }
        return "{\"type\": \"control-setpoint\",\"data\": [" + ch[0] + "," + ch[1] + "," + ch[2] + "," + ch[3] + "]}";
    }

    String JsonSetbound()
    {
        String ch[CHANNEL_NUMBER];
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {
            String data = "\"setbound\": { \"upper\":" + String(rom_channel[i].setbound.upper) + ",\"lower\":" + String(rom_channel[i].setbound.lower) + "}";
            ch[i] = "{ \"ch\":" + String(i + 1) + ", \"mode\":" + String(rom_channel[i].mode) + ",\"sensor\":" + String(rom_channel[i].sensor) + "," + data + "}";
        }
        return "{\"type\": \"control-setbound\",\"data\": [" + ch[0] + "," + ch[1] + "," + ch[2] + "," + ch[3] + "]}";
    }

    String JsonIrrigation()
    {
        String ch[CHANNEL_NUMBER];
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {
            String data = "\"irrigation\":{ \"soil_upper\": " + String(rom_channel[i].irrigation.soil_upper) + ",\"soil_lower\":" + String(rom_channel[i].irrigation.soil_lower) + ",\"par_accum\":" + String(rom_channel[i].irrigation.par_accum) + ",\"mode\": " + String(rom_channel[i].irrigation.mode) + ",\"working\": " + String(rom_channel[i].irrigation.working) + "}";
            ch[i] = "{ \"ch\":" + String(i + 1) + ", \"mode\":" + String(rom_channel[i].mode) + ",\"sensor\":" + String(rom_channel[i].sensor) + "," + data + "}";
        }
        return "{\"type\": \"control-irrigation\",\"data\": [" + ch[0] + "," + ch[1] + "," + ch[2] + "," + ch[3] + "]}";
    }

    String JsonTimer()
    {
        String ch[CHANNEL_NUMBER];
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {
            String timer_list = "[";
            for (int j = 0; j < rom_channel[i].timer.size; j++)
            {
                String timer = "[" + String(rom_channel[i].timer.timer_list[j].st) + "," + String(rom_channel[i].timer.timer_list[j].en) + "]";
                timer_list += timer;
                if (j != (rom_channel[i].timer.size - 1))
                {
                    timer_list += ",";
                }
            }
            timer_list += "]";
            // data = "{\"mode\": 1,\"timer_mode\":" + String(rom_channel[i].timer.mode) +
            //         ",\"timer_list\":" + timer_list + "}";
            String data = "\"timer\": { \"mode\":" + String(rom_channel[i].timer.mode) + ",\"size\":" + String(rom_channel[i].timer.size) + ",\"list\":" + timer_list + "}";
            ch[i] = "{ \"ch\":" + String(i + 1) + ", \"mode\":" + String(rom_channel[i].mode) + ",\"sensor\":" + String(rom_channel[i].sensor) + "," + data + "}";
        }
        return "{\"type\": \"control-timer\",\"data\": [" + ch[0] + "," + ch[1] + "," + ch[2] + "," + ch[3] + "]}";
    }

    String JsonControl()
    {
        String ch[CHANNEL_NUMBER];
        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {

            String data;
            if (rom_channel[i].mode == 0)
            {
                // data = "{\"mode\": 0,\"gpio_status\":" + String(rom_channel[i].manual.status) + "}";
                data = "\"manual\":{ \"status\":" + String(rom_channel[i].manual.status) + "}";
            }
            else if (rom_channel[i].mode == 1)
            {
                String timer_list = "[";
                for (int j = 0; j < rom_channel[i].timer.size; j++)
                {
                    String timer = "[" + String(rom_channel[i].timer.timer_list[j].st) + "," + String(rom_channel[i].timer.timer_list[j].en) + "]";
                    timer_list += timer;
                    if (j != (rom_channel[i].timer.size - 1))
                    {
                        timer_list += ",";
                    }
                }
                timer_list += "]";
                // data = "{\"mode\": 1,\"timer_mode\":" + String(rom_channel[i].timer.mode) +
                //         ",\"timer_list\":" + timer_list + "}";
                data = "\"timer\": { \"mode\":" + String(rom_channel[i].timer.mode) + ",\"size\":" + String(rom_channel[i].timer.size) + ",\"list\":" + timer_list + "}";
            }
            else if (rom_channel[i].mode == 2)
            {
                // data = "{\"mode\": 2,\"setpoint\":" + String(rom_channel[i].setpoint.setpoint) +
                //         ",\"detecting\":" + String(rom_channel[i].setpoint.detecting) +
                //         ",\"working\":" + String(rom_channel[i].setpoint.working) +
                //         ",\"sensor\":" + String(rom_channel[i].sensor) + "}";
                data = "\"setpoint\": { \"working\":" + String(rom_channel[i].setpoint.working) + ",\"setpoint\":" + String(rom_channel[i].setpoint.setpoint) + ",\"detecting\":" + String(rom_channel[i].setpoint.detecting) + "}";
            }
            else if (rom_channel[i].mode == 3)
            {
                data = "\"setbound\": { \"upper\":" + String(rom_channel[i].setbound.upper) + ",\"lower\":" + String(rom_channel[i].setbound.lower) + "}";
            }
            else if (rom_channel[i].mode == 4)
            {
                // data = "{\"mode\": 2,\"soil_upper\":" + String(rom_channel[i].irrigation.soil_upper) +
                //         ",\"soil_lower\":" + String(rom_channel[i].irrigation.soil_lower) +
                //         ",\"par_accum\":" + String(rom_channel[i].irrigation.par_accum) +
                //         ",\"mode\":" + String(rom_channel[i].irrigation.mode) + "}";

                data = "\"irrigation\":{ \"soil_upper\": " + String(rom_channel[i].irrigation.soil_upper) + ",\"soil_lower\":" + String(rom_channel[i].irrigation.soil_lower) + ",\"par_accum\":" + String(rom_channel[i].irrigation.par_accum) + ",\"mode\": " + String(rom_channel[i].irrigation.mode) + ",\"working\": " + String(rom_channel[i].irrigation.working) +"}";
            }
            ch[i] = "{ \"ch\":" + String(i + 1) + ", \"mode\":" + String(rom_channel[i].mode) + ",\"sensor\":" + String(rom_channel[i].sensor) + "," + data + "}";
        }
        String jsonControl = "{\"type\": \"control\",\"data\": [" + ch[0] + "," + ch[1] + "," + ch[2] + "," + ch[3] + "]}";
        return jsonControl;
    }

   

  private:
    void Init()
    {
        int i = 0;
        for (i = 0; i < CHANNEL_NUMBER; i++)
        {
            int mode = rom_channel[i].mode;
            switch (mode)
            {
            case 0:
                channel[i] = ControlFactory::instance("manual", (i + 1));
                taskManager.StartTask(channel[i]);
                break;
            case 1:
                channel[i] = ControlFactory::instance("timer", (i + 1));
                taskManager.StartTask(channel[i]);
                break;
            case 2:
                channel[i] = ControlFactory::instance("setpoint", (i + 1));
                taskManager.StartTask(channel[i]);
                break;
            case 3:
                channel[i] = ControlFactory::instance("setbound", (i + 1));
                taskManager.StartTask(channel[i]);
                break;
            case 4:
                channel[i] = ControlFactory::instance("irrigation", (i + 1));
                taskManager.StartTask(channel[i]);
                break;
            default:
                DisplayLog::PrintError("ChannelHandler: Unknow channel mode " + String(mode));
            }
        }
    }
    virtual bool OnStart()
    {

        return true;
    }
    virtual void OnUpdate(uint32_t delta_time)
    {
    }
};
ChannelHanler *ChannelHanler::s_instance = 0;
