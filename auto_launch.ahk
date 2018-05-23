
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SETUP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Game Variables
Launcher_Path = "D:/of_v0.9.8_vs_release/apps/dream_launcher/dream_launcher/bin/dream_launcher_debug.exe"

; General Interface Settings
Start_With_Hidden_Cursor = 0


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; INITIALIZATION
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

if (Start_With_Hidden_Cursor = 1)
{
	SystemCursor("Toggle")
}
;SetTitleMatchMode, 2
;SendMode Input

;kick this thing off
Restart_Launcher()

; middle mouse click restarts 
MButton::Restart_Launcher()

;set the mouse to move every so often
SetTimer, MoveMouse, 300000

;testing
q::Restart_Launcher()

;k kills all games and returns focus to the launcer
k::KilLAllGames()

;R and F are used by the oF app and should not be used here

;temp kill command for testing
;Esc::ExitApp

;Win-Z to kill this script
#z::ExitApp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; RESTART BUTTON
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Restart_Launcher()
{
	;MsgBox restarting

	global Launcher_Path
	
	Process,Close,%Game_Id%

	;Restart Program
	Run %Launcher_Path%,,Max,Game_Id
	
	Send {#h}
}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Killing Windows
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

KillAllGames(){
	
	KillWindow("chrome.exe")
	KillWindow("firefox.exe")
	KillWindow("ConspiracyTheories_RC1.exe")
	KillWindow("dreamhard_rc3.exe")
	KillWindow("OrbTown_RC1.exe")
	KillWindow("queerspace_win.exe")
	
	;if the launcher was closed somehow, relaunch it
	If !ProcessExist("dream_launcher_debug.exe")
		Restart_Launcher()
	
	;Return focus to launcher
	WinActivate, dream_launcher
	Sleep 20
	Send {R 1}
}

KillWindow(exe_name)
{
	;MsgBox %windowName%
	;WinClose, %windowName%
	Process,Exist, %exe_name%
	If ErrorLevel
		Process,Close,%Errorlevel%
}


;https://autohotkey.com/board/topic/98317-if-process-exist-command/
ProcessExist(Name){
	Process,Exist,%Name%
	return Errorlevel
}




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MOUSE WIGGLE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MoveMouse(){
	mousemove 5, 5, 10, R
	sleep 1000
	mousemove -5, -5, 10, R
}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SYSTEM KEY MAPPINGS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Press Win-A to Reload Autohotkey
#a::Reload

; Press Win-C to Toggle Cursor
#c::SystemCursor("Toggle")

#t::WinShow ahk_class Shell_TrayWnd



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; BABYCASTLES LIBRARY
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SystemCursor(OnOff=1)   ; INIT = "I","Init"; OFF = 0,"Off"; TOGGLE = -1,"T","Toggle"; ON = others
{
    static AndMask, XorMask, $, h_cursor
        ,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13 ; system cursors
        , b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13   ; blank cursors
        , h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,h13   ; handles of default cursors
    if (OnOff = "Init" or OnOff = "I" or $ = "")       ; init when requested or at first call
    {
        $ = h                                          ; active default cursors
        VarSetCapacity( h_cursor,4444, 1 )
        VarSetCapacity( AndMask, 32*4, 0xFF )
        VarSetCapacity( XorMask, 32*4, 0 )
        system_cursors = 32512,32513,32514,32515,32516,32642,32643,32644,32645,32646,32648,32649,32650
        StringSplit c, system_cursors, `,
        Loop %c0%
        {
            h_cursor   := DllCall( "LoadCursor", "uint",0, "uint",c%A_Index% )
            h%A_Index% := DllCall( "CopyImage",  "uint",h_cursor, "uint",2, "int",0, "int",0, "uint",0 )
            b%A_Index% := DllCall("CreateCursor","uint",0, "int",0, "int",0
                , "int",32, "int",32, "uint",&AndMask, "uint",&XorMask )
        }
    }
    if (OnOff = 0 or OnOff = "Init" or OnOff = "I" or $ = "" OnOff = "Off" or $ = "h" and (OnOff < 0 or OnOff = "Toggle" or OnOff = "T"))
        $ = b  ; use blank cursors
    else
        $ = h  ; use the saved cursors

    Loop %c0%
    {
        h_cursor := DllCall( "CopyImage", "uint",%$%%A_Index%, "uint",2, "int",0, "int",0, "uint",0 )
        DllCall( "SetSystemCursor", "uint",h_cursor, "uint",c%A_Index% )
    }
}



;;;;;;;;;;;;;;;;;;;;;;
; CLEANUP
;;;;;;;;;;;;;;;;;;;;;;

OnExit, Cleanup
return

Cleanup:
SystemCursor("On")
ExitApp