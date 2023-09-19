/*
Name: Jack Knapp, 302.6
Purpose: Use a Priority Queue Baby!
Description: Determine the finish order of a Mario Kart race!
Input: Racers + Distances from a text file
What to do?:  Keep the order of the racers with a priority queue, then update them and output results
Output: The results of the race, along with any errors and some status updates
*/
#include <iostream>
#include <unordered_map>
#include "priorityQ.h"
#include "priorityQ.cpp"

using namespace std;

int main() {

    //sets some vars
    priorityQ<string,double> race;
    string racer = "";
    int currRacers = 0;
    const double defcon = 50;
    unordered_map<string, bool> racersSeen, racersDone;

    //racer input loop
    while(true) {
        //grab next racer
        getline(cin, racer);

        //break condition
        if (racer == "END") {
            break;
        }

        //string formatting and push to queue
        for (int i=0; i<racer.size(); i++) {
                racer[i] = tolower(racer[i]);
            }
        race.push_back(racer,defcon);
        currRacers++;
    }   

    int laps = 0, place = 0;
    //main race loop vroom vroom baby
    while (true) {

        //reset some vars between laps
        int lapUps = 0;
        racersSeen.clear();

        laps++;
        cout << endl << "Interval " << laps << endl << endl;

        //CHECK FOR RACERS THAT FINISHED: REMOVE AND OUTPUT RESULTS
        while (true) {

            //for (int i =1; i<=race.size; i++) {
            //    cout << race.heapArray[i].key << "\t" << i << "\t" << race.heapArray[i].priority << endl;
            //}
            //cout << endl;
            
            //check for race end
            if (currRacers == 0) {
                break;
            }

            //if race not over, remove finished racers
            double front = race.get_front_priority();
            if (front <= 0) {
                //determine racer finishing
                string name = race.get_front_key();
                place++;
                cout << place << " " << name << endl << endl;

                //remove them
                race.pop_front();
                racersDone[name] = true;
                currRacers--;
                
            }
            else {
                break;
            }
        }

        //check for race end again
        if (currRacers == 0) {
            break;
        }

        //lap loop losers
        while(true) {

            //grab next racer and clean 'em up!
            getline(cin, racer);
            for (int i=0; i<racer.size(); i++) {
                racer[i] = tolower(racer[i]);
            }

            //break condition 1
            if (racer == "done") {
                break;
            }

            //check whether racer has finished yet
            bool valrac = true;
            if (racersDone[racer] == true) {
                cout << "Racer has already finished the race!\n\n";
                valrac = false;
            }

            //if racer still in race
            if (valrac == true) {
                //check whether racer has been seen this lap yet
                if (racersSeen[racer] == false) {
                    racersSeen[racer] = true;
                    lapUps++;

                    //change priority value
                    string gottagofast = "SONIC";
                    getline(cin, gottagofast);
                    double speed = stod(gottagofast);

                    race.decrease_priority(racer,speed);
                    cout << "Updating " << racer << endl;

                    //cout << race.heapArray[0].key << "\t" << "0" << "\t" << race.heapArray[0].priority << endl;
                    //cout << race.heapArray[1].key << "\t" << "1" << "\t" << race.heapArray[1].priority << endl;
                    //cout << race.heapArray[2].key << "\t" << "2" << "\t" << race.heapArray[2].priority << endl;

                    //break condition 2
                    if (currRacers == lapUps) {
                        break;
                    }  

                }

                //if racer seen already do not change priority
                else {
                    cout << "Already updated " << racer << " in this interval!\n\n";
                }  

            }

        }

    }

    //we done bb ezpz
    return 0;
}