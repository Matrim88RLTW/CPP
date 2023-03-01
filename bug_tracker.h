#ifndef BUGTRACKER_H
#define BUGTRACKER_H

#include <string>
#include <vector>

// Define a struct to represent a bug report
struct BugReport {
  std::string description;  // description of the bug
  std::string status;       // status of the bug (e.g. "open", "closed", etc.)
  std::string assignee;     // person responsible for fixing the bug
  std::string reporter;     // person who reported the bug
};

// Define a class to represent the bug tracker
class BugTracker {
 public:
  // Add a new bug to the tracker
  void AddBug(const BugReport& bug);

  // Change the status of a bug
  void SetStatus(int index, const std::string& status);

  // Assign a bug to a person
  void AssignBug(int index, const std::string& assignee);

  // Print a list of all the current bugs
  void PrintBugs() const;

 private:
  std::vector<BugReport> bugs_;
};

#endif  // BUGTRACKER_H
