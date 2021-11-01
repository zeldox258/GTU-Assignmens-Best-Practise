#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
ofstream myfile("output.txt");

bool isReflexive(vector<string> vec, map<string, int>& map) { //checks reflexieve
    for (int i = 0; i < vec.size(); i++) {
        string temp = "";
        temp += vec[i];
        temp += vec[i];
        if (!map.count(temp)) return false;
    }

    return true;
}

void doItReflexive(vector<string> vec, map<string, int>& map) {// do the set reflexieve
    for (int i = 0; i < vec.size(); i++) {
        string temp = "";
        temp += vec[i];
        temp += vec[i];
        if (!map.count(temp)) map[temp] = 1;
    }
}

void clearReflexive(vector<string> vec, map<string, int>& map) {//remove pairs exp:1,1
    for (int i = 0; i < vec.size(); i++) {
        string temp = "";
        temp += vec[i];
        temp += vec[i];
        if (map.count(temp)) map.erase(temp);
    }
}

bool isSymetric(vector<string> vec, map<string, int>& map) {//checks symetric
    for (auto elem : map){
        string temp = "";
        temp += elem.first[1];
        temp += elem.first[0];
        if (!map.count(temp)) return false;
    }
    return true;
}
/*//another way to do it
void clearSymetric(vector<string> vec, map<string, int>& map) {
    vector<string> vect;
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        if (it->first[0] == it->first[1]) continue;
        string temp = "";
        temp += it->first[1];
        temp += it->first[0];
        if (map.count(temp)) {
            vect.push_back(temp);
        }
    }
    for (int i = 0; i < vect.size(); i++) {
        string temp = "";
        temp += vect[i][1];
        temp += vect[i][0];
        if(map.count(temp))map.erase(vect[i]);
    }
    //map.erase(temp);
}
*/
void clearSymetric(vector<string> vec, map<string, int>& map) {//clearsymetric
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        if (it->first[0] == it->first[1]) continue;
        string temp = "";
        temp += it->first[1];
        temp += it->first[0];
        //cout << temp;
        if (map.count(temp)) {
            map.erase(temp);
            clearSymetric(vec, map);
            return;
        }
    }
}

bool isAntiSymetric(vector<string> vec, map<string, int>& map) {//checks anti symetric
    for (auto elem : map) {
        if (elem.first[1] == elem.first[0]) continue;
        string temp = "";
        temp += elem.first[1];
        temp += elem.first[0];
        if (map.count(temp)) return false;
    }
    return true;
}

bool isTransative(vector<string> vec, map<string, int>& map) {//checks transative
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int z = 0; z < size; z++){
                if (i == z || i == j || j == z) continue;
                string t1 = "";
                string t2 = "";
                string t3 = "";

                t1 += vec[i];
                t1 += vec[j];

                t2 += vec[j];
                t2 += vec[z];

                t3 += vec[i];
                t3 += vec[z];

                if (map.count(t1) && map.count(t2) && !map.count(t3)) return false;

            }
        }
    }

    return true;
}


void doItTransative(vector<string> vec, map<string, int>& map) {//do the set transative
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int z = 0; z < size; z++) {
                if (i == z || i == j || j == z) continue;
                string t1 = "";
                string t2 = "";
                string t3 = "";

                t1 += vec[i];
                t1 += vec[j];

                t2 += vec[j];
                t2 += vec[z];

                t3 += vec[i];
                t3 += vec[z];

                if (map.count(t1) && map.count(t2) && !map.count(t3)) map[t3] = 1;

            }
        }
    }
}

void clearTransative(vector<string> vec, map<string, int>& map) {//remove bridge for clear transative
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int z = 0; z < size; z++) {
                if (i == z || i == j || j == z) continue;
                string t1 = "";
                string t2 = "";
                string t3 = "";

                t1 += vec[i];
                t1 += vec[j];

                t2 += vec[j];
                t2 += vec[z];

                t3 += vec[i];
                t3 += vec[z];

                if (map.count(t1) && map.count(t2) && map.count(t3)) {
                    map.erase(t3);
                    clearTransative(vec, map);
                    return;
                }

            }
        }
    }

}



void checker(vector<string> vec, map<string, int>& map) {//gloabal check function
    //cout << " reflex :" << isReflexive(vec, map) << "symetric:" << isSymetric(vec, map) << " antisym:" << isAntiSymetric(vec, map) << "transative:" << isTransative(vec, map) << endl;
    if (!isReflexive(vec, map)) {
        doItReflexive(vec, map);
    }
    
    doItTransative(vec, map);
    clearSymetric(vec, map);

    //cout << " reflex :" << isReflexive(vec, map) << "symetric:" << isSymetric(vec, map) << " antisym:" << isAntiSymetric(vec, map) << "transative:" << isTransative(vec, map) << endl;
    myfile << vec.size() << endl;
    myfile << "Poset: ";
    for (auto it = map.cbegin(); it != map.cend(); ++it){
        if (++it != map.cend()) {
            --it;
            myfile << "(" << it->first[0] << ", " << it->first[1] << "), ";
        }
            
        else {
            --it;
            myfile << "(" << it->first[0] << ", " << it->first[1] << ") \n";
        }
            
    }
    clearReflexive(vec, map);
    clearTransative(vec, map);
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        myfile <<  it->first[0] << ", " << it->first[1] << "\n";
    }


}
bool isHave(vector<string> vec, char a) {//for exception
    string temp = "";
    temp += a;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == temp)return true;
    }
    return false;
}

void read() {// reading file
    string line;
    ifstream myfile("input.txt");
    if (myfile.is_open()) {
        int s = 1;
        int count = 0;
        int members = 0;
        vector<string> vec;
        map<string, int> map;
        while (getline(myfile, line)) {
            //cout << line << " " << count << " " << members << endl;
            if (count == 0) {
                if (s != 1)checker(vec, map);
                s = 0;
                vec.clear();
                map.clear();

                int i = 0;
                while (i < line.length()) {
                    count *= 10;
                    count += line[i++] - '0';
                }
                members = 1;
            }
            else if (members == 1) {
                members = 0;
                int j = 0;
                int temp = 0;
                for (int i = 0; i < line.length(); i++) {
                    if (line[i] == ',') {
                        vec.push_back(line.substr(j, temp));
                        j = i + 1;
                        temp = 0;
                    }
                    else temp++;
                }
                vec.push_back(line.substr(j, temp));
            }

            else {
                count--;
                string temp = "";
                temp += line[0];
                temp += line[2];
                if(isHave(vec,line[0])  && isHave(vec, line[2]))
                    map[temp] = 1;
            }


        }
        if(vec.size()>0)checker(vec, map);
        myfile.close();
    }

    else cout << "404 FILE NOT FOUND";
}
int main() {
    read();
    cout << "Gizem sungu is best <3<3";
    return 0;
}