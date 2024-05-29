/* Đọc file dữ liệu và tạo ra mảng có M phần tử là người đi bộ trong hành lang.

M = 'value' trong file dữ liệu.

số nhân viên y tế (đối tượng của lớp Personel) < số người noDisability.

Không có đối tượng nào của lớp Personel lại thuộc nhóm crutches, sticks, wheelchairs hay blind.

Các đối tượng đều có số lượng các khoa Viện cần đến (không tính khoa viện đầu tiên và kết thúc) 
bằng đúng số lượng khoa viện trong tùy chọn journeyDistribution. Tất cả các khoa viện đều 
xuất hiện ít nhất một lần trong danh sách các khoa viện cần đến của người đi bộ.

tỉ lệ người có tính cách open hay neurotic là xấp xỉ (sai số dưới 5%) 50%

Không có người nào dưới 11 tuổi lại có tính cách neurotic 

không có nhân viên y tế nào có tuổi < 23 và > 61

Giá trị cảm xúc ban đầu của mọi người là 
pleasure = 0.75; surprise = 0.5; anger = fear = -0.2; hate = sad = -0.4
*/

#ifndef EX3_HPP
#define EX3_HPP
#include <iostream>
#include <vector>
#include <random>   
#include "docfileTXT.hpp"
#include "khoiTaoPedestrian.hpp"
#include "lop.hpp"
using namespace std;

void ex3(obJect &doituong) {
    vector<Patient> nguoiBenh = doituong.getNguoiBenh();
    vector<Visitor> nguoiTham = doituong.getNguoiTham();
    vector<Personel> bacSi = doituong.getBacSi();

    // lấy dữ liệu đầu vào có 43 sự kiện
    vector<Event> allEvents = eventTacDong();
    // lấy thời gian sự kiện tác động của tất cả các đối tượng
    vector<vector<int>> allTimeDistances = timeEvents();
    // khởi tạo generator ngẫu nhiên
    random_device rd;
    mt19937 gen(rd());
    // phạm vi số ngẫu nhiên
    int min_value = 0;
    int max_value = allEvents.size() - 1;
    uniform_int_distribution<int> distribution(min_value, max_value);

    // Thiết lập danh sách các Events tác động lên Patient
    for (int i = 0; i < nguoiBenh.size(); i++) 
    {
        int id = nguoiBenh[i].getID();
        vector<Event> events;
        for (int j = 0; j < 20; ++j) 
        {
            int X = distribution(rd);
            Event event = allEvents[X];
            event.setTime(allTimeDistances[id][j]);
            events.push_back(event);
        }    
        nguoiBenh[i].setEvents(events);
    }
    // Thiết lập danh sách các Events tác động lên Visitor
    for (int i = 0; i < nguoiTham.size(); i++) 
    {
        int id = nguoiTham[i].getID();
        vector<Event> events;
        for (int j = 0; j < 20; ++j) 
        {
            int X = distribution(rd);
            Event event = allEvents[X];
            event.setTime(allTimeDistances[id][j]);
            events.push_back(event);
        }
        nguoiTham[i].setEvents(events);
    }
    // Thiết lập danh sách các Events tác động lên Personel
    for (int i = 0; i < bacSi.size(); i++) 
    {
        int id = bacSi[i].getID();
        vector<Event> events;
        for (int j = 0; j < 20; ++j) 
        {
            int X = distribution(rd);
            Event event = allEvents[X];
            event.setTime(allTimeDistances[id][j]);
            events.push_back(event);
        }
        bacSi[i].setEvents(events);
    }
    
    // Cập nhật lại các đối tượng
    doituong.setNguoiBenh(nguoiBenh);
    doituong.setNguoiTham(nguoiTham);
    doituong.setBacSi(bacSi);
}

#endif // EX3_HPP