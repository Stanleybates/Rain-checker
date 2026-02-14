#ifndef RAINFALLMAIN_H
#define RAINFALLMAIN_H

#include <wx/wx.h>
#include <vector>

class RainfallFrame : public wxFrame
{
public:
    RainfallFrame();

private:
    wxTextCtrl* inputs[7];
    wxButton* analyzeBtn;
    wxButton* saveBtn;

    std::vector<double> weekData;
    std::vector<double> weeklyTotals;

    void OnAnalyze(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
};

#endif
