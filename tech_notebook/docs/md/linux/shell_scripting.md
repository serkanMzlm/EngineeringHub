# Shell Script

- Linux’ta yaygın olarak Bash kullanılır; yüklü tüm shell’leri görmek için: `cat /etc/shells`
- Script’in hangi shell ile çalışacağını en başta belirtmek için **shebang** kullanılır: `#!/bin/bash`
- Satır başına `#` koyarak o satırı yorum haline getirirsiniz.

!!! note "Not"
    Shebang `(#!/bin/bash)` da aslında yorum satırı gibi davranır ama kernel’e hangi yorumlayıcıyı yükleyeceğini söyler.


| Operatör | 	Anlamı	| Örnek | 
|-------|-------------|---------|
| -eq | 	eşit	| `[ $a -eq 5 ]` | 
| -ne | 	eşit değil | 	`[ $a -ne 0 ]` | 
| -lt | 	küçük |	`[ $a -lt 10 ]` | 
| -gt | 	büyük |	`[ $a -gt 100 ]` | 
| -le | 	küçük veya eşit |	`[ $a -le 20 ]` | 
| -ge | 	büyük veya eşit	| `[ $a -ge 1 ]` | 
| -e | 	dosya veya dizin var mı	 | `[ -e /path/to/file ]` | 
| -f | 	normal dosya mu? |	`[ -f /etc/passwd ]` | 
| -d | 	dizin mi? |	`[ -d /home/user ]` | 


```bash
#!/bin/bash

# read, echo, değişkenler    
my_host=`hostname`   # Bilgisayarın hostname verisini alır
name="Arif"
name2=arif           # İki değişken atamasıda doğrudur.

echo "server name: $my_host"   # Ekrana çıktı vermeyi sağlar.
echo "My name is $name."       # Bir değişkene erişmek için $ kullanılır.   
echo what is your name?
read new_name                 # Kullanıcdan veri alınması sağlanır.
read new_surname              # Bu olay read name surname olarak tek seferde
                              # alınabilir. Bir bolukla değişkenler doldurulur.
echo hello $new_name

gun=$(date +%a)  # Mon, Tue, …

if [ "$gun" = "Mon" ]; then
  echo "Bugün Pazartesi."
elif [ "$gun" = "Tue" ]; then
  echo "Bugün Salı."
else
  echo "Hafta içi başka bir gün."
fi

for i in 1 2 3 4 5; do
  echo "Sayaç: $i"
done

for num in {1..10}; do
  echo "Numara = $num"
  sleep 1
done

count=0
while [ "$count" -lt 5 ]; do
  echo "Merhaba Dünya ($count)"
  ((count++))
  sleep 1
done

echo "Seçiminiz (a: ls, b: cd ~, c: echo):"
read choice

case "$choice" in
  a) ls ;;
  b) cd ~ ;;
  c) echo "Hello, world!" ;;
  *) echo "Geçersiz seçim!" ;;
esac
```