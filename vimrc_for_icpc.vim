let &termencoding=&encoding
set fileencodings=utf-8,gbk,utf-16,big5
set si go= nu ts=4 sw=4 sts=4 acd noswapfile nobackup et
set backspace=eol,start,indent
syntax on
filetype indent plugin on

map <F4> :!g++ -std=c++11 -O2 % -o %<<cr>
map <F5> :!%<<cr>

map <F3> :!javac %<cr>
map <F2> :!java %<<cr>

map <F6> :!python %<cr>

map <F8> :!ghc -o %< %<cr>

colorscheme solarized

