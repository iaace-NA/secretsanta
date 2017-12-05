#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <functional>
//compile -std=c++11
std::ostream& operator<<(std::ostream& output, const std::list<std::string>& contents);
const std::string gift(const std::list<std::string>& contents);
template <class T> void shuffle(std::list<T>& lst);
int main() {
	std::cout << "Please enter the names of the people separated by commas." << std::endl;
	std::string raw_input;
	std::cin >> raw_input;
	std::list<std::string> names;
	for (std::size_t space_location = raw_input.find(","); space_location != std::string::npos; raw_input = raw_input.substr(space_location + 1), space_location = raw_input.find(",")) names.push_back(raw_input.substr(0, space_location));
	names.push_back(raw_input);
	shuffle(names);
	std::cout << "Who gifts who:\n" << gift(names) << std::endl;
	return 0;
}
std::ostream& operator<<(std::ostream& output, const std::list<std::string>& contents) {
    for (std::list<std::string>::const_iterator i = contents.begin(); i != contents.end(); ++i) output << *i << "\n";
    return output;
}
template <class T> void shuffle(std::list<T>& lst) { // shuffle contents of a list
    std::vector< std::reference_wrapper< const T > > vec(lst.begin(), lst.end());// create a vector of (wrapped) references to elements in the list
    std::shuffle(vec.begin(), vec.end(), std::mt19937{ std::random_device{}() });// shuffle (the references in) the vector
    std::list<T> shuffled_list { vec.begin(), vec.end() };// copy the shuffled sequence into a new list
    lst.swap(shuffled_list);// swap the old list with the shuffled list
}
const std::string gift(const std::list<std::string>& contents) {
    std::string answer = *(--contents.end());
    std::list<std::string>::const_iterator i = contents.begin();
    for (; i != (--contents.end()); ++i) answer += "->" + *i + "\n" + *i;
    return answer + "->" + *i;
}
