#include <wx/wx.h>
#include "RainfallMain.h"

class RainfallApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        RainfallFrame* frame = new RainfallFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(RainfallApp);
