#ifndef BUSDIALOG_H
#define BUSDIALOG_H

#include <FL/Fl_Tree.h>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Input.H>

#include <DialogWindow.h>
#include <FL/Fl_Select_Browser.H>
#include "Bus.h"
#include "StructData.h"

class BusDialog : public DialogWindow
{
    public:
        BusDialog(int x,int y, int w, int h, const char* t);
        virtual void ShowDialog(Fl_Tree_Item *item, unsigned int mode);
        virtual bool GetData(Bus *bus);
        virtual bool SetData(Bus *bus);
        virtual void ClearInputs();

        #ifdef DBG_FUNC
        void PrintBusData(Fl_Select_Browser *browser, const Fl_Tree_Item *bus);
        #endif // DBG_FUNC

    protected:

    private:
        Fl_Choice *BusType;
        Fl_Input *nameBus;
        Fl_Float_Input *baseKV;
        Fl_Float_Input *Pg;
        Fl_Float_Input *Qg;
        Fl_Float_Input *Pd;
        Fl_Float_Input *Qd;
        Fl_Float_Input *Gs;
        Fl_Float_Input *Bs;
        Fl_Float_Input *Vm;
        Fl_Float_Input *Va;
        Fl_Check_Button *Status;
};

#endif // BUSDIALOG_H
