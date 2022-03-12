" -----------------------------------
" --- Rich Nakasato's .vimrc file ---
" -----------------------------------

" --- General Settings ---{{{
set nocompatible " disable vi compatibility
set secure " be safe about our commands
syntax on " enable syntax highlighting
syntax case ignore

set backspace=indent,eol,start " ensure backspace works as expected
set ignorecase
set encoding=utf-8 " character encoding
set fileencoding=utf-8 " file encoding
set termencoding=utf-8 " terminal encoding

set hlsearch " highlight searches by default
set incsearch " highlight searches as they are typed

set showcmd " show commands
set showmode " show current mode
set history=1000 " save lots of command line history
set undolevels=1000 " allow us to make lots of mistakes

set hidden " keep buffers in background open

set noswapfile " disable swap files
set nobackup " disable backups
set nowb " disable write backup

set cursorline " show cursor row
"set cursorcolumn " show cursor column

"set spell " enable spell check
"set spelllang=en " set language to English

set guifont=Consolas:h26

"highlight Comment ctermbg=DarkGray
"highlight Constant ctermbg=Blue
"highlight Normal ctermbg=Black
"highlight NonText ctermbg=Black
"highlight Special ctermbg=DarkMagenta
"highlight Cursor ctermbg=Green

colorscheme murphy












set textwidth=80 " wrap lines at 80 chars
set number " show line numbers
set ruler " show line number & cursor position in the lower right
set laststatus=2 " always show status bar

set scrolloff=10 " start scrolling when we're n rows from a margin
set sidescrolloff=20 " start scrolling when we're n columns from a margin

set autoindent " use indentation from previous line
set copyindent " copy indent structure from previous line
set smartindent " use smart indenting when starting a new line

set showmatch " highlight matching braces

" enable plugins
filetype on
filetype indent on
filetype plugin on
filetype plugin indent on

"}}}

" --- UI Settings ---{{{
"colorscheme wombat256 " set the colorscheme
set t_Co=256 " set 256 colors

" highlight out of bounds text (beyond our text width), new style
"set colorcolumn=81

" highlight trailing white space
match ErrorMsg /\s\+$/

"}}}

" --- Spaces & Tabs ---{{{
set tabstop=2
set softtabstop=2
set shiftwidth=2
set expandtab

"}}}

" zR to open up all folding
" --- Folding ---{{{
set foldenable "enable folding
set foldmethod=indent " use indents as fold markers
set foldmethod=marker " use markers as fold markers
set foldlevelstart=0 " start with all folds closed
set foldnestmax=3 " set maximum number of nested folds

"}}}

" --- Misc ---{{{
" turn markdown highlighting on
au BufRead,BufNewFile *.md set filetype=markdown

" intelligent comments
set comments=sl:/*,mb:\ *,elx:\ */

"}}}

" --- Key Binds ---{{{
let mapleader = ","

" bind a new ESC
inoremap jj <Esc>

" use ctrl-[hjkl] to select the active split
nnoremap <silent> <c-k> :wincmd k<CR>
nnoremap <silent> <c-j> :wincmd j<CR>
nnoremap <silent> <c-h> :wincmd h<CR>
nnoremap <silent> <c-l> :wincmd l<CR>

" remove trailing whitespace
nnoremap <Leader>rw :%s/\s\+$//e<CR>

" convert DOS newlines to UNIX newlines
nnoremap <Leader>cn :%s/^M/\r/g<CR>

" convert all tabs to spaces
nnoremap <Leader>ct :%retab<CR>

" toggle highlight search
nnoremap <Leader><space> :set hlsearch!<CR>

" edit and source .vimrc
nnoremap <Leader>ev :vs ~/.vimrc<CR>
nnoremap <Leader>sv :so ~/.vimrc<CR>

" generic source
nnoremap <Leader>s :so ~/.vim/

"vim session = alias
"vim -S session_name to open
" generic session save
nnoremap <Leader>m :mksession! ~/.vim/

" alternate file toggle (alternate!)
map <Leader>a :A<CR>

" nerd tree toggle (tree!)
map <Leader>1 :NERDTreeToggle<CR>

" tag bar toggle (list!)
map <Leader>2 :TagbarToggle<CR>

" quick (zippy) save
map <Leader>z :mksession! ~/.vim/zippy.vim<CR>

" view in hex
map <Leader>h :%!xxd<CR>

"}}}

" --- Plugins ---{{{
let g:plug_timeout=1000
" plugin management
call plug#begin('~/.vim/plugged')

" search vim plugged and run curl and :PlugInstall

" alternate files quickly
Plug 'https://github.com/vim-scripts/a.vim'

" complete c/c++
Plug 'https://github.com/Rip-Rip/clang_complete'

" ctrl-p - ESSENTIAL
Plug 'https://github.com/ctrlpvim/ctrlp.vim'

",1 to open file list
" file browser
Plug 'https://github.com/scrooloose/nerdtree'

" comment functions
"Plug 'https://github.com/scrooloose/nerdcommenter'

" code outlines
"Plug 'https://github.com/majutsushi/tagbar'

" fancy status bar
"Plug 'https://github.com/vim-airline/vim-airline'

" snips
"Plug 'https://github.com/SirVer/ultisnips'

" automatically close brackets
"Plug 'https://github.com/Townk/vim-autoclose'

" easy grep
Plug 'https://github.com/dkprice/vim-easygrep'

"GrepOption to change directory and files

" git wrapper
"Plug 'https://github.com/tpope/vim-fugitive'

" git modifier column (gutter for +/-/~)
"Plug 'https://github.com/airblade/vim-gitgutter'

" multi selection
"Plug 'https://github.com/terryma/vim-multiple-cursors'

" toggle quickfix and location windows
"Plug 'https://github.com/milkypostman/vim-togglelist'

call plug#end()
"
"" ultisnips
"let g:UltiSnipsExpandTrigger="<tab>"
"let g:UltiSnipsListSnippets="<c-tab>"
"let g:UltiSnipsJumpForwardTrigger="<c-j>"
"let g:UltiSnipsJumpBackwardTrigger="<c-k>"

" alternate
"iunmap <leader>ihn
"iunmap <leader>is
"iunmap <leader>ih

"}}}
