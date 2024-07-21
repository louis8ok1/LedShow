//---------------------------------------------------------------------------

// Server_MainForm.h
#ifndef Server_MainFormH
#define Server_MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
//---------------------------------------------------------------------------
class TLEDDisplay_Form : public TForm
{
__published:	// IDE-managed Components  // 使用 TLEDPanel
	TIdTCPServer *IdTCPServer;
	TPaintBox *PaintBox;




	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall IdTCPServerExecute(TIdContext *AContext);

private:	// User declarations

	String ReceivedData;

public:		// User declarations
	__fastcall TLEDDisplay_Form(TComponent* Owner);
	void __fastcall DisplayMessage(String message);
};
//---------------------------------------------------------------------------
extern PACKAGE TLEDDisplay_Form *LEDDisplay_Form;
//---------------------------------------------------------------------------
#endif
