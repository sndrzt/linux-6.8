// g++ -o annotation annotation.cc
// argv[1] contains config list like this:
// CONFIG_USB_ISP1760_GADGET_ROLE -n
// CONFIG_USB_ISP1760_HOST_ROLE n-
// CONFIG_USB_M66592 -m
// argv[2] should be original annotation files, for example debian.master/config/annotation
// ./annotation a.txt debian.master/config/annotation debian.master/config/annotation_
// step 1. read config_list_file line by line, add " " then push into config_list
// step 2. for each item in config_list, seach 'amd64': 'n' in annotation file, replace with -, search 'amd64': '-', replace with n
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <regex>
using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
 
int main(int argc, char *argv[]) {
	ifstream config_list_file(argv[1]);
	string line1;
	vector<vector<string>> config_list;

	if (config_list_file.is_open()) {
		while(getline(config_list_file, line1)) {
			//cout << line1 << endl;
			stringstream ss(line1);
			vector<string> items;
			string item;
    
			while (getline(ss, item, ' ')) {
				items.push_back(item);
			}
    
			//cout << items[0] << " / " << items[1] << endl;

			config_list.push_back(items);
		}
	
		config_list_file.close();
	}

	ifstream annotations(argv[2]);
	string line2;
	vector<string> annotations_list;
	if (annotations.is_open()) {
		while (getline(annotations, line2)) {
			//cout << line2 << endl;
			for (const vector<string> s : config_list) {
				//cout << s[0] << " | " << s[1] << endl;
				if(line2.find(s[0] + " ") != string::npos) {
					if (s[1] == "-m") {
						cout << s[0] << " found, - to m" << endl;
						line2 = regex_replace(line2, regex("'amd64': '-'"), "'amd64': 'm'");
					}
					if (s[1] == "m-") {
						cout << s[0] << " found, m to -" << endl;
						line2 = regex_replace(line2, regex("'amd64': 'm'"), "'amd64': '-'");
					}
					if (s[1] == "-n") {
						cout << s[0] << " found, - to n" << endl;
						line2 = regex_replace(line2, regex("'amd64': '-'"), "'amd64': 'n'");
					}
					if (s[1] == "n-") {
						cout << s[0] << " found, n to -" << endl;
						line2 = regex_replace(line2, regex("'amd64': 'n'"), "'amd64': '-'");
					}
					if (s[1] == "-y") {
						cout << s[0] << " found, - to y" << endl;
						line2 = regex_replace(line2, regex("'amd64': '-'"), "'amd64': 'y'");
					}
					if (s[1] == "y-") {
						cout << s[0] << " found, y to -" << endl;
						line2 = regex_replace(line2, regex("'amd64': 'y'"), "'amd64': '-'");
					}
				}
			}

			annotations_list.push_back(line2);
		}
	}
	annotations.close();

	ofstream outfile(argv[3]);
	for (auto it = annotations_list.begin(); it != annotations_list.end(); ++it) {
		outfile << *it << endl;
	}
	outfile.close();

	return 0;
}

