set nu
set ts=4
set expandtab
set wrap
set autoindent
set cindent
set shiftwidth=4


" adding copyright info
map <F4> :call UpdateCopyright()<cr>'s

function AddCopyrightForPython()
    call append(0, "####################################################")
    call append(1, "#        Author : zergl <e3.gemini@qq.com>")
    call append(2, "#  FisrtCreated : ".strftime("%Y-%m-%d %H:%M"))
    call append(3, "#  LastModified : ".strftime("%Y-%m-%d %H:%M"))
    call append(4, "#      Filename : ".expand("%:t"))
    call append(5, "#   Description : ")
    call append(6, "#       History : ")
    call append(7, "#             1. First created.")
    call append(8, "#")
    call append(9, "####################################################")
    call append(10, "#!/usr/bin/env python             ")
    call append(11, "#-*- coding: UTF-8 -*-             ")
    call append(12, "")
    echohl WarningMsg | echo "Copyright added." | echohl None
endfunction

function UpdateCopyrightForPython()
    normal m'
    execute '/#  *LastModified :/s@:.*$@\=strftime(": %Y-%m-%d %H:%M")@'
    normal ''
    normal mk
    execute '/# *Filename :/s@:.*$@\=": ".expand("%:t")@'
    execute "noh"
    normal 'k
    echohl WarningMsg | echo "Copyright updated." | echohl None
endfunction

function UpdateCopyright()
    " support python only!!!
    if &filetype == "python"
        let n=1
        while n < 10
            let line = getline(n)
            if line =~ '^\#\s*\S*LastModified :\S*.*$'
                call UpdateCopyrightForPython()
                return
            endif
            let n = n + 1
        endwhile
        
        call AddCopyrightForPython()
    else
        echohl WarningMsg | echo "Not support."
    endif
    
endfunction
