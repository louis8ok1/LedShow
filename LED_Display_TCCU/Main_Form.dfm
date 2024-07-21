object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 252
  ClientWidth = 787
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
    Width = 787
    Height = 252
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 822
    ExplicitHeight = 559
    object Setup: TGroupBox
      Left = 1
      Top = 1
      Width = 785
      Height = 250
      Align = alClient
      Caption = 'Setup'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      ExplicitLeft = 2
      ExplicitTop = 0
      ExplicitWidth = 680
      object Label1: TLabel
        Left = 27
        Top = 60
        Width = 82
        Height = 28
        Caption = 'Message'
      end
      object Label2: TLabel
        Left = 378
        Top = 60
        Width = 57
        Height = 28
        Caption = 'Speed'
      end
      object Label3: TLabel
        Left = 490
        Top = 60
        Width = 42
        Height = 28
        Caption = 'Font'
      end
      object Edit_One: TEdit
        Left = 27
        Top = 94
        Width = 321
        Height = 36
        TabOrder = 0
      end
      object SendButton: TButton
        Left = 27
        Top = 160
        Width = 81
        Height = 41
        Caption = 'Send'
        TabOrder = 1
        OnClick = SendButtonClick
      end
      object SpeedComboBox: TComboBox
        Left = 378
        Top = 94
        Width = 71
        Height = 36
        Style = csDropDownList
        TabOrder = 2
      end
      object Font_ComboBox: TComboBox
        Left = 490
        Top = 94
        Width = 183
        Height = 36
        Style = csDropDownList
        TabOrder = 3
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
