#include <vcl.h>
#pragma hdrstop
#include "LEDDisplayForm.h"
#include <System.IOUtils.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"

TLEDDisplay_Form *LEDDisplay_Form;
 __fastcall TLEDDisplay_Form::TLEDDisplay_Form(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TLEDDisplay_Form::FormCreate(TObject *Sender)
{
    IdTCPServer->DefaultPort = 8080;
    IdTCPServer->Active = true;
    this->BorderStyle = bsNone;
    this->Top = 0;
    this->Left = 0;
	this->Width = 384;
	this->Height = 96;

	PaintBox->Color = clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TLEDDisplay_Form::IdTCPServerExecute(TIdContext *AContext)
{
   try
	{
        String message = AContext->Connection->IOHandler->ReadLn(IndyTextEncoding_UTF8());
        TThread::Synchronize(nullptr, [this, message](){ DisplayMessage(message); });
    }
    catch (Exception &e)
    {
        // Handle exceptions
	}
}
//---------------------------------------------------------------------------
 void __fastcall TLEDDisplay_Form::DisplayMessage(String message)
{
    ReceivedData = message;
    PaintBox->Repaint();
}

void __fastcall TLEDDisplay_Form::FormPaint(TObject *Sender)
{
	  // 设置背景色
    TRect rect = PaintBox->ClientRect;
    PaintBox->Canvas->Brush->Color = clBlack;
    PaintBox->Canvas->FillRect(rect);

    // 设置字体
    PaintBox->Canvas->Font->Name = "Arial";  // 选择适合的字体
    PaintBox->Canvas->Font->Size = 24;       // 放大字体
    PaintBox->Canvas->Font->Color = clLime;  // 设置字体颜色为绿色，模拟LED效果

    // 绘制文本
	PaintBox->Canvas->TextOut(10, 10, ReceivedData);
}
