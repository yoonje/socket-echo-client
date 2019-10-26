#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void
main(int argc, char **argv) {
    int client_socket;

    struct sockaddr_in server_addr;

    if (argv[1] == NULL) {
        printf("메세지 입력 필요\n");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr)); // 0으로 초기화
    server_addr.sin_family = AF_INET; // AF_INET은 주소 체계에서 IPv4를 의미
    server_addr.sin_port = htons(4000); // htons 함수를 통해서 Little Endian일 경우 Big Endian으로 변경하여 포트 번호 대입
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 32bit IPv4 주소로 초기화

    client_socket = socket(PF_INET, SOCK_STREAM, 0); // PF_INET은 프로토콜 체계에서 IPv4, SOCK_STREAM은 TCP를 의미

    if (-1 == client_socket) {
        printf("socket 생성 실패\n");
        exit(1);
    }

    if (-1 == connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr))) { // 연결 요청
        printf("접속 실패\n");
        exit(1);
    }

    write(client_socket, argv[1], strlen(argv[1]) + 1); // 메세지 write, NULL까지 포함해서 전송하기 위해 +1
    close(client_socket); // 소켓 닫기

    return;
}