#pragma once

#include <wx/frame.h>

/**
 * 
 */
class Frame : public wxFrame
{
public:
	Frame(wxWindow* parent, const wxPoint& position, const wxSize& size);
	virtual ~Frame();

private:
};