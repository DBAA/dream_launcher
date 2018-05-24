; some code from https://autohotkey.com/board/topic/17656-breaking-an-infinite-loop-with-keypress/



	
Loop, 
{
	;MsgBox big loop
	;loop waiting for it to launch
	Loop,
	{
		;MsgBox, loop me
		WinWait, Mozilla Firefox, , 5
		if ErrorLevel
		{
			;MsgBox, WinWait timed out.
		}
		else{
			;Sleep, 100
			;ControlSend, , {F11 1}, firefox.exe
			;ControlSend , , {F11}, A
			;MsgBox, slam it
			WinActivate
			Send {F11 1}
			break
		}
	}
	
	;loop waiting for it to close
	Loop,
	{
		Process,Exist, firefox.exe
		If ErrorLevel{
			;do nothing
		}
		else{
			;MsgBox, it gone
			break
		}
		Sleep, 1000
	}
		

}



#f::
	Msgbox, ending firefox full-screener
	ExitApp
	return

	



