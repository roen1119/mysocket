#include "client.h"

int main()
{
    myClient client;
    client.run();
}

myClient::myClient()
{
    cout << "[ debug] in myClient::myClinet\n";
    socketfd = -1;
}

myClient::~myClient()
{

}

void myClient::run()
{
    cout << "[ debug] in void myClient::run()\n";
    printMenu();
    while(true)
    {
        string command;
        cout << "> ";
        getline(cin, command);
        /**
         * TODO:  
         * my split 
         */
            regex whitespace("\\s+");
            vector<string> words(sregex_token_iterator(command.begin(), command.end(), whitespace, -1),
                             sregex_token_iterator());
        /**
         * TODO:
         * remember to check the length of `words[]` to prevent segment error
         */
        string op = words[0];
        if (op == "")
        {
            continue;
        }
        else if (op =="connect")
        {
            if (-1 != socketfd)
            {
                /* TODO
                 * 从serverAddr中获得
                 *  sin_addr.s_addr -ip地址
                 *  sin_port        -端口号
                 * 并通过ntohl函数转换成string，然后打印
                 */
                cout << "Already connected to \n";
            }
            else
            {
                // connect
                socketfd = socket(AF_INET, SOCK_STREAM, 0);
                cout << "[ debug] socketfd = " << socketfd << endl;
                serverAddr.sin_family = AF_INET;
                serverAddr.sin_port = htons(stoi(words[2]));
                serverAddr.sin_addr.s_addr = inet_addr(words[1].c_str());

                if( connect(socketfd, (sockaddr*)&serverAddr, (socklen_t)sizeof(serverAddr)) < 0 )
                {
                    cout << "Connect failed!\n";
                    socketfd = -1;
                }
                else
                {
                    cout << "[ debug] pthread_create()...\n";
                    // new thread: 新线程的内存单元，null指针，新线程开始的地方，传入参数给start_rtn
                    pthread_create(&tidp, nullptr, start_rtn, &socketfd);
                }
            }
        }
        else if (op == "gettime")
        {
            // 调用函数send
            cout << "404 not done. \n";
        }
        else if (op == "getname")
        {
            // 调用函数send
            cout << "404 not done. \n";
        }
        else if (op == "getclients")
        {
            // 调用函数send
            cout << "404 not done. \n";
        }
        else if (op == "send")
        {
            // 调用函数send
            cout << "404 not done. \n";
        }
        else if (op == "close")
        {
            if(-1 == socketfd)
            {
                cout << "No connection.\n";
            }
            else
            {
                cout << "[ debug] disconnect()...\n";
                disconnect();
                // TODO: 
                //       关闭子线程
                socketfd = -1;
                // cout << "Connection closed. \n";
            }
        }
        else if (op == "exit")
        {
            if(-1 != socketfd)
            {
                disconnect();
            }
            cout << "Exit Clinet\n";
            exit(0);
        }
        else if (op == "help")
        {
            printMenu();
        }
        else if (op=="debug")
        {
            if(words[1] == "socketfd")
            {
                cout << "[ debug] socketfd: " <<  socketfd << endl;
            }
        }
        else
        {
            cout << op << ": illegal operation\n";
        }
    }
}

// 新创建的子进程要做什么？
void connection_handle(int sfd)
{
    // 创建时，第一次connect成功，应该print提示消息
    // TODO: keep receiving
}

void myClient::printMenu()
{
    cout << "Please input a command:\n"
         << "- connect [IP] [port]\n"
         << "- gettime\n"
         << "- getname\n"
         << "- getclients\n"
         << "- send [IP] [port] [message]\n"
         << "- close\n"
         << "- exit\n"
         << "- help\n";
}

void myClient::disconnect()
{
    return;
}