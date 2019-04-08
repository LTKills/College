#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int mat[8][8];


bool check(string ans, int i) {
    char a, b;
//    cout << ans << ans.length() << endl;
    for(int j = i+1; j < (int) ans.length(); j++) {
        a = ans[i];
        b = ans[j];
  //      printf("a = %c    b = %c\n", a, b);
    //    printf("mat[%d][%d] = %d\n", a - 48, b - 48, mat[a - 48][b - 48]);
        if((mat[a - 48][b - 48] > 0 and mat[a - 48][b - 48] < (j-i)) or
                (mat[a - 48][b - 48] < 0 and (-1)*mat[a - 48][b - 48] > (j-i)))
            return false;
    }
    return true;
}


int checkString(string ans) {

    for(int i = 0; i < (int) ans.length()-1; i++)
        if(!check(ans, i)) return 0;

    return 1;
}


void permutations(int m, int n) {
    string ans = "";
    int res = 0;

    for(int i = 0; i < n; i++)
        ans.append(to_string(i));

    do {
        res += checkString(ans);
    } while(next_permutation(ans.begin(), ans.end()));

    printf("%d\n", res);
}


int main(int argc, char *argv[]) {
    int m = 1, n = 1, a, b, val;

    scanf("%d %d", &n, &m);
    while(m != 0 or n != 0) {

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                mat[i][j] = 0;

        // initialize constraints
        for(int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &val);
            mat[a][b] = val;
            mat[b][a] = val;
        }

        permutations(m, n);
        scanf("%d %d", &n, &m);
    }

    return 0;
}
