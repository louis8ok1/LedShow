object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 563
  ClientWidth = 826
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
    Width = 826
    Height = 563
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 822
    ExplicitHeight = 559
    object Setup: TGroupBox
      Left = 1
      Top = 1
      Width = 824
      Height = 561
      Align = alClient
      Caption = 'Setup'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      ExplicitWidth = 820
      ExplicitHeight = 557
      object showCheckBoxOne: TCheckBox
        Left = 40
        Top = 96
        Width = 129
        Height = 49
        Caption = 'No.1 Show'
        TabOrder = 0
      end
      object Edit_One: TEdit
        Left = 192
        Top = 102
        Width = 321
        Height = 36
        TabOrder = 1
      end
      object SendButton: TButton
        Left = 344
        Top = 432
        Width = 81
        Height = 41
        Caption = 'Send'
        TabOrder = 2
        OnClick = SendButtonClick
      end
    end
  end
  object IdTCPClient: TIdTCPClient
    ConnectTimeout = 0
    Port = 0
    ReadTimeout = -1
    Left = 289
    Top = 481
  end
end
