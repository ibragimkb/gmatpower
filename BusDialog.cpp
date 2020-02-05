#include "BusDialog.h"
#include "DataIndex.h"

BusDialog::BusDialog(int x,int y, int w, int h, const char* t) : DialogWindow(x, y, w, h, t)
{
    //ctor
    int x1 = x + WIDGET_W * 0.75;
    int x2 = x + w * 0.5 + WIDGET_W;
    int y1 = y + WIDGET_BORDER;
    int widget_h = WIDGET_H + WIDGET_BORDER;

    nameBus = new Fl_Input(x1,y1,WIDGET_W,WIDGET_H, "Name:");
    nameBus->maximum_size(NAME_LENGTH);

    Status = new Fl_Check_Button(x2, y1, WIDGET_H, WIDGET_H, "status");
    Status->value(1);
    Status->visible_focus(0);

    baseKV = new Fl_Float_Input(x1,y1+widget_h,WIDGET_W,WIDGET_H, "Vbase:");
    //Vnom->align(FL_ALIGN_LEFT);
    baseKV->tooltip("kV");
    baseKV->maximum_size(INPUT_LENGTH);

    BusType = new Fl_Choice(x2,y1+widget_h,WIDGET_W,WIDGET_H, "Bus type:");
    BusType->add(Bus::get_type_bus_label(PQ));
    BusType->add(Bus::get_type_bus_label(PV));
    BusType->add(Bus::get_type_bus_label(REF));
    //BusType->value(-1);

    Vm = new Fl_Float_Input(x1,y1+2*widget_h+WIDGET_OFFSET, WIDGET_W, WIDGET_H, "Vm:");
    Va = new Fl_Float_Input(x1,y1+3*widget_h+WIDGET_OFFSET, WIDGET_W, WIDGET_H, "Va:");
    Vm->tooltip("p.u.");
    Va->tooltip("deg");

    Pg = new Fl_Float_Input(x1,y1+4*widget_h+2*WIDGET_OFFSET, WIDGET_W, WIDGET_H, "Pg:");
    Qg = new Fl_Float_Input(x1,y1+5*widget_h+2*WIDGET_OFFSET, WIDGET_W, WIDGET_H, "Qg:");

    Vm->maximum_size(INPUT_LENGTH);
    Va->maximum_size(INPUT_LENGTH);
    Pg->maximum_size(INPUT_LENGTH);
    Qg->maximum_size(INPUT_LENGTH);
    Pg->tooltip("MW");
    Qg->tooltip("MVAr");

    Gs = new Fl_Float_Input(x2,y1+2*widget_h+WIDGET_OFFSET,WIDGET_W,WIDGET_H, "Gs:");
    Bs = new Fl_Float_Input(x2,y1+3*widget_h+WIDGET_OFFSET,WIDGET_W,WIDGET_H, "Bs:");

    Pd = new Fl_Float_Input(x2,y1+4*widget_h+2*WIDGET_OFFSET,WIDGET_W,WIDGET_H, "Pd:");
    Qd = new Fl_Float_Input(x2,y1+5*widget_h+2*WIDGET_OFFSET,WIDGET_W,WIDGET_H, "Qd:");

    Gs->maximum_size(INPUT_LENGTH);
    Bs->maximum_size(INPUT_LENGTH);
    Pd->maximum_size(INPUT_LENGTH);
    Qd->maximum_size(INPUT_LENGTH);
    Gs->tooltip("MW");
    Bs->tooltip("MVAr");
    Pd->tooltip("MW");
    Qd->tooltip("MVAr");
    end();

    for (int i=0; i<children(); i++) {
        child(i)->labelfont(FL_COURIER);
        child(i)->labelsize(WIDGET_FONT_SIZE);
        //child(i)->textfont(FL_COURIER);
    }

    nameBus->textfont(FL_COURIER);
    baseKV->textfont(FL_COURIER);
    nameBus->textsize(WIDGET_FONT_SIZE);
    baseKV->textsize(WIDGET_FONT_SIZE);

    BusType->textfont(FL_COURIER);
    BusType->textsize(WIDGET_FONT_SIZE);

    Pg->textfont(FL_COURIER);
    Qg->textfont(FL_COURIER);
    Pg->textsize(WIDGET_FONT_SIZE);
    Qg->textsize(WIDGET_FONT_SIZE);

    Pd->textfont(FL_COURIER);
    Qd->textfont(FL_COURIER);
    Pd->textsize(WIDGET_FONT_SIZE);
    Qd->textsize(WIDGET_FONT_SIZE);

    Gs->textfont(FL_COURIER);
    Bs->textfont(FL_COURIER);
    Gs->textsize(WIDGET_FONT_SIZE);
    Bs->textsize(WIDGET_FONT_SIZE);

    Vm->textfont(FL_COURIER);
    Va->textfont(FL_COURIER);
    Vm->textsize(WIDGET_FONT_SIZE);
    Va->textsize(WIDGET_FONT_SIZE);

    set_modal();
    hide();
}

void BusDialog::ShowDialog(Fl_Tree_Item *item, unsigned int mode)
{
    SetMode(mode);
    ClearInputs();

    if (NULL != item) {
        Bus *busData = (Bus*)item->user_data();
        if (NULL != busData) {
            SetData(busData);
        }
        else {
            //!!error
        }
    }
    switch (mode) {
        case VIEW_MODE:
            SetTitle("View bus properties");
            break;
        case ADD_MODE:
            SetTitle("Add bus");
            break;
        case EDIT_MODE:
            SetTitle("Edit bus properties");
            break;
        default:
            break;
    }
    show();
}

bool BusDialog::GetData(Bus *bus)
{
    struct stBusData busData;
    if (BusType->value() == -1) return false;
    memset(&busData, 0, sizeof(struct stBusData ));

    strncpy(busData.nameBus, nameBus->value(), NAME_BUFFER_LENGTH);

    sscanf(baseKV->value(),"%lg",&busData.baseKV);
    if (0.0 == busData.baseKV) return false;
    sscanf(Pg->value(),"%lg",&busData.Pg);
    sscanf(Qg->value(),"%lg",&busData.Qg);
    sscanf(Vm->value(),"%lg",&busData.Vm);
    sscanf(Va->value(),"%lg",&busData.Va);
    sscanf(Gs->value(),"%lg",&busData.Gs);
    sscanf(Bs->value(),"%lg",&busData.Bs);
    sscanf(Pd->value(),"%lg",&busData.Pd);
    sscanf(Qd->value(),"%lg",&busData.Qd);
    busData.typebus = BusType->value();
    busData.status = Status->value();
    bus->setBusData(busData);

    return true;
}

bool BusDialog::SetData(Bus *bus)
{
    const struct stBusData *busData = bus->getBusData();
    if (busData->baseKV != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->baseKV);
        baseKV->value(buffer);
    }
    if (busData->Vm != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Vm);
        Vm->value(buffer);
    }
    if (busData->Va != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Va);
        Va->value(buffer);
    }

    if (busData->Pg != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Pg);
        Pg->value(buffer);
    }
    if (busData->Qg != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Qg);
        Qg->value(buffer);
    }

    if (busData->Gs != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Gs);
        Gs->value(buffer);
    }
    if (busData->Bs != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Bs);
        Bs->value(buffer);
    }

    if (busData->Pd != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Pd);
        Pd->value(buffer);
    }
    if (busData->Qd != 0.0) {
        snprintf(buffer, getBufLen(), "%.7g", busData->Qd);
        Qd->value(buffer);
    }

    nameBus->value(busData->nameBus);

    BusType->value(busData->typebus);
    Status->value(busData->status);
}

void BusDialog::ClearInputs()
{
    nameBus->value("");
    baseKV->value("");
    Vm->value("");
    Va->value("");
    Pg->value("");
    Qg->value("");
    Gs->value("");
    Bs->value("");
    Pd->value("");
    Qd->value("");
    BusType->value(-1);
    Status->value(1);
    baseKV->take_focus();
}

#ifdef DBG_FUNC
void BusDialog::PrintBusData(Fl_Select_Browser *browser, const Fl_Tree_Item *bus)
{
    struct stBusData *busData = (struct stBusData *)bus->user_data();

    browser->clear();
    snprintf(buffer, getBufLen(), "@fPrefences: '%s'", bus->label());
    browser->add(buffer);
    browser->add("");
    snprintf(buffer, getBufLen(), "@f Vbase = %.5g kV", busData->baseKV);
    browser->add(buffer);
    snprintf(buffer, getBufLen(), "@f V = %.5g p.u.", busData->Vm);
    browser->add(buffer);
    browser->add("");
    snprintf(buffer, getBufLen(), "@f Pg = %.5g MW", busData->Pg);
    browser->add(buffer);
    snprintf(buffer, getBufLen(), "@f Qg = %.5g MVAr", busData->Qg);
    browser->add(buffer);
    browser->add("");
    snprintf(buffer, getBufLen(), "@f Pd = %.5g MW", busData->Pd);
    browser->add(buffer);
    snprintf(buffer, getBufLen(), "@f Qd = %.5g MVAr", busData->Qd);
    browser->add(buffer);
}
#endif
