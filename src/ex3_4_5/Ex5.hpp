#ifndef EX5_HPP
#define EX5_HPP
#include <map>
#include <algorithm>
#include "docfileTXT.hpp"
#include "bai4.hpp"
using namespace std;

void ex5(obJect& doituong) 
{
    vector<Patient> nguoiBenh = doituong.getPatient();
    vector<Visitor> nguoiTham = doituong.getVisitor();
    vector<Personel> bacSi = doituong.getPersonel();

    // Số lượng đối tượng
    int M = get_numOfPedestrian();
    int single = nguoiTham.size();
    int triple = nguoiBenh.size() + bacSi.size();

    // Bản đồ bệnh viện
    pair<vector<Ward>, A> map = mapWard();
    vector<Ward> cacKhoaVien = map.first;

    // true - lời gọi hàm bài 4
    bool test = false;
    do {
        // Thiết lập số lượt đi qua tương ứng các khoa
        vector<pair<Ward, int>> numKhoa = ex4(cacKhoaVien, triple, single);

        // map lưu trữ số lần xuất hiện của các khoa
        map<string, int> numWard;
        for (pair<Ward, int> a : numKhoa) 
        {
            numWard[a.first.getName()] += a.second;
        }

        vector<pair<string, int>> numWardSort(numWard.begin(), numWard.end());
        int sizeWard = numWardSort.size();
        // Duyệt vector Patient
        int demPatient = 0;
        // Duyệt vector Visitor
        int demVisitor = 0;
        // Duyệt vector Personel
        int demPersonel = 0;

        for (int i = 0; i < M; ++i) 
        {
            if (demVisitor < nguoiTham.size() && nguoiTham[denVistor].getID == i)
            {
                // Sắp xếp theo thứ tự giảm dần
                sort(numWardSort.begin(), numWardSort.end(), [](pair<string, int>& a, pair<string, int>& b) {
                    return a.second > b.second;
                });

                // Khoa có số lượt di chuyển qua còn lại nhiều nhất
                pair<string, int> m = numWardSort[0];
                string nameMax = m.first;
                // Khoa đi qua của Visitor
                Ward max = findWardMax(nameMax, cacKhoaVien);
                vector<Ward> journey;
                journey.push_back(max);
                // Thiết lập khoa đi qua
                nguoiTham[demVisitor].setJourney(journey);

                // Tăng giảm biến đếm
                demVisitor++;
                numWard[nameMax]--;
                numWardSort[0].second--;
            }
            else if (demPatient < nguoiBenh.size() && nguoiBenh[demPatient].getID() == i) 
            {
                // Sắp xếp theo thứ tự giảm dần
                sort(numWardSort.begin(), numWardSort.end(), [](pair<string, int>& a, pair<string, int>& b) {
                    return a.second > b.second;
                });

                pair<string, int> max1 = numWardSort[0];
                pair<string, int> max2 = numWardSort[1];
                pair<string, int> max3 = numWardSort[2];
                // 3 Khoa có số lượt di chuyển qua còn lại nhiều nhất
                Ward maxWard1 = findWardMax(max1.first, cacKhoaVien);
                Ward maxWard2 = findWardMax(max2.first, cacKhoaVien);
                Ward maxWard3 = findWardMax(max3.first, cacKhoaVien);

                vector<Ward> journey{maxWard1, maxWard2, maxWard3};
                // Thiết lập khoa đi qua
                nguoiBenh[demPatient].setJourney(journey);

                // Giảm số lượt đi qua của các khoa
                numWard[max1.first]--;
                numWard[max2.first]--;
                numWard[max3.first]--;

                // Giảm số lượt đi qua của các khoa
                numWardSort[0].second--;
                numWardSort[1].second--;
                numWardSort[2].second--;

                // Tăng giảm biến đếm
                demPatient++;
            }
            else if (demPersonel < bacSi.size() && bacSi[demPersonel].getID() == i) 
            {
                // Sắp xếp theo thứ tự giảm dần
                sort(numWardSort.begin(), numWardSort.end(), [](pair<string, int>& a, pair<string, int>& b) {
                    return a.second > b.second;
                });

                pair<string, int> max1 = numWardSort[0];
                pair<string, int> max2 = numWardSort[1];
                pair<string, int> max3 = numWardSort[2];
                // 3 Khoa có số lượt di chuyển qua còn lại nhiều nhất
                Ward maxWard1 = findWardMax(max1.first, cacKhoaVien);
                Ward maxWard2 = findWardMax(max2.first, cacKhoaVien);
                Ward maxWard3 = findWardMax(max3.first, cacKhoaVien);

                vector<Ward> journey{maxWard1, maxWard2, maxWard3};
                // Thiết lập khoa đi qua
                bacSi[demPersonel].setJourney(journey);

                // Giảm số lượt đi qua của các khoa
                numWard[max1.first]--;
                numWard[max2.first]--;
                numWard[max3.first]--;

                // Giảm số lượt đi qua của các khoa
                numWardSort[0].second--;
                numWardSort[1].second--;
                numWardSort[2].second--;

                // Tăng giảm biến đếm
                demPersonel++;
            }
        }
        // Kiểm tra lại
        for (auto& k : numWard) 
        {
            if (k.second != 0) 
            {
                test = true;
            }
        }

    } while (test);

    // Cập nhật lại các đối tượng
    doituong.setPatient(nguoiBenh);
    doituong.setVisitor(nguoiTham);
    doituong.setPersonel(bacSi);
}


#endif // EX5_HPP