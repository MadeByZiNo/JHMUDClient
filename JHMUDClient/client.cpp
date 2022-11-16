#include <chrono>
#include <iostream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <thread>

#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;
//27015
static unsigned short SERVER_PORT = 27015;
    
void startIntro()
{
    cout << "       *                                                 *                " << endl;
    cout << "                *                            *                            " << endl;
    cout << "                              *                               *           " << endl;
    cout << "          *                                                               " << endl;
    cout << "                                                                          " << endl;
    cout << "           ~@ * #@;    @@;      = @@@. *   @@ =.;@ = . =@:. @@@@@@@, .    " << endl;
    cout << "           :@*  #@;    @@;       =@@@~   .=@@=. ;@=   .=@: ,@@=**#@@:     " << endl;
    cout << "           :@*  #@!    @@;       =@@@$   ~@*@=. ;@=   .=@: ,@#-  ,#@#,    " << endl;
    cout << "           ~@*  #@;    @@;       =@!##,  :@-@=. ;@=   .=@: .@#-    @@~    " << endl;
    cout << "           ~@*  #@=::~~@@;       =@!#@!  @$~@=. ;@=   .=@: .@#-    @@:    " << endl;
    cout << "           ~@*  #@@@@@@@@;       =@!~@=.~@;-@=. ;@=   .=@: .@#-    @@:    " << endl;
    cout << "           ~@*  #@!,,,,@@;       =@; @@~@#-,@=. ;@=   .=@~ .@#-    @@:    " << endl;
    cout << "           !@;  #@;    @@;.      =@! ;@;@=.,@=. ;@#.  ,#@, ,@#-   ~@#-    " << endl;
    cout << "          .@@-  #@;    @@;       =@! ,@#@; ,@=. :@@:  *@@. .@#- .;@@!     " << endl;
    cout << "        ;@@@#.  #@;    @@;       =@!  !@@, -@=.  $@@@@@@:  .@@@@@@@=.     " << endl;
    cout << "        :## = -*$ : = $ : ; = :  ~== , $!.  . = $##$; .  . = $ = $ == ~   " << endl;
    cout << "                                                                          " << endl;
    cout << "          *                          *          *                         " << endl;
    cout << "     *                                      *                             " << endl;
    cout << "                          *                                         *     " << endl;
    Sleep(2000);
    system("cls");
    cout << "       *                                                 *                " << endl;
    cout << "                *                            *                            " << endl;
    cout << "                              *                               *           " << endl;
    cout << "          *                                                               " << endl;
    cout << "                                                                          " << endl;
    cout << "           ~@ * #@;    @@;      = @@@. *   @@ =.;@ = . =@:. @@@@@@@, .    " << endl;
    cout << "           :@*  #@;    @@;       =@@@~   .=@@=. ;@=   .=@: ,@@=**#@@:     " << endl;
    cout << "           :@*  #@!    @@;       =@@@$   ~@*@=. ;@=   .=@: ,@#-  ,#@#,    " << endl;
    cout << "           ~@*  #@;    @@;       =@!##,  :@-@=. ;@=   .=@: .@#-    @@~    " << endl;
    cout << "           ~@*  #@=::~~@@;       =@!#@!  @$~@=. ;@=   .=@: .@#-    @@:    " << endl;
    cout << "           ~@*  #@@@@@@@@;       =@!~@=.~@;-@=. ;@=   .=@: .@#-    @@:    " << endl;
    cout << "           ~@*  #@!,,,,@@;       =@; @@~@#-,@=. ;@=   .=@~ .@#-    @@:    " << endl;
    cout << "           !@;  #@;    @@;.      =@! ;@;@=.,@=. ;@#.  ,#@, ,@#-   ~@#-    " << endl;
    cout << "          .@@-  #@;    @@;       =@! ,@#@; ,@=. :@@:  *@@. .@#- .;@@!     " << endl;
    cout << "        ;@@@#.  #@;    @@;       =@!  !@@, -@=.  $@@@@@@:  .@@@@@@@=.     " << endl;
    cout << "        :## = -*$ : = $ : ; = :  ~== , $!.  . = $##$; .  . = $ = $ == ~   " << endl;
    cout << "                                                                          " << endl;
    cout << "          *                          *          *                         " << endl;
    cout << "     *                                      *                             " << endl;
    cout << "                          *                                         *     " << endl;
    cout << "                                                                          " << endl;
    cout << "                                                                          " << endl;
    cout << "                   ����Ͻ÷��� ����Ű�� �����ּ���                       " << endl;
    while (!getchar());
    return;
}

int sendMessage(const char* message, SOCKET sock)
{
    int r = 0;
    int dataLen = strlen(message);
    int dataLenNetByteOrder = htonl(dataLen);
    int offset = 0;

    while (offset < 4) {
        r = send(sock, ((char*)&dataLenNetByteOrder) + offset, 4 - offset, 0);
        if (r == SOCKET_ERROR) {
            std::cerr << "failed to send length: " << WSAGetLastError() << std::endl;
            return 1;
        }
        offset += r;
    }

    char data[1000];
    strcpy(data, message);
    offset = 0;
    while (offset < dataLen) {
        r = send(sock, data + offset, dataLen - offset, 0);
        if (r == SOCKET_ERROR) {
            std::cerr << "send failed with error " << WSAGetLastError() << std::endl;
            return 1;
        }
        std::cout << "Sent " << r << " bytes" << std::endl;
        offset += r;
    }
    return 0;
}

shared_ptr<char> recvMessage(SOCKET sock)
{
    int dataLenNetByteOrder;
    int offset = 0;
    while (offset < 4) {
        int r = recv(sock, ((char*)&dataLenNetByteOrder) + offset, 4 - offset, 0);
        if (r == SOCKET_ERROR) {
            cerr << "recv failed with error " << WSAGetLastError() << endl;
            return nullptr;
        }
        else if (r == 0) {
            cerr << "Socket closed: " << sock << endl;
            return nullptr;
        }
        offset += r;
    }
    int dataLen = ntohl(dataLenNetByteOrder);
    cout << "[" << sock << "] Received length info: " << dataLen << endl;

    shared_ptr<char> buf(new char[dataLen + 1]);
    offset = 0;
    while (offset < dataLen) {
        int r = recv(sock, buf.get() + offset, dataLen - offset, 0);
        if (r == SOCKET_ERROR) {
            cerr << "recv failed with error " << WSAGetLastError() << endl;
            return nullptr;
        }
        else if (r == 0) {
            return nullptr;
        }
        cout << "[" << sock << "] Received " << r << " bytes" << endl;
        offset += r;
    }
    buf.get()[dataLen] = '\0';
    return buf;
}

int main()
{
    //Ŭ���̾�Ʈ�� ����ÿ� ������ ������ �õ��Ѵ�.

    cout << "������ �������Դϴ�.. ��ø� ��ٷ��ּ���..";
    
    int r = 0;

    WSADATA wsaData;
    r = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (r != NO_ERROR) {
        std::cerr << "WSAStartup failed with error " << r << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddr;

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "socket failed with error " << WSAGetLastError() << std::endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    r = connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (r == SOCKET_ERROR) {
        std::cerr << "connect failed with error " << WSAGetLastError() << std::endl;
        return 1;
    }
    
    system("cls");
    cout << "����Ϸ�";
    Sleep(500);

    //���� �Ϸ� �Ŀ��� ��Ʈ�θ� ����.

    startIntro();
    system("cls");
    
    //�г����� �Է¹ް� ������ ������ �α����� �õ��Ѵ�.

    char inputNickname[20];
    cout << "����� �г����� �Է����ּ���." << endl;
    cin >> inputNickname;


    if (sendMessage(inputNickname,sock) == 1) {
        exit(1);
    }
    
    system("cls");
    
    shared_ptr<char> buf = recvMessage(sock);
    if (buf == nullptr) { return false; }
    cout << buf.get();
    cout << "   ��ɾ �Է����ּ���   " << endl;
    cout << "������ɾ� ���������" << endl;
    cout << "                           " << endl;
    cout << "move x y   : ���� ��ǥ���� x y��ŭ �̵��մϴ�. " << endl;
    cout << "                           " << endl;
    cout << "attack     : ������ ������ �����մϴ�. " << endl;
    cout << "                           " << endl;
    cout << "monsters   : ���͵��� ��ǥ�� �����մϴ�. " << endl;
    cout << "                           " << endl;
    cout << "users      : ������ �̸��� ��ǥ�� �����մϴ�. " << endl;
    cout << "                           " << endl;
    cout << "chat �����̸� ��ȭ����   : �������� ��ȭ������ �����մϴ�. " << endl;
    cout << "                           " << endl;
    cout << "bot        : bot��带 Ȱ��ȭ�մϴ�. " << endl;


    while (1)
    {
       //��ɾ �Է¹޴´�.
        string s;
        cin >> s;
        if (s == "move")
        {
            int x, y;
            cin >> x >> y;
            
        }
        else if (s == "attack") {  }
        else if (s == "monsters")
        {
           /* list<slime*>::iterator iter;
            for (iter = slimes.begin(); iter != slimes.end(); iter++)
            {
                cout << "(" << (*iter)->getx() << "," << (*iter)->gety() << ")" << endl;
            }*/

        }
        else if (s == "users") {  }
        else if (s == "chat") { }
        else if (s == "bot") { }
        else
        {
            cout << "\n\n �ùٸ� ����� �Է����ּ���.\n\n";
            Sleep(1500);
        }
    }

    // Socket �� �ݴ´�.
    r = closesocket(sock);
    if (r == SOCKET_ERROR) {
        std::cerr << "closesocket failed with error " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Winsock �� �����Ѵ�.
    WSACleanup();
    return 0;
}
