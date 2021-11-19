set nocompatible              " be iMproved, required

call plug#begin('~/.vim/plugged')
Plug 'Vimjas/vim-python-pep8-indent'
Plug 'Yggdroot/LeaderF', { 'do': ':LeaderfInstallCExtension' }
Plug 'ludovicchabant/vim-gutentags'
Plug 'powerline/powerline'
Plug 'scrooloose/nerdtree'
Plug 'tpope/vim-fugitive'
call plug#end()

set t_Co=256
let g:Powerline_symbols='unicode'
let g:Powerline_colorscheme = 'solarized256'

let mapleader='\'

" LeaderF
let g:Lf_ShortcutF = '<c-p>'
let g:Lf_ShortcutB = '<m-n>'
noremap <c-n> :LeaderfMru<cr>
noremap <leader>f :LeaderfTag<cr>
noremap <leader>d :LeaderfFunction<cr>
noremap <leader>g :LeaderfBuffer<cr>
let g:Lf_StlSeparator = { 'left': '', 'right': '', 'font': '' }
let g:Lf_RootMarkers = ['.project', '.root', 'WORKSPACE']
let g:Lf_WorkingDirectoryMode = 'Ac'
let g:Lf_WindowHeight = 0.30
let g:Lf_CacheDirectory = expand('~/.cache/leaderf')
let g:Lf_ShowRelativePath = 0
let g:Lf_HideHelp = 1
let g:Lf_StlColorscheme = 'powerline'
let g:Lf_PreviewResult = {'Function':0, 'BufTag':0}
let g:Lf_WindowPosition = 'popup'
let g:Lf_PreviewInPopup = 1

" gutentags config
let g:gutentags_project_root = ['.project', '.root', '.svn', '.git', 'WORKSPACE']
let g:gutentags_ctags_tagfile = '.tags'
let s:vim_tags = expand('~/.cache/tags')
let g:gutentags_cache_dir = s:vim_tags
let g:gutentags_ctags_extra_args = ['--fields=+niazS', '--extra=+q']
let g:gutentags_ctags_extra_args += ['--c++-kinds=+pxI']
let g:gutentags_ctags_extra_args += ['--c-kinds=+px']

if !isdirectory(s:vim_tags)
   silent! call mkdir(s:vim_tags, 'p')
endif

set cin nu ts=2 sw=2 sts=2 bs=eol,start,indent et acd noic
set relativenumber
set linebreak wrap textwidth=100
set laststatus=2 "Always show the statusline
syntax on
set path=., ",/usr/include,/usr/local/include
set autochdir
set tags=./.tags;.tags

set cinoptions=g0,:0,(0,W4,N-s,j1
set completeopt=menu,longest
setglobal complete-=t
setglobal complete-=i
set encoding=utf-8
set fileencodings=usc-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1

au BufNewFile,BufRead *.jenkinsfile setf groovy
au BufNewFile,BufRead *.j2 setf groovy

let NERDTreeMapOpenInTab='<c-t>'
nnoremap <leader>n :NERDTreeToggle %<cr>

nnoremap <c-l> gt
nnoremap <c-h> gT
vnoremap <leader>s :sort u<cr>
nnoremap <leader>b :Gblame<cr>

" Refresh opened files in vim.
nnoremap <leader>r :bufdo e<cr>

" Algo usage
nnoremap <leader>E :!g++ % -std=c++17 -O2 -Wno-unused-result -o %<<cr>
nnoremap <leader>e :!g++ % -std=c++17 -O2 -D ALGO -I ~/.vim/icpc/include -Wno-unused-result -g -fsanitize=undefined -o %<<cr>
nnoremap <leader>w :!./%<<cr>
nnoremap <leader>q :!time ./%< <%<.in<cr>

if has('unix')
  nnoremap <leader>1 :!xclip -selection clipboard -o >%<.in<cr>
elseif has('macunix')
  nnoremap <leader>1 :!pbpaste >%<.in<cr>
endif

" set mouse=a

" Add Template
autocmd BufNewFile *.cpp 0r ~/.vim/icpc/algo_header
autocmd BufNewFile *.hs 0r ~/.vim/icpc/haskell_header
autocmd BufWritePre * %s/\s\+$//e
