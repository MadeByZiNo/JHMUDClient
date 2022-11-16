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
    cout << "                   계속하시려면 엔터키를 눌러주세요                       " << endl;
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
    //클라이언트는 실행시에 서버에 연결을 시도한다.

    cout << "서버에 연결중입니다.. 잠시만 기다려주세요..";
    
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
    cout << "연결완료";
    Sleep(500);

    //연결 완료 후에는 인트로를 띄운다.

    startIntro();
    system("cls");
    
    //닉네임을 입력받고 서버에 보내서 로그인을 시도한다.

    char inputNickname[20];
    cout << "사용할 닉네임을 입력해주세요." << endl;
    cin >> inputNickname;


    if (sendMessage(inputNickname,sock) == 1) {
        exit(1);
    }
    
    system("cls");
    
    shared_ptr<char> buf = recvMessage(sock);
    if (buf == nullptr) { return false; }
    cout << buf.get();
    cout << "   명령어를 입력해주세요   " << endl;
    cout << "↓↓↓↓명령어 종류↓↓↓↓" << endl;
    cout << "                           " << endl;
    cout << "move x y   : 현재 좌표에서 x y만큼 이동합니다. " << endl;
    cout << "                           " << endl;
    cout << "attack     : 주위의 적들을 공격합니다. " << endl;
    cout << "                           " << endl;
    cout << "monsters   : 몬스터들의 좌표를 나열합니다. " << endl;
    cout << "                           " << endl;
    cout << "users      : 유저의 이름과 좌표를 나열합니다. " << endl;
    cout << "                           " << endl;
    cout << "chat 유저이름 대화내용   : 유저에게 대화내용을 전달합니다. " << endl;
    cout << "                           " << endl;
    cout << "bot        : bot모드를 활성화합니다. " << endl;


    while (1)
    {
       //명령어를 입력받는다.
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
            cout << "\n\n 올바른 명령을 입력해주세요.\n\n";
            Sleep(1500);
        }
    }

    // Socket 을 닫는다.
    r = closesocket(sock);
    if (r == SOCKET_ERROR) {
        std::cerr << "closesocket failed with error " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Winsock 을 정리한다.
    WSACleanup();
    return 0;
}
