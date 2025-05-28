# BASH & LINUX

- Terminal üzerinden direkt çıktının kopyalanması için `xsel --clipboard` komutu kullanılır. Bu komutu kolaylaştırmak için `alias copy='xsel --clipboard'` şeklinde **.bashrc** dosyasına yazılabilir.

## Kali Linux Terminal

- Terminal **User** (`/home/${USER}/.bashrc`)
```sh
prompt_color='\[\033[;32m\]'
info_color='\[\033[1;34m\]'
prompt_symbol=㉿
if [ "$color_prompt" = yes ]; then
        PS1=$prompt_color'┌──${debian_chroot:+($debian_chroot)──}('$info_color'\u${prompt_symbol}\h'$prompt_color')-[\[\033[0;1m\]\w'$prompt_color']\n'$prompt_color'└─'$info_color'\$\[\033[0m\] '
else
        PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$'
fi
```

- Terinal **Root** (`/root/.bashrc`)
```sh
prompt_color='\[\033[;94m\]'
info_color='\[\033[1;31m\]'
prompt_symbol=💀
if [ "$color_prompt" = yes ]; then
        PS1=$prompt_color'┌──${debian_chroot:+($debian_chroot)──}('$info_color'\u${prompt_symbol}\h'$prompt_color')-[\[\033[0;1m\]\w'$prompt_color']\n'$prompt_color'└─'$info_color'\$\[\033[0m\] '
else
        PS1=$prompt_color'┌──${debian_chroot:+($debian_chroot)──}('$info_color'\u${prompt_symbol}\h'$prompt_color')-[\[\033[0;1m\]\w'$prompt_color']\n'$prompt_color'└─'$info_color'\$\[\033[0m\] '
fi
```