#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Bu program:
 * - Linux sistem komutunu çalıştırır
 * - stdout çıktısını pipe üzerinden okur
 * - IP adreslerini satır satır parse eder
 *
 * Not:
 * popen() → shell üzerinden process açar (fork + exec + pipe)
 * güvenlik açısından input kontrollü kullanılmalıdır
 */

int main(void)
{
    // Linux network stack üzerinden IPv4 adreslerini filtreleyen komut
    // grep -oP → Perl regex kullanır
    // (?<=inet\s) → "inet " sonrası IP yakalanır
    const char *command =
        "ifconfig | grep -oP '(?<=inet\\s)\\d+(\\.\\d+){3}'";

    char buffer[128];

    /*
     * popen:
     * - shell process başlatır
     * - stdout'u pipe'a yönlendirir
     *
     * risk:
     * - shell injection (command string dynamic olmamalı)
     */
    FILE *pipe = popen(command, "r");

    if (!pipe)
    {
        perror("popen failed");
        return EXIT_FAILURE;
    }

    /*
     * fgets:
     * - stream buffer'dan line-based okuma yapar
     * - buffer overflow kontrolü sağlar
     */
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        // newline temizleme:
        // strcspn → ilk '\n' indexini bulur
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("IP address: %s\n", buffer);
    }

    /*
     * pclose:
     * - child process kapanışını bekler
     * - exit status döner (debug için kullanılabilir)
     */
    pclose(pipe);

    return EXIT_SUCCESS;
}