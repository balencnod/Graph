#include <iostream>

using namespace std;

struct e {
	int data;
	e* prt;
};

class Graph {
private:
	e graph[30];
	e* head;
	bool done[30];
	int wait[30];
	int i;
	int temp;
	int tmp;
public:
	Graph() {
		for (int i = 0; i < 30; i++) {
			graph[i].data = 0;
			graph[i].prt = nullptr;
			head = nullptr;
		}
		for (int i = 0; i < 30; i++) {
			done[i] = false;
		}
		for (int i = 0; i < 30; i++) {
			wait[i] = -1;
		}
	}

	//初始化表
	void initGraph() {
		cout << "请输入边的条数:";
		int num = 0;
		cin >> num;
		bool table[30][30];
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				table[i][j] = false;
			}
		}
		int n1 = 0; int n2 = 0;
		for (int i = 0; i < num; i++) {
			cout << "请输入边的起始节点:";
			cin >> n1;
			cout << "请输入边的终止节点:";
			cin >> n2;
			table[n1][n2] = true;
			table[n2][n1] = true;
		}
		for (int i = 0; i < 30; i++) {
			e* p = &graph[i];
			p->data = i;
			p->prt = nullptr;
			e* q = nullptr;
			for (int j = 0; j < 30; j++) {
				if (table[i][j]) {
					q = new e;
					q->data = j;
					q->prt = nullptr;
					p->prt = q;
					p = q;
					q = nullptr;
				}
			}
		}
	}

	//更新判断数组
	void updateBool() {
		for (int i = 0; i < 30; i++) {
			done[i] = false;
		}
		for (int i = 0; i < 30; i++) {
			wait[i] = -1;
		}
		tmp = -1;
		i = 0;
		temp = 0;
	}

	//深度优先遍历输出节点
	void DepthFstTrvsN(int anchor) {
		done[anchor] = true;
		e* next = &graph[anchor];
		cout << graph[anchor].data << "\t";
		while (next->prt != nullptr) {
			next = next->prt;
			if (!done[next->data]) {
				DepthFstTrvsN(next->data);
			}
		}
	}

	//深度优先遍历输出边
	void DepthFstTrvsS(int anchor) {
		done[anchor] = true;
		e* next = &graph[anchor];
		if (tmp != -1) {
			cout << "(" << tmp << "," << graph[anchor].data << ")\t";
		}
		tmp = graph[anchor].data;
		while (next->prt != nullptr) {
			next = next->prt;
			if (!done[next->data]) {
				DepthFstTrvsS(next->data);
			}
		}
	}

	//广度优先遍历输出节点
	void BreathFstTrvsN(int anchor) {
		e* p = &graph[anchor];
		if (!done[anchor]) {
			cout << p->data << "\t";
			for (; p->prt != nullptr;) {
				p = p->prt;
				if (!done[p->data]) {
					wait[i] = p->data;
					i++;
				}
			}
			for (; wait[temp] != -1; temp++) {
				if (!done[wait[temp]]) {
					done[anchor] = true;
					BreathFstTrvsN(wait[temp]);
				}
			}

		}
	}

	//广度优先遍历输出边
	void BreathFstTrvsS(int anchor) {
		e* p = &graph[anchor];
		if (!done[anchor]) {
			if (tmp != -1) {
				cout << "(" << tmp << "," << graph[anchor].data << ")\t";
			}
			tmp = graph[anchor].data;
			for (; p->prt != nullptr;) {
				p = p->prt;
				if (!done[p->data]) {
					wait[i] = p->data;
					i++;
				}
			}
			for (; wait[temp] != -1; temp++) {
				if (!done[wait[temp]]) {
					done[anchor] = true;
					BreathFstTrvsS(wait[temp]);
				}
			}

		}
	}

};



int main() {
	int tmp;
	Graph g = Graph();
	g.initGraph();

	cout << "深度优先遍历开始的节点：";
	cin >> tmp;
	g.DepthFstTrvsN(tmp);
	g.updateBool();
	cout << endl;
	g.DepthFstTrvsS(tmp);
	g.updateBool();
	cout << endl;

	cout << "广度优先遍历开始的节点：";
	cin >> tmp;
	g.BreathFstTrvsN(tmp);
	g.updateBool();
	cout << endl;
	g.BreathFstTrvsS(tmp);
	g.updateBool();
	cout << endl;

	while (true);
	return 0;
}
