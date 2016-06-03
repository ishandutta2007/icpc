" 一般设置
set smartindent nu ai ts=4 sw=4 sts=4 et acd noswapfile nobackup go=
set bs=eol,start,indent
syntax on

colorscheme solarized

" 编码设置
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set fileencoding=utf-8
set encoding=utf-8
set termencoding=utf-8
set fileformat=unix
language messages zh_CN.utf-8
source $VIMRUNTIME/delmenu.vim
source $VIMRUNTIME/menu.vim

" 编译
function! Compile()
    if &filetype=="cpp" || &filetype=="c"
        :!g++ -std=c++0x -O2 -m32 % -o %<
    elseif &filetype=="java"
        :!javac %
    elseif &filetype=="haskell"
        :!ghc -o %< %
    endif
endfunction

" 运行
function! Run()
    if &filetype=="java"
        :!java %<
    elseif &filetype=="python"
        :!python %
    else
        :!%<
    endif
endfunction

" 插入头文件
function! SetTitle()
    if &filetype=="java"
        let l = 0
        for line in readfile(join([$vim,"\\templates\\Main.java"],""))
            let l = l + 1 | call setline(l,line)
        endfor
    elseif &filetype=="cpp"
        let l = 0
        for line in readfile(join([$vim,"\\templates\\main.cpp"],""))
            let l = l + 1 | call setline(l,line)
        endfor
    endif
endfunction

map <F4> :call Compile()<cr>
map <F5> :call Run()<cr>
map <F9> :call SetTitle()<cr>

" mapleader
let mapleader="-"
nnoremap <leader>ev :vsplit $MYVIMRC<cr>
nnoremap <leader>sv :source $MYVIMRC<cr>

" 插件管理器Vundle
filetype off  
" 此处规定Vundle的路径  
set rtp+=$VIM/bundle/vundle/  
call vundle#rc('$VIM/bundle/')  
Bundle 'gmarik/vundle'  
filetype plugin indent on  
  
" original repos on github<br>Bundle 'mattn/zencoding-vim'  
   
" vim-scripts repos  
Bundle 'The-NERD-tree'
Bundle 'matrix.vim--Yang'
   
filetype plugin indent on     " required!   

" 目录树设定
map <F2> :silent! NERDTreeToggle<cr>
let NERDTreeWinPos="right"
"let NERDTreeShowBookmarks=1
