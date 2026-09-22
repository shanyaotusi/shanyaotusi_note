/**
 * 文件压缩，接收第一个参数是文件名，第二个参数是压缩后目标文件名，默认同名，后缀 .huf
 * 
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>

#define MAX_SYMBOLS 256

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

// 符号频率表/次数表 按符号从小到大排列
typedef std::vector<int> weightList;

// 二叉树节点
struct bTreeNode {
	uint8_t symbol;
	int weight;
	bTreeNode *lchild, *rchild;
};
typedef std::vector<bTreeNode*> huffmanTree;


// template<typename char8>
// uint8_t toUint8_t(char8 char_) {
// 	return char_;
// }

// 根据最优二叉树/哈夫曼树，生成编码表
class HuffmaCode {

public:

	HuffmaCode() {
		codeTable.resize(MAX_SYMBOLS);
		hfmTree.reserve(MAX_SYMBOLS);
	}

	~HuffmaCode() {
		if (!hfmTree.empty()) {
			freeFromNode(hfmTree.front());
		}
	}

	// 使用已经统计好的符号和频率(次数)表生成最优二叉树
	bool generateTree(weightList wl) {
		for (int i = 0; i < MAX_SYMBOLS; ++i) {
			bTreeNode* node = new bTreeNode{(uint8_t)i, wl.at(i), nullptr, nullptr};
			hfmTree.push_back(node);
		}

		// 建堆
		auto cmp = [](bTreeNode* prev, bTreeNode* nex) {
			return prev->weight > nex->weight;
		};
		std::make_heap(hfmTree.begin(), hfmTree.end(), cmp);

		while (hfmTree.size() > 1) {
			// 取出最小的两个节点
			std::pop_heap(hfmTree.begin(), hfmTree.end(), cmp);
			auto tmp1 = *std::prev(hfmTree.end());
			hfmTree.pop_back();

			std::pop_heap(hfmTree.begin(), hfmTree.end(), cmp);
			auto tmp2 = *std::prev(hfmTree.end());
			hfmTree.pop_back();
			int totalWeight = tmp1->weight + tmp2->weight;
			// 加入新结点
			bTreeNode* node = new bTreeNode{0, totalWeight, tmp1, tmp2};
			hfmTree.push_back(node);
			std::push_heap(hfmTree.begin(), hfmTree.end(), cmp);
		}
		return true;
	}

	// 遍历树生成编码表
	void generateCodeTable() {
		if (hfmTree.empty()) return;
		bTreeNode* ptr = hfmTree.front();
		std::string code;
		travTree(ptr, code);
	};

	void travTree(bTreeNode* ptr, std::string& code) {
		if (!ptr) return;
		// 叶子节点：输出最终编码
		if(!ptr->lchild && !ptr->rchild) {
			codeTable[ptr->symbol] = code;
			return;
		}
		code.push_back('0');
		travTree(ptr->lchild, code);
		code.pop_back();

		code.push_back('1');
		travTree(ptr->rchild, code);
		code.pop_back();
	}

	void printCodeTable() {
		for (size_t i = 0; i < codeTable.size(); ++i) {
			if (!codeTable[i].empty()) {
				std::cout << "symbol=" << i << " code=" << codeTable[i] << std::endl;
			}
		}
	}

protected:

	std::vector<std::string> codeTable;

private:

	huffmanTree hfmTree;

	void freeFromNode(bTreeNode* root) {
		if (!root) return;
		freeFromNode(root->lchild);
		freeFromNode(root->rchild);
		delete root;
	}
};


class Compress: public HuffmaCode {

public:

	Compress() {
		wl.clear();
		wl.resize(256);
	};
	~Compress() = default;

	bool compressFile(const std::string& srcFile, const std::string& destFile) {
		if (!std::filesystem::exists(srcFile)) {
			std::cout << "file not exists: " << srcFile << std::endl;
			return false;
		}

		std::cout << "compress file: " << srcFile << " to " << destFile << std::endl;

		generateWeightList(srcFile);
		printWeightList();

		generateTree(wl);
		generateCodeTable();

		printCodeTable();
		// output compressed file

		return true;
	}

	void printWeightList() {
		for (int i = 0; i < 256; ++i) {
			std::cout << wl[i] << std::endl;
		}
	}

private:

	weightList wl;

	void generateWeightList(const std::string& srcFile) {
		std::ifstream ifs(srcFile, std::ios::binary);
		int ch = 0;
		while ((ch = ifs.get()) != EOF) { // 修正：文件结束判断
			++wl.at(static_cast<uint8_t>(ch));
		}
		// 修正：取消排序，保持符号顺序
		// std::sort(wl.begin(), wl.end());
	}

};

int main(int argc, char* argv[]) {
		std::cout << "argc=" << argc << std::endl;
		if (argc != 3) {
			std::cerr << "Invalid number of arguments" << std::endl;
			return 1;	// 修正：文件参数错误返回
		}
	try {
		Compress compress;
		compress.compressFile(argv[1], argv[2]);
	}
	catch (const std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}

	return 0;
}

