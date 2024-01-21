#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "cmd.cpp"


int main() {
    Schedule schedule;
    Controller controller;

    while (true) {
        std::cout << "Enter command (showSchedule, deleteSchedule, showWholeSchedule): ";
        std::string command;
        std::cin >> command;

        Command* cmd = nullptr;

        if (command == "showSchedule") {
            cmd = new ShowScheduleCommand();
        }
        else if (command == "deleteSchedule") {
            cmd = new DeleteScheduleCommand();
        }
        else if (command == "showWholeSchedule") {
            cmd = new ShowWholeScheduleCommand();
        }
        else {
            std::cout << "Invalid command. Please try again." << std::endl;
            continue;
        }
        controller.processCommand(cmd, schedule);
        delete cmd;
    }

    return 0;
}




//class DeleteLessonCommand : public Command {
//public:
//    void execute(Schedule& schedule) override {
//        std::string day;
//        std::cout << "Enter the day of the week to delete a lesson: ";
//        std::cin >> day;
//        DayOfWeek& selectedDay = schedule.getDay(day);
//
//        std::string lessonName;
//        std::cout << "Enter the name of the lesson to delete: ";
//        std::cin >> lessonName;
//
//        selectedDay.deleteLesson(lessonName);
//        std::cout << "Lesson deleted.\n";
//    }
//};
//
//class AddHomeworkCommand : public Command {
//public:
//    void execute(Schedule& schedule) override {
//        std::string day;
//        std::cout << "Enter the day of the week to add homework: ";
//        std::cin >> day;
//        DayOfWeek& selectedDay = schedule.getDay(day);
//
//        std::string lessonName;
//        std::cout << "Enter the name of the lesson to add homework: ";
//        std::cin >> lessonName;
//
//        std::string newHomework;
//        std::cout << "Enter the new homework: ";
//        std::cin.ignore();
//        std::getline(std::cin, newHomework);
//
//        selectedDay.addHomework(lessonName, newHomework);
//        std::cout << "Homework added.\n";
//    }
//};
//
//class DeleteHomeworkCommand : public Command {
//public:
//    void execute(Schedule& schedule) override {
//        std::string day;
//        std::cout << "Enter the day of the week to delete homework: ";
//        std::cin >> day;
//        DayOfWeek& selectedDay = schedule.getDay(day);
//
//        std::string lessonName;
//        std::cout << "Enter the name of the lesson to delete homework: ";
//        std::cin >> lessonName;
//
//        selectedDay.deleteHomework(lessonName);
//        std::cout << "Homework deleted.\n";
//    }
//};
//
//class SaveChangesCommand : public Command {
//public:
//    void execute(Schedule& schedule) override {
//        std::string day;
//        std::cout << "Enter the day of the week to save changes: ";
//        std::cin >> day;
//        DayOfWeek& selectedDay = schedule.getDay(day);
//
//        selectedDay.saveChanges();
//        std::cout << "Changes saved.\n";
//    }
//};