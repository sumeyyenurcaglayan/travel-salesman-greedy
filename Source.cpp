#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <math.h>
#include <chrono>

using namespace std;

class city {

public:
	int x_coord;
	int y_coord;
	int c_no;
	bool uni = false;
	int remaining = 2;

	city(int x, int y, int no) {
		x_coord = x;
		y_coord = y;
		c_no = no;
	}

};

float Distance(city a, city b) {
	return sqrt(pow(a.x_coord - b.x_coord, 2) + pow(a.y_coord - b.y_coord, 2));
}

int main() {

	auto t1 = chrono::high_resolution_clock::now();
	vector<vector<int>> coords;

	ifstream reader("att48_xy.txt");
	int a, b;
	int i = 0;
	while (reader >> a >> b){
		coords.push_back({ a,b });
	}

	vector<city> created;
	vector<vector<int>> cityNo;
	vector<float> dist;
	vector<vector<int>> S_cityNo;
	vector<float> sortedDistance;
	vector<city> endpoints;


	for (int i = 0; i < coords.size(); i++) {
		created.push_back(city(coords[i][0], coords[i][1], i));
	}

	for (int i = 0; i < created.size(); i++) {
		for (int j = i; j < created.size(); j++) {
			float disto = Distance(created[i], created[j]);
			if (disto != 0) {
				dist.push_back(disto);
				cityNo.push_back({ created[i].c_no, created[j].c_no });
			}
		}
	}

	float min = dist[0];
	int iterator = 0;
	int keeper = 0;

	while (!dist.empty()) {
		float min = dist[0];
		while (iterator < dist.size()) {
			if (min >= dist[iterator]) {
				min = dist[iterator];
				keeper = iterator;
				
			}
			iterator++;
		}
		
		sortedDistance.push_back(min);
		dist.erase(dist.begin() + keeper);

		S_cityNo.push_back({ cityNo[keeper][0], cityNo[keeper][1] });
		if (S_cityNo.size() == 1) {
			created[cityNo[keeper][0]].uni = true;
		}
		cityNo.erase(cityNo.begin() + keeper);

		iterator = 0;
	}


	float total_dist = 0;

	for (int i = 0; i < sortedDistance.size(); i++) {


		if (created[S_cityNo[i][0]].remaining > 0 && created[S_cityNo[i][1]].remaining > 0) {

			//cout << S_cityNo[i][0] << " - " << S_cityNo[i][1] << endl;    // for the connection
			total_dist += sortedDistance[i];
			if (created[S_cityNo[i][0]].uni != true) {
				created[S_cityNo[i][0]].remaining--;
			}
			else {
				created[S_cityNo[i][0]].remaining -= 2; 
			}
			created[S_cityNo[i][1]].remaining--;
		}
	}

	for (auto c : created) {
		if (c.uni == true || c.remaining > 0) {
			endpoints.push_back(c);
		}
	}

	total_dist += Distance(endpoints[0], endpoints[1]);

	cout << total_dist << endl;


	auto t2 = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	cout << "Execution Time: "<<(float)duration/1000000<<endl;

	system("pause");
	return 0;
}