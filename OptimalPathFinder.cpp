
#include <iostream>
#include <algorithm>
#include <string.h>
#include <climits>
#include <fstream>
#include <queue>
#include <Windows.h>
#include <vector>
using namespace std;
#define INF 999
#define nofStations 12
#define maxi 100000

void userinput(vector<vector<pair<float, float>>> &map);
void dijkstra(vector<vector<pair<float, float>>> &map, int source, string stations[nofStations]);
int login();
void signup();

int main()
{
    float graph[nofStations][nofStations] = {
        {0, 4, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0},
        {4, 0, 7, 0, 0, 0, 0, 17, 0, 14, 0, 0},
        {0, 7, 0, 5, 0, 0, 0, 0, 0, 15, 10, 0},
        {0, 0, 5, 0, 21, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 21, 0, 33, 0, 12, 0, 0, 0, 0},
        {0, 0, 0, 0, 33, 0, 48, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 48, 0, 20, 0, 0, 0, 0},
        {0, 17, 0, 0, 12, 0, 20, 0, 26, 0, 0, 45},
        {10, 0, 0, 0, 0, 0, 0, 26, 0, 0, 0, 22},
        {0, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 45, 22, 0, 0, 0}

    };

    vector<vector<pair<float, float>>> map;
    for (int i = 0; i < nofStations; i++)
    {
        vector<pair<float, float>> temp;
        for (int j = 0; j < nofStations; j++)
        {

            if (graph[i][j] != 0)
            {
                temp.push_back({j, graph[i][j]});
            }
        }
        map.push_back(temp);
    }
    int source;
    int n, W, ch, flag;
    char s;
    cout << "\n\n\n";
    cout << "\t\t\t-----------------------------------WELLCOME TO MY PROJECT-----------------------------------" << endl
         << endl;
    do
    {
        cout << endl;
        cout << endl;
        cout << "\t\t\t\t====================\n";
        cout << "\t\t\t\t|| 1) LOGIN      ||\n";
        cout << "\t\t\t\t|| 2) REGISTER   ||\n";
        cout << "\t\t\t\t|| 3) EXIT       ||\n";
        cout << "\t\t\t\t====================\n";

        cout << "Enter your Choice : ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            flag = login();
            break;
        case 2:
            signup();
            cout << "Do you want to LOGIN (Y/N)? : ";
            cin >> s;
            if (s == 'y' || s == 'Y')
                flag = login();
            else
            {
                cout << "\n\n\n";
                cout << "\t\t\t-------------------------------Thank you have a nice day !-------------------------------\t\t\t" << endl;
                exit(1);
            }
            break;
        case 3:
            cout << "\n\n\n";
            cout << "\t\t\t-------------------------------Thank you have a nice day !-------------------------------\t\t\t" << endl;
            exit(0);
            break;
        default:
            cout << "\t\t\t----INCORRECT CHOICE!!!----" << endl;
            break;
        }
    } while (flag != 1);
    if (flag == 1)
    {
        userinput(map);
    }
}

void dijkstra(vector<vector<pair<float, float>>> &map, int source, string stations[12])
{

    priority_queue<pair<float, float>, vector<pair<float, float>>, greater<pair<float, float>>> pq;

    float distance[nofStations];
    int parent[nofStations];
    for (int i = 0; i < nofStations; i++)
    {
        distance[i] = maxi;
        parent[i] = i;
    }

    distance[source] = 0;
    pq.push({0.0, source});

    while (!pq.empty())
    {

        int d = pq.top().first;
        int st = pq.top().second;
        pq.pop();

        for (pair<int, int> itr : map[st])
        {

            int w = itr.second;
            int v = itr.first;

            if (d + w < distance[v])
            {
                distance[v] = w + d;
                pq.push({w + d, v});
                parent[v] = st;
            }
        }
    }

    cout << endl
         << endl;
    cout << "Enter the station code of destination:";
    int dest;
    cin >> dest;
    int dummy_dest = dest;

    if (dest >= 0 && dest < nofStations)
    {
        vector<int> path;

        while (parent[dest] != dest)
        {

            path.push_back(dest);
            dest = parent[dest];
        }
        path.push_back(source);

        cout << endl
             << endl;
        cout << "\t\t----------------Total Distance from source to destination----------------" << endl
             << endl;
        cout << "\t\t" << stations[source] << " <------------> " << stations[dummy_dest] << " = " << distance[dummy_dest] << " km" << endl;
        cout << "\n\n\n\t\t";

        reverse(path.begin(), path.end());

        cout << "\n\t\t";
        cout << "Your route will be as follows: " << endl;
        cout << endl
             << "\t\t";

        for (int i = 0; i < path.size(); i++)
        {
            cout << stations[path[i]];
            if (i != path.size() - 1)
            {
                cout << " -----> ";
                cout << " " << distance[path[i + 1]] - distance[path[i]] << " km ";
                cout << " ------> ";
            }
        }
    }

    else
    {
        cout << "Station code doesnot exist !" << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << " .. ";
            Sleep(250);
        }
        system("CLS");
        cout << "\n\n\n\n\n\t\t\t\t\tPlease re-enter station code !" << endl;
        Sleep(2000);
        system("CLS");
        userinput(map);
    }
}

int login()
{
    char dum, u_name[30], name[30], g_pwd[30], pwd[30];
    int flag = 0, s = 1;
    cout << "\n\n\n\n\n\n\t\t\t\t\t======================" << endl;
    cout << "\t\t\t\t\t  WELCOME TO LOGIN " << endl;
    cout << "\t\t\t\t\t======================" << endl;
    if (s == 1)
    {

        cout << "Enter your USER NAME  : " << endl;
        cin >> name;
    }

    cout << "Enter the PASSWORD   : " << endl;
    cin >> pwd;
    fstream f;
    f.open("user_logins.txt", ios::in);
    f.seekg(0);
    while (f)
    {
        f.get(dum);
        f.get(u_name, 30);
        f.get(dum);
        f.get(g_pwd, 30);
        if (strcmp(u_name, name) == 0 && strcmp(pwd, g_pwd) == 0)
        {
            flag = 1;
            cout << "\t\t\t WELCOME PLEASE WAIT A COUPLE OF SECONDS WHILE WE LOG YOU IN" << endl;
            for (int i = 0; i < 6; i++)
            {
                cout << " .  . ";
                Sleep(250);
            }
            break;
        }
        else if (strcmp(u_name, name) == 0 && strcmp(pwd, g_pwd) != 0)
        {
            do
            {

                cout << "----INCORRECT PASSWORD!----" << endl;
                cout << "Re-Enter the PASSWORD : " << endl;

                cin >> pwd;
            } while (strcmp(pwd, g_pwd) != 0);

            for (int i = 0; i < 6; i++)
            {
                cout << " .  . ";
                Sleep(250);
            }
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n\t\t\tSORRY!!! USER NAME does not Exist, please REGISTER yourself first !" << endl
             << endl;
    Sleep(2000);
    system("CLS");
    f.close();
    return flag;
}

void signup()
{
    cout << "\n\n\n\n\n\n\t\t\t";
    cout << "\n\n\n\n\n\n\t\t\t\t\t======================" << endl;
    cout << "\t\t\t\t\t  WELCOME TO SIGNUP " << endl;
    cout << "\t\t\t\t\t======================" << endl;
    char name[30], pwd[30], check_pwd[30];
    fstream f;
    f.open("user_logins.txt", ios::in);
    char g_name[30], g_pwd[30], dum;
    int flag;
    cout << "Enter the USER NAME : ";
    string phrase = "Enter your USER NAME And PASSWORD: ";

    cin >> name;
    do
    {
        f.seekg(0);
        while (f)
        {
            flag = 1;
            f.get(dum);
            f.get(g_name, 30);
            f.get(dum);
            f.get(g_pwd, 30);
            if (strcmp(g_name, name) == 0)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
        {
            cout << "\n\t\t\t----SORRY! USER-NAME ALREADY EXIST----" << endl;
            cout << "Enter the USER NAME : ";
            cin >> name;
        }
    } while (flag == 0);
    f.close();
    f.open("user_logins.txt", ios::out | ios::app);
    cout << "Enter your PASSWORD : ";
    cin >> pwd;
    cout << "Re-Enter your PASSWORD : ";
    cin >> check_pwd;
    while (strcmp(pwd, check_pwd) != 0)
    {
        cout << "\t\t\t----INCORRECT PASSWORD!!!----" << endl;
        cout << "Enter your PASSWORD : ";
        cin >> pwd;
        cout << "Re-Enter your PASSWORD : ";
        cin >> check_pwd;
    }
    f << endl
      << name << endl
      << pwd;
    cout << "\n\t\t\t\t\t  YOUR NEW ID IS CREATING PLEASE WAIT";
    for (int i = 0; i < 6; i++)
    {
        cout << ".";
        Sleep(500);
    }
    cout << "\n\n\t\t\t\t\t\aCONGRATULATION!!!YOUR ID CREATED SUCCESSFULL....Please wait";
    Sleep(3000);
    system("CLS");
    f.close();
}

void userinput(vector<vector<pair<float, float>>> &map)
{
    string stations[12] = {"Chembur", "Kurla", "Dadar", "Bandra", "Borevali", "Virar", "Kalyan", "Thane", "Vashi", "CST", "ChurchGate", "Panvel"};
    char x;
    int source;

    do
    {
        cout << "\t\t\t-------------------------------Mumbai Local Minimum Distance Calculator-------------------------------\t\t\t\n\n"
             << endl
             << endl;
        cout << "Select the Source station" << endl
             << endl;
        for (int i = 0; i < nofStations; i++)
        {
            cout << "Enter "
                 << " " << i << " "
                 << " for " << stations[i] << endl;
        }

        cout << endl
             << "Enter the code for source station:";
        cin >> source;
        if (source >= 0 && source < nofStations)
            dijkstra(map, source, stations);
        else
        {
            cout << "Station code doesnot exist !" << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << ".";
                Sleep(250);
            }
            system("CLS");
            cout << "\n\n\n\n\n\t\t\t\t\tPlease re-enter station code !" << endl;
            Sleep(2000);
            system("CLS");
            userinput(map);
        }

        cout << "\n\nDo you want to continue (Y/N)? : ";

        cin >> x;
        system("cls");
    } while (x == 'y' || x == 'Y');
    cout << "\n\n\n";
    cout << "\t\t\t-------------------------------Thank you have a nice day !-------------------------------\t\t\t" << endl;
    Sleep(2000);
}
