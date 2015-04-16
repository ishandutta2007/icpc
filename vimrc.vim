let &termencoding=&encoding
set fileencodings=utf-8,gbk,utf-16,big5
set go= cin nu ts=4 sw=4 sts=4 et incsearch noswapfile nobackup
syntax on

map <F4> :!g++ -std=c++11 % -o %<<cr>
map <F5> :!%<<cr>

map <F3> :!javac %<cr>
map <F2> :!java %<<cr>

colorscheme solarized

