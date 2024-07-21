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
	TTimer *Timer;





	void __fastcall FormCreate(TObject *Sender);
	void __fastcall IdTCPServerExecute(TIdContext *AContext);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall PaintBoxPaint(TObject *Sender);

private:	// User declarations

	String ReceivedData;
	int TextPosition;
	TBitmap *Buffer;
	String CurrentFont; // 当前选择的字体
	void __fastcall DisplayMessage(String message);


public:		// User declarations
	__fastcall TLEDDisplay_Form(TComponent* Owner);
	__fastcall ~TLEDDisplay_Form();

};
//---------------------------------------------------------------------------
extern PACKAGE TLEDDisplay_Form *LEDDisplay_Form;
//---------------------------------------------------------------------------
#endif
