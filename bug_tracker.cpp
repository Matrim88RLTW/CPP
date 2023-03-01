#include "bugtracker.h"
#include <iostream>

void BugTracker::AddBug(const BugReport& bug) {
  bugs_.push_back(bug);
}

void BugTracker::SetStatus(int index, const std::string& status) {
  bugs_[index].status = status;
}

void BugTracker::AssignBug(int index, const std::string& assignee) {
  bugs_[index].assignee = assignee;
}

void BugTracker::PrintBugs() const {
  for (int i = 0; i < bugs_.size(); ++i) {
    std::cout << "Bug #" << i << ": " << bugs_[i].description << " ("
              << bugs_[i].status << ", assigned to " << bugs_[i].assignee
              << ", reported by " << bugs_[i].reporter << ")\n";
  }
}
