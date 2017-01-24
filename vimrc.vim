set si nu ts=4 sw=4 sts=4 bs=eol,start,indent et acd relativenumber tags=tags;/
syntax on

set nocompatible              " be iMproved, required
filetype off                  " required

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'majutsushi/tagbar'
call vundle#end()            " required
filetype plugin indent on    " required
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

let mapleader='-'
nnoremap <leader>e :!g++ -std=c++11 -O2 % -o %<<cr>
nnoremap <leader>w :!./%<<cr>
nnoremap <leader>q :!./%< <data.in<cr>
nnoremap <leader>tt :TagbarToggle<cr>
nnoremap <leader>nt :NERDTreeToggle<cr>
