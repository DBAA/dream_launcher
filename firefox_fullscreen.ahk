; some code from https://autohotkey.com/board/topic/17656-breaking-an-infinite-loop-with-keypress/
Loop, 
{
	;loop waiting for it to launch
	Loop,
	{
		WinWait, Mozilla Firefox, , 5
		if ErrorLevel
		{
			;do nothing
		}
		else{
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
			break
		}
		Sleep, 1000
	}
}

#f::
	Msgbox, ending firefox full-screener
	ExitApp
	return