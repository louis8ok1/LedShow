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
#include <Vcl.ComCtrls.hpp>
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
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *DIY_TabSheet;
	TGroupBox *GroupBox1;
	TPaintBox *PaintBox;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SendButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);


private:	// User declarations
	void SendDataToDisplay();
	void SendSpeedToDisplay(int speed);
	void __fastcall SendFontToDisplay(String font);
	//客製化版型
	 int RedLinePosition;
    int GreenLine1Position;
    int GreenLine2Position;
    int CellSize;
    bool IsDraggingRed;
    bool IsDraggingGreen1;
    bool IsDraggingGreen2;

    void __fastcall GridPaintBoxPaint(TObject *Sender);
    void __fastcall GridPaintBoxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall GridPaintBoxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall GridPaintBoxMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	TBitmap *BufferBitmap;

     // ... 其他成员变量 ...
    int TempRedPosition;
    int TempGreen1Position;
    int TempGreen2Position;


public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	void PopulateFontComboBox();


};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
