#include "RainfallMain.h"
#include <wx/filedlg.h>
#include <fstream>

RainfallFrame::RainfallFrame()
    : wxFrame(NULL, wxID_ANY, "Rainfall Analyzer", wxDefaultPosition, wxSize(900,650))
{
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(40,40,55));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxGridSizer* grid = new wxGridSizer(7,2,5,5);

    wxString days[7] = {"Monday","Tuesday","Wednesday",
                        "Thursday","Friday","Saturday","Sunday"};

    for(int i=0;i<7;i++)
    {
        grid->Add(new wxStaticText(panel, wxID_ANY, days[i]));
        inputs[i] = new wxTextCtrl(panel, wxID_ANY);
        grid->Add(inputs[i]);
    }

    analyzeBtn = new wxButton(panel, wxID_ANY, "Analyze");
    saveBtn = new wxButton(panel, wxID_ANY, "Save CSV");

    mainSizer->Add(grid, 0, wxALL, 10);
    mainSizer->Add(analyzeBtn, 0, wxALL, 10);
    mainSizer->Add(saveBtn, 0, wxALL, 10);

    panel->SetSizer(mainSizer);

    analyzeBtn->Bind(wxEVT_BUTTON, &RainfallFrame::OnAnalyze, this);
    saveBtn->Bind(wxEVT_BUTTON, &RainfallFrame::OnSave, this);
    panel->Bind(wxEVT_PAINT, &RainfallFrame::OnPaint, this);
}

void RainfallFrame::OnAnalyze(wxCommandEvent& event)
{
    weekData.clear();
    double total = 0;

    for(int i=0;i<7;i++)
    {
        double value = 0;
        inputs[i]->GetValue().ToDouble(&value);
        weekData.push_back(value);
        total += value;
    }

    weeklyTotals.push_back(total);

    Refresh();  // redraw charts
}

void RainfallFrame::OnSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, "Save CSV", "", "",
                                "CSV files (*.csv)|*.csv",
                                wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    std::ofstream file(saveFileDialog.GetPath().ToStdString());

    file << "Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday\n";

    for(double val : weekData)
        file << val << ",";

    file << "\n";
    file.close();
}

void RainfallFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    if(weekData.empty())
        return;

    int baseY = 550;
    int barWidth = 40;

    dc.SetBrush(*wxBLUE_BRUSH);

    // Bar chart (current week)
    for(size_t i=0;i<weekData.size();i++)
    {
        int height = weekData[i] * 3;  // scale factor
        dc.DrawRectangle(60 + i*80, baseY - height, barWidth, height);
    }

    // Trend line (multiple weeks)
    dc.SetPen(wxPen(*wxRED, 2));

    for(size_t i=1;i<weeklyTotals.size();i++)
    {
        dc.DrawLine(60 + (i-1)*80,
                    200 - weeklyTotals[i-1],
                    60 + i*80,
                    200 - weeklyTotals[i]);
    }
}
