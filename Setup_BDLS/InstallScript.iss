; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "BDLS"
#define MyAppVersion "1.0"
#define MyAppPublisher "DIGIBOOK"
#define MyAppURL "http://www.docuscan.co.kr/"
#define MyAppExeName "BDLS.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{95ADECE0-978B-470A-83A3-43475CC972F4}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={commonpf64}\{#MyAppName}
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputBaseFilename=SetupBDLS
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "Korean"; MessagesFile: "compiler:Languages\Korean.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "E:\source\BDLS\x64\Release\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\source\BDLS\x64\Release\multimedia\*"; DestDir: "{app}\multimedia"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\source\BDLS\x64\Release\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\source\BDLS\x64\Release\qml\*"; DestDir: "{app}\qml"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\source\BDLS\x64\Release\resources\*"; DestDir: "{app}\resources"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\source\BDLS\x64\Release\sqldrivers\*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\source\BDLS\x64\Release\database_search_icon.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\libmupdf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\PdfTxtExtractor.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Multimedia.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6MultimediaWidgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6OpenGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Pdf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6PdfQuick.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6PdfWidgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Qml.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QmlCore.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QmlModels.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QmlWorkerScript.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Quick.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickControls2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickControls2Impl.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickDialogs2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickDialogs2QuickImpl.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickDialogs2Utils.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickLayouts.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickShapes.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickTemplates2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6QuickWidgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6WebChannel.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6WebEngineCore.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6WebEngineWidgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\QtWebEngineProcess.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\SumatraPDF.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\SumatraPDF-settings.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\source\BDLS\x64\Release\cpdf.exe"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\database_search_icon.ico"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

