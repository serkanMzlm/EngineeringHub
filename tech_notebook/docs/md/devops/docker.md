# Docker

## Genel Kavramlar
- **Container:** Uygulamanın kodunu, bağımlılıklarını ve çalışması için gereken her şeyi bir araya getiren, işletim sistemi seviyesinde izole edilmiş taşınabilir çalışma ortamıdır.
- **Docker:** Konteynerleri kolayca oluşturup yönetmenizi sağlayan platformdur. Linux çekirdeğinin isim alanları (namespaces) ve cgroups özelliklerini kullanarak hafif sanallaştırma sağlar.
- **Docker Hub:** Hazır container image’larının paylaşıldığı merkezi kayıt defteridir.
- **Volume:** Konteyner yaşam döngüsünden bağımsız veri saklamak için kullanılır. Konteyner silinse bile volume içindeki veriler korunur.

## Image Yönetimi

```bash title="pull" linenums="1"
docker pull ubuntu:20.04
docker pull node:16
docker pull redis
```
```bash title="Listeleme" linenums="1"
docker image ls    # İndirilen image'ları gösterir
docker image tag ubuntu:20.04 my_ubuntu:latest
docker image rm <IMAGE_ID_or_NAME>
```

## Konteyner Yönetimi

```bash title="run" linenums="1"
docker run [OPTIONS] IMAGE [COMMAND] [ARGS...]
```

- `-d` Arka planda (detached) çalıştırır.
- `-it` İnteraktif terminal açar (`-i` stdin açık, `-t` tty tahsis eder).
- `--name <name>` Konteynere kolay hatırlanır bir isim verir.
- `-p <hostPort>:<containerPort>` Port eşlemesi yapar.
- `-v <hostPath>:<containerPath>` Host–konteyner arasında volume mount eder.
- `-e KEY=VALUE` Ortam değişkeni ayarlar.
- `--network <net>` Belirli Docker ağına bağlar.
- `--link <other>:<alias>` Eski stil bağlantı, yerine kullanıcı tanımlı ağ ve DNS önerilir.


```bash title="" linenums="1"
docker run -d --name my_mongo -p 27018:27017 -v ~/mongo-data:/data/db mongo:6.0
```
```bash title="" linenums="1"
docker stop my_mongo # Durdurma
docker start my_mongo # Başlatma
docker rm my_mongo # Çalıştırma
docker container prune # Tüm durdurulmuş konteynerleri temizleme

docker ps # Çalışan konteynerler listeleme
docker ps -a # Tüm konteynerler listeleme

docker attach my_mongo # Bağlanma
docker logs my_mongo # Log görüntüleme 
docker inspect my_mongo # Detaylı bilgi
```

```bash title="Ağ Yönetimi" linenums="1"
docker network ls # Listeleme
docker network create --driver bridge --subnet 172.18.0.0/16 my_bridge_net # Oluşturma
docker network rm my_bridge_net # Silme

```

```bash title="Volume Yönetimi" linenums="1"
docker volume ls
docker volume create my_volume
docker volume rm my_volume
docker volume prune # Tüm kullanılmayan volümleri temizleme
```

## Dockerfile & Build

```bash title="" linenums="1"
docker build -t my_app:1.0 . # Dockerfile ile image oluşturma (-t : Oluşacak image’a isim ve tag verir.)

docker-compose build
docker-compose up -d
docker-compose down
```

### İpuçları

- Veri kalıcılığı için her zaman -v veya named volume kullanın.
- Ağ izolasyonu ve container DNS’yi kullanmak için custom network tercih edin, `--link` artık eskidi.
- Geliştirme aşamasında `--rm` bayrağıyla otomatik silinmeyi sağlayın:

```bash title="" linenums="1"
docker run --rm -it my_app:dev
```

- Image katmanlarını küçültmek, multi-stage build ile gereksiz dosyaları final image’dan çıkarmak performans ve güvenlik için kritiktir

```bash title="" linenums="1"
```

### Docker Network Türleri

Docker, konteynerler arası ve host ile container arasındaki iletişimi farklı ağ sürücüleri (drivers) ile yönetir:

| Ağ Türü |	Açıklama | 
|-------|-------|
| `bridge`	| Varsayılan ağ. İzole bir köprü ağıdır; her container bu ağda kendi IP’sini alır. | 
| `none` |	Hiçbir ağa bağlı olmaz; dış erişime kapalı, tamamen izole konteyner. | 
| `host` |	Container, host’un network yığınıyla paylaşılır; port eşlemesine gerek kalmaz. | 
| `custom`	| Kullanıcı tanımlı ağ: kendi subnet, gateway vb. ayarlarınızı yapabilirsiniz. | 

```bash
# none ağına bağlanarak mongo konteyneri çalıştırma
docker run --network none mongo

# host ağına bağlanma (Linux'ta geçerli)
docker run --network host nginx

# Örnek kullanıcı tanımlı ağ oluşturma
docker network create --driver bridge --subnet 182.18.0.0/16 --gateway 182.18.0.1 my_bridge_net
```

### Kendi Dockerfile’ınızı Yazmak
Bir uygulamayı konteynerleştirmek için projenizin kök dizininde Dockerfile oluşturun. Aşağıdaki örneklerde adım adım açıklamalar göreceksiniz.

```title="Ubuntu Tabanlı Örnek"
# 1. Base image
FROM ubuntu:18.04

# 2. Paket listelerini güncelle ve curl yükle
RUN apt-get update && apt-get install -y curl

# 3. Uygulama kodlarını kopyala
COPY . /opt/my-app/

# 4. Çalışma dizinini ayarla
WORKDIR /opt/my-app/

# 5. Ortam değişkeni tanımla
ENV APP_ENV=production

# 6. Uygulamayı başlat
CMD ["./start.sh"]
```

- Her `RUN/COPY` komutu bir layer (katman) oluşturur.
- `CMD` ile konteyner çalıştığında hangi komutun çalışacağı belirtilir.

```title="Node.js Tabanlı Örnek"
# 1. Node.js resmi image’ı (slim versiyonu daha küçük)
FROM node:14-slim

# 2. Çalışma dizinini ayarla
WORKDIR /usr/src/app

# 3. Bağımlılıkları kopyala ve yükle
COPY package*.json ./
RUN npm install

# 4. Uygulama kodunu kopyala
COPY . .

# 5. Uygulamanın dinleyeceği portu bildir
EXPOSE 3000

# 6. Varsayılan komut
ENTRYPOINT ["node", "index.js"]
```

- `ENTRYPOINT` ile konteyner argument’ları değişse bile sürekli çalışacak komut belirlenir.
- `CMD` override etmek mümkün; `ENTRYPOINT` ise kalıcıdır.

``` title=".dockerignore"
node_modules
.git
*.log
.env
```

### Docker Compose ile Çoklu Servis Yönetimi
Birden fazla konteyneri birlikte tanımlayıp çalıştırmak için docker-compose.yml kullanın. İndent (girinti) YAML’de kritiktir.

```yaml
version: "3.8"

services:
  webapp:
    build: .
    container_name: my_webapp
    ports:
      - "8080:80"
    volumes:
      - ./static:/usr/src/app/static
    environment:
      - NODE_ENV=production

  db:
    image: postgres:14
    container_name: my_db
    volumes:
      - db_data:/var/lib/postgresql/data
    environment:
      POSTGRES_USER: user
      POSTGRES_PASSWORD: pass
      POSTGRES_DB: appdb

networks:
  default:
    driver: bridge

volumes:
  db_data:
```

- `services` Çalıştırılacak konteyner tanımları.
- `build` Dockerfile’ın bulunduğu dizin (veya context).
- `image` Hazır image kullanımı.
- `ports` `<hostPort>:<containerPort>` eşlemesi.
- `volumes` Kalıcı veri saklama veya kod mount etme.
- `environment` Ortam değişkenleri.
- `networks/volumes` Kullanıcı tanımlı ağ ve kalıcı volume tanımları.

```title="Compose Komutları"
docker-compose build      # Tüm servisleri derler
docker-compose up -d      # Arka planda başlatır
docker-compose ps         # Servis durumunu gösterir
docker-compose logs -f    # Tüm logları takip eder
docker-compose down       # Tüm servisleri durdurur ve ağları siler
```