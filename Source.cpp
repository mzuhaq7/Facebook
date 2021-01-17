#include <fstream>
#include<iostream>
#include <conio.h>             .
#include <Windows.h>

using namespace std;
class User;
class Page;
class Comment;
class Post;
class Helper {

    public:
        ///this function returns string length of a string
        static int StringLenght (char *str) {
            int i = 0;
            for (; str[i] != '\0'; i++);
            return i;
        }
        static char *GetStringFromBuffer (char *str) {
            //This function should allocate required memory on heap,
            //copy string in this memory and return newly created cstring.
            int len = StringLenght (str);
            char *arr = new char[len + 1];
            int i = 0;
            for (; str[i] != '\0'; i++) {
                arr[i] = str[i];
            }
            arr[i] = '\0';
            return arr;
        }
        static bool FindString (char *mainstr, char *substr) {
            int len = strlen (mainstr);
            int len2 = strlen (substr);
            for (int i = 0; i < len; i++) {
                bool found = true;
                for (int j = i, k = 0; j < len && k < len2 ; k++, j++) {
                    if (mainstr[j] != substr[k]) {
                        found = false;
                    }
                }
                if (found == true) {
                    return true;
                }
            }
            return false;
        }
        ///// this function is used to compare twe C-strings it returns true if both arrays have same members
        ////else return false
        static bool Mystrcmp (char *str, char *str2) {
            if (strlen (str) != strlen (str2))
            { return false; }
            else {
                for (int i = 0; str[i] != '\0'; i++) {
                    if (str[i] != str2[i]) {
                        return false;
                    }
                }
            }
            return true;
        }
        /////this function is used to copy the content from one array to another
        static void StrCpy (char *src, char *dest) {
            int i = 0;
            for (; src[i] != '\0'; i++) {
                dest[i] = src[i];
            }
            dest[i] = '\0';
        }
};

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        Date();
        void Print();
        Date (int, int, int);
        ~Date();
        void Input();
        void setday (int d);
        void setmonth (int m);
        void setyear (int y);
        int getday();
        int getmonth();
        int getyear();
        bool compare (Date *&);
        Date incremenantMonth();
        void setDate (int, int, int);
};
Date::Date()
{
    day = 1;
    month = 1;
    year = 1926;
}
Date::Date (int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}
void Date::Print()
{
    cout << day << "/" << month << "/" << year ;
}
Date::~Date()
{
}
void Date::setday (int d)
{
    day = d;
}
void Date::setmonth (int m)
{
    month = m;
}
void Date::setyear (int y)
{
    year = y;
}
int Date::getday()
{
    return day;
}
int Date::getmonth()
{
    return month;
}
int Date::getyear()
{
    return year;
}
void Date::setDate (int d, int mon, int y)
{
    day = d;
    month = mon;
    year = y;
}
bool Date::compare (Date *&aid)
{
    if (month == aid->month && year == aid->year) {
        if (day == aid->day || day == aid->day - 1) {
            return true;
        }
        return false;
    }
    return false;
}
Date Date:: incremenantMonth()
{
    int incremenant = month + 1;
    Date newly (day, incremenant, year);
    return newly;
}

class Object {
        char *id;
    public:
        Object();
        ~Object();
        Object (char *);

        char *getID();
        void setID (char *);
        virtual void printName() {
            cout << id;
        }
        virtual void printListview() {
        }
};
Object::Object()
{
    id = 0;
}
Object::~Object()
{
    delete[] id;
}
Object::Object (char *I)
{
    if (I) {
        id = Helper::GetStringFromBuffer (I);
    } else
    { id = 0; }
}
void Object::setID (char *I)
{
    id = Helper::GetStringFromBuffer (I);
}
char *Object::getID()
{
    return id;
}

class Page: public Object {
        char *Title;
        User **linked;
        Post **posts;
        static int TotalPages;
        int postsShared;
    public:
        Page();
        ~Page();

        void pageInfo (ifstream &);
        void printListView() {
            cout << getID() << "---" << Title << endl;
        }
        void Output();
        static int GetTotalPages() {
            return TotalPages;
        }
        char *returnId() {
            return getID();
        }
        char *returnTitle() {
            return Title;
        }
        void setPosts (Post *&obj) {
            if (obj) {
                posts[postsShared] = obj;
                postsShared++;
            }
        }
        void setUsers (User *&obj, int i) {
            linked[i] = obj;
        }

        void Search (char *str) {
            if (Helper::FindString (Title, str) == 1) {
                printListView();
                cout << endl;
            }
        }
        void printName() {
            cout << Title;
        }
        void likedPages();
};
int Page::TotalPages = 0;
Page::Page()
{
    Title = 0;
    linked = new User*[10];
    for (int i = 0; i < 10; i++) {
        linked[i] = 0;
    }
    posts = new Post*[10];
    for (int i = 0; i < 10; i++) {
        posts[i] = 0;
    }
    TotalPages++;
    postsShared = 0;
}
void Page::pageInfo (ifstream &fin)
{
    char  buffer[80], *id = 0;
    fin >> buffer;
    id = Helper::GetStringFromBuffer (buffer);
    setID (id);
    fin.getline (buffer, 80);
    Title = Helper::GetStringFromBuffer (buffer);
}

class User: public Object {
        char *First_Name;
        char *Last_Name;
        char **Friends;
        User **friendList;
        Page **likedPages;
        Post **Timeline;
        int TotalFriends;
        int totalPosts;
        int MyPosts;

    public:
        User();
        ~User();
        void DisplayLikedPages();
        char *returnFriendid (int i);
        User (char *, char *[]);
        void UserInfoFromFile (ifstream &);
        void PageLiked (Page *&obj, int i);
        void ViewFriendList();
        char *returnId();
        void DisplayHomepage();
        void viewPosts();
        int getTotalFriends();
        void LinkFriends (User *&obj, int i);
        void SetPost (Post *&timeline);
        void ViewTimeline();
        void Search (char *str) {
            if (Helper::Mystrcmp (str, First_Name) == 1 || Helper::Mystrcmp (str, Last_Name) == 1) {
                printListview();
                cout << endl;
            }
        }
        void SharePost (Post *&, User *&);
        void printName() {
            cout << First_Name << " " << Last_Name;
        }
        void printListview() {
            cout << getID();
            printName();
        }


};
char *User::returnId()
{
    return getID();
}
void User::SetPost (Post *&post)
{
    /*post->output();*/
    if (totalPosts < 10) {
        Timeline[totalPosts] = post;
        totalPosts++;
    }
}
User::User()
{
    totalPosts = 0;
    First_Name = 0;
    TotalFriends = 0;
    Last_Name = 0;
    MyPosts = 0;
    Friends = new char *[10];
    friendList = new User*[10];
    likedPages = new Page*[10];
    Timeline = new Post*[10];
    for (int i = 0; i < 10; i++) {
        friendList[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        Timeline[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        Friends[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        likedPages[i] = 0;
    }
}
void User::DisplayLikedPages()
{
    cout << "------------------------------------------------------------\n";
    cout << First_Name << " " << Last_Name << "--Liked Pages\n";
    for (int i = 0; i < 10; i++) {
        if (likedPages[i]) {
            likedPages[i]->printListView();//returnId() <<  likedPages[i]->returnTitle() << "  " << endl;
        }
    }
}
void User::PageLiked (Page *&obj, int i)
{
    likedPages[i] = obj;
}
int User::getTotalFriends()
{
    return TotalFriends;
}
char *User::returnFriendid (int i)
{
    return Friends[i];
}
void User::LinkFriends (User *&obj, int i)
{
    friendList[i] = obj;
}
void User::ViewFriendList()
{
    cout << "------------------------------------------------------------\n";
    printName();
    cout << "--Friend List\n\n";
    for (int i = 0; i < TotalFriends; i++) {
        if (friendList[i]) {
            cout << friendList[i]->getID() << " - ";
            friendList[i]->printName();
            cout << endl;
        }
    }
    cout << endl;
}
void User::UserInfoFromFile (ifstream &fin)
{
    char  buffer[80];
    fin >> buffer;
    setID (buffer);
    fin >> buffer;
    First_Name = Helper::GetStringFromBuffer (buffer);
    fin >> buffer;
    Last_Name = Helper::GetStringFromBuffer (buffer);
    fin >> buffer;
    if (Helper::Mystrcmp (buffer, "-1") != 1) {
        int j = 0;
        for (; Helper::Mystrcmp (buffer, "-1") != 1; j++) {
            Friends[j] = Helper::GetStringFromBuffer (buffer);
            fin >> buffer;
            TotalFriends++;
        }
    } else {
        Friends = 0;
    }
}

class Post: public Object  {
        char *Description;
        Date date;
        Date *Current;
        Comment **comment;
        Object **likedby;
        Object **shared;
        int totalLiked;
        int totalShared;
        static int TotalPosts;
        int TotalComments;
    public:
        Post();
        ~Post();
        void PostFromFile (ifstream &);
        static int GetPosts();
        void setUserLikes (User *&);
        char *getLikes (int);
        static void setPost (int);
        void setComment (Comment *&);
        void output();
        void setPagesLikes (Page *&obj);
        char *getpostID() {return getID();}
        void viewLikes();

        void sharePost (Post *&pos, User *&obj);
        void setLikedby (Object *);
        void Search (char *);
        void setCurrentDate (Date *&);
        void printDes() {
            if (date.compare (Current) == 1) {
                cout << Description;
            }
        }
        void Sharing (Object *&obj);
        void printListview();

};
int Post::TotalPosts = 0;
Post::Post()
{
    Current = new Date;
    Description = 0;
    totalLiked = 0;
    likedby = new Object*[10];
    for (int i = 0; i < 10; i++)
    { likedby[i] = 0; }
    shared = new Object*[10];
    for (int i = 0; i < 10; i++)
    { shared[i] = 0; }
    comment = new Comment*[10];
    for (int i = 0; i < 10; i++)
    { comment[i] = 0; }
    totalShared = 0;
    TotalComments = 0;
}
void Post::setComment (Comment *&obj)
{
    if (TotalComments <= 10) {
        comment[TotalComments] = obj;
        TotalComments++;
    }
}
int Post::GetPosts()
{
    return TotalPosts;
}
void Post::setPost (int num)
{
    TotalPosts = num;
}
void Post::viewLikes()
{
    for (int i = 0; i < totalLiked; i++) {
        likedby[i]->printName();
        cout << endl;
    }
}
void Post::setCurrentDate (Date *&obj)
{
    Current = obj;
}
void Post::PostFromFile (ifstream &fin)
{
    char buffer[80];
    int dat;
    fin >> buffer;
    setID (buffer);
    fin.getline (buffer, 80);
    fin >> dat;
    date.setday (dat);
    fin >> dat;
    date.setmonth (dat);
    fin >> dat;
    date.setyear (dat);
    fin.getline (buffer, 80);
    fin.getline (buffer, 80);
    Description = Helper::GetStringFromBuffer (buffer);
}
void Post::sharePost (Post *&pos, User *&obj)
{
    this->Description = Helper::GetStringFromBuffer (pos->Description);
    char str[10] = "0";
    char str2[10] = "post";
    _itoa_s (TotalPosts + 1, str, 10);
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++, j++) {
        str2[j] = str[i];
    }
    str2[j] = '\0';
    setID (Helper::GetStringFromBuffer (str2));
    this->date.setDate (pos->date.getday(), pos->date.getmonth(), pos->date.getyear());
    this->Current->setDate (pos->date.getday(), pos->date.getmonth(), pos->date.getyear());
    shared[totalShared] = obj;
    totalShared++;
    TotalPosts++;
}
void Post::setLikedby (Object *obj)
{
    if (obj) {
        if (totalLiked < 10) {
            likedby[totalLiked] = obj;
            totalLiked++;
        }
    }
}
void Post::Sharing (Object *&obj)
{
    if (totalShared < 10) {
        if (obj) {
            shared[totalShared] = obj;
            totalShared++;
        }
    }
}
void Post::Search (char *str)
{
    if (Helper::FindString (Description, str) == 1) {
        printDes();
        cout << endl;
    }
}
class Comment : public Post {
        char *text;
        Post *post;
        Object *ID;
    public:
        Comment();
        void WriteComment (char *, int);
        ~Comment();
        void getCommentFromFile (ifstream &);
        char *getcommentId();
        void printListview();

        void setPostID (Post *&);
        void setwhoComments (Object *&obj);
        void SetDescription (char *);

};
void Comment::WriteComment (char *str, int total)
{
    text = Helper::GetStringFromBuffer (str);
    char temp[10] = "0";
    _itoa_s (total, temp, 10);
    int i = 0;
    for (; temp[i] != 0; i++) ;
    for (int j = i + 1; j > 0; j--) {
        temp[j] = temp[j - 1];
    }
    temp[0] = 'c';
    setID (Helper::GetStringFromBuffer (temp));
}
char *Comment::getcommentId() {return getID();}
void Comment::printListview()
{
    if (ID) {
        cout << "---  ";
        ID->printName();
        cout << " commented " << text << endl;
    }
}
void Comment::setPostID (Post *&obj) {post = obj;};
Comment::Comment()
{
    text = 0;
    post = 0;
    ID = 0;
}
Comment::~Comment()
{
    delete[] text;
    post = 0;
}
void Comment::getCommentFromFile (ifstream &fin)
{
    char  buffer[80];
    fin >> buffer;
    setID (buffer);
}
void Comment::SetDescription (char *str)
{
    text = Helper::GetStringFromBuffer (str);
}
void Comment::setwhoComments (Object *&obj)
{
    ID = obj;
}

void Post::printListview()
{
    cout << "---- \"" << Description << "\"(" ;
    date.Print();
    cout << ")\n";
    for (int i = 0; comment[i]; i++) {
        comment[i]->printListview();
    }
    cout << endl;
}
void Post::output()
{
    for (int i = 0; i < totalShared; i++) {
        if (shared[i]) {
            if (date.compare (Current) == 1) {
                cout << "------------------------------------------------------\n";
                shared[i]->printName();
                cout << " shared \"" << Description << "\"(" ;
                date.Print();
                cout << ")\n";
                for (int i = 0; comment[i]; i++) {
                    comment[i]->printListview();
                }
                cout << endl;
            }
        }
    }
}
Post::~Post()
{
    delete[] Description;
    for (int i = 0; i < totalLiked; i++) {
        likedby[i] = 0;
    }
    delete[] likedby;
    for (int i = 0; i < totalShared; i++) {
        shared[i] = 0;
    }
    delete[] shared;
    for (int i = 0; i < TotalComments; i++) {
        delete comment[i];
    }
    delete[] comment;
}

Page::~Page()
{
    delete[] Title;
    for (int i = 0; linked[i]; i++) {
        linked[i] = 0;
    }
    delete[] linked;
    for (int i = 0; i < postsShared; i++) {
        delete posts[i];
    }
    delete[] posts;
}
void Page::Output()
{
    for (int i = 0; i < 10; i++) {
        if (posts[i]) {
            posts[i]->output();
        }
    }
}
void Page::likedPages()
{
    printName();
    for (int i = 0; i < postsShared; i++) {
        cout << "\n------------------------------------------------------\n";
        posts[i]->printListview();
    }
}

void User::SharePost (Post *&t, User *&obj)
{
    if (totalPosts < 10) {
        Timeline[totalPosts] = new Post;
        Timeline[totalPosts]->sharePost (t, obj);
        totalPosts++;
    }
}
void User::ViewTimeline()
{
    for (int i = 0; i < 10; i++) {
        if (Timeline[i]) {
            Timeline[i]->output();
        }
    }
}
void User::DisplayHomepage()
{
    for (int i = 0; i < TotalFriends; i++) {
        for (int j = 0; j < 10; j++) {
            if (friendList[i]->Timeline[j]) {
                friendList[i]-> Timeline[j]->output();
            }
        }
    }
    for (int k = 0; k < 10; k++) {
        if (likedPages[k]) {
            likedPages[k]->Output();
        }
    }
}
User::~User()
{
    delete[] First_Name;
    delete[] Last_Name;
    for (int i = 0; i < TotalFriends; i++) {
        delete[] Friends[i];
    }
    delete[] Friends;
    for (int i = 0; likedPages[i]; i++) {
        likedPages[i] = 0;
    }
    delete[] likedPages;
    for (int i = 0; friendList[i]; i++) {
        friendList[i] = 0;
    }
    delete[] friendList;
}

class Facebook {
    private:
        Page **pages;
        User **users;
        Post **posts;
        User *Current;
        Date *CurrentDate;
        Comment **comments;

        static int LikedPages;
        static int usersCount;
        static int pagesCount;
        static int count;
        static int comCount;
    public:
        Facebook();
        ~Facebook();
        void LoadData();
        void LoadUsers();
        void PrintAllPages();
        void viewlikespages (char *);
        void linking();
        static int GetUserCount();
        static int GetLikedPages();
        static int GetPostCOunt() {
            return count;
        }
        static int GetCOMCOunt() {
            return comCount;
        }
        Date *getDate() {
            return CurrentDate;
        }
        void likePost (char *);
        void LinkPosts();
        void run();
        void Comments();
        void setUser (char *);
        void output (char *);
        void viewLiked (char *);
        void CommentAPost (char *, char *);
        void resizeTotalComment();
        void ShareAPost (char *);
        void Search (char *);
};
int Facebook::LikedPages = 0;
int Facebook::usersCount = 0;
int Facebook::pagesCount = 0;
int Facebook::count = 0;
int Facebook::comCount = 0;
void Facebook::PrintAllPages()
{
    int totalPages = Page::GetTotalPages();
    for (int i = 0; i < totalPages ; i++) {
        pages[i]->printListView();
    }
}
int Facebook::GetLikedPages()
{
    return LikedPages;
}
int Facebook::GetUserCount()
{
    return usersCount;
}
Facebook::~Facebook()
{
    for (int i = 0; i < usersCount; i++) {
        delete users[i];
    }
    delete[] users;
    for (int i = 0; i < pagesCount; i++) {
        delete pages[i];
    }
    delete[] pages;
    for (int i = 0; i < count; i++) {
        posts[i] = 0;
    }
    delete[] posts;
    for (int i = 0; i < comCount; i++) {
        comments[i] = 0;
    }
    delete[] comments;
    Current = 0;
    delete CurrentDate;
}
Facebook::Facebook()
{
    pages = 0;
    users = 0;
    posts = 0;
    Current = 0;
    CurrentDate = 0;
    comments = 0;
}
void Facebook::output (char *str)
{
    cout << "Command: Set current user \"" << str << "\"\n\n";
    if (Current) {
        Current->printName();
        cout << " successfully set as current user\n\n";
        cout << "Command: Set current System ";
        CurrentDate->Print();
        cout << "\n\n";
        CurrentDate->Print();
        cout << " successfully set as current date\n\n";
        cout << "Command : View Friendlist\n";
        Current->ViewFriendList();
        cout << "Command : View Liked Pages\n";
        Current->DisplayLikedPages();
    } else
    { cout << "wrong id!!\n"; }
}
void Facebook::setUser (char *str)
{
    bool flag = false;
    for (int i = 0; i < usersCount ; i++) {
        if (Helper::Mystrcmp (users[i]->getID(), str) == 1) {
            Current = users[i];
            flag = true;
            break;
        }
    }
    if (!flag) {
        Current = 0;
    }
}
void Facebook::LoadUsers()
{
    LoadData();
    char tempBuffer[80];
    ifstream fin ;
    fin.open ("Users.txt");
    if (fin.is_open()) {
        fin >> usersCount;
        fin.getline (tempBuffer, 80);
        users = new User *[usersCount];
        int  i = 0;
        while (!fin.eof()) {
            users[i] = new User;
            users[i]->UserInfoFromFile (fin);
            fin >> tempBuffer;
            if (Helper::Mystrcmp (tempBuffer, "-1") != 1) {
                int a = 0;
                for (int j = 0; Helper::Mystrcmp (tempBuffer, "-1") != 1 ; j++) {
                    if (Helper::Mystrcmp (tempBuffer, pages[j]->returnId()) == 1) {
                        users[i]->PageLiked (pages[j], a);
                        a++;
                        j = 0;
                        fin >> tempBuffer;
                        LikedPages++;
                    }
                }
                fin.getline (tempBuffer, 80);
            } else
            { fin.getline (tempBuffer, 80); }
            i++;
        }
        for (int i = 0; i < pagesCount ; i++) {
            for (int j = 0; j < usersCount ; j++) {
                if (Helper::Mystrcmp (pages[i]->getID(), users[j]->getID()) == 1) {
                    pages[i]->setUsers (users[j], i);
                }
            }
        }
    }
}
void Facebook::run()
{
    const unsigned char WHITE = 219;
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "/////////////////////////////////////////////////////  Facebook  ///////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    for (int i = 0; i < 60; i++) {
        cout << WHITE << " ";
        Sleep (25);
    }
    system ("CLS");
    cout << "                                                        Welcome\n\n\n";
    char str[20] = "u7";
    this->setUser (str);
    CurrentDate = new Date;
    CurrentDate->setDate (15, 11, 2017);
    for (int i = 0; i < count; i++) {
        posts[i]->setCurrentDate (CurrentDate);
    }
    output (str);
    cout << "------------------------------------------------------------\nCommand : HomePage\n------------------------------------------------------------\n";
    Sleep (5000);
    system ("CLS");
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "/////////////////////////////////////////////////////  HomePage  ///////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    for (int i = 0; i < 60; i++) {
        cout << WHITE << " ";
        Sleep (25);
    }
    system ("CLS");
    Current->DisplayHomepage();
    cout << "-------------------------------------------\nCommand : Timeline\n---------------------------------\n";
    Sleep (10000);
    system ("CLS");
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "/////////////////////////////////////////////////////  Timeline  ///////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    for (int i = 0; i < 60; i++) {
        cout << WHITE << " ";
        Sleep (25);
    }
    system ("CLS");
    Current->ViewTimeline();
    cout << "-------------------------------------------\nCommand : View Likes\n---------------------------------\n";
    viewLiked ("post1");
    cout << "-------------------------------------------\nCommand : Like Post\n---------------------------------\n";
    likePost ("post1");
    viewLiked ("post1");
    cout << "-------------------------------------------\nCommand : Comment \n---------------------------------\n";
    CommentAPost ("post8", "Thanks for the wishes");
    posts[7]->printListview();
    cout << "-------------------------------------------\nCommand : Comment \n---------------------------------\n";
    CommentAPost ("post4", " Good Luck for your Result");
    posts[3]->printListview();
    cout << "-------------------------------------------\nCommand : Share Post\n---------------------------------\n";
    ShareAPost ("post7");
    cout << "-------------------------------------------\nCommand : Share TimeLine\n---------------------------------\n";
    Current->ViewTimeline();
    cout << "-------------------------------------------\nCommand : View Page\n---------------------------------\n";
    viewlikespages ("p1");
    cout << "-------------------------------------------\nCommand : Search Ali\n---------------------------------\n";
    Search ("Ali");
    cout << "-------------------------------------------\nCommand : Search Birthday\n---------------------------------\n";
    Search ("Birthday");
}
void Facebook::linking()
{
    for (int i = 0; i < usersCount; i++) {
        int a = 0;
        for (int j = 0; j < users[i]->getTotalFriends(); j++) {
            for (int k = 0; k < usersCount; k++) {
                if ( (Helper::Mystrcmp (users[i]->returnFriendid (j), users[k]->returnId())) == 1) {
                    users[i]->LinkFriends (users[k], a);
                    a++;
                    break;
                }
            }
        }
    }
}
void Facebook::LinkPosts()
{
    ifstream fin;
    fin.open ("Posts.txt");
    if (fin.is_open()) {
        char buffer[80];
        fin >> count;
        posts = new Post*[count];
        for (int i = 0; i < 8; i++)
        { fin.getline (buffer, 80); }
        for (int a = 0; a < count; a++) {
            posts[a] = new Post;
            posts[a]->PostFromFile (fin);
            fin >> buffer;
            if (buffer[0] == 'u') {
                for (int i = 0; i < usersCount; i++) {
                    if (Helper::Mystrcmp (buffer, users[i]->getID()) == 1) {
                        Object *obj = users[i];
                        obj = users[i];
                        posts[a]->Sharing (obj);
                        users[i]->SetPost (posts[a]);
                        obj = 0;
                        break;
                    }
                }
            }
            if (buffer[0] == 'p') {
                for (int b = 0; b < pagesCount; b++) {
                    if (Helper::Mystrcmp (buffer, pages[b]->returnId()) == 1) {
                        Object *obj = pages[b];
                        posts[a]->Sharing (obj);
                        pages[b]->setPosts (posts[a]);
                        obj = 0;
                        break;
                    }
                }
            }
            fin.getline (buffer, 80);
            fin >> buffer;
            if (Helper::Mystrcmp (buffer, "-1") != 1) {
                int j = 0;
                for (; Helper::Mystrcmp (buffer, "-1") != 1; j++) {
                    if (buffer[0] == 'u') {
                        for (int i = 0; i < usersCount; i++) {
                            if (Helper::Mystrcmp (buffer, users[i]->getID()) == 1) {
                                Object *obj = users[i];
                                obj = users[i];
                                posts[a]->setLikedby (obj);
                                obj = 0;
                                break;
                            }
                        }
                        fin >> buffer;
                    }
                    if (buffer[0] == 'p') {
                        for (int i = 0; i < pagesCount; i++) {
                            if (Helper::Mystrcmp (buffer, pages[i]->returnId()) == 1) {
                                Object *obj = pages[i];
                                posts[a]->setLikedby (pages[i]);
                                obj = 0;
                                break;
                            }
                        }
                        fin >> buffer;
                    }
                }
            }
            fin.getline (buffer, 80);
            fin.getline (buffer, 80);
        }
        Post::setPost (count);
    }
}
void Facebook::LoadData()
{
    //------------------------------------------
    char tempBuffer[80];
    ifstream fin ("Pages.txt");
    fin >> pagesCount;
    fin.getline (tempBuffer, 80);
    pages = new Page*[pagesCount];
    int i = 0;
    while (!fin.eof()) {
        pages[i] = new Page;
        pages[i]->pageInfo (fin);
        i++;
    }
    //------------------------------------------
}
void Facebook::Comments()
{
    ifstream fin;
    fin.open ("Comments.txt");
    if (fin.is_open()) {
        char buffer[800];
        fin >> comCount;
        comments = new Comment*[comCount];
        fin.getline (buffer, 800);
        fin.getline (buffer, 800);
        int i = 0;
        while (i < comCount) {
            comments[i] = new Comment;
            comments[i]->getCommentFromFile (fin);
            fin >> buffer;
            for (int j = 0; j < count; j++) {
                if (Helper::Mystrcmp (buffer, posts[j]->getpostID()) == 1) {
                    posts[j]->setComment (comments[i]);
                    comments[i]->setPostID (posts[j]);
                }
            }
            fin >> buffer;
            if (buffer[0] == 'u') {
                for (int j = 0; j < usersCount; j++) {
                    if (Helper::Mystrcmp (buffer, users[j]->returnId()) == 1) {
                        Object *obj = users[j];
                        comments[i]->setwhoComments (obj);
                    }
                }
            } else if (buffer[0] == 'p') {
                for (int j = 0; j < pagesCount; j++) {
                    if (Helper::Mystrcmp (buffer, pages[j]->returnId()) == 1) {
                        Object *obj = pages[j];
                        comments[i]->setwhoComments (obj);
                    }
                }
            }
            fin.getline (buffer, 300);
            comments[i]->SetDescription (buffer);
            i++;
        }
    }
}
void Facebook::viewLiked (char *post)
{
    for (int i = 0; i < count; i++) {
        if (Helper::Mystrcmp (post, posts[i]->getpostID()) == 1) {
            posts[i]->viewLikes();
        }
    }
}
void Facebook::likePost (char *id)
{
    for (int i = 0; i < count; i++) {
        if (Helper::Mystrcmp (id, posts[i]->getpostID()) == 1) {
            posts[i]->setLikedby (Current);
        }
    }
}
void Facebook::resizeTotalComment()
{
    Comment **temp = 0;
    temp = new Comment*[comCount + 1];
    int i = 0;
    for (; i < comCount; i++) {
        temp[i] = comments[i];
    }
    delete[] comments;
    comments = temp;
    comments[i] = new Comment;
    comCount++;
}
void Facebook::CommentAPost (char *postID, char *Com)
{
    for (int i = 0; i < count; i++) {
        if (Helper::Mystrcmp (postID, posts[i]->getpostID()) == 1) {
            resizeTotalComment();
            comments[comCount - 1]->WriteComment (Com, comCount);
            Object *obj = Current;
            comments[comCount - 1]->setwhoComments (obj);
            posts[i]->setComment (comments[comCount - 1]);
            obj = 0;
        }
    }
}
void Facebook::ShareAPost (char *postID)
{
    for (int i = 0; i < count; i++) {
        if (Helper::Mystrcmp (postID, posts[i]->getpostID()) == 1) {
            Current->SharePost (posts[i], Current);
        }
    }
}
void Facebook::Search (char *str)
{
    for (int i = 0; i < usersCount; i++) {
        users[i]->Search (str);
    }
    for (int i = 0; i < pagesCount; i++) {
        pages[i]->Search (str);
    }
    for (int i = 0; i < count; i++) {
        posts[i]->Search (str);
    }
}
void Facebook::viewlikespages (char *str)
{
    for (int i = 0; i < pagesCount; i++) {
        if (Helper::Mystrcmp (str, pages[i]->returnId()) == 1) {
            pages[i]->likedPages();
            break;
        }
    }
}

int main()
{
    Facebook fb;
    fb.LoadUsers();
    fb.linking();
    fb.LinkPosts();
    fb.Comments();
    fb.run();
    system ("pause");
}