#include <vcl.h>
#pragma hdrstop

#include "LEDDisplayForm.h"
#include <System.IOUtils.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"

TLEDDisplay_Form *LEDDisplay_Form;

__fastcall TLEDDisplay_Form::TLEDDisplay_Form(TComponent* Owner)
	: TForm(Owner) , CurrentFont("Arial")
{
	 // 启用双缓冲
    SetWindowLong(Handle, GWL_EXSTYLE, GetWindowLong(Handle, GWL_EXSTYLE) | WS_EX_COMPOSITED);

    TextPosition = 384; // 初始化文本位置
    Buffer = new TBitmap(); // 创建内存位图
}

__fastcall TLEDDisplay_Form::~TLEDDisplay_Form()
{
    delete Buffer; // 釋放內存位圖
}
//---------------------------------------------------------------------------

void __fastcall TLEDDisplay_Form::FormCreate(TObject *Sender)
{
    IdTCPServer->DefaultPort = 8080; // 設置TCP伺服器默認端口
    IdTCPServer->Active = true; // 啟動TCP伺服器
    this->BorderStyle = bsNone; // 設置窗口邊框樣式為無邊框
    this->Top = 0; // 設置窗口頂端位置
    this->Left = 0; // 設置窗口左側位置
    this->Width = 384; // 設置窗口寬度
    this->Height = 96; // 設置窗口高度

	// 設置內存位圖大小
    Buffer->Width = PaintBox->Width; // 將內存位圖寬度設置為PaintBox的寬度
	Buffer->Height = PaintBox->Height; // 將內存位圖高度設置為PaintBox的高度

    // 設置計時器
    Timer = new TTimer(this); // 創建計時器
    Timer->Interval = 50; // 設置計時器的間隔時間為50毫秒
	Timer->OnTimer = TimerTimer; // 設置計時器的事件處理函數
    Timer->Enabled = true; // 啟動計時器

}
//---------------------------------------------------------------------------

void __fastcall TLEDDisplay_Form::IdTCPServerExecute(TIdContext *AContext)
{
    try
    {
        String message = AContext->Connection->IOHandler->ReadLn(IndyTextEncoding_UTF8());

        // 分离消息、速度和字体
        int separatorIndex1 = message.Pos("|");
        if (separatorIndex1 > 0) {
            int separatorIndex2 = message.SubString(separatorIndex1 + 1, message.Length() - separatorIndex1).Pos("|");
            if (separatorIndex2 > 0) {
                ReceivedData = message.SubString(1, separatorIndex1 - 1);
                String speedStr = message.SubString(separatorIndex1 + 1, separatorIndex2 - 1);
                String fontStr = message.SubString(separatorIndex1 + separatorIndex2 + 1, message.Length() - (separatorIndex1 + separatorIndex2));

				// 设置移动速度
                int speed = StrToIntDef(speedStr, 5); // 默认为5
                Timer->Interval = 200 - (speed * 20); // 根据速度调整计时器间隔

                // 设置字体
                CurrentFont = fontStr;

                TextPosition = PaintBox->Width; // 重置文本位置到右边
                PaintBox->Repaint();
            }
        }
    }
    catch (Exception &e)
    {
        // 处理异常
	}
}
//---------------------------------------------------------------------------

void __fastcall TLEDDisplay_Form::DisplayMessage(String message)
{
    ReceivedData = message; // 更新接收到的消息
    TextPosition = PaintBox->Width; // 將文本位置重置到右邊
    PaintBox->Repaint(); // 觸發PaintBox的重繪
}

void __fastcall TLEDDisplay_Form::TimerTimer(TObject *Sender)
{
	TextPosition -= 2; // 每次計時器觸發時，將文本位置向左移動2個像素

    // 當文本完全離開左邊界時，重置文本位置到右邊
    if (TextPosition + Buffer->Canvas->TextWidth(ReceivedData) < 0)
    {
        TextPosition = PaintBox->Width;
    }

	PaintBox->Repaint(); // 觸發PaintBox的重繪
}
//---------------------------------------------------------------------------

void __fastcall TLEDDisplay_Form::PaintBoxPaint(TObject *Sender)
{
	 // 在内存位图中绘制
    TRect rect(0, 0, Buffer->Width, Buffer->Height);

    Buffer->Canvas->Brush->Color = clBlack;
    Buffer->Canvas->FillRect(rect);

    // 设置字体属性
    Buffer->Canvas->Font->Name = CurrentFont.IsEmpty() ? "Arial" : CurrentFont;
    Buffer->Canvas->Font->Size = 24;
    Buffer->Canvas->Font->Color = clLime;

    Buffer->Canvas->TextOut(TextPosition, 10, ReceivedData);

    // 将内存位图绘制到PaintBox
	PaintBox->Canvas->Draw(0, 0, Buffer);
}
//---------------------------------------------------------------------------

