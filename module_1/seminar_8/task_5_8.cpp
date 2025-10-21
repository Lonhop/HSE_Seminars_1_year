#include<iostream>
#include<vector>

template < class T , class F >
void map2d ( std::vector<std::vector<T>>& a ,F f) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            a[i][j] = f(a[i][j]);
        }
    }
}

template < class T , class Pred>
std::size_t count_if2d ( const std::vector<std::vector<T>>& a , Pred p ) {
    size_t cnt = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[i].size(); ++j) {
            if (p(a[i][j])) ++cnt;
        }
    }
    return cnt;
}

template < class T , class U , class Op >
U reduce2d ( const std :: vector < std :: vector <T > >& a , U init , Op op ) {
    U result = init;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            result = op(a[i][j], result);
        }
    }
    return result;
}

void print(const std::vector<std::vector<int>> a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> mat(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> mat[i][j];
        }
    }
    int q;
    std::cin >> q;
    while (q--) {
        std::string cm,temp;
        std::cin >> cm >> temp;
        int nm;

        if (cm == "MAP") {
            std::cin >> nm;
            if (temp == "ADD")
                map2d(mat, [nm](int x){return x + nm;});
            else map2d(mat, [nm](int x){return x * nm;});
        }
        else if (cm == "FILTER") {
            std::cin >> nm;
            if (temp == "GT") count_if2d(mat,[nm](int x){return x > nm;});
            else if (temp == "GE") count_if2d(mat,[nm](int x){return x >= nm;});
            else count_if2d(mat,[nm](int x){return x == nm;});
        }
        else {
            if (temp == "SUM") reduce2d(mat, 0, [nm](int x,int y){return y + x;});
            else if (temp == "MAX") reduce2d(mat, mat[0][0], [nm](int x, int y){return x > y ? x : y;});
            else reduce2d(mat, mat[0][0], [nm](int x, int y){return x > y ? y : x;});
        }
        print(mat);
    }
    return 0;
}