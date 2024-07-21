#include <vcl.h>
#pragma hdrstop

#include "CustomPanel.h"

#pragma package(smart_init)

__fastcall TLEDPanel::TLEDPanel(TComponent* Owner) : TPanel(Owner)
{
    DisplayText = "";
    ScrollOffset = 0;
}

void __fastcall TLEDPanel::Paint()
{
    TPanel::Paint();  // 直接調用基類的 Paint 方法

    TCanvas *canvas = Canvas;
    TRect clientRect = ClientRect;

    canvas->Brush->Color = Color;
    canvas->FillRect(clientRect);

    canvas->Font->Assign(Font);

    canvas->TextOut(ScrollOffset, (clientRect.Height() - canvas->TextHeight(DisplayText)) / 2, DisplayText);

    canvas->Pen->Color = clGray;
    canvas->Pen->Width = 2;
    canvas->Rectangle(clientRect);
}

void __fastcall TLEDPanel::Resize()
{
    TPanel::Resize();
    Invalidate();
}

TSize TLEDPanel::GetTextExtent(const String &text)
{
    return Canvas->TextExtent(text);
}
