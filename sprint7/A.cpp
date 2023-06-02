// proof sketch (see the problem description for the details):
//
// aim: for a function f [a, b] -> R choose set of sequential pairs (b_i, s_i) 
// in the domain such that \sum_i f(b_i) - f(s_i) is maximal
//
// solution: given that A_i are intervals of function ascending (b_i, s_i) are 
// their bounds
//
// proof: the domain is decomposed in E-s - intervals between local maxima.We 
// want to dispose points in them. (each E = A \cup D - a union if an ascending 
// and a descending interval)
// - if we dispose points at one E - the optimal is the bounds of A.
// - if we dispose points at arbitraty E_i, E_j the optimal is bounds of A_i and
// A_j.
// - proceed by induction.
//

#include <iostream>
#include <vector>

int max_profit(const std::vector<int> &v);

class FSM {
    typedef enum {NO_SH, SH} State; // have no share / have share
    const std::vector<int> &tape;
    State state = NO_SH;
    int profit = 0;
    int cur, next;

public:
    FSM(const std::vector<int> &buf) : tape(buf) {};
    int operator() ();

private:
    void buy (int share) { profit-=share; };
    void sell(int share) { profit+=share; };

};

int main() {
    int n;
    std::cin >> n;

    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    FSM fsm(v);
    std::cout << fsm() << std::endl;
    return 0;
}



int FSM::operator() () {
        // normal go
        for (int i = 0; i < (tape.size()-1); ++i) {
            cur = tape[i]; next = tape[i+1];

            switch (state) {
                case NO_SH:
                    if (next > cur) {
                        buy(cur);
                        state = SH;
                    }
                    break;
                case SH:
                    if (next < cur) {
                        sell(cur);
                        state = NO_SH;
                    }
                    break;
            }
        }
        // final step
        cur = *tape.rbegin();
        if (state == SH) {
            sell(cur);
        }

        return profit;
    }
