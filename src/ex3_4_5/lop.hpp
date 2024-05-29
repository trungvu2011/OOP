#ifndef LOP_HPP
#define LOP_HPP
#include <vector>
#include <string>
using namespace std;

class Point
{
    private:
        double x;
        double y;
    public:
        Point(double x, double y)
        {
            this->x = x;
            this->y = y;
        }
        Point() {}
        double getX() { return x; } 
        double getY() { return y; }

        void setX(double x) { this->x = x; }
        void setY(double y) { this->y = y; }
};

class Ward
{
    protected:
        string name; // Tên khoa viện
        vector<pair<Point, Point>> wallCoordinate; // Các cạnh viền của khoa viện
        double width; // chiều ngang khoa viện
    private:
        Point entrance; // Cổng vào khoa viện
        Point exit; // Cổng ra khoa viện
    public:
        Ward(string name, Point entrance, Point exit, vector<pair<Point, Point>> wallCoordinate)
        {
            this->name = name;
            this->entrance = entrance;
            this->exit = exit;
            this->wallCoordinate = wallCoordinate;
        }
        Ward() {}

        string getName() { return name; }
        Point getEntrance() { return entrance; }
        Point getExit() { return exit; }
        double getWidth() { return width; }
        vector<pair<Point, Point>> getWallCoordinate() { return wallCoordinate; }

        void setName(string name) { this->name = name; }
        void setEntrance(Point entrance) { this->entrance = entrance; }
        void setExit(Point exit) { this->exit = exit; }
        void setWidth(double width) { this->width = width; }
        void setWallCoordinate(vector<pair<Point, Point>> wallCoordinate) { this->wallCoordinate = wallCoordinate; }
};

class A : public Ward 
{
    private:
        vector<Point> entrance; // 2 điểm đầu vào
        vector<Point> exit; // 2 điểm đầu ra
    public:
        void setEntrance(vector<Point> entrance) { this->entrance = entrance; }
        void setExit(vector<Point> exit) { this->exit = exit; }
};

// enum chứa các kiểu di chuyển của con người trên hành lang
enum Walkability
{
    noDisabilityNoOvertaking = 0, // Không khuyết tật, không vượt
    noDisabilityOvertaking = 1, // Không khuyết tật, vượt
    crutches = 2, // Di chuyển bằng nạng
    sticks = 3, // Di chuyển bằng gậy
    wheelchairs = 4, // Di chuyển bằng xe lăn
    blind = 5 // Người mù
};

// Lớp chứa 6 cảm xúc của con người
class Emotion
{
    private:
        double pleasure = 0.75; // vui vẻ
        double surprise = 0.5; // bất ngờ
        double anger = -0.2; // tức giận
        double fear = -0.2; // sợ hãi
        double hate = -0.4; // ghét bỏ
        double sad = -0.4; // buồn bã
    public:
        Emotion(double pleasure, double surprise, double anger, double fear, double hate, double sad)
        {
            this->pleasure = pleasure;
            this->surprise = surprise;
            this->anger = anger;
            this->fear = fear;
            this->hate = hate;
            this->sad = sad;
        }
        Emotion() {}

        double getPleasure() { return pleasure; }
        double getSurprise() { return surprise; }
        double getAnger() { return anger; }
        double getFear() { return fear; }
        double getHate() { return hate; }
        double getSad() { return sad; }

        void setPleasure(double pleasure) { this->pleasure = pleasure; }
        void setSurprise(double surprise) { this->surprise = surprise; }
        void setAnger(double anger) { this->anger = anger; }
        void setFear(double fear) { this->fear = fear; }
        void setHate(double hate) { this->hate = hate; }
        void setSad(double sad) { this->sad = sad; }
};

// Lớp chứa thông tin của mỗi sự kiện
class Event
{
    private:
        // dữ liệu sinh ra ở bai 2i
        // mỗi sự kiện tác động 6 cảm xúc của con người
        vector<double> intensity; // Mức độ cảm xúc
        double time; // Thời gian xảy ra sự kiện
    public:
        Event(vector<double> intensity, double time)
        {
            this->intensity = intensity;
            this->time = time;
        }
        Event() {}

        vector<double> getIntensity() { return intensity; }
        double getTime() { return time; }

        void setIntensity(vector<double> intensity) { this->intensity = intensity; }
        void addIntensity(double intensity) { this->intensity.push_back(intensity); }
        void setTime(double time) { this->time = time; }
};

// 
class AGVEvent : public Event
{

};


class Personality
{
    private:
        double lambda; 
        double positiveEmotionThreshold; // Ngưỡng cảm xúc tích cực
        double negativeEmotionThreshold; // Ngưỡng cảm xúc tiêu cực
    public:
        Personality(double lambda, double positiveEmotionThreshold, double negativeEmotionThreshold)
        {
            this->lambda = lambda;
            this->positiveEmotionThreshold = positiveEmotionThreshold;
            this->negativeEmotionThreshold = negativeEmotionThreshold;
        }
        Personality() {}

        double getLambda() { return lambda; }
        double getPositiveEmotionThreshold() { return positiveEmotionThreshold; }
        double getNegativeEmotionThreshold() { return negativeEmotionThreshold; }

        void setLambda(double lambda) { this->lambda = lambda; }
        void setPositiveEmotionThreshold(double positiveEmotionThreshold) { this->positiveEmotionThreshold = positiveEmotionThreshold; }
        void setNegativeEmotionThreshold(double negativeEmotionThreshold) { this->negativeEmotionThreshold = negativeEmotionThreshold; }
};

class Pedestrian
{
    protected:
        int ID; // ID của người đi bộ
        Ward start; // Khoa viện bắt đầu
        Ward end; // Khoa viện kết thúc
        vector<Ward> journey; // Danh sách các khoa viện cần đến
        double velocity; // Vận tốc di chuyển
        Personality personality; // Tính cách của người đi bộ
        Emotion emotion; // Cảm xúc của người đi bộ
        vector<Event> events; // Danh sách các sự kiện tác động đến người đi bộ
        double walkingTime; // Thời gian di chuyển
        int values; //Số lượng các khoa viện cần đến;
        double distance; // Khoảng cách di chuyển
        double age; // Tuổi của người đi bộ
        AGVEvent impactOfAGV; // Sự kiện tác động đến người đi bộ
        Point tempPoints; // Điểm tạm
    public:
        Pedestrian(int ID,Ward start,Ward end,vector<Ward> journey,double velocity,Personality personality,Emotion emotion,
        vector<Event> events,double walkingTime,int values,double distance,double age,AGVEvent impactOfAGV,Point tempPoints)
        {
            this->ID = ID;
            this->start = start;
            this->end = end;
            this->journey = journey;
            this->velocity = velocity;
            this->personality = personality;
            this->emotion = emotion;
            this->events = events;
            this->walkingTime = walkingTime;
            this->values = values;
            this->distance = distance;
            this->age = age;
            this-> impactOfAGV = impactOfAGV;
            this->tempPoints = tempPoints;

        }
        Pedestrian() {}

        int getValue() { return values; }
        int getID() { return ID; }
        Ward getStart() { return start; }
        Ward getEnd() { return end; }
        vector<Ward> getJourney() { return journey; }
        double getVelocity() { return velocity; }
        Personality getPersonality() { return personality; }
        Emotion getEmotion() { return emotion; }
        vector<Event> getEvents() { return events; }
        double getWalkingTime() { return walkingTime; }
        double getDistance() { return distance; }
        double getAge() { return age; }
        AGVEvent getImpactOfAGV() { return impactOfAGV; }
        Point getTempPoints() { return tempPoints; }
        
        void setValue(int values) { this->values = values; }
        void setID(int ID) { this->ID = ID; }
        void setStart(Ward start) { this->start = start; }
        void setEnd(Ward end) { this->end = end; }
        void setJourney(vector<Ward> journey) { this->journey = journey; }
        void setVelocity(double velocity) { this->velocity = velocity; }
        void setPersonality(Personality personality) { this->personality = personality; }
        void setEmotion(Emotion emotion) { this->emotion = emotion; }
        void setEvents(vector<Event> events) { this->events = events; }
        void setWalkingTime(double walkingTime) { this->walkingTime = walkingTime; }
        void setDistance(double distance) { this->distance = distance; }
        void setAge(double age) { this->age = age; }
        void setImpactOfAGV(AGVEvent impactOfAGV) { this->impactOfAGV = impactOfAGV; }
        void setTempPoints(Point tempPoints) { this->tempPoints = tempPoints; }
};

// lớp bệnh nhân
class Patient : public Pedestrian
{
    private:
        Walkability walkability; // Kiểu di chuyển
    public:
        Walkability getWalkability() { return walkability; }
        void setWalkability(Walkability walkability) { this->walkability = walkability; }
        Patient() {}
};

// lớp người thăm bệnh nhân
class Visitor : public Pedestrian
{
    private:
        Walkability walkability; // Kiểu di chuyển
    public:
        Walkability getWalkability() { return walkability; }
        void setWalkability(Walkability walkability) { this->walkability = walkability; }
        Visitor() {}
};

// lớp bác sĩ
class Personel : public Pedestrian
{

};

class obJect 
{
    private:
        vector<Patient> nguoiBenh;  
        vector<Visitor> nguoiTham;
        vector<Personel> bacSi;
    public:
        vector<Patient> getNguoiBenh() { return nguoiBenh; }
        vector<Visitor> getNguoiTham() { return nguoiTham; }
        vector<Personel> getBacSi() { return bacSi; }

        void setNguoiBenh(vector<Patient> nguoiBenh) { this->nguoiBenh = nguoiBenh; }
        void setNguoiTham(vector<Visitor> nguoiTham) { this->nguoiTham = nguoiTham; }
        void setBacSi(vector<Personel> bacSi) { this->bacSi = bacSi; }
};

// Các lớp chế độ đọc

// Chế độ chạy
class runMode 
{
    public:
        int value; // giá trị chấp nhận file hospital.txt
};

// Sinh ngẫu nhiên/nạp dữ liệu 
class randomness 
{
    public:
        string description; 
        //'1': Đại diện cho tạo ra giá trị ngẫu nhiên mới 
        //'0': chương trình nạp từ các dữ liệu có sẵn
        bool value;
};

// Độ tuổi của ngươi đi chuyển trên hành lang
class ageDistribution 
{
    public:
        string description;
        int samples; // Đọc giá trị của numOfAgents
        int numOfValues;
        int minValue; // Tuổi nhỏ nhất
        int maxValue; // Tuổi lớn nhất

        vector<float> ageInput;
};

class speedWalkability 
{
    public:
        string description;
        float velocity;
};

class journeyDistribution 
{
    public:
        // Lớp lưu trữ thông tin về từng loại đối tượng di chuyển
        class typeObject
        {
            public:
                string description;
                int value; // số khoa viện đi qua
                Ward start; // khoa viện bắt đầu
                Ward end; // khoa viện kết thúc
        };  
        typeObject forPaient; // Số khoa viện đi qua của bệnh nhân
        typeObject forVisitor; // Số khoa viện đi qua của người thăm
        typeObject forPersonel; // Số khoa viện đi qua của bác sĩ
        
};

// Phân chia khoa viện theo chức năng
class warDistribution
{
    public:
        string description;
        class deparment
        {
            public:
                string description; // Mô tả chức năng của khoa viện
        };
        class normal
        {
            public:
                string description; // Mô tả
                int samples;
                int sumOfValues;
                int lowerBound;
                int upperBound; 
        };
};

// Thời gian ở trong khoa viện cuả mỗi người
class insideTimeDistribution
{
    public:
        string description;
        class uniform 
        {
            public:
                string description;
                int value;
        };

        // Thời gian ở mỗi khoa viện chung
        uniform uniform;
};

#endif // LOP_HPP
