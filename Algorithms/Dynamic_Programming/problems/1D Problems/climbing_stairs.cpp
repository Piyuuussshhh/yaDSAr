#include "../../headers/dp.h"

// ! QUESTION.
/*
    Count the number of ways to reach nth stair.
    You can climb 1 or 2 steps at a time.
    Return the total number of distinct ways in which you can climb from the 0th step to nth step.
*/

// ! INTUITION
/*
    -> Try to represent in terms of index.
    -> Do all possible sutff on that index.
    -> If count all possible ways, sum everything.
    -> If find min soln, find min of everything.


    Here, take the steps as indices in an array.
    If nth step is 0, you are already there, so there's only 1 way.
    If nth step is 1, there's only 1 way.

    * The number of ways you can reach the nth step depends on the number of ways you can reach
    * the (n-1)th step and the (n-2)th step, because you can take either 1 or 2 steps.

    eg. Since 0th step and 1st step can be reached in a single way,
        you can reach the 2nd step is either by climbing 1 step twice,
                                                        or
                                             by taking 2 steps at once.
        Therefore, you can reach it in 2 ways.

        You can reach the third step by either 1+1+1 or 1+2 or 2+1, therefore 3 ways (number of ways to reach 2nd step {2} + number of ways to reach 1st step {1}).
        Similarly, no. of ways to reach 4th step: 1+1+1+1 or 1+1+2 or 1+2+1 or 2+1+1 or 2+2 => 5 ways (no. of ways to reach 3rd step {3} + no. of ways to reach 2nd step {2}).

    * This follows the Fibonacci sequence, given allowable step size is 1 or 2.
*/

int total_possible_ways_to_reach_nth_step(int n) {
    std::vector<int> dp(n + 1, INT_MIN);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main() {

    return 0;
}