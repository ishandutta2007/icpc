set cin nu ts=4 sw=4 sts=4 et acd noswapfile nobackup go=
set bs=eol,start,indent
syntax on

colorscheme solarized

set fileencodings=utf-8,gb2312,gbk,gb18030
set termencoding=utf-8

function! Compile()
    if &filetype=="cpp" || &filetype=="c"
        :!g++ -std=c++0x -O2 -m32 % -o %<
    elseif &filetype=="java"
        :!javac %
    elseif &filetype=="haskell"
        :!ghc -o %< %
    endif
endfunction

function! Run()
    if &filetype=="java"
        :!java %<
    elseif &filetype=="python"
        :!python %
    else
        :!%<
    endif
endfunction

function! SetTitle()
    if &filetype=="java"
        let l = 0
        for line in readfile(join([$vim,"\\templates\\Main.java"],""))
            let l = l + 1 | call setline(l,line)
        endfor
    endif
endfunction

map <F4> :call Compile()<cr>
map <F5> :call Run()<cr>
map <F2> :call SetTitle()<cr>

let mapleader="-"
nnoremap <leader>ev :vsplit $MYVIMRC<cr>
nnoremap <leader>sv :source $MYVIMRC<cr>
