# Tutorial

### Table of Contents

- C
- C++
- CMake
- Python
- Linux (Bash)
- Matlab
- ROS2
- Gazebo
- QT
- IPC (Inter Process Commonication)
- Serial
- MAVLink
- gstreamer

---

### C++

- The appearance of outputs for packages with loading bars

  - `loading_bar_1.cpp`
    ![image_1](images/loadbar_1.png)
  - `loading_bar_2.cpp`
    ![image_2](images/loadbar_2.png)
  - `loading_bar_3.cpp`
    ![image_3](images/loadbar_3.png)
  - `loading_bar_color_1.cpp`
    ![image_4](images/loadbar_color_y_1.png)
    ![image_4](images/loadbar_color_r_1.png)
    ![image_4](images/loadbar_color_g_1.png)
  - `loading_bar_color_2.cpp`
    ![image_4](images/loadbar_color_r_2.png)
    ![image_4](images/loadbar_color_y_2.png)
    ![image_4](images/loadbar_color_g_2.png)

- The code `g++ -o yaml_parser yaml_parser.cpp -lyaml-cpp` is used in the build process of packages that read data from YAML files
- To align the specified texts on the same lines, use the content of write_on_the_same_line.cpp code
```
\033[B     Move the cursor one lines down
\033[2B    Move the cursor two lines down
 
\033[A      Move the cursor one lines up
\033[2A     Move the cursor one lines up
``` 



```
#!/bin/bash
var="$(xxd -ps /sys/class/i2c-adapter/i2c-1/of_node/clock-frequency)"
var=${var//[[:blank:].\}]/}

```
## Raspberry Pi:
- Ethernet üzerinden bilgisayarda bulunan interneti raspberry aktarmak için []-cloud-init.ymal dosyası düzeltilmelidir.
```
# This file is generated from information provided by the datasource.  Changes
# to it will not persist across an instance reboot.  To disable cloud-init's
# network configuration capabilities, write a file
# /etc/cloud/cloud.cfg.d/99-disable-network-config.cfg with the following:
# network: {config: disabled}
network:
    version: 2
    renderer: networkd
    wifis:
        wlan0:
            access-points:
                SM:
                    password: "123456789"
            dhcp4: true
            optional: true
    ethernets:
        eth0:
            dhcp4: false
            addresses: [10.42.0.10/24]
            gateway4: 10.42.0.1  
            routes:
            - to: default
              via: 10.42.0.1
            nameservers:
                addresses: [10.42.0.1]
#                addresses:
#                    - 8.8.8.8
#                    - 8.8.4.4
```

## BASH 

- Terminal üzerinden direkt çıktının kopyalanması için `xsel --clipboard` komutu kullanılır. Bu komutu kolaylaştırmak için `alias copy='xsel --clipboard'` şeklinde **.bashrc** dosyasına yazılabilir.

### Kali Linux Terminal

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