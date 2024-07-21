//---------------------------------------------------------------------------

#ifndef Main_FormH
#define Main_FormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPClient.hpp>
//---------------------------------------------------------------------------

	int CALLBACK EnumFontFamExProc(const LOGFONT *lpelfe, const TEXTMETRIC *lpntme, DWORD FontType, LPARAM lParam);

class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *Setup;
	TEdit *Edit_One;
	TButton *SendButton;
	TIdTCPClient *IdTCPClient;
	TComboBox *SpeedComboBox;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *Font_ComboBox;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SendButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	void SendDataToDisplay();
	void SendSpeedToDisplay(int speed);
	void __fastcall SendFontToDisplay(String font);
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	void PopulateFontComboBox();


};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
