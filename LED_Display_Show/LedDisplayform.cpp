//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LedDisplayform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLEDDisplay_Form *LEDDisplay_Form;
//---------------------------------------------------------------------------


__fastcall TLEDDisplay_Form::TLEDDisplay_Form(TComponent* Owner)
    : TForm(Owner), ScrollOffset(0)
{
    BufferBitmap = std::make_unique<Graphics::TBitmap>();
}
//---------------------------------------------------------------------------
void __fastcall TLEDDisplay_Form::FormCreate(TObject *Sender)
{
	IdTCPServer->DefaultPort = 8080;
    IdTCPServer->Active = true;

    Timer1->Interval = 50; // 50毫秒更新一次
    Timer1->Enabled = true;

    BufferBitmap->Width = PaintBox1->Width;
    BufferBitmap->Height = PaintBox1->Height;

    // 初始化顯示文字
    DisplayText = "歡迎使用 LED 顯示屏";
	UpdateBufferBitmap();
}
//---------------------------------------------------------------------------
void __fastcall TLEDDisplay_Form::PaintBox1Paint(TObject *Sender)
{
	if (BufferBitmap)
    {
		PaintBox1->Canvas->Draw(0, 0, BufferBitmap.get());
	}
}
//---------------------------------------------------------------------------
void TLEDDisplay_Form::UpdateDisplay(const String &text)
{
	DisplayText = text;
    ScrollOffset = PaintBox1->Width; // 從右邊開始
	 UpdateBufferBitmap();
}
void TLEDDisplay_Form::UpdateBufferBitmap()
{
    ShowMessage("Updating buffer: " + DisplayText);
if (!BufferBitmap)
        return;

    TCanvas *canvas = BufferBitmap->Canvas;
    TRect clientRect = Rect(0, 0, BufferBitmap->Width, BufferBitmap->Height);

    // 設置背景
    canvas->Brush->Color = clBlack;
    canvas->FillRect(clientRect);

    // 設置字體
    canvas->Font->Name = "Arial";
    canvas->Font->Size = 24;
    canvas->Font->Color = clRed;

    // 繪製文字
    canvas->TextOut(ScrollOffset, (clientRect.Height() - canvas->TextHeight(DisplayText)) / 2, DisplayText);

    // 繪製 LED 邊框效果
    canvas->Pen->Color = clGray;
    canvas->Pen->Width = 2;
    canvas->Rectangle(clientRect);

    // 強制重繪
	PaintBox1->Invalidate();
}
//----------------------------------------------------------------------
void __fastcall TLEDDisplay_Form::IdTCPServerExecute(TIdContext *AContext)
{
	try
	{
		String data = AContext->Connection->IOHandler->ReadLn(IndyTextEncoding_UTF8());
		TThread::Queue(NULL, [this, data]() {
			UpdateDisplay(data);
		});
    }
    catch (Exception &e)
    {
        ShowMessage("接收數據錯誤：" + e.Message);
	}
}
//---------------------------------------------------------------------------
void TLEDDisplay_Form::SyncUpdateDisplay(TObject *Sender)
{
    UpdateDisplay(ReceivedData);
}
void __fastcall TLEDDisplay_Form::Timer1Timer(TObject *Sender)
{
 ScrollOffset -= 5; // 每次移動5個像素

    TSize textSize = BufferBitmap->Canvas->TextExtent(DisplayText);
	if (ScrollOffset < -textSize.cx)
	{
        ScrollOffset = PaintBox1->Width;
	}

	UpdateBufferBitmap();
}
//---------------------------------------------------------------------------

void __fastcall TLEDDisplay_Form::FormClose(TObject *Sender, TCloseAction &Action)

{
      if (IdTCPServer->Active)
    {
        IdTCPServer->Active = false;
    }
    if (Timer1->Enabled)
    {
        Timer1->Enabled = false;
    }
	Sleep(100);
}
//---------------------------------------------------------------------------

