/**
 * @brief: Extract the most active cookies given the date, based on the iso 8601 timestamp format
 * @author: Zhirui Wang, <zhiruiw@cs.cmu.edu>
 * */

#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include <fstream>

/**
 * @brief Return whether the given iso timestamp is during the give date
 * @param[in] iso_time: str of the time stamp
 * @param[in] data: str
 * @return 1 if the iso_time is during the given date, else 0
 */
int parse_iso(std::string iso_time, std::string date){
    if (iso_time.find(date)==-1){
        return 0;
    }
    return 1;
}

/**
 * @brief load the cookies and their corresponding timestamp from the given csv file, then record the frequencies
 * of every cookie existing during the given date. The frequencies are stored in the input parameters, which is a STL map
 * @param[in] filename: the relative path or the name of the csv file
 * @param[in] cookie_map: the reference of a STL map, which maps the cookie name to its corresponding frequency
 * @param[in] date: str format, the specific date when the cookies are active
 * @return The results will be stored at the reference of the cookie_map parameter
 */
void read_cookie_data(std::string filename, std::map<std::string, int> & cookie_map, std::string date){
    ifstream fp(filename);
    std::string line;
    getline(fp,line);
    while (getline(fp,line)){ // read the csv file line by line
        int punc_idx = line.find(",");
        std::string cookie_name = line.substr(0,punc_idx);
        std::string cookie_iso = line.substr(punc_idx + 1);
        if (cookie_map.find(cookie_name)==cookie_map.end()){
            cookie_map.insert(pair<std::string,int>(cookie_name,0)); // insert if the map did not include this key
        }
        cookie_map[cookie_name]+= parse_iso(cookie_iso,date); //
    }
    return;
}

/**
 * @brief Output the most active cookies, based on the recorded cookie frequencies
 * @param[in] cookie_map: the STL map, mapping the cookie name to its corresponding frequency
 * @return
 */
void output_result(std::map<std::string, int> cookie_map){
    int cur_max = -1;
    vector<std::string> outputs;
    for (auto iter = cookie_map.begin(); iter!= cookie_map.end(); ++iter){
        if (iter->second>cur_max){
            cur_max = iter->second;
            outputs.clear();
            outputs.push_back(iter->first);
        }
        else if (iter->second==cur_max) {
            outputs.push_back(iter->first);
        }
    }
    for (auto iter = outputs.begin();iter!=outputs.end(); ++iter){
        std::cout << iter->data()<< endl;
    }
    return;
}

/**
 * @brief Extract the most active cookies given the date, based on the iso 8601 timestamp format
 * @param[in] argc: the number of the arguments
 * @param[in] argv: the arguments
 * @return 0
 */

int main(int argc, char *argv[]) {

    // sanity check for the argc
    if (argc != 4){
        std::cout << "The number of the args is  " <<argc<<", please check if the input format is correct" << std::endl;
        return 0;
    }

    // sanity check for the third argument
    if (std::string ("-d").compare(argv[2])){
        std::cout << "The third argument is not \"-d\", please check if the input format is correct" << std::endl;
        return 0;
    }

    // sanity check for the csv file
    ifstream f (argv[1]);
    if (!f.good()){
        std::cout<< "The given csv file does not exist, please check if the input format is correct"<<std::endl;
        return 0;
    }


    // read the cookie frequency into the cookie_map
    std::map<std::string, int> cookie_map;
    read_cookie_data(argv[1],cookie_map,argv[3]);

    // output the most active cookies
    output_result(cookie_map);
    return 0;

}
