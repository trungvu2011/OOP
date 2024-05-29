/*Bài 4 thực hiện nhiệm vụ
- nhận đầu vào là:
+ i) mảng các Ward.
+ ii) triple:Số lượng các mảng có 3 phần tử của Ward
+ iii) single: Số lượng các mảng có 1 phần tử của Ward
- Đầu ra 1 vector<pair<Ward,int>> sao cho
+ Tổng các giá trị int của pair bằng đúng triple*3 + single
+ Các int của pair tuân theo phân phối chuẩn
- Chú ý trả về lỗi nếu tổng triple và single không bằng numOfAgents
(tùy chọn bài 2)
*/
#ifndef EX4_HPP
#define EX4_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "doc_json.hpp"
#include "docfileTXT.hpp"
#include "lop.hpp"
using namespace std;

double rand_normal(double mean, double stddev) 
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(mean, stddev);
    double output = dist(gen);
    return output;
}

// triple - số đối tượng phải đi qua 3 khoa viên
// single - số đối tượng phải đi qua 1 khoa viện
vector<pair<Ward, int>> ex4(vector<Ward>& input, int triple, int single) 
{
    vector<pair<Ward, int>> result;

    int numOfAgents = get_numOfAgents(); // Tổng số người trong bệnh viện
    if (numOfAgents == -1) 
    {
        cerr << "Lỗi khi lấy số lượng người trong bệnh viện." << endl;
        return result;
    }

    // Tổng số lượng người
    int sum = triple + single;
    // Kiểm tra dữ liệu
    if (sum != numOfAgents) 
    {
        cerr << "Dữ liệu không khớp với số lượng người trong bệnh viện." << endl;
        return result;
    }

    // Số lượng khoa viện
    int sLuongWard = input.size();
    // Tổng số lượt đi qua các khoa viện
    int total_value = triple * 3 + single;
    int min_value = 0;
    int mean = total_value / sLuongWard; // Số lượng lượt đi qua trung bình của mỗi khoa viện
    double std = 3; // độ lệch chuẩn

    // Số lượt đi qua của từng khoa viện
    vector<int> number;
    bool test = true; // trạng thái lặp
    while (test)
    {
        // Xóa hết các giá trị không thỏa mãn
        number.clear();
        for (int i = 0; i < sLuongWard; i++) 
        {
            int a = static_cast<int>(rand_normal(mean, std));
            number.push_back(a);
        }

        // Tính tổng số lượt đi qua các khoa viện
        int sum = 0;
        for (int num : number) 
        {
            sum += num;
        }

        // Kiểm tra tổng số lượt đi qua các khoa viện
        if (sum == total_value) 
        {
            test = false;
        }
    }

    // Thiết lập khoa tương ứng số lượt đi qua
    for (int i = 0; i < sLuongWard; i++) 
    {
        result.push_back(make_pair(input[i], number[i]));
    }

    return result;
}

#endif // EX4_HPP