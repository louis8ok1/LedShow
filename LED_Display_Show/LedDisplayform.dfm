object LEDDisplay_Form: TLEDDisplay_Form
  Left = 0
  Top = 0
  Caption = 'LEDDisplay_Form'
  ClientHeight = 445
  ClientWidth = 628
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 628
    Height = 445
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 624
    ExplicitHeight = 440
    object PaintBox1: TPaintBox
      Left = 128
      Top = 128
      Width = 353
      Height = 161
      OnPaint = PaintBox1Paint
    end
  end
  object IdTCPServer: TIdTCPServer
    Bindings = <>
    DefaultPort = 0
    OnExecute = IdTCPServerExecute
    Left = 128
    Top = 32
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 504
    Top = 48
  end
end
