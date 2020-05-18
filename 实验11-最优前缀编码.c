#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//树
typedef struct
{
	int weight;    
	int parent, lChild, rChild; 
}HTNode, *HuffmanTree;

//表
typedef struct
{
	char** code;    
	int n;          
}HuffmanCode;

// 选择权值最小的两颗树
void SelectMin(HuffmanTree hT, int n, int &s1, int &s2)；
// 构造有n个权值的哈夫曼树
void CreateHufmanTree(HuffmanTree &hT)；
// 哈夫曼编码
void CreateHuffmanCode(HuffmanTree hT, HuffmanCode &hC);
//输出
void PrintHuffmanCode(HuffmanCode &hC);
//销毁
void DestoryHuffmanTree(HuffmanTree &hT);
void DestoryHuffmanCode(HuffmanCode &hC);

int main()
{
	HuffmanTree hT;
	CreateHufmanTree(hT);

	HuffmanCode hC;
	CreateHuffmanCode(hT, hC);
	PrintHuffmanCode(hC);

	DestoryHuffmanTree(hT);
	DestoryHuffmanCode(hC);
	return 0;
}

void CreateHufmanTree(HuffmanTree &hT)
{
	int n, m;
	cout << "一共有几个点？";
	cin >> n;
	m = 2 * n - 1;//总节点数

	hT = new HTNode[m + 1];   

	//初始化
	for (int i = 1; i <= m; ++i) {
		hT[i].parent = hT[i].lChild = hT[i].rChild = 0;
	}

	cout << "各点权值：" << endl;
	for (int i = 1; i <= n; ++i) {
		cin >> hT[i].weight;    // 输入
	}
	hT[0].weight = m;    // 用0保存节点的数量

	for (int i = n + 1; i <= m; ++i) {
		int s1, s2;
		SelectMin(hT, i, s1, s2);

		hT[s1].parent = hT[s2].parent = i;
		hT[i].lChild = s1; hT[i].rChild = s2;    
		hT[i].weight = hT[s1].weight + hT[s2].weight;    
	}
}

void CreateHuffmanCode(HuffmanTree hT, HuffmanCode &hC)
{
	hC.n = (hT[0].weight + 1) / 2;
	hC.code = new char*[hC.n + 1];    

	char *cd = new char[hC.n];  

	for (int i = 1; i <= hC.n; ++i) {

		// 从叶子节点向上回溯
		int len = 0, child = i, parent = hT[i].parent;
		while (parent != 0) {
			if (hT[parent].lChild == child) {
				cd[len++] = '0';
			}
			else {
				cd[len++] = '1';
			}
			child = parent;
			parent = hT[parent].parent;
		}
		cd[len] = 0;

		reverse(cd, cd + len);    // 将序列翻转
		hC.code[i] = new char[len];
		strcpy(hC.code[i], cd);
	}
	delete[] cd;
}

void SelectMin(HuffmanTree hT, int n, int &s1, int &s2)
{
	s1 = s2 = 0;

	int i;
	for (i = 1; i < n; ++i) {
		if (0 == hT[i].parent) {
			if (0 == s1) {
				s1 = i;
			}
			else {
				s2 = i;
				break;
			}
		}
	}
	if (hT[s1].weight > hT[s2].weight) {
		int t = s1;
		s1 = s2;
		s2 = t;
	}

	for (i += 1; i < n; ++i) {
		if (0 == hT[i].parent) {
			if (hT[i].weight < hT[s1].weight) {
				s2 = s1;
				s1 = i;
			}
			else if (hT[i].weight < hT[s2].weight) {
				s2 = i;
			}
		}
	}
}

void PrintHuffmanCode(HuffmanCode &hC)
{
	for (int i = 1; i <= hC.n; ++i) {
		cout << i << ":" << hC.code[i] << endl;
	}
}

void DestoryHuffmanTree(HuffmanTree &hT)
{
	delete[] hT;
	hT = NULL;
}

void DestoryHuffmanCode(HuffmanCode &hC)
{
	for (int i = 1; i <= hC.n; ++i) {
		delete[] hC.code[i];
	}
	delete[] hC.code;
	hC.code = NULL;
}