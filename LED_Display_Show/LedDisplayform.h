//---------------------------------------------------------------------------

#ifndef LedDisplayformH
#define LedDisplayformH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <IdContext.hpp>
//---------------------------------------------------------------------------
class TLEDDisplay_Form : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPaintBox *PaintBox1;
	TIdTCPServer *IdTCPServer;
	TTimer *Timer1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall IdTCPServerExecute(TIdContext *AContext);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
	 String DisplayText;
	int ScrollOffset;
     String ReceivedData;
	void __fastcall SyncUpdateDisplay(TObject *Sender);

    std::unique_ptr<Graphics::TBitmap> BufferBitmap;
    void UpdateBufferBitmap();

public:		// User declarations
	__fastcall TLEDDisplay_Form(TComponent* Owner);
	  void UpdateDisplay(const String &text);
};
//---------------------------------------------------------------------------
extern PACKAGE TLEDDisplay_Form *LEDDisplay_Form;
//---------------------------------------------------------------------------
#endif
