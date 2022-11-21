#define RAPIDJSON_HAS_STDSTRING 1
#include <chrono>
#include <iostream>
#include <list>
#include <mutex>
#include <sstream>
#include <stdlib.h>
#include <thread>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace rapidjson;
using namespace std;

static unsigned short SERVER_PORT = 27015;
    


//인트로 화면을 보여준다.
void showIntro()
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

void showCommand()
{
    cout << "\n\n   명령어를 입력해주세요   " << endl;
    cout << "↓↓↓↓명령어 종류↓↓↓↓" << endl;
    cout << "                           " << endl;
    cout << "data   : 현태 내 캐릭터의 데이터를 확인합니다. " << endl;
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
    cout << "                           " << endl;
    cout << "help        : 명령어들을 보여줍니다. " << endl;
    cout << "                           " << endl;
    cout << "clear        : 화면을 정리합니다. " << endl<<endl<<endl;

}
//메시지를 보낸다. 실패시 1, 성공시 0을 반환한다.
int sendMessage(const char* message, SOCKET sock)
{
    cout << message;
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

//메시지를 스마트 포인터로 받는다. 잘못받을시 nullptr의 포인터를 반환한다.
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

//객체를 string으로 변환한다.
string getJsonmessage(Document& d)
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}

void messageControler(SOCKET sock)
{
    //서버로부터 계속 메시지를 받으려고 한다.
    while (true)
    {
     
        shared_ptr<char> buf = recvMessage(sock);
        if (buf == nullptr) { cout << "recv error"; exit(1); }

        Document d;
        d.Parse(buf.get());

        Value& _command = d["command"];
 

        if (strcmp(_command.GetString(), "slimeAttack") == 0) 
        {
            Value& _nickname = d["nickname"];
            Value& _hp = d["hp"];
            Value& _damaged = d["damaged"];
            Value& _status = d["status"];
            Value& _who = d["who"];
            if (strcmp(_status.GetString(), "live")==0)
            {
                cout <<_nickname.GetString()<< "이(가) 슬라임에게 " << _damaged.GetInt() << "의 데미지를 입었다!\n 남은 hp : " << _hp.GetInt();
            }
            else if (strcmp(_status.GetString(), "death")==0)
            {
                if (strcmp(_who.GetString(), "commander") == 0)
                {
                    cout << _nickname.GetString() << "이(가) 슬라임에게 " << _damaged.GetInt() << "의 데미지를 입었다!\n캐릭터가 사망하여 종료합니다.";
                    exit(1);
                }
                if (strcmp(_who.GetString(), "receiver") == 0)
                {
                    cout << _nickname.GetString() << "이(가) 슬라임에게 " << _damaged.GetInt() << "의 데미지를 입었다!\n"<<_nickname.GetString()<<"의 캐릭터가 사망하였습니다\n";
                }
            }
        }
        else if (strcmp(_command.GetString(), "checkdata") == 0)
        {
            Value& _nickname = d["nickname"];
            Value& _x = d["x"];
            Value& _y = d["y"];
            Value& _hp = d["hp"];
            Value& _str = d["str"];
            Value& _potionhp = d["potionhp"];
            Value& _potionstr = d["potionstr"];


            cout << "=======캐릭터 정보======" << endl;
            cout << "닉네임 : " << _nickname.GetString() << endl;
            cout << "  hp : " << _hp.GetInt() << endl;
            cout << "  str : " << _str.GetInt() << endl;
            cout << "  x : " << _x.GetInt() << endl;
            cout << "  y : " << _y.GetInt() << endl;
            cout << "  potionHp : " << _potionhp.GetInt() << endl;
            cout << "  potionstr : " << _potionstr.GetInt() << endl;
            cout << "=======캐릭터 정보======" << endl << endl;
        }
        else if (strcmp(_command.GetString(),"inputNickname") == 0)
        {
            // 서버로부터 생성된 캐릭터 정보를 입력받는다.

            Value& _result = d["result"];   
            Value& _nickname = d["nickname"];
            Value& _x = d["x"];
            Value& _y = d["y"];
            Value& _hp = d["hp"];
            Value& _str = d["str"];
            Value& _potionhp = d["potionhp"];
            Value& _potionstr = d["potionstr"];

            if (strcmp(_result.GetString(), "load") == 0) { cout << "저장된 데이터를 불러옵니다.\n" << endl; }
            else { cout << "저장된 데이터가 없어 새로 생성합니다.\n" << endl; }
            cout << "=======캐릭터 정보======" << endl;
            cout << "닉네임 : " << _nickname.GetString() << endl;
            cout << "  hp : " << _hp.GetInt() << endl;
            cout << "  str : " << _str.GetInt() << endl;
            cout << "  x : " << _x.GetInt() << endl;
            cout << "  y : " << _y.GetInt() << endl;
            cout << "  potionHp : " << _potionhp.GetInt() << endl;
            cout << "  potionstr : " << _potionstr.GetInt() << endl;
            cout << "=====================" << endl << endl;

        }
        else if (strcmp(_command.GetString(), "move") == 0)
        {
            Value& _result = d["result"];

            //만약 던전범위가 벗어나 실패했으면 알람을 아니면 이동 후 좌표를 출력한다.
            if (strcmp(_result.GetString(), "fail") == 0)
            {
                cout << "던전 범위를 벗어날 수 없습니다.";
            }
            else if (strcmp(_result.GetString(), "success") == 0)
            {
                Value& _x = d["x"];
                Value& _y = d["y"];

                cout << "이동 후 : (" << _x.GetInt() << "," << _y.GetInt() << ")\n" << endl;
            }
        }
        else if (strcmp(_command.GetString(), "slimePosition") == 0)
        {
            Value& _slimeList = d["slimeList"];
            for (SizeType i = 0; i < _slimeList.Size(); i++)
            {
                Value& _x = _slimeList[i]["x"];
                Value& _y = _slimeList[i]["y"];
                cout << "슬라임" << i << "의 위치 : (" << _x.GetInt() << "," << _y.GetInt() << ")\n";
            }
        }
        else if (strcmp(_command.GetString(), "userPosition") == 0)
        {
            Value& _userList = d["userList"];
            for (SizeType i = 0; i < _userList.Size(); i++)
            {
                Value& _x = _userList[i]["x"];
                Value& _y = _userList[i]["y"];
                Value& _nickname = _userList[i]["nickname"];
                cout << "유저 " << _nickname.GetString() << "의 위치 : (" << _x.GetInt() << ", " << _y.GetInt() << ")\n";
            }
        }
    }
}

//최초에 닉네임을 입력하는 함수
bool checkData(SOCKET sock)
{
    Document d;
    d.SetObject();

    d.AddMember("Command", "Checkdata", d.GetAllocator());

    string s = getJsonmessage(d);
    const char* message = s.c_str();
    //문자를 전송한다.
    if (sendMessage(message, sock) == 1) {
        return false;
    }
    return true;
}

//최초에 닉네임을 입력하는 함수
bool sendNickname(SOCKET sock) 
{

    //닉네임을 입력받는다.
    cout << "사용할 닉네임을 입력해주세요." << endl;     
    char _inputNickname[20];
    cin >> _inputNickname;

    //입력받은 nickname으로 객체를 만들어서 문자열로 변환한다.
    Document d;
    d.SetObject();
    Value inputNickname;
    inputNickname.SetString(_inputNickname, strlen(_inputNickname), d.GetAllocator());
     
    d.AddMember("Command", "Login", d.GetAllocator());
    d.AddMember("Nickname", inputNickname, d.GetAllocator());

    string s = getJsonmessage(d);
    const char* message = s.c_str();

    //문자를 전송한다.
    if (sendMessage(message, sock) == 1) {
        return false;
    }

    system("cls");
    return true;
}

bool sendMove(SOCKET sock)
{
    Document d;
    d.SetObject();

    //이동할 좌표를 입력받는다.
    int _x, _y;
    cin >> _x >> _y;

    if (_x > 3 || _x < -3 || _y > 3 || _y < -3)
    {
        cout << "\n\n-3 ~ 3 사이의 값만 이동할 수 있습니다" << endl;
    }
    else
    {
        //문자열로 만든다.
        Value x, y;
        x.SetInt(_x);
        y.SetInt(_y);

        d.AddMember("Command", "Move", d.GetAllocator());
        d.AddMember("x", x, d.GetAllocator());
        d.AddMember("y", y, d.GetAllocator());

        string s = getJsonmessage(d);
        const char* message = s.c_str();

        //문자를 전송한다.
        if (sendMessage(message, sock) == 1) {
            return false;
        }
    }
    return true;
}


bool checkMonsters(SOCKET sock)
{
    Document d;
    d.SetObject();


    d.AddMember("Command", "SlimePosition", d.GetAllocator());
    string s = getJsonmessage(d);
    const char* message = s.c_str();

        //문자를 전송한다.
    if (sendMessage(message, sock) == 1) {
        return false;
    }

    return true;
}

bool checkUsers(SOCKET sock)
{
    Document d;
    d.SetObject();


    d.AddMember("Command", "UserPosition", d.GetAllocator());
    string s = getJsonmessage(d);
    const char* message = s.c_str();

    //문자를 전송한다.
    if (sendMessage(message, sock) == 1) {
        return false;
    }

    return true;
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

    showIntro();
    system("cls");
    
    //닉네임을 입력받고 서버에 보내서 로그인을 시도한다.
    if (sendNickname(sock) == false) {
        cout << "연결 오류 종료" << endl;
        exit(1);
    }
  
    //로그인 후에는 명령어를 1회 보여준다.
    showCommand();

    shared_ptr<thread> messageThread(new thread(messageControler,sock));
   //명령어를 입력받는다.
    while (true)   
    {
        string s;
        cin >> s;
        if (s == "move")
        {
            if (sendMove(sock) == false) {
                cout << "연결 오류 종료" << endl;
                exit(1);
            }
        }
        else if (s == "data") 
        {
            if (checkData(sock) == false) {
                cout << "연결 오류 종료" << endl;
                exit(1);
            }
        }
        else if (s == "attack") {  }
        else if (s == "monsters")
        {
            if (checkMonsters(sock) == false) {
                cout << "연결 오류 종료" << endl;
                exit(1);
            }

        }
        else if (s == "users") 
        {
            if (checkUsers(sock) == false) {
                cout << "연결 오류 종료" << endl;
                exit(1);
            }
        }
        else if (s == "chat") { }
        else if (s == "bot") { }
        else if (s == "help") { showCommand(); }
        else if (s == "clear") { system("cls"); }
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

    messageThread->join();
    // Winsock 을 정리한다.
    WSACleanup();
    return 0;
}
