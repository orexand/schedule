#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "ui.cpp"

class Command {
public:
    virtual void execute(Schedule& schedule) = 0;
};

class ShowScheduleCommand : public Command {
public:
    void execute(Schedule& schedule) override {
        std::cout << "Enter the day of the week: ";
        std::string day;
        std::cin >> day;

        schedule.loadScheduleFromFile(day + ".txt", day);

        const DayOfWeek& day_schedule = schedule.getDay(day);

        if (!day_schedule.getLessons().empty()) {
            for (const Lesson& lesson : day_schedule.getLessons()) {
                std::cout << "Start Time: " << lesson.getStartTime()
                    << ", End Time: " << lesson.getEndTime()
                    << ", Lesson Name: " << lesson.getLessonName()
                    << ", Homework: " << lesson.getHomework() << std::endl;
            }
        }
        else {
            std::cout << "weekend" << std::endl;
        }
    }
};

class DeleteScheduleCommand : public Command {
public:
    void execute(Schedule& schedule) override {
        std::cout << "Enter the day of the week to delete schedule: ";
        std::string day;
        std::cin >> day;

        if (schedule.deleteDay(day)) {
            std::cout << "Schedule for " << day << " deleted successfully." << std::endl;
        }
        else {
            std::cout << "Schedule for " << day << " not found." << std::endl;
        }
    }
};

class ShowWholeScheduleCommand : public Command {
public:
    void execute(Schedule& schedule) override {
        for (const auto& entry : schedule.getDays()) {
            const std::string& day = entry.first;

            schedule.loadScheduleFromFile(day + ".txt", day);

            const DayOfWeek& day_schedule = entry.second;

            std::cout << "Day: " << day << std::endl;

            if (!day_schedule.getLessons().empty()) {
                for (const Lesson& lesson : day_schedule.getLessons()) {
                    std::cout << "Start Time: " << lesson.getStartTime()
                        << ", End Time: " << lesson.getEndTime()
                        << ", Lesson Name: " << lesson.getLessonName()
                        << ", Homework: " << lesson.getHomework() << std::endl;
                }
            }
            else {
                std::cout << "weekend" << std::endl;
            }

            std::cout << std::endl;
        }
    }
};

class Controller {
public:
    void processCommand(Command* command, Schedule& schedule) {
        command->execute(schedule);
    }
};