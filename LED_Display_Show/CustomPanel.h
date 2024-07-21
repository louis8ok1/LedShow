#ifndef CustomPanelH
#define CustomPanelH

#include <System.Classes.hpp>
#include <Vcl.ExtCtrls.hpp>

class TLEDPanel : public TPanel
{
protected:
    virtual void __fastcall Paint();
    DYNAMIC void __fastcall Resize();
public:
    __fastcall TLEDPanel(TComponent* Owner);
    String DisplayText;
    int ScrollOffset;
    TSize GetTextExtent(const String &text);
};

#endif
