#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock kütüphanesini bağla

class UdpReceiver {
public:
    UdpReceiver(int port);
    ~UdpReceiver();
    void receive();

private:
    SOCKET sock;
    sockaddr_in serverAddr;
    char buffer[1024];
};

UdpReceiver::UdpReceiver(int port) {
    // Winsock'ı başlat
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock başlatılamadı!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Socket oluştur
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket oluşturulamadı!" << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Sunucu adresini ayarla
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Tüm arayüzlerden gelecek verileri dinle
    serverAddr.sin_port = htons(port); // Port numarasını ayarla

    // Socket'i bağla
    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Socket bağlanamadı!" << std::endl;
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

UdpReceiver::~UdpReceiver() {
    // Socket'i kapat ve Winsock'ı temizle
    closesocket(sock);
    WSACleanup();
}

void UdpReceiver::receive() {
    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    
    std::cout << "Veri alımı başlatıldı. Bekleniyor..." << std::endl;

    while (true) {
        // Veriyi al
        int bytesReceived = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                      (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0'; // Sonlandırıcı ekle
            std::cout << "Aldım: " << buffer << std::endl;
        } else {
            std::cerr << "Veri alınamadı!" << std::endl;
        }
    }
}

int main() {
    UdpReceiver receiver(1234); // 12345 portunu dinle
    receiver.receive();
    return 0;
}
