#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MEASURE = 5;
const int DAY = 7;
const int WEEK = 3;

const char DEGREE = char(248);

void standard_length(string& str) {
    while(str.size()<16){
        str += " ";
    }
    str += '|';
}

void print(vector<double> v, const string& range) {

    cout << "\t\t^" <<endl;
    cout << range << "\t\t|" <<endl;
    for(size_t i = 0; i < v.size(); ++i) {
        if(v[i]>60)
            throw runtime_error("Achtung durchschnittliche Temperatur ist zu gross!");
        string tickmark = to_string(i+1) + ". " + range;
        standard_length(tickmark);
        cout << tickmark;
        for (int j =0;j<static_cast<int>(v[i]);++j) {
            cout << '*';
            if(j==static_cast<int>(v[i])-1)
                cout  <<  "   " << v[i] << DEGREE << 'C' << endl;
        }
    }
    cout << "\t\t-------------------------------------------------------------->" << endl;
    cout << "\t\t     ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^" << endl;
    cout << "\t\t     5    10   15   20   25   30   35   40   45   50   55   60\t"<< DEGREE << 'C' << endl;
}

void average(const double temp[5][7][3]) {
    vector<double> daily_t, weekly_t;
    int count {0};
    double d_avg {0}, w_avg {0},sum{0};

    for(int w = 0; w < WEEK; w++) {

        for(int d = 0; d < DAY; d++) {
            for(int m = 0; m < MEASURE; m++) {

                sum += temp[m][d][w];

                ++count;
                if(count%5==0) {
                    d_avg = sum/5.;
                    daily_t.push_back(d_avg);
                    sum=0;
                }
            }
        }

    }
    cout << "Die Taegliche durchschnittliche Temperatur verteilt sich wie folgt:" << endl;
    print(daily_t, "Tag");


    for(size_t i = 1; i <= daily_t.size(); ++i) {
        sum += daily_t[i-1];
        if(i%7==0) {
            w_avg = sum/35.;
            weekly_t.push_back(w_avg*5);
            sum=0;
        }
    }

    cout << "Die woechentliche durchschnittliche Temperatur verteilt sich wie folgt:" << endl;
    print(weekly_t, "Woche");

    for(double i : weekly_t) {
        sum += i*35;
    }

    double total_avg{sum/(5*7*3.)};
    cout << "Die totale durchschnittliche Temperature ist: " << total_avg << " " <<DEGREE << 'C' << endl;


}

int main() {
    /*
     * Dies habe habe ich für testing initialisiert
    double temperature[MEASURE][DAY][WEEK]=
    {
        {{3.5, 8, 15}, {2, 9, 16}, {3, 10, 17}, {4, 11, 18}, {5, 12, 19}, {6, 13, 20}, {7, 14, 22}},
        {{3.5, 8, 15}, {2, 9, 16}, {3, 10, 17}, {4, 11, 18}, {5, 12, 19}, {6, 13, 20}, {7, 14, 22}},
        {{3.5, 8, 15}, {2, 9, 16}, {3, 10, 17}, {4, 11, 18}, {5, 12, 19}, {6, 13, 20}, {7, 14, 22}},
        {{3.5, 8, 15}, {2, 9, 16}, {3, 10, 17}, {4, 11, 18}, {5, 12, 19}, {6, 13, 20}, {7, 14, 22}},
        {{3.5, 8, 15}, {2, 9, 16}, {3, 10, 17}, {4, 11, 18}, {5, 12, 19}, {6, 13, 20}, {7, 14, 22}}
    };
    */

    double temperature[MEASURE][DAY][WEEK]=
            {
                    {{8.7, 8.5, 18.9}, {6, 12.7, 15}, {7.3, 15.6, 17.8}, {10.2, 16.8, 20}, {10.5, 13, 20}, {12.3, 13, 20.5}, {8, 5.6, 6}},
                    {{15.5, 10.2, 20}, {8.7, 16.8, 26}, {8.9, 14.5, 15.7}, {12.6, 19.5, 25.6}, {13.8, 12, 25.8}, {14.6, 16.4, 19.7}, {15.7, 14.3, 9}},
                    {{17.6, 12.6, 25.3}, {10, 26.4, 30}, {12.5, 13.2, 26.8}, {15.8, 26.7, 30.9}, {20.5, 11.5, 35}, {23.5, 15.8, 30.6}, {26.4, 14.6, 13.5}},
                    {{14.8, 13.8, 33.4}, {13.6, 23.5, 35}, {14.8, 19.6, 16.8}, {16.9, 23, 34.6}, {19.6, 9.8, 38}, {22.4, 19.6, 30.7}, {23.5, 14.8, 16.8}},
                    {{9.9, 11.5, 29}, {8.7, 18.6, 30}, {10.4, 20.6, 17.9}, {13.5, 23.8, 32.5}, {15.4, 10.4, 31.5}, {16, 17.4, 29.6}, {25.9, 14.9, 15}}
            };

    average(temperature);

    return 0;
}
