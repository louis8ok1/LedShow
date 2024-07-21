//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_Form.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <algorithm>
#include <vcl.h>
#include <windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    IdTCPClient->Host = "127.0.0.1";
	IdTCPClient->Port = 8080;


	for (int i = 1; i <= 9; ++i) {
		SpeedComboBox->Items->Add(IntToStr(i));
	}


	SpeedComboBox->ItemIndex = 9;


	PopulateFontComboBox();

	//DIY
	CellSize = 32; // 设置单元格大小
    RedLinePosition = ((PaintBox->Height / CellSize) / 2) * CellSize;
    GreenLine1Position = ((PaintBox->Width / CellSize) / 3) * CellSize;
	GreenLine2Position = ((PaintBox->Width / CellSize) * 2 / 3) * CellSize;

     BufferBitmap = new TBitmap();
    BufferBitmap->Width = PaintBox->Width;
    BufferBitmap->Height = PaintBox->Height;

    // 确保线条位置不超出 PaintBox 边界
	RedLinePosition = std::min(RedLinePosition, PaintBox->Height - CellSize);
	GreenLine1Position = std::min(GreenLine1Position, PaintBox->Width - CellSize);
	GreenLine2Position = std::min(GreenLine2Position, PaintBox->Width - CellSize);

    IsDraggingRed = false;
    IsDraggingGreen1 = false;
	IsDraggingGreen2 = false;

	// 设置 PaintBox 的事件
	PaintBox->OnPaint = GridPaintBoxPaint;
	PaintBox->OnMouseDown = GridPaintBoxMouseDown;
	PaintBox->OnMouseMove = GridPaintBoxMouseMove;
	PaintBox->OnMouseUp = GridPaintBoxMouseUp;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GridPaintBoxPaint(TObject *Sender)
{
   TCanvas *canvas = BufferBitmap->Canvas;
    int width = PaintBox->Width;
    int height = PaintBox->Height;

    // 设置背景为黑色
    canvas->Brush->Color = clBlack;
    canvas->FillRect(TRect(0, 0, width, height));

    // 绘制背景格子
    canvas->Pen->Color = clGray;
    canvas->Pen->Width = 1;

    // 计算需要绘制的行数和列数
    int columns = (width + CellSize - 1) / CellSize;
    int rows = (height + CellSize - 1) / CellSize;

    // 绘制垂直线
    for (int i = 0; i <= columns; i++) {
        int x = i * CellSize;
        canvas->MoveTo(x, 0);
        canvas->LineTo(x, height);
    }

    // 绘制水平线
    for (int i = 0; i <= rows; i++) {
        int y = i * CellSize;
        canvas->MoveTo(0, y);
        canvas->LineTo(width, y);
    }

    // 绘制水平红线
    canvas->Pen->Width = 2;
    canvas->Pen->Color = clRed;
    int redY = IsDraggingRed ? TempRedPosition : RedLinePosition;
    canvas->MoveTo(0, redY);
    canvas->LineTo(width, redY);

    // 绘制两条垂直绿线
    canvas->Pen->Color = clGreen;
    int green1X = IsDraggingGreen1 ? TempGreen1Position : GreenLine1Position;
    canvas->MoveTo(green1X, 0);
    canvas->LineTo(green1X, height);
    int green2X = IsDraggingGreen2 ? TempGreen2Position : GreenLine2Position;
    canvas->MoveTo(green2X, 0);
    canvas->LineTo(green2X, height);

    // 将缓冲位图绘制到 PaintBox
	PaintBox->Canvas->Draw(0, 0, BufferBitmap);
}
void __fastcall TMainForm::GridPaintBoxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft) {
        if (abs(Y - RedLinePosition) <= 5) {
            IsDraggingRed = true;
            TempRedPosition = RedLinePosition;
        } else if (abs(X - GreenLine1Position) <= 5) {
            IsDraggingGreen1 = true;
            TempGreen1Position = GreenLine1Position;
        } else if (abs(X - GreenLine2Position) <= 5) {
            IsDraggingGreen2 = true;
            TempGreen2Position = GreenLine2Position;
        }
	}
}

void __fastcall TMainForm::GridPaintBoxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	bool needsUpdate = false;
    int newPosition;

    if (IsDraggingRed) {
        newPosition = (Y / CellSize) * CellSize;
        if (newPosition >= 0 && newPosition <= PaintBox->Height - CellSize && newPosition != TempRedPosition) {
            TempRedPosition = newPosition;
            needsUpdate = true;
        }
    } else if (IsDraggingGreen1) {
        newPosition = (X / CellSize) * CellSize;
        if (newPosition >= 0 && newPosition <= PaintBox->Width - CellSize && newPosition != TempGreen1Position) {
            TempGreen1Position = newPosition;
            needsUpdate = true;
        }
    } else if (IsDraggingGreen2) {
        newPosition = (X / CellSize) * CellSize;
        if (newPosition >= 0 && newPosition <= PaintBox->Width - CellSize && newPosition != TempGreen2Position) {
            TempGreen2Position = newPosition;
            needsUpdate = true;
        }
    }

    if (needsUpdate) {
        PaintBox->Invalidate();  // 重绘整个 PaintBox
	}
}
void __fastcall TMainForm::GridPaintBoxMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (IsDraggingRed) {
        RedLinePosition = TempRedPosition;
    } else if (IsDraggingGreen1) {
        GreenLine1Position = TempGreen1Position;
    } else if (IsDraggingGreen2) {
        GreenLine2Position = TempGreen2Position;
    }

    IsDraggingRed = false;
    IsDraggingGreen1 = false;
    IsDraggingGreen2 = false;
	PaintBox->Invalidate();
}


void __fastcall TMainForm::SendButtonClick(TObject *Sender)
{


	SendDataToDisplay();

    String selectedSpeedStr = SpeedComboBox->Text;
    int speed = StrToIntDef(selectedSpeedStr, 9);

	SendSpeedToDisplay(speed);
}
//---------------------------------------------------------------------------
void TMainForm::SendDataToDisplay()
{
 	try
    {
        if (!IdTCPClient->Connected())
        {
            IdTCPClient->Host = "127.0.0.1";
            IdTCPClient->Port = 8080;
            IdTCPClient->Connect();
        }
        String data = Edit_One->Text;
        IdTCPClient->IOHandler->WriteLn(data, IndyTextEncoding_UTF8());
    }
    catch (Exception &e)
    {
        ShowMessage("连接错误：" + e.Message);
	}
}
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (IdTCPClient->Connected())
    {
        IdTCPClient->Disconnect();
    }
}
//---------------------------------------------------------------------------
 void __fastcall TMainForm::SendFontToDisplay(String font)
{
    try
    {
        if (!IdTCPClient->Connected())
        {
            IdTCPClient->Host = "127.0.0.1"; // 确保这是正确的IP
            IdTCPClient->Port = 8080;
            IdTCPClient->Connect();
		}
        String data = Edit_One->Text;
        String speedStr = IntToStr(SpeedComboBox->ItemIndex + 1); // 发送选择的速度
        String fontStr = font; // 发送选择的字体
        IdTCPClient->IOHandler->WriteLn(data + "|" + speedStr + "|" + fontStr, IndyTextEncoding_UTF8()); // 发送数据、速度和字体
    }
    catch (Exception &e)
    {
        ShowMessage("连接错误：" + e.Message);
    }
}
//---------------------------------------------------------------------------
 void TMainForm::SendSpeedToDisplay(int speed)
{
	try
    {
        if (!IdTCPClient->Connected())
        {
            IdTCPClient->Host = "127.0.0.1";
            IdTCPClient->Port = 8080;
            IdTCPClient->Connect();
        }
        String data = Edit_One->Text;
        String speedStr = IntToStr(speed);
        String fontStr = Font_ComboBox->Text; // 获取选择的字体

        IdTCPClient->IOHandler->WriteLn(data + "|" + speedStr + "|" + fontStr, IndyTextEncoding_UTF8());
    }
    catch (Exception &e)
    {
        ShowMessage("连接错误：" + e.Message);
	}
}
void TMainForm::PopulateFontComboBox()
{
    HDC hdc = GetDC(0);
    LOGFONT lf = {0};
    lf.lfCharSet = DEFAULT_CHARSET;
    EnumFontFamiliesEx(hdc, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)this, 0);
    ReleaseDC(0, hdc);
}

int CALLBACK EnumFontFamExProc(const LOGFONT *lpelfe, const TEXTMETRIC *lpntme, DWORD FontType, LPARAM lParam)
{
    TMainForm *mainForm = reinterpret_cast<TMainForm*>(lParam);
    mainForm->Font_ComboBox->Items->Add(lpelfe->lfFaceName);
    return 1;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	delete BufferBitmap;
}
//---------------------------------------------------------------------------

