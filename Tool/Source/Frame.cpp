#include "Frame.h"

Frame::Frame(wxWindow* parent, const wxPoint& position, const wxSize& size) : wxFrame(parent, wxID_ANY, wxT("Hog Archive Tool"), position, size)
{
}

/*virtual*/ Frame::~Frame()
{
}