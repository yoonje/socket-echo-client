#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int main(int argc, char **argv) {
    int client_socket;

    struct sockaddr_in server_addr;

    char buff[BUFF_SIZE + 5];

    client_socket = socket(PF_INET, SOCK_STREAM, 0); // PF_INET은 프로토콜 체계에서 IPv4, SOCK_STREAM은 TCP를 의미
    if (-1 == client_socket) {
        printf("socket 생성 실패\n");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr)); // 0으로 초기화
    server_addr.sin_family = AF_INET; // AF_INET은 주소 체계에서 IPv4를 의미
    server_addr.sin_port = htons(4000); // htons 함수를 통해서 Little Endian일 경우 Big Endian으로 변경하여 포트 번호 대입
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 32bit IPv4 주소로 초기화

    if (-1 == connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        printf("접속 실패\n");
        exit(1);
    }
    write(client_socket, argv[1], strlen(argv[1]) + 1); // +1: NULL까지 포함해서 전송
    close(client_socket);
    return 0;
}