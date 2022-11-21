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
    


//��Ʈ�� ȭ���� �����ش�.
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
    cout << "                   ����Ͻ÷��� ����Ű�� �����ּ���                       " << endl;
    while (!getchar());
    return;
}

void showCommand()
{
    cout << "\n\n   ��ɾ �Է����ּ���   " << endl;
    cout << "������ɾ� ���������" << endl;
    cout << "                           " << endl;
    cout << "data   : ���� �� ĳ������ �����͸� Ȯ���մϴ�. " << endl;
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
    cout << "                           " << endl;
    cout << "help        : ��ɾ���� �����ݴϴ�. " << endl;
    cout << "                           " << endl;
    cout << "clear        : ȭ���� �����մϴ�. " << endl<<endl<<endl;

}
//�޽����� ������. ���н� 1, ������ 0�� ��ȯ�Ѵ�.
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

//�޽����� ����Ʈ �����ͷ� �޴´�. �߸������� nullptr�� �����͸� ��ȯ�Ѵ�.
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

//��ü�� string���� ��ȯ�Ѵ�.
string getJsonmessage(Document& d)
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}

void messageControler(SOCKET sock)
{
    //�����κ��� ��� �޽����� �������� �Ѵ�.
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
                cout <<_nickname.GetString()<< "��(��) �����ӿ��� " << _damaged.GetInt() << "�� �������� �Ծ���!\n ���� hp : " << _hp.GetInt();
            }
            else if (strcmp(_status.GetString(), "death")==0)
            {
                if (strcmp(_who.GetString(), "commander") == 0)
                {
                    cout << _nickname.GetString() << "��(��) �����ӿ��� " << _damaged.GetInt() << "�� �������� �Ծ���!\nĳ���Ͱ� ����Ͽ� �����մϴ�.";
                    exit(1);
                }
                if (strcmp(_who.GetString(), "receiver") == 0)
                {
                    cout << _nickname.GetString() << "��(��) �����ӿ��� " << _damaged.GetInt() << "�� �������� �Ծ���!\n"<<_nickname.GetString()<<"�� ĳ���Ͱ� ����Ͽ����ϴ�\n";
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


            cout << "=======ĳ���� ����======" << endl;
            cout << "�г��� : " << _nickname.GetString() << endl;
            cout << "  hp : " << _hp.GetInt() << endl;
            cout << "  str : " << _str.GetInt() << endl;
            cout << "  x : " << _x.GetInt() << endl;
            cout << "  y : " << _y.GetInt() << endl;
            cout << "  potionHp : " << _potionhp.GetInt() << endl;
            cout << "  potionstr : " << _potionstr.GetInt() << endl;
            cout << "=======ĳ���� ����======" << endl << endl;
        }
        else if (strcmp(_command.GetString(),"inputNickname") == 0)
        {
            // �����κ��� ������ ĳ���� ������ �Է¹޴´�.

            Value& _result = d["result"];   
            Value& _nickname = d["nickname"];
            Value& _x = d["x"];
            Value& _y = d["y"];
            Value& _hp = d["hp"];
            Value& _str = d["str"];
            Value& _potionhp = d["potionhp"];
            Value& _potionstr = d["potionstr"];

            if (strcmp(_result.GetString(), "load") == 0) { cout << "����� �����͸� �ҷ��ɴϴ�.\n" << endl; }
            else { cout << "����� �����Ͱ� ���� ���� �����մϴ�.\n" << endl; }
            cout << "=======ĳ���� ����======" << endl;
            cout << "�г��� : " << _nickname.GetString() << endl;
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

            //���� ���������� ��� ���������� �˶��� �ƴϸ� �̵� �� ��ǥ�� ����Ѵ�.
            if (strcmp(_result.GetString(), "fail") == 0)
            {
                cout << "���� ������ ��� �� �����ϴ�.";
            }
            else if (strcmp(_result.GetString(), "success") == 0)
            {
                Value& _x = d["x"];
                Value& _y = d["y"];

                cout << "�̵� �� : (" << _x.GetInt() << "," << _y.GetInt() << ")\n" << endl;
            }
        }
        else if (strcmp(_command.GetString(), "slimePosition") == 0)
        {
            Value& _slimeList = d["slimeList"];
            for (SizeType i = 0; i < _slimeList.Size(); i++)
            {
                Value& _x = _slimeList[i]["x"];
                Value& _y = _slimeList[i]["y"];
                cout << "������" << i << "�� ��ġ : (" << _x.GetInt() << "," << _y.GetInt() << ")\n";
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
                cout << "���� " << _nickname.GetString() << "�� ��ġ : (" << _x.GetInt() << ", " << _y.GetInt() << ")\n";
            }
        }
    }
}

//���ʿ� �г����� �Է��ϴ� �Լ�
bool checkData(SOCKET sock)
{
    Document d;
    d.SetObject();

    d.AddMember("Command", "Checkdata", d.GetAllocator());

    string s = getJsonmessage(d);
    const char* message = s.c_str();
    //���ڸ� �����Ѵ�.
    if (sendMessage(message, sock) == 1) {
        return false;
    }
    return true;
}

//���ʿ� �г����� �Է��ϴ� �Լ�
bool sendNickname(SOCKET sock) 
{

    //�г����� �Է¹޴´�.
    cout << "����� �г����� �Է����ּ���." << endl;     
    char _inputNickname[20];
    cin >> _inputNickname;

    //�Է¹��� nickname���� ��ü�� ���� ���ڿ��� ��ȯ�Ѵ�.
    Document d;
    d.SetObject();
    Value inputNickname;
    inputNickname.SetString(_inputNickname, strlen(_inputNickname), d.GetAllocator());
     
    d.AddMember("Command", "Login", d.GetAllocator());
    d.AddMember("Nickname", inputNickname, d.GetAllocator());

    string s = getJsonmessage(d);
    const char* message = s.c_str();

    //���ڸ� �����Ѵ�.
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

    //�̵��� ��ǥ�� �Է¹޴´�.
    int _x, _y;
    cin >> _x >> _y;

    if (_x > 3 || _x < -3 || _y > 3 || _y < -3)
    {
        cout << "\n\n-3 ~ 3 ������ ���� �̵��� �� �ֽ��ϴ�" << endl;
    }
    else
    {
        //���ڿ��� �����.
        Value x, y;
        x.SetInt(_x);
        y.SetInt(_y);

        d.AddMember("Command", "Move", d.GetAllocator());
        d.AddMember("x", x, d.GetAllocator());
        d.AddMember("y", y, d.GetAllocator());

        string s = getJsonmessage(d);
        const char* message = s.c_str();

        //���ڸ� �����Ѵ�.
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

        //���ڸ� �����Ѵ�.
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

    //���ڸ� �����Ѵ�.
    if (sendMessage(message, sock) == 1) {
        return false;
    }

    return true;
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

    showIntro();
    system("cls");
    
    //�г����� �Է¹ް� ������ ������ �α����� �õ��Ѵ�.
    if (sendNickname(sock) == false) {
        cout << "���� ���� ����" << endl;
        exit(1);
    }
  
    //�α��� �Ŀ��� ��ɾ 1ȸ �����ش�.
    showCommand();

    shared_ptr<thread> messageThread(new thread(messageControler,sock));
   //��ɾ �Է¹޴´�.
    while (true)   
    {
        string s;
        cin >> s;
        if (s == "move")
        {
            if (sendMove(sock) == false) {
                cout << "���� ���� ����" << endl;
                exit(1);
            }
        }
        else if (s == "data") 
        {
            if (checkData(sock) == false) {
                cout << "���� ���� ����" << endl;
                exit(1);
            }
        }
        else if (s == "attack") {  }
        else if (s == "monsters")
        {
            if (checkMonsters(sock) == false) {
                cout << "���� ���� ����" << endl;
                exit(1);
            }

        }
        else if (s == "users") 
        {
            if (checkUsers(sock) == false) {
                cout << "���� ���� ����" << endl;
                exit(1);
            }
        }
        else if (s == "chat") { }
        else if (s == "bot") { }
        else if (s == "help") { showCommand(); }
        else if (s == "clear") { system("cls"); }
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

    messageThread->join();
    // Winsock �� �����Ѵ�.
    WSACleanup();
    return 0;
}
