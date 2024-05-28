#ifndef KHOITAOPEDESTRIAN_HPP
#define KHOITAOPEDESTRIAN_HPP
#include <iostream>
#include <random>
#include "lop.hpp"
#include "docfileTXT.hpp"
using namespace std;

int randomInt(int min, int max) 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

Personality xacDinhNguongCamXuc(int numLoaiCamXuc[2], const vector<Personality>& inputNguongCamXuc, const int numOfAgents)
{
    if (numLoaiCamXuc[0] == numOfAgents / 2) 
    {
        numLoaiCamXuc[1]++;
        return inputNguongCamXuc[1];
    }
    else if (numLoaiCamXuc[1] == numOfAgents / 2) 
    {
        numLoaiCamXuc[0]++;
        return inputNguongCamXuc[0];
    }
    else 
    {
        int x = randomInt(0, 1);
        numLoaiCamXuc[x]++;
        return inputNguongCamXuc[x];
    }
}

obJect khoitaodoituong() 
{
    /*Số lượng của mỗi kiểu di chuyển của đối tượng 
    noDisabilityNoOvertaking = 0,//Không khuyết tật,không vượt
    noDisabilityOvertaking = 1,//Không khuyết tật,vượt
    crutches = 2,//Di chuyển bằng nạng
    sticks = 3,//Di chuyển bằng gậy
    wheelchairs = 4,//Di chuyển bằng xe lăn
    blind = 5//Dị mù
    */
    vector<int> soLudiChuyen = layDulieumoiLoaiDichuyen();
    // Tuổi của các Object
    vector<double> ageObject = layTuoi();
    // Các thông số khoa viện
    pair<vector<Ward>, A> inputWard = mapWard();

    // Số lượng đối tương
    int M = get_numOfPedestrian();
    cout << "M: " << M << endl;
    // Ngưỡng cảm xúc tích cực/tiêu cực 0-open, 1-neurotic, 2-heuristic
    vector<Personality> inputNguongCamXuc = layNguongCamXuc();
    // tốc độ của từng kiểu di chuyển
    vector<speedWalkability> inputSpeed = getSpeedWalkability();

    // Tổng noDisability
    int sumNoDisability = soLudiChuyen[0] + soLudiChuyen[1];

    // Lưu trữ tất cả đối tượng
    vector<Patient> nguoiBenh;
    vector<Vistor> nguoiTham;
    vector<Personel> bacSi;

    int numPatient = 0; // Số lượng bệnh nhân
    int numVisitor = 0; // Số lượng người thăm
    int numPersonel = 0; // Số lượng bác sĩ

    // Lưu trữ số lượng đối tượng thuộc từng loại cảm xúc
    int numLoaiCamXuc[2] = {0, 0};
    // đối tượng dưới 11 tuổi
    vector<int> age11;
    for (int i = 0; i < ageObjec.size(); i++) 
    {
        if (ageObject[i] < 11) 
        {
            age11.push_back(i);
            cout << i << ' ';
        }
    }
    cout << endl;
    // khởi tạo đối tượng có tuổi dưới 11
    for (int i = 0; i < age11.size(); i++) 
    {
        // 0-Patient, 1-Vistor
        int x = randomInt(0, 1);
        switch (x)
        {
            case 0:
            {
                Patient object;
                object.setID(age11[i]); // ID của đối tượng
                object.setAge(ageObject[age11[i]]); // Tuổi của đối tượng
                object.setValue(3); // Số lượng khoa viện cần đi qua
                object.setStart(inputWard.second);
                object.setEnd(inputWard.second);
                // Nhỏ hơn 11 tuổi chỉ có cảm xúc open
                if (numLoaiCamXuc[0] < M/2) 
                {
                    object.setPersonality(inputNguongCamXuc[0]);
                    numLoaiCamXuc[0]++;
                }
                else 
                {
                    cout << "Không thể khởi tạo đối tượng dưới 11 tuổi có cảm xúc neurotic." << endl;
                }

                // Tốc độ di chuyển
                bool speedTest = false;
                while (!speedTest) 
                {
                    int speed = randomInt(0, 5);
                    if (soLudiChuyen[speed] > 0) 
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numPatient++;
                nguoiBenh.push_back(object);
                break;
            }

            case 1:
            {
                Visitor object;
                object.setID(age11[i]); // ID của đối tượng
                object.setAge(ageObject[age11[i]]); // Tuổi của đối tượng
                object.setValue(3); // Số lượng khoa viện cần đi qua
                object.setStart(inputWard.second);
                object.setEnd(inputWard.second);
                if (numLoaiCamXuc[0] < M/2) 
                {
                    object.setPersonality(inputNguongCamXuc[0]);
                    numLoaiCamXuc[0]++;
                }
                else 
                {
                    cout << "Không thể khởi tạo đối tượng dưới 11 tuổi có cảm xúc neurotic." << endl;
                }
                // Tốc độ di chuyển
                bool speedTest = false;
                while (!speedTest) 
                {
                    int speed = randomInt(0, 5);
                    if (soLudiChuyen[speed] > 0) 
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numVisitor++;
                nguoiTham.push_back(object);
                break;
            }

            default:
            {
                cout << "Không thể khởi tạo đối tượng dưới 11 tuổi." << endl;
                break;
            }
        }
    }
    for (int k = 0; k < M; ++k)
    {
        //Kiểu đối tượng
        int rd = 0;
        if(ageObject[k] < 11)
        {
            continue;
        }
        //Personel- bác sĩ không thể có tuổi < 23 hoặc > 63
        else if(ageObject[k] < 23.0 || ageObject[k] > 63.0)
        {
            rd = randomnumber(0,1);
        }
        //Đảm bảo điều kiện số Personel bé hơn noDisability
        else if(sumNoDisability == numPersonel + 1)
        {
            rd = randomnumber(0,1);
        }
        else
        {
            rd = randomnumber(0,2);
        }
        switch (rd)
        {
            //Xử lí dữ liệu với Patient- bệnh nhân
            case 0:
            {
                Patitent object;
                object.setID(k);//Thiết lặp ID
                object.setAge(ageObject[k]);//Thiết lặp tuổi
                object.setValues(3);//Số lượng khóa/viện cần đi qua
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                object.setPersonality(xacDinhNguongCamXuc(numLoaiCamXuc,inputNguongCamXuc,M));
                bool speedTest = false;
                while(!speedTest)
                {
                    int speed = randomnumber(0,5);
                    if(soLudiChuyen[speed] > 0)
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numPatient++;
                nguoibenh.push_back(object);
                break;
            }
            //Xử lí với Visitol
            case 1:
            {
                Visitor object;
                object.setID(k);//Thiết lặp ID
                object.setAge(ageObject[k]);//Thiết lặp tuổi
                object.setValues(1);//Số lượng khoa/viện cần đi qua
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                //Xác định ngưỡng cảm xúc
                object.setPersonality(xacDinhNguongCamXuc(numLoaiCamXuc,inputNguongCamXuc,M));
                bool speedTest = false;
                while(!speedTest)
                {
                    int speed = randomnumber(0,5);
                    if(soLudiChuyen[speed] > 0)
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numVisitor++;
                nguoiTham.push_back(object);
                break;
            }
        //Khởi tạo bác sĩ - Personel
            case 2:
            {
                Personel object;
                object.setID(k);//Thiết lặp ID
                object.setAge(ageObject[k]);//Thiết lặp tuổi
                object.setValues(3);
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                //Xác định ngưỡng cảm xúc
                object.setPersonality(xacDinhNguongCamXuc(numLoaiCamXuc,inputNguongCamXuc,M));
                //Kiểu di chuyển 
                numVisitor++;
                bacSi.push_back(object);
                break;
            }
            default:
            {
                cout << "Lỗi random.\n";
                break;
            }
        }
    }
    //lưu giữ các đối tượng theo từng loại
    obJect doiTuong;
    doiTuong.setPatient(nguoibenh);
    doiTuong.setVisitor(nguoiTham);
    doiTuong.setPersonel(bacSi);
    return doiTuong;
}

#endif // KHOITAOPEDESTRIAN_HPP