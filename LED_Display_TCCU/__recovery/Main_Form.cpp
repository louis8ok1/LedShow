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
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SendButtonClick(TObject *Sender)
{
	  SendDataToDisplay();
}
//---------------------------------------------------------------------------
void TMainForm::SendDataToDisplay()
{
 try
    {
        if (!IdTCPClient->Connected())
        {
            IdTCPClient->Host = "127.0.0.1"; // 確保這是正確的IP
            IdTCPClient->Port = 8080;
            IdTCPClient->Connect();
        }
        String data = Edit_One->Text;
        IdTCPClient->IOHandler->WriteLn(data, IndyTextEncoding_UTF8());
    }
    catch (Exception &e)
    {
        ShowMessage("連接錯誤：" + e.Message);
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
