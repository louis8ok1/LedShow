//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_Form.h"
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
}
//---------------------------------------------------------------------------
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


