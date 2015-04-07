let &termencoding=&encoding
set fileencodings=utf-8,gbk,utf-16,big5
set cin nu ts=4 sw=4 sts=4 et incsearch noswapfile nobackup
syntax on
imap {<cr> {<cr>}<c-o>O

map <F4> :exec "!g++ -std=c++11 % -o %<"<cr>
map <F5> :exec "!%<"<cr>

colorscheme solarized

