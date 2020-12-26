set si nu ts=2 sw=2 sts=2 bs=eol,start,indent et acd relativenumber
syntax on

let mapleader='\'
nnoremap <leader>e :!g++ -std=c++14 -O2 % -o %<<cr>
nnoremap <leader>w :!./%<<cr>
nnoremap <leader>q :!./%< <data.in<cr>
