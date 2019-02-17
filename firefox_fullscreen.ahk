; some code from https://autohotkey.com/board/topic/17656-breaking-an-infinite-loop-with-keypress/

Loop, 
{

	;MsgBox, loop me
	
	Process,Exist, firefox.exe
	pid =  %ErrorLevel%
	;MsgBox test %pid% test %ErrorLevel%
	If (pid){
		;MsgBox it here.
		window_name := getWindowNameFromPid(pid)
		;MsgBox window name %window_name%
		
		WinGetPos, X, Y, Width, Height, %window_name%
		;MsgBox, firefox is at %X%`,%Y%
		
		if (X > 0 && Y > 0){
			sleep 1000
			;MsgBox, slam it
			WinActivate %window_name%
			Send {F11 1}
		}
	}else{
		;MsgBox no fire fox
	}
	
	sleep 500
		
}

getWindowNameFromPid(pid){
	WinGetClass, ClassID, ahk_pid %pid%   ; ClassID will be read here for the process
    WinGetTitle, Title, ahk_pid %pid% ; Title will contain the processe's first window's title
	;MsgBox title %Title%
	return Title
}

;This one does now wortk
;https://stackoverflow.com/questions/11957430/how-to-get-window-handle-by-pid-in-autohotkey
getHwndForPid(pid) {
    pidStr := "ahk_pid " . pid
    WinGet, hWnd, ID, %pidStr%
	MsgBox %pid% is %hWnd%
    return hWnd
}



#f::
	Msgbox, ending firefox full-screener
	ExitApp
	return

	



