#include <QCoreApplication>
#include <QDebug>
class CustomString
{
//https://www.youtube.com/watch?v=ehMg6zvXuMY
//https://www.youtube.com/watch?v=OWNeCTd7yQE&t=352s

public:
    char *_data=nullptr;
    uint _dataSize=0;
    CustomString()=default;
    CustomString(const char*  data)
    {
        _dataSize=strlen(data);
        _data=new char[_dataSize];
        memcpy(_data,data,_dataSize);
        qDebug()<<"created ...";

    }
    CustomString(const CustomString&  other)
    {
        _dataSize=other._dataSize;
        _data=new char[_dataSize];
        memcpy(_data,other._data,_dataSize);

        qDebug()<<"copy";
    }
    //this part is solution
    CustomString( CustomString&&  other) noexcept
    {
        _dataSize=other._dataSize;
        _data=other._data;
        ///////part 2 whe shoul add this check what happen when we drop this part
        /// when distructor delete object it deletes nothing but null ptr
        other._dataSize=0;
        other._data=nullptr;
        /////////////////////
        qDebug()<<"moved";
    }
    ///////////////////////////move assignment  operator
    CustomString& operator=(CustomString&&other) noexcept
    {
          qDebug()<<"moved operator";
        if(this!=&other)
        {
        delete [] _data;
        _dataSize=other._dataSize;
        _data=other._data;

        other._dataSize=0;
        other._data=nullptr;
    }
        return *this;

    }
    ~CustomString()
    {
        qDebug()<<"distructed";
        delete  _data;
    }
    void Print()
    {

        for (uint i=0;i<_dataSize;i++)
        {
            printf("%c",_data[i]);
        }
        printf("\n");
    }

};



class Entity
{
    CustomString _name;
public:
    Entity(const CustomString &name):_name(name)
    {
         qDebug()<<"entity 1";
    }
    //this part is solution
//    Entity(CustomString &&name):_name((CustomString &&)name)
//    {
//      qDebug()<<"entity 2";
//    }

    //or
    Entity(CustomString &&name):_name(std::move(name))
    {

    }
    ////////////////////////
    void PrintName()
    {
        _name.Print();
    }

};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Entity e1("amin");
    e1.PrintName();
    qDebug()<<"============";
    CustomString apple="apple";
    CustomString dest;
    qDebug()<<"apple=";
   apple.Print();
   qDebug()<<"dest=";
    dest.Print();

    dest=std::move(apple);
    qDebug()<<"apple=";
    apple.Print();
    qDebug()<<"dest=";
    dest.Print();

    return a.exec();
}
