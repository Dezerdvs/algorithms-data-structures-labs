#include <iostream>
#include <vector>
#include <string>
#define NOMINMAX
#include <windows.h>

#include <chrono>
#include <fstream>

using namespace std;

template<class keyType>
class PQi {
    int d, N;
    vector<int> pq, qp;
    const vector<keyType> &a;

    void exch(int i, int j) {
        int t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

    void fixUp(int k) {
        while (k > 1 && a[pq[(k + d - 2) / d]] > a[pq[k]]) {
            exch(k, (k + d - 2) / d);
            k = (k + d - 2) / d;
        }
    }

    void fixDown(int k, int N) {
        int j;
        while ((j = d * (k - 1) + 2) <= N) {
            for (int i = j + 1; i < j + d && i <= N; i++)
                if (a[pq[j]] > a[pq[i]]) j = i;
            if (!(a[pq[k]] > a[pq[j]])) break;
            exch(k, j);
            k = j;
        }
    }

public:
    PQi(int N, const vector<keyType> &a, int d = 3) :
            a(a), pq(N + 1, 0), qp(N + 1, 0), N(0), d(d) {}

    int empty() const { return N == 0; }

    void insert(int v) {
        pq[++N] = v;
        qp[v] = N;
        fixUp(N);
    }

    int getmin() {
        exch(1, N);
        fixDown(1, N - 1);
        return pq[N--];
    }

    void lower(int k) {
        fixUp(qp[k]);
    }
};

class EDGE {
    int v_, w_;
    double wt_;
public:
    EDGE(int v__ = -1, int w__ = -1, double wt__ = 0.0) : v_(v__), w_(w__), wt_(wt__) {}

    int v() const {
        return v_;
    }

    int w() const {
        return w_;
    }

    double wt() const {
        return wt_;
    }
};

template<class Edge>
class DenseGRAPH {
    int Vcnt, Ecnt;
    bool digraph;
    vector<vector<Edge *> > adj;

public:
    DenseGRAPH(int V, bool digraph = false) :
            adj(V), Vcnt(V), Ecnt(0), digraph(digraph) {
        for (int i = 0; i < V; i++)
            adj[i].assign(V, 0);
    }

    int V() const {
        return Vcnt;
    }

    int E() const {
        return Ecnt;
    }

    bool directed() const {
        return digraph;
    }

    void insert(Edge *e) {
        int v = e->v(), w = e->w();
        if (adj[v][w] == 0)
            Ecnt++;
        adj[v][w] = e;
        if (!digraph)
            adj[w][v] = e;
    }

    void remove(Edge *e) {
        int v = e->v(), w = e->w();
        if (adj[v][w] != 0)
            Ecnt--;
        adj[v][w] = 0;
        if (!digraph)
            adj[w][v] = 0;
    }

    Edge *edge(int v, int w) const {
        return adj[v][w];
    }

    class adjIterator;

    friend class adjIterator;
};

template<class Edge>
class DenseGRAPH<Edge>::adjIterator {
    const DenseGRAPH<Edge> &G;
    int i, v;
public:
    adjIterator(const DenseGRAPH<Edge> &G, int v) :
            G(G), v(v), i(0) {}

    Edge *beg() {
        i = -1;
        return nxt();
    }

    Edge *nxt() {
        for (i++; i < G.V(); i++)
            if (G.edge(v, i))
                return G.adj[v][i];
        return 0;
    }

    bool end() const {
        return i >= G.V();
    }
};

template<class Graph, class Edge>
class SPT_Deikstra {
    const Graph &G;
    vector<double> wt;
    vector<Edge *> spt;

public:
    SPT_Deikstra(const Graph &G, int start) : G(G), spt(G.V()), wt(G.V(), G.V()) {
        for (int i = 0; i < G.V(); i++)
            spt[i] = NULL;

        PQi<double> pQ(G.V(), wt);
        for (int v = 0; v < G.V(); v++)
            pQ.insert(v);
        wt[start] = 0.0;
        pQ.lower(start);
        while (!pQ.empty()) {
            int v = pQ.getmin(); // wt[v] = 0.0;
            if (v != start && spt[v] == 0)
                return;
            typename Graph::adjIterator A(G, v);
            for (Edge *e = A.beg(); !A.end(); e = A.nxt()) {
                int w = e->w();
                double P = wt[v] + e->wt();
                if (P < wt[w]) {
                    wt[w] = P;
                    pQ.lower(w);
                    spt[w] = e;
                }
            }
        }
    }

    void wt_print(void) {
        for (int i = 0; i < 11; i++)
            cout << "wt " << wt[i] << " ";
        cout << endl;
    }

    Edge *pathR(int v) const { return spt[v]; }

    double dist(int v) const { return wt[v]; }
};

template<class Graph, class Edge>
class allSP_Deikstra {

    const Graph &G;
    vector<SPT_Deikstra<Graph, Edge> *> A;
public:
    allSP_Deikstra(const Graph &G) : G(G), A(G.V()) {
        for (int s = 0; s < G.V(); s++)
            A[s] = new SPT_Deikstra<Graph, Edge>(G, s);
    }

    Edge *pathR(int s, int t) const {
        return A[s]->pathR(t);
    }

    double dist(int s, int t) const {
        return A[s]->dist(t);
    }
};

template<class Graph, class Edge>
class allSP_Floyd {

    const Graph &G;
    vector<vector<Edge *> > p;
    vector<vector<double> > d;
public:
    allSP_Floyd(const Graph &G) : G(G), p(G.V()), d(G.V()) {
        int V = G.V();
        for (int i = 0; i < V; i++) {
            p[i].assign(V, 0);
            d[i].assign(V, V);
        }

        for (int s = 0; s < V; s++)
            for (int t = 0; t < V; t++)
                if (G.edge(s, t)) {
                    p[s][t] = G.edge(s, t);
                    d[s][t] = G.edge(s, t)->wt();
                }

        for (int s = 0; s < V; s++)
            d[s][s] = 0;

        for (int i = 0; i < V; i++)
            for (int s = 0; s < V; s++)
                if (p[s][i])
                    for (int t = 0; t < V; t++)
                        if (s != t)
                            if (d[s][t] > d[s][i] + d[i][t]) {
                                p[s][t] = p[s][i];
                                d[s][t] = d[s][i] + d[i][t];
                            }
    }

    Edge *path(int s, int t) const {
        return p[s][t];
    }

    double dist(int s, int t) const {
        return d[s][t];
    }
};

void time_tests(int var = 1) {
    float numerator = 0.1;
    int start_p = 1000 * numerator;
    int end_p = 20000 * numerator;
    int jump = 1000 * numerator;

    string file = "data" + to_string(var) + ".txt";
    ofstream fin;
    fin.open(file);
    cout << "К-сть вершин \t Час(сек)";
    for (int n = start_p; n <= end_p; n += jump) {
        double res = 0;
        for (int i = 0; i < 5; i++) {
            DenseGRAPH<EDGE> G(n, 1);
            int max_edges = n * (n - 1) / 2;
            int num_edges = rand() % max_edges;
            for (int j = 0; j < num_edges; j++) {
                int v = rand() % n;
                int w = rand() % n;
                double weight = (double) (rand() % 100 + 1);
                G.insert(new EDGE(v, w, weight));
            } //Створюємо граф з псевдовипадковими значеннями

            chrono::time_point start = chrono::high_resolution_clock::now();
            if (var == 1) {
                allSP_Deikstra<DenseGRAPH<EDGE>, EDGE> allsp_D(G);
            } else {
                allSP_Floyd<DenseGRAPH<EDGE>, EDGE> allsp_F(G);
            }
            chrono::time_point done = chrono::high_resolution_clock::now();
            double time = chrono::duration_cast<chrono::duration<double>>(done - start).count();
            time /= 1000;
            //cout << endl << time;
            res += time;
        }
        cout << "\n" << n << "\t" << res / 5;
        fin << "\n" << n << "\t" << res / 5;
    }
    fin.close();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Бажаэте провести заміри часу?(1/0)";
    cout << "\nВаш вибір: ";
    bool test;
    cin >> test;

    if (test == true) {
        cout << "\nДейстра\n";
        time_tests();
        cout << "\nФлойда\n";
        time_tests(2);
        return 0;
    }

    const int N = 5;
    DenseGRAPH<EDGE> D_G(N, 1);
    D_G.insert(new EDGE(0, 1, 0.8));
    D_G.insert(new EDGE(1, 0, 0.8));

    D_G.insert(new EDGE(1, 2, 0.8));
    D_G.insert(new EDGE(2, 1, 0.8));

    D_G.insert(new EDGE(2, 3, 0.55));
    D_G.insert(new EDGE(3, 2, 0.55));

    D_G.insert(new EDGE(0, 3, 0.7));
    D_G.insert(new EDGE(3, 0, 0.7));

    D_G.insert(new EDGE(4, 3, 0.45));
    D_G.insert(new EDGE(3, 4, 0.45));

    D_G.insert(new EDGE(1, 3, 0.65));
    D_G.insert(new EDGE(3, 3, 0.65));//Створюэмо базовий граф

    allSP_Deikstra<DenseGRAPH<EDGE>, EDGE> all_Deikstra(D_G); // Створюємо об'єкт класу алгоритму Дейсктри для всіх пар
    allSP_Floyd<DenseGRAPH<EDGE>, EDGE> allsp_Fl(D_G); // Створюємо об'єкт класу алгоритму Флойда для всіх пар

    cout << "Маршрути за допомогою алгоримту Дейсктри: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << all_Deikstra.dist(j, i) << "\t";
        cout << endl;
    }
    cout << endl;

    cout << "Маршрути за допомогою алгоритму Флойда: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << allsp_Fl.dist(j, i) << "\t";
        cout << endl;
    }
    cout << endl;

    return 0;
}