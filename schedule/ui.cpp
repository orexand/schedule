#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

struct LessonInfo {
    int start_time;
    int end_time;
    std::string lesson_name;
    std::string homework;
};

class Lesson {
private:
    int start_time;
    int end_time;
    std::string lesson_name;
    std::string homework;
public:
    Lesson(const LessonInfo& info)
        : start_time(info.start_time), end_time(info.end_time), lesson_name(info.lesson_name), homework(info.homework) {}

    int getStartTime() const { return start_time; }
    int getEndTime() const { return end_time; }
    const std::string& getLessonName() const { return lesson_name; }
    const std::string& getHomework() const { return homework; }
};

class DayOfWeek {
private:
    std::vector<Lesson> lessons;
public:
    void addLesson(const Lesson& lesson) {
        lessons.push_back(lesson);
        std::sort(lessons.begin(), lessons.end(), [](const Lesson& a, const Lesson& b) {
            return a.getStartTime() < b.getStartTime();
            });
    }

    const std::vector<Lesson>& getLessons() const {
        return lessons;
    }
};

class Schedule {
private:
    void addLessonToDay(const std::string& day, const Lesson& lesson) {
        days[day].addLesson(lesson);
    }

    std::map<std::string, DayOfWeek> days;
public:
    void addDay(const std::string& day, const DayOfWeek& day_schedule) {
        days[day] = day_schedule;
    }

    const DayOfWeek& getDay(const std::string& day) const {
        auto it = days.find(day);
        if (it != days.end()) {
            return it->second;
        }
        else {
            static DayOfWeek empty_day;
            return empty_day;
        }
    }

    bool deleteDay(const std::string& day) {
        auto it = days.find(day);
        if (it != days.end()) {
            days.erase(it);
            return true;
        }
        return false;
    }

    const std::map<std::string, DayOfWeek>& getDays() const { return days; }

    void loadScheduleFromFile(const std::string& filename, const std::string& day) {
        std::ifstream file(filename);
        if (file.is_open()) {
            LessonInfo lessonInfo;
            while (file >> lessonInfo.start_time >> lessonInfo.end_time >> lessonInfo.lesson_name >> lessonInfo.homework) {
                addLessonToDay(day, Lesson(lessonInfo));
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
};
