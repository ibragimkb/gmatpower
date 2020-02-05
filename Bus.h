#ifndef BUS_H
#define BUS_H

#include "StructData.h"
class Bus
{
    public:
        Bus();
        ~Bus();
        void setBusData(struct stBusData busData);
        const struct stBusData* getBusData();
        const char* get_name_bus();
        void set_name_bus(const char* name);
        int get_type_bus();
        char get_status();
        double get_baseKV();
        int get_bus_i();
        void set_bus_i(int i);

        double get_Pg();
        double get_Qg();
        double get_Pd();
        double get_Qd();
        double get_Gs();
        double get_Bs();
        double get_Vm();
        double get_Va();
        const char* get_type_label();
        static const char* get_type_bus_label(char typebus);


    protected:
        struct stBusData *data;

    private:
};

#endif // BUS_H
