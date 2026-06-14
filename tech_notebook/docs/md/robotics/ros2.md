# ROS2 
- **ROS (Robot Operating System):** Robot uygulamaları geliştirmek için sunduğu mesajlaşma altyapısı ve araç setiyle, farklı yazılım bileşenlerinin (düğüm, node) birbirleriyle kolayca iletişim kurmasını sağlar.

| Özellik |	ROS 1	| ROS 2 |
|---------|---------|-------|
| Mimari |	Merkezi (master node) |	Merkeziyetsiz (no master) |
| Gerçek Zaman Desteği	| Sınırlı	| DDS tabanlı, gerçek zaman yetenekli |
| Çoklu Dil Desteği| C++, Python	| C++, Python, Java, Rust, … |
| Ağ Desteği |	Aynı ağda (multicast)| 	Farklı ağlarda firewall dostu |
| Güvenlik	| Ek eklentiler gerekir |	DDS Security eklentisi |

- Yeni bir paket oluşturduğunuzda, `src/` altında dil fark etmeksizin (C++, Python vb.) `ros2 pkg create` ile paket iskeletleri oluşturulur.
- Bir ROS/ROS 2 çalışma alanı (workspace), genellikle şu dizinleri içerir:

```
<workspace>/
├─ src/        # Paket kaynak kodları
├─ build/      # Derleme dosyaları
├─ install/    # Kurulum (derlenmiş paketler)
└─ log/        # Derleyici ve runtime logları
```

- **RCL:** “ROS Client Library”
- **RCLCPP / RCLPY:** C++ ve Python için üst katman kütüphaneleri.
- Mesajlaşma, parametre, zamanlayıcı, servis ve aksiyon gibi temel API’leri sunar.

- **RQT:** Qt tabanlı GUI panelleri; topic’ler, parametreler, servislere erişim ve grafik çizimler yapar.
- **ros2 doctor --report:** Sistem yapılandırmanızı analiz eder, eksik bağımlılıkları ve uyumsuzlukları raporlar.

```bash
NETWORK CONFIGURATION

PLATFORM INFORMATION

RMW MIDDLEWARE

ROS 2 INFORMATION

TOPIC LIST
```

### Logging (Günlükleme)

- **Log seviyeleri:** `DEBUG, INFO, WARN, ERROR, FATAL`.
```c++
RCLCPP_INFO(node->get_logger(), "Bilgi mesajı");
RCLCPP_WARN(node->get_logger(), "Uyarı mesajı");
RCLCPP_ERROR(node->get_logger(), "Hata mesajı");
RCLCPP_DEBUG_STREAM(node->get_logger(), "Detay: " << variable);
```

```bash title="Komut Satırları"
ros2 run <pkg> <exe> --ros-args --log-level debug
ros2 run <pkg> <exe> --ros-args --log-level <node_name>:=warn
```

- Log dosyaları `~/.ros/log/` altında saklanır `rqt_logging` ile de izleyebilirsiniz.

### DDS ve DOMAIN ID
- ROS 2, **DDS** (Data Distribution Service) protokolünü kullanır.
- **Domain ID:** Aynı DDS domain’inde olan düğümler birbirini görür.
    - Varsayılan: `0`
    - Güvenli aralık: `0–101` (Linux port çakışmalarından kaçınmak için).
    - DD S UDP port aralığı: `0–65535` → Domain ID `0–232` önerilir.
```bash
export ROS_DOMAIN_ID=42
# Geçerli aralığı kontrol
cat /proc/sys/net/ipv4/ip_local_port_range
```

- `export ROS_LOCALHOST_ONLY=1` Düğümler yalnızca localhost üzerinden iletişim kurar; diğer cihazlardan erişim engellenir.

### Derleme Zamanında Hata Ayıklama
- `colcon build --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo` 
    - **RelWithDebInfo:** Optimize edilmiş kodda hata ayıklama sembollerini tutar.
- `ros2 run --prefix "gdbserver localhost:3000" <pkg_name> <node_executable>`
    - **gdbserver:** Kodunuzu dinleyen bir sunucu gibi çalışır.
    - **localhost:3000:** VS Code veya başka bir istemci bu port üzerinden hata ayıklamayı üstlenir.

- vs code launch.json  dosyası:
```json title="launch.json" linenums="1" hl_lines="10"
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "ROS2 C++ Remote Debug",
      "type": "cppdbg",
      "request": "launch",
      "miDebuggerServerAddress": "localhost:3000",
      "miDebuggerPath": "/usr/bin/gdb",
      "program": "${workspaceFolder}/install/<pkg_name>/lib/<pkg_name>/<node_executable>",
      "cwd": "${workspaceFolder}",
      "stopAtEntry": false,
      "environment": [],
      "externalConsole": false
    }
  ]
} 
```

- **program:** Hata ayıklamak istediğiniz executable’ın tam yolu (colcon install sonrası).
- **miDebuggerServerAddress:** gdbserver’ın dinlediği adres ve port.
- Diğer ayarlar (stopAtEntry, environment) tercihinize göre düzenlenebilir.

- VS Code’da `Run & Debug` panelinden bu konfigürasyonu seçip başlatın. Kod, gdbserver üzerinden bağlanacak ve breakpoint’lerinizde duracaktır.

- Menüden Terminal → Run Build Task ya da `Ctrl+Shift+P`
```json title="tasks.json" linenums="1" 
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build Release",
      "type": "shell",
      "command": "source /opt/ros/${command:rosdistro}/setup.bash && colcon build --symlink-install"
    },
    {
      "label": "Build Debug",
      "type": "shell",
      "command": "source /opt/ros/${command:rosdistro}/setup.bash && colcon build --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo --symlink-install"
    }
  ]
} 
```

###  DDS Katmanını Seçme

```bash
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
# veya
export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
```

## Paket Oluşturma ve Çalıştırma

1. **Ortamı Hazırlama (Setup):** `echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc`

	```bash title=".bashrc"
	# ROS 2 dağıtımını yükle
	source /opt/ros/humble/setup.bash

	# Colcon argcomplete ile otomatik tamamlama (tab ile paket/komut önerisi)
	source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash
	```

	!!! note "Not"
		`colcon build` komutunu sisteme “eklemek” zorunlu değil; ancak argcomplete sayesinde paket adları ve düğüm isimleri **tab** tuşuyla tamamlanır.

2. **Bağımlılıkları Kurma (rosdep):** Çalışma alanınızdaki paketlerin sistemdeki eksik kütüphane ve bağımlılıklarını otomatik kurmak için

    - `--from-paths src` → yalnızca sizin src/ içindeki paketleri tarar.
    - `--ignore-src` → kaynak kodu değil, sistem paketlerini yükler.

	```bash
	rosdep update
	rosdep install --from-paths src --ignore-src --rosdistro humble -y
	```


3. **Paket Oluşturma:**

	=== "C++"

		```bash
			ros2 pkg create --build-type ament_cmake --node-name my_node --dependencies rclcpp  my_cpp_pkg
		```

	=== "Python"

		```cmake
			ros2 pkg create --build-type ament_python --node-name my_node --dependencies rclpy  my_cpp_pkg
		```



	!!! note "Not"
		Eğer `--node-name` parametresi verilmezse, sadece paket klasörü ve temel dosyalar **(package.xml, CMakeLists.txt veya setup.py)** oluşturulur.


	```bash title="Lisans ve Diğer Optiyonlar"
	ros2 pkg create --build-type ament_cmake --node-name dstar_node --license Apache-2.0 --dependencies rclcpp std_msgs dstar_package
	```

	- `--license` → otomatik olarak package.xml içine lisans etiketi ekler.
	- `--dependencies` → package.xml ve (C++) CMakeLists.txt dosyasına gerekli kütüphane tanımlamalarını ekler.

4. **Derleme ve Paket Seçimi:**

	```bash
	colcon build
	colcon build --packages-select my_cpp_pkg my_py_pkg
	colcon build --symlink-install --packages-select my_py_pkg

	colcon graph  # Hangi paketin hangi pakete bağlı olduğunu çizimle gösterir.
	```

5. **Çalışma Alanını Aktif Etme:**

	```bash
	# Kök dizinde:
	source install/setup.bash

	# Alternatif olarak, yalnızca bu dizin için:
	source install/local_setup.bash
	```

6. **Düğümleri Çalıştırma ve Remap:**

	```bash
	# Basit Çalıştırma
	ros2 run my_cpp_pkg my_node_executable
	ros2 run my_py_pkg my_python_node

	# Launch Dosyaları
	ros2 launch my_cpp_pkg my_launch_file.launch.py

	# Remapping (Yeniden Adlandırma) Node adını değiştirme:
	ros2 run demo_nodes_cpp talker --ros-args -r __node:=new_talker

	# Topic/Service adını değiştirme:
	ros2 run my_pkg talker --ros-args -r /old_topic:=/new_topic -r /old_service:=/my_service
	```

	!!! note "Not"
			-r kısa adıyla da kullanılabilir. Remap, aynı paketi birden çok kez farklı isimlerle çalıştırmanızı sağlar.


7. **Görselleştirme: RQT**
	```bash
	rqt
	rqt_graph
	```

### Node
Her biri tek bir görevi (sensör okuma, kontrol komutu üretme, görüntü işleme vb.) yerine getiren bağımsız yürütülebilir bileşenlerdir. Dilediğiniz programlama dilinde (C++, Python, Rust…) yazabilirsiniz; ROS 2, bu düğümlerin haberleşmesini sağlar.

```bash
ros2 node list                # Aktif tüm node'ları listeler
ros2 node info /[node_name]   # Tek bir node hakkında ayrıntılı bilgi verir
```

### Topic 
**Publish/Subscribe** modeline dayalı, **asenkron** veri akış kanalıdır. Birden fazla publisher ve subscriber olabilir; gönderici beklemeksizin mesajını yayınlar.

```bash title="Temel Komutlar" linenums="1"
ros2 topic list                    # Tüm aktif topic’leri listeler
ros2 topic list -t                 # Tip bilgisiyle beraber listeler
ros2 topic echo /[topic]           # Yayınlanan mesajları gerçek zamanlı gösterir
ros2 topic info /[topic]           # Kaç publisher/subscriber olduğunu söyler
ros2 topic hz /[topic]             # Ortalama yayın hızını (Hz) ölçer
ros2 topic bw /[topic]             # Bant genişliği kullanımını gösterir
```

```bash title="Mesaj Yayınlama (Publisher)" linenums="1"
# Tek seferlik
ros2 topic pub /chatter std_msgs/msg/String "data: 'Merhaba ROS2'" --once

# Sürekli yayın, örn. 10 Hz
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 1.0}, angular: {z: 0.5}}" -r 10
```

```bash title="Mesaj Türü İnceleme" linenums="1"
ros2 interface show std_msgs/msg/String
```

### Service (Hizmet)
**Request–Response modeliyle çalışır:** client, service’e istek (request) gönderir; server işlem yapıp cevap (response) döner. Senkron iletişim gerektiren durumlar için idealdir.

```bash title="Listeleme ve Tür" linenums="1"
ros2 service list              # Tüm servisleri listeler
ros2 service list -t           # Tip bilgisiyle beraber listeler
ros2 service type /[service]   # Bir servisin veri tipini gösterir
```

```bash title="Servis Çağrısı (Client)" linenums="1"
ros2 service call /clear std_srvs/srv/Empty "{}"
ros2 service call /spawn turtlesim/srv/Spawn "{x: 2.0, y: 3.0, theta: 1.57, name: 'turtle2'}"
```

```bash title="Servis Mesaj Şeması" linenums="1"
ros2 interface show turtlesim/srv/Spawn
```

!!! note "Not"
	Çıktıda `---` ile ayrılmış bölüm, request ve response alanlarını gösterir.


### Action
**Goal–Feedback–Result** modeline sahip, uzun süreli işlemleri kontrol etmek için tasarlanmıştır. İptal edilebilir ve ara aşama bilgilerini (`feedback`) alabilirsiniz.

```bash title="Listeleme ve Bilgi" linenums="1"
ros2 action list               # Tüm action’ları listeler
ros2 action list -t            # Tip bilgisiyle beraber listeler
ros2 action info /[action]     # Detaylı tip ve arayüz bilgisi
```

```bash title="Action Kullanımı" linenums="1"
ros2 action send_goal /fibonacci example_interfaces/action/Fibonacci "{order: 10}"
```

- `send_goal` ile istek gönderdikten sonra:
	- feedback ve result çıktıları otomatik gösterilir.
	- İsterseniz `--feedback` ve `--result` bayraklarıyla ekstra kontroller yapabilirsiniz.

### Launch
Birden fazla düğümü **tek komutla** başlatmanızı sağlayan Python tabanlı betiklerdir (`.launch.py`). Parametre aktarımı, remap, ns (namespace) oluşturma, koşullu başlatma gibi ileri düzey senaryoları destekler.

```bash title="" linenums="1"
ros2 launch my_pkg bringup.launch.py
```

```python title="" linenums="1"
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='demo_nodes_cpp',
            executable='talker',
            name='my_talker',
            remappings=[('/chatter', '/my_chatter')],
            parameters=[{'use_sim_time': True}],
            output='screen'
        ),
        Node(
            package='demo_nodes_cpp',
            executable='listener',
            name='my_listener',
            output='screen'
        )
    ])
```

- `remappings` ile topic veya node isimlerini çalışma zamanında değiştirebilirsiniz.
- `parameters` listesiyle YAML yerine doğrudan Python dict kullanabilirsiniz.
- `output='screen'` veya `output='log'` ile çıktının yönünü belirleyin.
- `respawn=True` parametresi ile node’un çöktüğünde otomatik yeniden başlatılmasını sağlayabilirsiniz.

### Mesaj (.msg) ve Servis (.srv) Dosyaları

- **İsimlendirme Kuralları:** Dosya adı boşluk içermez; kelime ayrımı için PascalCase (her kelime büyük harfle başlar) tercih edilir `Position2D.msg, ComputePath.srv`
- Paket içindeki referanslarda alt çizgi (_) kullanılır `my_robot_interfaces/msg/Position2D.msg, my_robot_interfaces/srv/ComputePath.srv`

```title=".msg"
# Position2D.msg
float64 x
float64 y
float64 theta
```

```title=".srv"
# ComputePath.srv
Position2D start
Position2D goal
---
Position2D[] path
```

!!! note "Not"
	`---` satırı, request ile response bölümlerini ayırır. Action dosyalarında `---` ayracı iki kez kullanılır: **Goal** ile **Result** arası, **Result** ile **Feedback** arası

- Yeni Dosya Ekledikten Sonra 

```bash
colcon build --packages-select my_pkg --allow-overriding
```

```bash
ros2 interface list                       # Tüm msg/srv/—action arayüzlerini listeler
ros2 interface packages                   # Arayüz tanımlı paketleri listeler
ros2 interface package my_pkg             # Paketin içerdiği msg/srv/action dosyalarını gösterir
ros2 interface show my_robot_interfaces/Position2D  # Belirli bir mesajın içeriğini gösterir
```

###  Parametreler

- **Parametreler**, bir node’un çalışma zamanındaki yapılandırma değerleridir (ör. hız sınırları, PID katsayıları, yol planlama seçenekleri).
- **Türü:** int, float, bool, string, list vb.
- Kod yeniden derlenmeden de runtime’da güncellenebilir.

```bash title="Temel Komutlar" linenums="1"
# Node’daki tüm parametreleri listeler
ros2 param list /my_node

# Belirli bir parametrenin tanımını gösterir
ros2 param describe /my_node max_speed

# Parametre değerini görüntüler
ros2 param get /my_node max_speed

# Parametre değerini atar
ros2 param set /my_node max_speed 2.5
```

```yaml title="config/my_params.yaml"
my_node:
  ros__parameters:
    max_speed: 3.0
    enabled: true
    waypoints: [ [0,0], [1,1], [2,2] ]
```

```bash title="Yükleme"
ros2 run my_pkg my_node --ros-args --params-file config/my_params.yaml
```

```bash title="Dump / Load"
# Aktif parametreleri dosyaya kaydet
ros2 param dump /my_node > params.yaml

# Dosyadan parametreleri yükle
ros2 param load /my_node params.yaml
```

### Kayıt & Yeniden Oynatma (ros2 bag)
```bash title="record"
# Belirli bir topic’i kaydet
ros2 bag record /cmd_vel

# Tüm aktif topic’leri kaydet
ros2 bag record -a

# Belirli topic’lerin alt kümesini kaydet, dosya adı “subset” olsun
ros2 bag record -o subset /turtle1/cmd_vel /turtle1/pose
```

- **Kayıt dosyaları:** `YYYY_MM_DD_HH_MM_SS` formatında klasör olarak oluşturulur.
- `-o <isim>` ile klasör adını belirleyebilirsiniz.

```bash title="info"
ros2 bag info subset
```

```bash title="play"
ros2 bag play subset
ros2 bag play --loop subset
```

##  Ek İpuçları

```bash title="Gazebo ile Entegrasyon"
export GZ_VERSION=garden
export GZ_SIM_RESOURCE_PATH=~/models:~/other_models
export GZ_SIM_SYSTEM_PLUGIN_PATH=~/build/plugins
```
```bash title="RMW Middleware Seçimi"
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
# veya
export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
```
```bash title="PlotJuggler ile Görselleştirme"
sudo snap install plotjuggler
ros2 run plotjuggler plotjuggler
```
