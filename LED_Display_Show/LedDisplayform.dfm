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
  OnCreate = FormCreate
  OnPaint = FormPaint
  TextHeight = 15
  object PaintBox: TPaintBox
    Left = 0
    Top = 0
    Width = 628
    Height = 445
    Align = alClient
    ExplicitLeft = 144
    ExplicitTop = 248
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object IdTCPServer: TIdTCPServer
    Bindings = <>
    DefaultPort = 0
    OnExecute = IdTCPServerExecute
    Left = 584
    Top = 320
  end
end
