#include <iterator>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::unordered_map;

struct Person {
  int age;
  string name;
};

void GroupByAge(vector<Person>* people) {
  // TODO - you fill in here.
  unordered_map<int, int> age_count;
  for(const Person& person : *people){
    age_count[person.age]++;
  }

  unordered_map<int, int> age_offset;
  int offset = 0;
  for(auto& p : age_count){
    age_offset[p.first] = offset;
    offset += p.second;
  }

  while(!age_offset.empty()){
    auto from = age_offset.begin();
    auto to = age_offset.find((*people)[from->second].age);

    std::swap((*people)[from->second], (*people)[to->second]);
    --age_count[to->first];

    if(age_count[to->first] > 0){
      ++age_offset[to->first];
    }else{
      age_offset.erase(to->first);
    }
  }
}

namespace test_framework {
template <>
struct SerializationTrait<Person> : UserSerTrait<Person, int, string> {};
}  // namespace test_framework

void GroupByAgeWrapper(TimedExecutor& executor, vector<Person>& people) {
  if (people.empty()) {
    return;
  }
  std::multiset<Person, std::function<bool(Person, Person)>> values(
      begin(people), end(people), [](const Person& a, const Person& b) {
        return a.age == b.age ? a.name < b.name : a.age < b.age;
      });

  executor.Run([&] { GroupByAge(&people); });

  if (people.empty()) {
    throw TestFailure("Empty result");
  }

  std::set<int> ages;
  int last_age = people[0].age;
  for (auto& x : people) {
    if (ages.count(x.age)) {
      throw TestFailure("Entries are not grouped by age");
    }
    if (x.age != last_age) {
      ages.insert(last_age);
      last_age = x.age;
    }
    auto it = values.find(x);
    if (it == end(values)) {
      throw TestFailure("Entry set changed");
    }
    values.erase(it);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "people"};
  return GenericTestMain(args, "group_equal_entries.cc",
                         "group_equal_entries.tsv", &GroupByAgeWrapper,
                         DefaultComparator{}, param_names);
}
