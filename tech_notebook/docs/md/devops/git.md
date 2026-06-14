# Git 

```mermaid
graph LR
  A[Working Directory] -->|git add| B{Staging Area};
  B -->|git commit| C[Local Repo];
  C --> |git push| D[Remote Repo];
  D --> |git pull| C;
  D --> |git fetch| C;
  D --> |git clone| C;
  C -->|git checout| A;
  C -->|git merge| A;
```

## Git Yapılandırma (Config)
- `--local`→ Mevcut repo içindeki **.git/config**
- `--global` → Kullanıcının **~/.gitconfig**
- `--system` → Sistem geneli **/etc/gitconfig**

```bash linenums="1"
# Kullanıcı bilgisi
git config --global user.name   "Serkan"
git config --global user.email  "serkanmazlum@gmail.com"

# Varsayılan editör
git config --global core.editor vim

# Tüm projelerde uygulanacak ignore dosyası
git config --global core.excludesfile ~/.gitignore_global

# Ayarları listele
git config --list

git --version        # Sistemde kurulu olan sürümü gösterir.
git help --all       # Git için bütün komutları gösterir.
git [command] --help # Belirli bir komut hakkında bilgi verir.
```

## Depo Oluşturma ve Klonlama
```bash linenums="1"
# Yeni repo başlatma
git init

# Mevcut bir depoyu klonlama
git clone [URL]

# Belirli branch ve alt modüllerle klonlama
git clone -b <branch> --recurse-submodules [URL]
```

## Durum Kontrolü & .gitignore
```bash linenums="1"
# Değişikliklerin kaba özeti
git status
git status -s    # kısa format

# gitignore dosyasında bulunan değişimleride gösterir.
git status --ignored 

# İzlenmemesini istediğiniz dosya/dizinleri ekleyin:
# .gitignore
*.log
build/
```

!!! note "Not"
    Eğer bir dosya önceden commit edildiyse ve sonra .gitignore’a eklerseniz: `git rm --cached <file>`

!!! note "Not"
    git status 
    ??: izlenemeyen dosya
    A: staging area eklenen dosya
    M: (modified) değiştirilmiş dosya
    D: (delete) silinmiş dosya.

## Staging (Sahneleme) & Commit

```bash linenums="1"
# Tüm değişiklikleri stage’e ekle
git add .

# Belirli dosyayı stage’e ekle
git add path/to/file

# Commit oluşturma
git commit -m "Mesaj"

# Değişiklikleri otomatik stage et + commit
git commit -am "Mesaj"

# Son commit mesajını veya içeriğini düzenle
git commit --amend
```

## Uzak Depolar (Remotes)

```bash linenums="1"
# Mevcut remote’ları listele
git remote -v

# Yeni remote ekle
git remote add origin https://github.com/you/repo.git

# Remote’u sil
git remote rm origin

# Remote adresini güncelle
git remote set-url origin git@github.com:you/repo.git

# Remote adını değiştir
git remote rename oldname newname

# Yerel branch’i remote’a gönder
git push origin main

# Tüm branch’leri gönder
git push --all

# Commit’leri alma + birleştirme
git pull origin main

# Zorla gönderme (dikkat!)
git push --force
```
!!! node "Not"
    `git update-index --skip-worktree [file_name]` komutu sayesinde belirli bir dosyayı o anlık göz ardı etmemizi sağlar. Tekrardan dahil etmek için `git update-index --no-skip-worktree [file_name]` komutu kullanılır
!!! note "Not"
    `git pull` aslında `git fetch` + `git merge` kombinasyonudur.

## Branch Yönetimi

```bash linenums="1"
# Branch listesi (aktifin yanında *)
git branch

# Yeni branch oluştur + geç
git checkout -b feature-x

# Branch’e geçiş
git checkout develop

# Branch silme
git branch -d feature-x    # güvenli siler (merge edilmediyse uyarır)
git branch -D feature-x    # zorla siler

# Varsayılan (main) branch’i yeniden adlandırma
git branch -M main
```

## Birleştirme (Merge) & Rebase
```bash linenums="1"
# Başka bir branch’i mevcut branch’e birleştir
git merge feature-x

# Rebase yaparak temiz geçmiş oluşturma
git rebase develop

# Rebase iptali (branch’in eski haline dön)
git rebase --abort
```

## Log ve İnceleme
```bash linenums="1"
# Commit geçmişi
git log

# Tek satırlık özet
git log --oneline

# Değişiklik dif’leriyle
git log -p

# Dosya bazlı geçmiş
git log --stat path/to/file

# Belirli committer’a göre filtrele
git log --committer="serkan"
```

## Etiketleme (Tags)

```bash linenums="1"
# Local tag listesi
git tag

# Yeni tag oluştur
git tag v1.0.0

# Tag’i göster
git show v1.0.0

# Tüm tag’leri remote’a gönder
git push origin --tags

# Belirli tag’i gönder
git push origin v1.0.0

# Remote’dan tag sil
git push origin :refs/tags/v1.0.0
```

## Alt Modüller (Submodules)

- `.gitsubmodules` dosyasına alt modüller kaydedilir.

```bash linenums="1"
# Submodule ekle
git submodule add [URL] path/to/sub

# Submodule init + update
git submodule update --init --recursive

# Submodule’ü güncelle
git submodule update --remote
```

## Farklılık İnceleme (Diff)

```bash linenums="1"
# Çalışma alanı vs. index
git diff

# Index vs. son commit
git diff --cached

# Alt modüller dahil diff
git diff --cached --submodule
```

## Fork Edilmiş Depoyu Senkronize Etme

```bash linenums="1"
# 1. Upstream’i ekle ve alın
git remote add upstream https://github.com/orijinal-kullanici/orijinal-repo.git
git fetch upstream

# 2. Tüm upstream branch’lerini yerelde oluştur
git branch -r \
  | grep -v '->' \
  | grep '^  upstream/' \
  | sed 's@  upstream/@@' \
  | xargs -n1 git branch --track

# 3. Yereldeki tüm branch’leri origin’e gönder
git push origin --all

# 4. Belirli branch’in commit sayısını öğren
git rev-list --count release/1.14

# 5. Upstream’den çektiğin branch’lerin local kopyalarını silme
git branch \
  | grep '^  upstream/' \
  | sed 's@  upstream/@@' \
  | xargs git branch -D

# 6. Origin’den yeni branch’leri lokalize et (tekrar)
git branch -r \
  | grep -v '->' \
  | grep '^  origin/' \
  | sed 's@  origin/@@' \
  | xargs -n1 git branch --track
```

```bash linenums="1" title="Büyük Dosyaları Geçici Olarak Hariç Tutma"
git update-index --skip-worktree path/to/large-file
# Yeniden dahil etmek için:
git update-index --no-skip-worktree path/to/large-file
```

```bash linenums="1" title="Geçmişten Büyük/Dosya Türlerini Temizleme"
git filter-branch --force \
  --index-filter \
    'git rm --cached --ignore-unmatch \
      -r *.png *.jpg *.pdf *.zip *.mp4 *.material *.dt2 *.sdf' \
  --prune-empty \
  --tag-name-filter cat \
  -- --all
```

!!! note "Uyarı"
    **Bu işlem bütün commit geçmişini değiştirir ve paylaşılan bir repoda dikkatli kullanılmalıdır!**