#include <string.h>
#include "Bus.h"
#include "DataIndex.h"

Bus::Bus()
{
    //ctor
    data = new stBusData;
}

Bus::~Bus()
{
    //dtor
    delete data;
}

void Bus::setBusData(struct stBusData busData)
{
    *data = busData;
}

const struct stBusData* Bus::getBusData()
{
    return data;
}

const char* Bus::get_name_bus()
{
    return data->nameBus;
}

void Bus::set_name_bus(const char* name)
{
    strncpy(data->nameBus, name, NAME_BUFFER_LENGTH);
}

int Bus::get_type_bus()
{
    return data->typebus;
}

char Bus::get_status()
{
    return data->status;
}

double Bus::get_baseKV()
{
    return data->baseKV;
}

int Bus::get_bus_i()
{
    return data->bus_i;
}

void Bus::set_bus_i(int i)
{
    data->bus_i = i;
}

double Bus::get_Pg()
{
    return data->Pg;
}

double Bus::get_Qg()
{
    return data->Qg;
}

double Bus::get_Pd()
{
    return data->Pd;
}

double Bus::get_Qd()
{
    return data->Qd;
}

double Bus::get_Gs()
{
    return data->Gs;
}

double Bus::get_Bs()
{
    return data->Bs;
}

double Bus::get_Vm()
{
    return data->Vm;
}

double Bus::get_Va()
{
    return data->Va;
}

const char* Bus::get_type_label()
{
    return get_type_bus_label(data->typebus + 1);
}

const char* Bus::get_type_bus_label(char typebus)
{
    switch (typebus)
    {
        case PQ:
            return "PQ";
        break;
        case PV:
            return "PV";
        break;
        case REF:
            return "REF";
        break;

        default:
            return "NONE";
        break;
    }
}
