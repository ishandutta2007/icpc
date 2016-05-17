set si go= nu ts=4 sw=4 sts=4 acd noswapfile nobackup et
set backspace=eol,start,indent
syntax on

map <F4> :!g++ -std=c++11 -O2 % -o %<<cr>
map <F5> :!%<<cr>
