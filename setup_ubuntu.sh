#!/usr/bin/env bash
set -e

echo "=== [1/5] Updating system and installing toolchain ==="
sudo apt-get update -y
sudo apt-get install -y \
    build-essential \
    g++ \
    clangd \
    nodejs \
    npm \
    curl \
    git

echo "=== [2/5] Installing vim-plug ==="
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

echo "=== [3/5] Writing ~/.vimrc ==="
cat << 'EOF' > ~/.vimrc
" --- Environment ---
se nu ai hls et ru ic is sc cul
se re=1 ts=4 sts=4 sw=4 ls=2 mouse=a
hi cursorline cterm=none ctermbg=89
inoremap {<CR> {<CR>}<Esc>O
syntax on
set bg=dark
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6

" --- Plugins ---
call plug#begin('~/.vim/plugged')
Plug 'neoclide/coc.nvim', {'branch': 'release'}
call plug#end()

" --- coc.nvim Keymaps ---
inoremap <silent><expr> <TAB>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ CheckBackspace() ? "\<Tab>" :
      \ coc#refresh()
inoremap <expr><S-TAB> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1] =~# '\s'
endfunction

inoremap <silent><expr> <CR> coc#pum#visible() ? coc#pum#confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"

nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)
nmap <leader>rn <Plug>(coc-rename)

nnoremap <silent> K :call ShowDocumentation()<CR>
function! ShowDocumentation()
  if CocAction('hasProvider', 'hover')
    call CocActionAsync('doHover')
  else
    call feedkeys('K', 'in')
  endif
endfunction

inoremap <silent><expr> <C-n>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ coc#refresh()
inoremap <silent><expr> <C-p>
      \ coc#pum#visible() ? coc#pum#prev(1) : "\<C-p>"

function! s:CustomizeInlayHints()
  highlight CocInlayHint ctermfg=244 ctermbg=236 guifg=#808080 guibg=#2d3139
endfunction

autocmd! ColorScheme * call s:CustomizeInlayHints()
call s:CustomizeInlayHints()

" --- Custom CP Tools: :Inc & :Init ---
let g:inc_lib_path = expand('~/cplibrary')

function! FinishInclude() abort
    let l:dir = b:netrw_curdir
    let l:file = netrw#Call("NetrwGetWord")

    if l:file ==# '../' || l:file ==# './' || empty(l:file)
        call netrw#LocalBrowseCheck(netrw#Call('NetrwBrowseChgDir', 1, l:file))
        return
    endif

    let l:full_path = simplify(l:dir . '/' . l:file)

    if isdirectory(l:full_path)
        call netrw#LocalBrowseCheck(netrw#Call('NetrwBrowseChgDir', 1, l:file))
        return
    endif

    let l:lib_root = fnamemodify(g:inc_lib_path, ':p')
    let l:abs_item = fnamemodify(l:full_path, ':p')

    if l:abs_item !~# '^\V' . l:lib_root
        echoerr "Selected file is outside of cplibrary! Run :Inc to reset."
        return
    endif

    let l:rel_path = substitute(l:abs_item, '^\V' . l:lib_root, '', '')
    let l:rel_path = substitute(l:rel_path, '^/', '', '')

    let l:netrw_buf = bufnr('%')
    let l:target_buf = g:inc_origin_buf
    
    if bufexists(l:target_buf)
        execute "buffer " . l:target_buf
        silent! execute "bdelete! " . l:netrw_buf
        call append(line('.'), '#include "' . l:rel_path . '"')
        normal! j
    else
        echoerr "The original file buffer doesn't exist!"
    endif
endfunction

augroup NetrwInclude
    autocmd!
    autocmd FileType netrw setlocal number
    autocmd FileType netrw nnoremap <buffer> <nowait> <silent> i :call FinishInclude()<CR>
    autocmd FileType netrw nnoremap <buffer> <nowait> <silent> <CR> :call FinishInclude()<CR>
    autocmd FileType netrw nnoremap <buffer> <nowait> <silent> q :execute 'buffer ' . g:inc_origin_buf<CR>
    autocmd FileType netrw nnoremap <buffer> <nowait> <silent> <Esc> :execute 'buffer ' . g:inc_origin_buf<CR>
    autocmd FileType netrw nnoremap <buffer> <nowait> <silent> u :execute 'edit ' . g:inc_lib_path<CR>
augroup END

command! Inc let g:inc_origin_buf = bufnr('%') | execute 'edit ' . g:inc_lib_path

function! InitCPFromCurrentBuffer(start_char, end_char) abort
    let l:s = char2nr(toupper(a:start_char))
    let l:e = char2nr(toupper(a:end_char))

    if l:s > l:e || l:s < 65 || l:e > 90
        echoerr "Please enter a valid letter range (e.g., :Init A G)"
        return
    endif

    let l:lines = getline(1, '$')

    let l:code = l:s
    while l:code <= l:e
        let l:fname = nr2char(l:code) . '.cpp'
        call writefile(l:lines, l:fname)
        let l:code += 1
    endwhile

    let l:code = l:s
    while l:code <= l:e
        let l:fname = nr2char(l:code) . '.cpp'
        execute 'tabedit ' . fnameescape(l:fname)
        let l:code += 1
    endwhile

    tabnext 2
endfunction

command! -nargs=+ Init call InitCPFromCurrentBuffer(<f-args>)
EOF

echo "=== [4/5] Configuring global clangd settings (~/.config/clangd/config.yaml) ==="
mkdir -p ~/.config/clangd
cat << EOF > ~/.config/clangd/config.yaml
CompileFlags:
  Add:
    - -I${HOME}/cplibrary
    - -Dbbq
    - -std=c++23
    - -Wall
    - -Wextra
    - -Wshadow
    - -Wno-unknown-pragmas

Diagnostics:
  UnusedIncludes: None
EOF

echo "=== [5/5] Installing Vim plugins and coc-clangd ==="
vim -es -u ~/.vimrc -i NONE -c "PlugInstall" -c "qa"
vim -es -u ~/.vimrc -i NONE -c "CocInstall -sync coc-clangd" -c "qa"

echo "=== Setup completed successfully! ==="
