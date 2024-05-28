#ifdef DOCFILETXT_HPP
#define DOCFILETXT_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "lop.hpp"
#include "doc_json.hpp"

using namespace std;

vector<int> layDulieumoiLoaiDichuyen() 
{
    string filename = "outputMoiLoaiDiChuyen.txt";
    ifstream file(filename);
    vector<int> soLuong;

    // Kiểm tra file mở thành công hay không
    if (!file.is_open())
    {
        cerr << "Mở file không thành công." << std::endl;
        return soLuong;
    }

    // Tổng số lượng các Perdestrian
    int sum;
    string line;
    getline(file, line);
    stringstream ss(line);
    ss >> sum;
    // Kiểm tra xem có lấy được dữ liệu hay không
    if (sum != get_numOfPedestrian())
    {
        cerr << "Dữ liệu không khớp với dữ liệu trong file." << endl;
        return soLuong;
    }

    // Lấy số lượng từng loại di chuyển
    while (getline(file, line)) 
    {
        stringstream ss(line);
        int num;
        while (ss >> num) 
        {
            soLuong.push_back(num);
        }
    }
    file.close();
    cout << "Gọi thành công layDulieumoiLoaiDichuyen()!" << endl;
    return soLuong;
}

vector<double> layTuoi()
{
    vector<double> tuoi;
    string filename = "outputTuoi.txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Mở file không thành công." << endl;
        return tuoi;
    }
    string line;
    while (getline(file, line)) 
    {
        double num = stod(line);
        tuoi.push_back(num);
    }
    file.close();
    cout << "Gọi thành công layTuoi()!" << endl;
    return tuoi;
} 

vector<Event> eventTacDong()
{
    vector<Event> sukien;
    string filename = "outputTacDongSuKien.txt";
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Không mở được file!" << endl;
    }
    string line;
    while(getline(file,line))
    {
        stringstream ss(line);
        vector<double> thongso;
        double num;
        while(ss >> num)
        {
            thongso.push_back(num);
        }
        Event ev;
        ev.setIntensity(thongso);
        sukien.push_back(ev);
    }
    cout << "Gọi thành công eventTacDong()!" << endl;
    return sukien;
}

vector<vector<int>> timeEvents()
{
    vector<vector<int>> timeAllObject;
    string filename = "outputTimeEvents.txt";
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Không mở thành công file!" <<'\n';
        return timeAllObject;
    }
    string line;
    while(getline(file,line))
    {
        stringstream ss(line);
        vector<int> timeOneObject;
        double num;
        while (ss >> num)
        {
            timeOneObject.push_back(num);
        }
        timeAllObject.push_back(timeOneObject);
    }
    cout << "Gọi thành công timeEvents()!" << endl;
    return timeAllObject;
}

pair<vector<Ward>,A> mapWard()
{
    pair<vector<Ward>,A> input;
    vector<Ward> khacA;
    string filename = "hospital.txt";
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Mở file không thành công!" << endl;
        return input;
    }
    string line;
    int soKhoa;
    getline(file,line);
    istringstream ss(line);
    ss >> soKhoa;
    for(int i = 0; i < soKhoa;i++)
    {
        getline(file,line);
        istringstream iss(line);
        Point entrance;
        Point exit;
        double x1,y1;
        double x2,y2;
        double num;
        double width;
        string name;
        iss >> x1 >> y1 >> x2 >> y2 >> width >> name;
        entrance.setX(x1);
        entrance.setY(y1);
        exit.setX(x2);
        exit.setY(y2);
        Ward khoa;
        khoa.setWidth(width);
        khoa.setEntrance(entrance);
        khoa.setExit(exit);
        khoa.setName(name);
        khacA.push_back(khoa);
    }
    getline(file,line);
    istringstream aa(line);
    string name = "A";
    vector<Point> entrance;
    vector<Point> exit;
    double x1,y1,x2,y2;
    aa >> x1 >> y1 >> x2 >> y2;
    Point diem1(x1,y1);
    Point diem2(x2,y2);
    entrance.push_back(diem1);
    entrance.push_back(diem2);
    aa >> x1 >> y1 >> x2 >> y2;
    Point diem3(x1,y1);
    Point diem4(x2,y2);
    exit.push_back(diem3);
    exit.push_back(diem4);
    A a;
    a.setEntrance(entrance);
    a.setExit(exit);
    input.first = khacA;
    input.second = a;
    cout << "Gọi thành công mapWard()!" << endl;
    return input;
}

#endif // DOCFILETXT_HPP