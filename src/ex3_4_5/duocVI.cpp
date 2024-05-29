#include <fstream>
#include "Ex3.hpp"
#include "Ex4.hpp"
#include "Ex5.hpp"
#include "khoiTaoPedestrian.hpp"
using namespace std;

int main() 
{
    // Bài 3
    // Khởi tạo thông số cơ bản cho Perdestrian
    obJect doituong = khoitaodoituong();
    // Thiết lập danh sách events tác động đến đối tượng
    ex3(doituong);
    int M = get_numOfAgents();
    // Bài 5
    // Thiết lập danh sách các khoa viện đi qua của các đối tượng
    ex5(doituong);
    
    string namefile = "doituong.txt";
    ofstream file(namefile);

    // Ghi thông tin đối tượng vào file
    vector<Patient> nguoiBenh = doituong.getNguoiBenh();
    vector<Visitor> nguoiTham = doituong.getNguoiTham();
    vector<Personel> bacSi = doituong.getBacSi();

    int demPatient = 0;
    int demVisitor = 0;
    int demPersonel = 0;

    for (int i = 0; i < M; ++i) 
    {
        if (nguoiBenh[demPatient].getID() == i)
        {
            file << "{ \"Type\": \"Patient\" , \"ID\": " << nguoiBenh[demPatient].getID() << "," << "\"Age\": " << nguoiBenh[demPatient].getAge() << ' ';
            file << "\"Journey\": ";
            vector<Ward> cacWard = nguoiBenh[demPatient].getJourney();
            for (auto tmp : cacWard) 
            {
                file << tmp.getName() << ' ';
            }
            file << ',' << "\"Events\": ";
            vector<Event> sk = nguoiBenh[demPatient].getEvents();
            for (auto tmp : sk) 
            {
                file << '(';
                vector<double> vt = tmp.getIntensity();
                for (int m = 0; m < vt.size(); ++m) 
                {
                    file << vt[m] << ' ';
                }
                file << ") - " << "\"Time\": " << tmp.getTime() << ' ';
            }
            file << "}," << endl;
            demPatient++;
        }
        else if (nguoiTham[demVisitor].getID() == i) 
        {
            file << "{ \"Type\": \"Visitor\" , \"ID\": " << nguoiTham[demVisitor].getID() << "," << "\"Age\": " << nguoiTham[demVisitor].getAge() << ' ';
            file << "\"Journey\": ";
            vector<Ward> cacWard = nguoiTham[demVisitor].getJourney();
            for (auto tmp : cacWard) 
            {
                file << tmp.getName() << ' ';
            }
            file << ',' << "\"Events\": ";
            vector<Event> sk = nguoiTham[demVisitor].getEvents();
            for (auto tmp : sk) 
            {
                file << '(';
                vector<double> vt = tmp.getIntensity();
                for (int m = 0; m < vt.size(); ++m) 
                {
                    file << vt[m] << ' ';
                }
                file << ") - " << "\"Time\": " << tmp.getTime() << ' ';
            }
            file << "}," << endl;
            demVisitor++;
        }
        else 
        {
            file << "{ \"Type\": \"Personel\" , \"ID\": " << bacSi[demPersonel].getID() << "," << "\"Age\": " << bacSi[demPersonel].getAge() << ' ';
            file << "\"Journey\": ";
            vector<Ward> cacWard = bacSi[demPersonel].getJourney();
            for (auto tmp : cacWard) 
            {
                file << tmp.getName() << ' ';
            }
            file << ',' << "\"Events\": ";
            vector<Event> sk = bacSi[demPersonel].getEvents();
            for (auto tmp : sk) 
            {
                file << '(';
                vector<double> vt = tmp.getIntensity();
                for (int m = 0; m < vt.size(); ++m) 
                {
                    file << vt[m] << ' ';
                }
                file << ") - " << "\"Time\": " << tmp.getTime() << ' ';
            }
            file << "}," << endl;
            demPersonel++;
        }
    }

}